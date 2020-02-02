#!/usr/bin/env python
"""Flask server controller.

Flask is light-weight and modular so this is actually all we need to set up a simple HTML page.
"""

import os
from urllib.parse import unquote
import flask
from flask import jsonify, request
import time
import datetime
from shlex import split

import robot.basestation.static.python.stream_capture as stream_capture
from robot.basestation.static.python.stream_capture import *
import robot.basestation.static.python.ros_utils as ros_utils
from robot.basestation.static.python.ros_utils import *

app = flask.Flask(__name__)

# Once we launch this, this will route us to the "/" page or index page and
# automatically render the Robot GUI
@app.route("/")
@app.route("/arm")
def index():
    """Current landing page, the arm panel."""
    return flask.render_template("pages/Arm.html", roverIP=fetch_ros_master_ip())

@app.route("/rover")
def rover():
    """Rover control panel."""
    return flask.render_template("pages/Rover.html", roverIP=fetch_ros_master_ip())

@app.route("/science")
def science():
    """Science page."""
    return flask.render_template("pages/Science.html", roverIP=fetch_ros_master_ip())

@app.route("/pds")
def pds():
    """PDS page."""
    return flask.render_template("pages/PDS.html", roverIP=fetch_ros_master_ip())


# routes for science page
@app.route('/science/numSections')
def numSections():
    return '4'

@app.route("/stream")
def stream():
    """Stream page."""
    return flask.render_template("pages/Stream.html", roverIP=fetch_ros_master_ip())

@app.route('/science/initialSection')
def initialSection():
    return '0'

@app.route("/ping_rover")
def ping_rover():
    success, ping_msg, ros_msg = run_ping_rover()
    return jsonify(success=success, ping_msg=ping_msg, ros_msg=ros_msg)


# only to be used when hacky implementation is fixed
# see odroid_rx package for details
@app.route("/odroid_rx", methods=["POST"])
def odroid_rx():
    success, odroid_rx = run_odroid_rx()
    return jsonify(success=success, odroid_rx=odroid_rx)

# Rover controls
@app.route("/rover_drive", methods=["POST"])
def rover_drive():
    success, cmd, feedback, error = run_rover_drive()
    return jsonify(success=success, cmd=cmd, feedback=feedback, error=error)

# capture image
@app.route("/capture_image", methods=["POST", "GET"])
def capture_image():
    msg = run_capture_image()
    return jsonify(msg=msg)

@app.route("/initiate_feed_recording/<stream>", methods=["POST", "GET"])
def initiate_feed_recording(stream):
    return start_recording_feed(stream)

@app.route("/stop_feed_recording/<stream>", methods=["POST", "GET"])
def stop_feed_recording(stream):
    return stop_recording_feed(stream)

if __name__ == "__main__":

    # feature toggles
    # the following two are used for UDP based communication with the Connection class
    global local
    local = False
    # print("fetch_ros_master_ip:", fetch_ros_master_ip())
    #
    # # either local or competition
    # ros_master_ip = fetch_ros_master_ip()
    # if ros_master_ip in ["127.0.0.1", "localhost"]
    #     local = True

    app.run(debug=True, host='0.0.0.0')
    # add param `host= '0.0.0.0'` if you want to run on your machine's IP address
