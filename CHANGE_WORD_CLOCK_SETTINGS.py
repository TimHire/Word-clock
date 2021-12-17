# May need to run the program a number of times for the port to correctly open
# Port should already be open --> check the bluetooth advanced settings

import serial
import time
import struct
from datetime import datetime


def change_time():
    ser.write(b't')
    now = datetime.now()
    ser.write(struct.pack('>B', int(now.strftime("%y"))))           # Sends an integer <255 as bytes to the serial port
    ser.write(struct.pack('>B', int(now.strftime("%m"))))
    ser.write(struct.pack('>B', int(now.strftime("%d"))))
    ser.write(struct.pack('>B', int(now.strftime("%H"))))
    ser.write(struct.pack('>B', int(now.strftime("%M"))))
    ser.write(struct.pack('>B', int(now.strftime("%S"))))
    time.sleep(0.2)
    ser.write(b'y')         # Records the end of the data transmission

def led_intensity(mode):
    intensity = int(input("Enter the intensity for the LEDs (as white): "))
    if mode == "day":
        ser.write(b'id')
    elif mode == "night":
        ser.write(b'in')        
    ser.write(struct.pack('>B', intensity))
    time.sleep(0.2)
    ser.write(b'y')

def change_colour(random):
    if random == False:
        r, g, b = input("Enter the 3 RGB values (max 255) with spaces between: ").split()
        ser.write(b'ca')
        ser.write(struct.pack('>B', int(r)))
        ser.write(struct.pack('>B', int(g)))
        ser.write(struct.pack('>B', int(b)))
    elif random == True:
        ser.write(b'cb')
    time.sleep(0.2)
    ser.write(b'y')

def night_mode(which_end):
    new_hour, new_min = input("Enter the new {} of night mode in format HOUR MINUTE (22 04): ".format(which_end)).split()
    if which_end == "start":
        ser.write(b'ss')
    elif which_end == "end":
        ser.write(b'se')
    ser.write(struct.pack('>B', int(new_hour)))
    ser.write(struct.pack('>B', int(new_min)))
    time.sleep(0.2)
    ser.write(b'y')




# ----------- Starting connection to the bluetooth port
ser = serial.Serial('COM7', 9600, timeout=1)
if ser.is_open:
    print("The port should now be open")
else:
    try:
        ser.open()
    except Exception as e:
        print("The port is not open --> the code may need to be changed to open the port/n{}".format(e))
    



def main():
    init_comm = input("""
    Type in the following letters to edit word clock settings:
    Change time:               't'
    LED intensity day:         'id'
    LED intensity night:       'in'
    LED colour not random:     'ca'
    LED colour random:         'cb'
    Night mode start:          'ss'
    Night mode end:            'se'
    Reset:                     'r'
    Exit:                      'exit'
    """)

    if init_comm == 't':
        change_time()
    elif init_comm == 'id':
        led_intensity("day")
    elif init_comm == 'in':
        led_intensity("night")
    elif init_comm == 'ca':
        change_colour(False)
    elif init_comm == 'cb':
        change_colour(True)
    elif init_comm == 'ss':
        night_mode("start")
    elif init_comm == 'se':
        night_mode("end")
    elif init_comm == 'r':
        ser.write(b'y')
    elif init_comm == 'exit':
        quit()
    else:
        print("Not a valid input\n\n")
        main()


    # -------- Checking if there is anything to read from the blutooth buffer
    if ser.in_waiting > 0:
        output = str(ser.read(1))                # Reads 1 byte of data from the bluetooth serial
        if output == "b'f'":
            print("The Word Clock settings have been updated")
        else:
            print("Something else has been received from the bluetooth module: {}".format(output))
    main()

#ser.close()                            # Not opening the port as it was already open

main()                  # Allows for looping of the function
