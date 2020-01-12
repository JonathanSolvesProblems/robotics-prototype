#!/usr/bin/env python3
import traceback
import rospy
from std_msgs.msg import String
from mcu_control.srv import *

class RoverCommander:
    COMMAND_TOPIC = '/rover_command'
    REQUEST_SERVICE = 'rover_request'
    NODE_NAME = 'rover_command_publisher'
    MIN_SPEED = 0
    MAX_SPEED = 45
    DEFAULT_SPEED = 40 # in percent
    STOP = str(MIN_SPEED) + ':' + str(MIN_SPEED)
    
    # utility functions
    @staticmethod
    def is_valid_percent(percent):
        '''
        return True if value given between 0 and 100 inclusive
        '''
        return percent >= 0 and percent <= 100

    # class related functions
    def __init__(self):
        rospy.loginfo('Initializing anonymous node: ' + RoverCommander.NODE_NAME)
        rospy.init_node(RoverCommander.NODE_NAME, anonymous=True)

        rospy.loginfo('Creating publisher for topic: ' + RoverCommander.COMMAND_TOPIC + '" topic')
        self.command_publisher = rospy.Publisher(RoverCommander.COMMAND_TOPIC, String, queue_size=10)

        rospy.loginfo('Creating service proxy for service: ' + RoverCommander.REQUEST_SERVICE)
        self.request_proxy = rospy.ServiceProxy(RoverCommander.REQUEST_SERVICE, ArmRequest)

    # lowest level functions - interface
    def client_request(self, request):
        '''
        sends given request to rover
        '''
        response = ''

        try:
            response = self.request_proxy(request)
        except rospy.ServiceException as e:
            print('Service call failed: {:s}'.format(str(e)))
            traceback.print_exc()

        return response

    def budge(self, cmd):
        '''
        sends budge command to rover
        '''
        self.command_publisher.publish(cmd)

    # wrappers using lowest level functions - implementation
    def activate(self):
        '''
        sends activate request to rover
        '''
        rospy.loginfo('Activating rover')
        response = self.client_request('activate')
        return response

    def deactivate(self):
        '''
        sends deactivate request to rover
        '''
        rospy.loginfo('Deactivating rover')
        response = self.client_request('deactivate')
        return response

    # main drive commands (without ramp up/down)
    # the interval at which the rover MCU currently checks for serial commands is 10ms
    # a single budge will therefore only drive the motors for 10 ms
    def budge_forward(self, percent=self.DEFAULT_SPEED):
        '''
        sends forward command to rover
        '''
        if not self.is_valid_percent(percent):
            raise Exception('invalid percent value given, must be integer between 0-100')
            return False

        throttle = RoverCommander.MIN_SPEED
        speed = RoverCommander.MAX_SPEED * percent/100

        self.budge(str(speed) + ':' + str(throttle))

    def budge_backward(self, percent=self.DEFAULT_SPEED):
        '''
        sends backward command to rover
        '''
        if not self.is_valid_percent(percent=self.DEFAULT_SPEED):
            raise Exception('invalid percent value given, must be integer between 0-100')
            return False

        throttle = RoverCommander.MIN_SPEED
        speed = RoverCommander.MAX_SPEED * percent/100 * -1

        self.budge(str(speed) + ':' + str(throttle))


    def rotate_left(self, percent=self.DEFAULT_SPEED):
        '''
        sends rotate left command to rover
        '''
        if not self.is_valid_percent(percent):
            raise Exception('invalid percent value given, must be integer between 0-100')
            return False

        throttle = RoverCommander.MAX_SPEED * -1
        speed = RoverCommander.MAX_SPEED * percent/100
    
        self.budge(str(speed) + ':' + str(throttle))

    def rotate_right(self, percent=self.DEFAULT_SPEED):
        '''
        sends rotate right command to rover
        '''
        if not self.is_valid_percent(percent):
            raise Exception('invalid percent value given, must be integer between 0-100')
            return False

        throttle = RoverCommander.MAX_SPEED
        speed = RoverCommander.MAX_SPEED * percent/100

        self.budge(str(speed) + ':' + str(throttle))

    def stop(self):
        '''
        sends stop command to rover
        '''
        self.command_publisher.publish(RoverCommander.STOP)
