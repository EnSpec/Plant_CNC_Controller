# Hello world example. Doesn't depend on any third party GUI framework.
# Tested with CEF Python v55.3+.

from cefpython3 import cefpython as cef
import platform
import sys
import os

class External(object):
    def test_function(self):
        print("Hello World!");

def main():
    url= 'file://%s/index.html'%os.getcwd()
    print(url)
    check_versions()
    sys.excepthook = cef.ExceptHook  # To shutdown all CEF processes on error

    
    cef.Initialize()
    #set up a browser
    browser = cef.CreateBrowserSync(window_title="Hello World!", url=url)
    frame = browser.GetMainFrame()
    #set up the browser's javascript bindings
    external = External()
    bindings = cef.JavascriptBindings()
    bindings.SetFunction("test_function", external.test_function)
    bindings.SetObject("external",external)
    browser.SetJavascriptBindings(bindings)
    cef.MessageLoop()
    cef.Shutdown()


def check_versions():
    print("[hello_world.py] CEF Python {ver}".format(ver=cef.__version__))
    print("[hello_world.py] Python {ver} {arch}".format(
          ver=platform.python_version(), arch=platform.architecture()[0]))
    assert cef.__version__ >= "55.3", "CEF Python v55.3+ required to run this"


if __name__ == '__main__':
    main()
