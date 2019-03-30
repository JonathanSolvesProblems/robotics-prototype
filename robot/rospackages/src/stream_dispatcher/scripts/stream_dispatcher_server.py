#!/usr/bin/env python

import signal
import subprocess
import os
import sys
import time
import rospy
from stream_dispatcher.srv import *

def handle_stream_dispatcher_server(req):
    response = "Video Stream starting {:s}".format(req.device)



def stream_dispatcher_server():
    stream_starter="./start_stream.sh"
    rospy.init_node('stream_dispatcher_server')
    s=rospy.Service()

if __name__ == '__main__':
    stream_dispatcher_server()
