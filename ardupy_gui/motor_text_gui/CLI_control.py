import echo

MENU= \
"""
1. Move X and Y Axes
2. Move Z Axis
3. Quit
"""


def main(device):
    ser = echo.SerialEcho(device)
    opt = ''
    while(opt != '3'):
        opt = input(MENU)
        if(opt == '1'):
            x,y = input("Enter X<Space>Y (eg: 400 500)").split()

            ser.send_chars("1")
            ser.send_chars(x)
            ser.send_chars(y)
        elif(opt == '2'):
            z = input("Enter Z (eg: 400)")
            ser.send_chars("4")
            ser.send_chars(z)
            ser.send_chars(z)


    ser.close()        
if __name__ == '__main__':
    import sys
    main('/dev/ttyACM0')

