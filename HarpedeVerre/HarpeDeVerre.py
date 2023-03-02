# arduino_LED_user.py

import serial
import time
from pynput import keyboard
from threading import Thread


# Define the serial port and baud rate.
# Ensure the 'COM#' corresponds to what was seen in the Windows Device Manager
ser = serial.Serial('COM4', 9600)
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
        if k in ['a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$','*','q','s','d','f','g','h','j','k','l','m','!']:  # keys of interest
            # self.keys.append(k)  # store it in global-like variable
            note=""
            match k:
                case 'a':
                    note="do 3"
                    
                case 'z':
                    note="do# 3"
                    
                case 'e':
                    note="ré 3"
                    
                case 'r':
                    note="ré# 3"
                    
                case 't':
                    note="mi 3"
                    
                case 'y':
                    note="fa 3"
                    
                case 'u':
                    note="fa# 3"
                    
                case 'i':
                    note="sol 3"
                    
                case 'o':
                    note="sol# 3"
                    
                case 'p':
                    note="la 3"
                    
                case '^':
                    note="la# 3"
                    
                case '$':
                    note="si 3"
                case '*':
                    note="do 2"
                    
                case 'q':
                    note="do# 2"
                    
                case 's':
                    note="ré 2"
                    
                case 'd':
                    note="ré# 2"
                    
                case 'f':
                    note="mi 2"
                    
                case 'g':
                    note="fa 2"
                    
                case 'h':
                    note="fa# 2"
                    
                case 'j':
                    note="sol 2"
                    
                case 'k':
                    note="sol# 2"
                    
                case 'l':
                    note="la 2"
                    
                case 'm':
                    note="la# 2"
                    
                case '!':
                    note="si 2"
                    
                
            print('Key pressed: ' + k+" = "+note)
            while (utilise):
                pass
            ser.write(bytes(k, 'utf8'))
            #ser.close()
        elif k=='x':
            ser.close()
            exit(1)

        nbrbytes=ser.in_waiting
        if(nbrbytes>0 and (not utilise)):
            utilise =True
            note = ser.read(nbrbytes)
            
            if (note==b'h'):
                clav=False
                print("Mode détection de note")
            else :
                print(note)
            utilise=False

time.sleep(2) # wait for the serial connection to initialize

listener = keyboard.Listener(on_press=on_press)
listener.start()
while True:
    nbrbytes=ser.in_waiting
    if(nbrbytes>0 and (not utilise)):
        utilise =True
        note = ser.read(nbrbytes)
        if (note==b'c'):
            clav=True
            print("Mode clavier")
        elif note==b'h':
            clav=False
            print("Mode détection de note")
        else:
            print(note)
        utilise=False
        #print(utilise)
    