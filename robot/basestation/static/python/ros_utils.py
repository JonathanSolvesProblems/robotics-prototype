import os
from urllib.parse import urlparse

import robot.basestation.static.python.utils as utils
from robot.basestation.static.python.utils import *
from robot.comms.connection import Connection

def fetch_ros_master_uri():
    """Fetch and parse ROS Master URI from environment variable.

    The parsed URI is returned as a urllib.parse.ParseResult instance.

    Returns:
        urllib.parse.ParseResult: 6-tuple instance with various attributes.

    Attributes (urllib.parse.ParseResult):
    - hostname -- the ip address or the dns resolvable name
    - port -- the port number
    - etc...

    See https://docs.python.org/3/library/urllib.parse.html?highlight=urlparse#urllib.parse.urlparse
    """
    return urlparse(os.environ["ROS_MASTER_URI"])

def fetch_ros_master_ip():
    """Fetch only the hostname (host IP) portion of the parse URI."""
    return fetch_ros_master_uri().hostname

def run_ping_rover():
    """Pings ROS_MASTER_URI and return response object with resulting outputs.

    Pings rover first directly with Unix ping command,
    then using ros ping_acknowledgment service.

    Returns JSON object with the following fields:
    success -- whether requests was successful
    ping_msg -- output of Unix ping command
    ros_msg -- output of the ROS ping_acknowledgment service
    """
    ping_output, error = run_shell("ping -c 1 " + fetch_ros_master_ip())
    ping_output = ping_output.decode()

    print("Output: " + ping_output)

    if "Destination Net Unreachable" in ping_output:
        error_msg = "Basestation has no connection to network, aborting ROS ping."
        return (False, ping_output, error_msg)

    if "Destination Host Unreachable" in ping_output:
        error_msg = "Rover has no connection to network, aborting ROS ping."
        return (False, ping_output, error_msg)

    if error:
        print("Error: " + error.decode())

    ros_output, error = run_shell("rosrun ping_acknowledgment ping_response_client.py hello")
    ros_output = ros_output.decode()

    print("Pinging rover")
    print("Output: " + ros_output)

    if error:
        print("Error: " + error.decode())

    return (False, ping_output, ros_output)

def run_odroid_rx():
    script_dir = os.path.dirname(os.path.realpath(__file__))
    log_file = script_dir + "/../rospackages/src/odroid_rx/scripts/odroid_rx.txt"
    print("odroid_rx")

    # query the topic exactly once
    output, error = run_shell("cat", log_file)
    output = str(output, "utf-8")

    print("output: " + output)

    return (True, output)

def run_rover_drive():
    print("rover_drive")

    cmd = str(request.get_data('cmd'), "utf-8")
    print("cmd: " + cmd)
    # remove fluff, only command remains
    if cmd:
        cmd = cmd.split("=")[1]
        # decode URI
        cmd = unquote(cmd)

    if local:
        rover_ip = "127.0.0.1"
        base_ip = rover_ip
        rover_port = 5020
        base_port = 5025
    else:
        rover_ip = "172.16.1.30"
        base_ip = "172.16.1.20"
        rover_port = 5030
        base_port = rover_port
    print("cmd: " + cmd)
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

    print("feedback:", feedback)

    if not feedback:
        feedback = "Timeout limit exceeded, no data received"

    return (True, cmd, feedback, error)
