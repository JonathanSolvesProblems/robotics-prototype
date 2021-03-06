#!/usr/bin/env python3

import serial
import rospy
from serial_cmd.srv import *

def handle_serial_cmd(req):
    response = "Forwarding serial cmd '{:s}'".format(req.msg)

    uart_tx(req.msg)

    return response


def uart_tx(msg):
    msg = str(msg)

    b_msg=msg.encode()
    ser = serial.Serial()
    ser.port = "/dev/ttySAC0"
    ser.baudrate = 9600
    ser.open()

    print("Sending serial message: '" + msg + "'")
    ser.write(b_msg)
    # Instead of expecting an "immediate" reply, use a separate listener
    # process for publishing most recent odroid Rx data
    #sleep(0.5)
    #print(ser.readline())

    # Josh says: I recommend actually listening for the response
    # in here, actually. Maybe grabbing 500ms of responses or something.
    ser.close()

    return "Message sent: '" + msg + "'\n"

def serial_cmd_server():
    rospy.init_node('serial_cmd_server')
    s = rospy.Service('serial_cmd', SerialCmd, handle_serial_cmd)
    print("Ready to respond to serial commands")
    rospy.spin()

if __name__ == "__main__":
    serial_cmd_server()
