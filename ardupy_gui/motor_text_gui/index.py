# Hello world example. Doesn't depend on any third party GUI framework.
# Tested with CEF Python v55.3+.

from cefpython3 import cefpython as cef
import platform
import sys
import os
import glob
import time
import serial
from http.server import SimpleHTTPRequestHandler, HTTPServer
from threading import Thread
try:
    from . import echo
    SerialEcho = echo.SerialEcho
except SystemError:
    from echo import SerialEcho
except ImportError:
    from echo import SerialEcho
import serial.tools.list_ports as list_ports

#STEPS_PER_CM = 382.8
#recailbration: 5/7/18
STEPS_PER_CM = 400.249
class External(object):
    KEY_CODES = {
        'SUM': ',s',
        'PROD':',p',
        'MEAN':',m',
        'CLEAR':',c',
        'EMPTY_BUFFSTR':SerialEcho.EMPTY_BUFFSTR
    }
    noop = lambda:None
    def __init__(self,tty='/dev/ttyACM0'):
        self.ser = None
        self.err_callback = None
        self.saved_states = dict()

    def coords_to_steps(self,coord_list):
        return [str(int(float(c)*STEPS_PER_CM)) for c in coord_list]

    def send_coords(self,string,mode=1,use_end=True):
        """Appends '1,' to each set of target_x,target_y coords in string
        then sends it to arduino using self.send
        mode determines movement type:
        1 - absolute x,y target
        3 - relative x,y target
        4 - absolute z target
        5 - relative z target
        """
        mode = str(mode)
        string = self.coords_to_steps(string.replace(',',' ').split())
        string = ' '.join([mode+','+c1+','+c2 for (c1,c2) 
            in zip(string[::2],string[1::2])])

        self.send(string)

    def send_delay(self,string,use_end=True):
        """Formulates a change-delay request from a single delay_ms value,
        then sends it to arduino using self.send
        """
        self.send('2,%s,0'%string,use_end)

    def send(self,string,use_end=True):
        """send a comma-separated string of values to the arduino via serial
        """
        if self.ser is None:
            if len(string) > 1:
                self.raise_serial_err("Not currently connected to an Arduino")
            return
        if string !='n': print(string)
        int_strings = string.replace(',',' ').split()
        try:
            for substr in int_strings:
                self.ser.send_chars(substr,use_end)
        except serial.serialutil.SerialException as e:
            if(len(string) > 1):
                self.raise_serial_err(e)
    
    def echo(self,js_callback):
        try:
            js_callback.Call(self.ser.recieve_chars(),External.noop)
        except AttributeError as e:
            return
        except Exception as e:
            self.raise_serial_err(e)

    def show_saved(self):
        print("My saved stuff:")
        print(self.saved_states)

    def save_state(self,js_key,js_val):
        self.saved_states[js_key] = js_val


    def restore_state(self, key, js_callback):
        js_callback.Call(self.saved_states.get(key,''),External.noop)

    def set_serial_err(self,js_callback):
        self.err_callback = js_callback

    def raise_serial_err(self,msg=''):
        print(msg)
        self.good_to_read = False
        if self.err_callback:
            self.err_callback.Call(str(msg),External.noop)

    def set_serial_port(self,tty):
        try:
            self.ser = SerialEcho(tty)
            self.good_to_read = True
            print("Connected to arduino at %s"%tty)
        except serial.serialutil.SerialException:
            self.raise_serial_err("Couldn't connect to Arduino at %s"%tty)

    def get_tty_options(self,js_callback):
        com_ports = [p.device for p in list_ports.comports()]
        js_callback.Call(com_ports,External.noop)


def main():
    #start a simple http server to host the content for CEF
    server_address = ('127.0.0.1', 8081)
    url= r'http://%s:%d/index.html'%server_address
    print(url)
    httpd = HTTPServer(server_address,SimpleHTTPRequestHandler)
    server_thread = Thread(target = httpd.serve_forever,daemon=True)
    server_thread.start()
    
    
    #set up a CEF browser
    check_versions()
    sys.excepthook = cef.ExceptHook  # To shutdown all CEF processes on error
    cef.Initialize()
    window_info = cef.WindowInfo()
    window_info.SetAsChild(0, [0,0,1024,680])
    browser = cef.CreateBrowserSync(window_title="Ardupy Motor Controller", url=url,
            window_info=window_info)
    frame = browser.GetMainFrame()
    #set up the browser's javascript bindings
    external = External()
    bindings = cef.JavascriptBindings()
    bindings.SetFunction("echo", external.echo)
    bindings.SetObject("external",external)
    bindings.SetProperty("KEY_CODES",External.KEY_CODES)
    browser.SetJavascriptBindings(bindings)
    #enter main loop
    cef.MessageLoop()
    cef.Shutdown()
    sys.exit(0)


def check_versions():
    print("[{prog}] CEF Python {ver}".format(prog=sys.argv[0],ver=cef.__version__))
    print("[{prog}] Python {ver} {arch}".format(prog=sys.argv[0],
          ver=platform.python_version(), arch=platform.architecture()[0]))
    assert cef.__version__ >= "55.3", "CEF Python v55.3+ required to run this"


if __name__ == '__main__':
    main()
