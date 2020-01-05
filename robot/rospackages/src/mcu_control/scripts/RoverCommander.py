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
    STOP = str(MIN_SPEED) + ':' + str(MIN_SPEED)

    def __init__(self):
        rospy.loginfo('Initializing anonymous node: ' + RoverCommander.NODE_NAME)
        rospy.init_node(RoverCommander.NODE_NAME, anonymous=True)

        rospy.loginfo('Creating publisher for topic: ' + RoverCommander.COMMAND_TOPIC + '" topic')
        self.command_publisher = rospy.Publisher(RoverCommander.COMMAND_TOPIC, String, queue_size=10)

        rospy.loginfo('Creating service proxy for service: ' + RoverCommander.REQUEST_SERVICE)
        self.request_proxy = rospy.ServiceProxy(RoverCommander.REQUEST_SERVICE, ArmRequest)

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

    def budge_forward(self):
        '''
        sends forward command to rover
        '''
        self.command_publisher.publish('5:' + str(RoverCommander.MIN_SPEED))

    def stop(self):
        '''
        sends stop command to rover
        '''
        self.command_publisher.publish(RoverCommander.STOP)
                        
if __name__ == '__main__':
    rover_commander = RoverCommander()
