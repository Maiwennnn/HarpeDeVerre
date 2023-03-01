# arduino_LED_user.py

import serial
import time
from pynput import keyboard
from threading import Thread

# Define the serial port and baud rate.
# Ensure the 'COM#' corresponds to what was seen in the Windows Device Manager
ser = serial.Serial('COM5', 9600)

def on_press(key):
    try:
        k = key.char  # single-char keys
    except:
        k = key.name  # other keys
    if k in ['a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$']:  # keys of interest
        # self.keys.append(k)  # store it in global-like variable
        print('Key pressed: ' + k)
        ser.write(bytes(k, 'utf8'))
        #ser.close()
    elif k=='x':
        ser.close()
        exit(1)

    nbrbytes=ser.in_waiting
    if(nbrbytes>0):
        note = ser.read(nbrbytes)
        print(note)




time.sleep(2) # wait for the serial connection to initialize


listener = keyboard.Listener(on_press=on_press)
listener.start()
listener.join()
