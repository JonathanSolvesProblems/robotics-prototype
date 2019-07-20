#!/usr/bin/env python3

import serial
import os.path
import time
from datetime import datetime

# takes values 0,1,2,3
def switch_channel(channel):
    s0 = 0
    s1 = 0

    if channel > 3 or channel < 0:
        return

    if channel == 0:
        s0 = 1
        s1 = 1
    elif channel == 1:
        s0 = 0
        s1 = 1
    elif channel == 2:
        s0 = 1
        s1 = 0
    elif channel == 3:
        s0 = 0
        s1 = 0

    gpio_dir = '/sys/class/gpio'

    with open(gpio_dir + '/gpio18/value', 'w') as f:
        f.write(str(s0))

    with open(gpio_dir + '/gpio21/value', 'w') as f:
        f.write(str(s1))



home = os.path.expanduser('~')
test_log = home + '/llc-test.log'

if not os.path.isfile(test_log):
    print('Creating log file: ' + test_log + '\n')
    f = open(test_log, "a+")
    f.write('--------------------------------------------------\n')
    f.close()
else:
    print('Using existing log file: ' + test_log + '\n')
    f = open(test_log, "a+")
    f.write('--------------------------------------------------\n')
    f.close()

while True:

    for i in range(4):
        switch_channel(i)
        ser = serial.Serial('/dev/ttySAC0', 115200)
        msg = str(i) + ',OK'
        ser.write(str.encode(msg))
        ser.close()
        sent_time_stamp = str(datetime.now())

        # get response
        response = ''
        while ser.in_waiting:
            response += ser.readline()
            received_time_stamp = str(datetime.now())


        # log data being sent
        f = open(test_log, "a+")
        log_msg = 'message \'' + msg + '\' sent at: ' + sent_time_stamp
        log_msg += 'response \'' + response + '\' received at: ' + received_time_stamp

        print('LOGGING: ' + log_msg)

        f.write(log_msg + '\n')
        f.close()

        # do not overflow communication buffers
        time.sleep(0.1)
