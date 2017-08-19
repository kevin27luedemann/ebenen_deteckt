#! /usr/bin/python
import numpy as np
import serial as se
import time as ti
import datetime as dt
import sys

def main():
    ser = se.Serial('/dev/ttyUSB0', 9600)
    last = ""
    while True:
        #now = dt.datetime.now().strftime("%H%M1AA%S1")
        now = dt.datetime.now().strftime("%H%M1")
        if now != last:
            for n in now:
                ser.write(n)
            last = now
        else:
            ti.sleep(1)
            ser.write('d')
            sys.stdout.write("\r{}, {}".format(now,ser.read()))
            sys.stdout.flush()
        #print now, ser.read()

if __name__ == "__main__":
    main()
