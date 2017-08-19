#! /usr/bin/python
import numpy as np
import serial as se
import time as ti
import datetime as dt
import sys

def main():
    ser = se.Serial('/dev/ttyUSB0', 9600)
    ind = 0;
    while True:
        now = dt.datetime.now().strftime("%H%M1AA%S1")
        for n in now[ind:5+ind]:
            ser.write(n)
        ti.sleep(0.5)
        ser.write('d')
        sys.stdout.write("\r{}, {}, {}".format(now,ind,ser.read()))
        sys.stdout.flush()
        ind = (ind+5)%10
        #print now, ser.read()

if __name__ == "__main__":
    main()
