import time
import os
try:
    from . import index
    Interface = index.External
except SystemError:
    from index import External as Interface
except ImportError:
    from index import External as Interface



controller = Interface()
controller.set_serial_port('/dev/ttyACM0')
fname = os.path.join(os.path.expanduser("~"),".ardupy","sched.csv")
with open(fname,"r") as f:
    cmds = f.readlines()
    z = cmds[0].replace('\n','')
    controller.send_coords(z+',0',4)
    spd = cmds[1].replace('\n','')
    controller.send_coords(spd+',0',6)
    for cmd in cmds[2:]:
        cmd = cmd.replace('\n','')
        print(cmd)
        controller.send_coords(cmd)
        time.sleep(0.5)
