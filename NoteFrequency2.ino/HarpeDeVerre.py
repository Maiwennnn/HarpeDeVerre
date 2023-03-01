# arduino_LED_user.py

import serial
import time
from pynput import keyboard
from threading import Thread


# Define the serial port and baud rate.
# Ensure the 'COM#' corresponds to what was seen in the Windows Device Manager
ser = serial.Serial('COM5', 9600)
clav = False
utilise=False

def on_press(key):
    global clav
    global utilise
    if clav:
        try:
            k = key.char  # single-char keys
        except:
            k = key.name  # other keys
        if k in ['a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$']:  # keys of interest
            # self.keys.append(k)  # store it in global-like variable
            print('Key pressed: ' + k)
            while (utilise):
                pass
            print("envoi")
            ser.write(bytes(k, 'utf8'))
            #ser.close()
        elif k=='x':
            ser.close()
            exit(1)

        nbrbytes=ser.in_waiting
        if(nbrbytes>0 and (not utilise)):
            utilise =True
            note = ser.read(nbrbytes)
            print(note)
            if (note==b'h'):
                clav=False
            utilise=False

time.sleep(2) # wait for the serial connection to initialize

listener = keyboard.Listener(on_press=on_press)
listener.start()
while True:
    nbrbytes=ser.in_waiting
    if(nbrbytes>0 and (not utilise)):
        utilise =True
        note = ser.read(nbrbytes)
        print(note)
        if (note==b'c'):
            clav=True
            print("Clav devient true")
        elif note==b'h':
            clav=False
        utilise=False
        #print(utilise)
    