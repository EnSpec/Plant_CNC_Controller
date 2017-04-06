import serial

MENU= \
"""
1. Send characters
2. Read characters
3. Quit
"""

def send_chars(ser):
    chars = input("Enter characters:")
    ser.write(chars.encode('ascii'))

def recieve_chars(ser):
    if(ser.in_waiting):
        print(ser.read(ser.in_waiting).decode('ascii'))
    else:
        print("No bytes on buffer")

calls = {'1':send_chars,'2':recieve_chars,'3':(lambda x:None)}
def main(device):
    ser = serial.Serial(device,timeout=3)
    opt = ''
    while(opt != '3'):
        opt = input(MENU)
        calls[opt](ser)
    ser.close()        
if __name__ == '__main__':
    import sys
    main(sys.argv[1])

