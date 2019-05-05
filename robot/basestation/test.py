#!/usr/bin/env python
"""Flask server controller.

Flask is light-weight and modular so this is actually all we need to set up a simple HTML page.
"""

import os, sys
import subprocess
from urllib.parse import urlparse, unquote
from connection import Connection
from time import sleep #for CSA testing

def run_shell(cmd, args=""): #modified this to split based on comma
    """Run script command supplied as string.

    Returns tuple of output and error.
    """
    cmd_list = cmd.split()
    #modified to commas because waleed's code has spaces in the message
    #all of the teensy code is space-separated as well
    arg_list = args.split(",")

    print("arg_list:", arg_list)

    for arg in arg_list:
        cmd_list.append(str(arg))

    print("cmd_list:", cmd_list)

    process = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)
    output, error = process.communicate()

    return output, error

# behaves more like how app.py will
if len(sys.argv) == 2:
    cmd = sys.argv[1]
    latitude = 45.520495
    longitude = -73.392162
# for testing at CSA
elif len(sys.argv) == 3:
    cmd = "b"
    latitude = sys.argv[1]
    longitude = sys.argv[2]
else:
    sys.exit(0)

print("requested latitude: "+str(latitude))
print("requested longitude: "+str(longitude))

rover_ip = "172.16.1.30"
base_ip = "172.16.1.20"
rover_port = 5030
base_port = rover_port
print("cmd: " + cmd)
while True:
    sender = Connection("rover_drive_sender", rover_ip, rover_port)

    error = str(None)

    try:
        sender.send(cmd)
    except OSError:
        error = "Network is unreachable"
        print(error)

    receiver = Connection("rover_drive_receiver", base_ip, base_port)
    feedback = str(None)
    error = str(None)

    try:
        feedback = receiver.receive(timeout=2)
    except OSError:
        error = "Network error"
        print(error)

    if not feedback:
        feedback = "Timeout limit exceeded, no data received"
    else:
        print("feedback:", feedback)
        data = feedback.split("\n") # last message will be an empty string (or have "\r")
        i = len(data)-2 #skip the empty string
        latestGpsMsg = None
        while True:
            #print("start of loop, iteration "+str(i))
            if data[i].find("GPS") != -1: # check if GPS is in the message
                #print("found GPS")
                if latestGpsMsg is None:
                    latestGpsMsg = i
                    #print(latestGpsMsg)
                if data[i].find("OK") is not -1: # there is GPS data
                    print("calling NavigationClient")
                    teensyMsg = str(latitude)+","+str(longitude)+","+data[i]
                    output, error = run_shell("python NavigationClient.py",teensyMsg)
                    output = str(output, "utf-8")
                    print("output: " + output)
                    break
            if len(data)-i >=5:
                if latestGpsMsg is not None:
                    print("calling NavigationClient")
                    teensyMsg = str(latitude)+","+str(longitude)+","+data[latestGpsMsg]
                    output, error = run_shell("python NavigationClient.py",teensyMsg)
                    output = str(output, "utf-8")
                    print("output: " + output)
                else:
                    print("no GPS data, not calling NavigationClient")
                break
            i-=1
    sleep(1)
