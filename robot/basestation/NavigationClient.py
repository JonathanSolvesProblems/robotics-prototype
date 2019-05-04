import serial.tools.list_ports
import sys
from Nav_funs import Direction , Distance , Turning

ser = serial.Serial('COM3' , 115200 )
# if sys.platform.startswith('linux'):
#     ports = list(serial.tools.list_ports.comports())
#     first_port = ports[0].name
#     ser = serial.Serial('/dev/' + first_port, 115200 , timeout = 1)
#
# elif sys.platform.startswith('win'):
#
#     ports = serial.tools.list_ports.comports()
#     connected = []
#     for element in ports:
#         connected.append(element.device)
#
#     if connected[0] == 'COM1':
#         ser = serial.Serial(connected[1] , 115200 , timeout = 1)
#     else:
#         ser = serial.Serial(connected[0] , 115200 , timeout = 1)

Destination = {'lat':0 , 'lon':0}
Rover = {'lat':0 , 'lon':0 , 'heading':0}

if len(sys.argv) == 4:
    Destination['lat'] = float(sys.argv[1])
	Destination['lon'] = float(sys.argv[2])
	Data = sys.argv[3]
	
else
	if len(sys.argv) >= 5:
		print(
			"too many arguments"
		)
	else
		print(
			"not enough arguments"
		)
    print("example usage: python Navigation_basestation.py <latitude> <longitude> <teensy message>")

Data = Data.split('--')
Location_info = Data[0]
Heading_info = Data[1]

if Location_info.find('GPS-OK') != -1:
	GPS_info_available = True
	temp = Location_info.split()
	Rover['lat'] = float(temp[1])
	Rover['lon'] = float(temp[2])
elif Location_info.find('GPS-N/A') != -1:
	GPS_info_available = False
	print('GPS information is not available yet')

Rover['heading'] = float(Heading_info.split()[1])

if GPS_info_available == True:

	Rov_to_des_distance = Distance(Rover['lat'],Rover['lon'],Destination['lat'],Destination['lon'])
	Rov_to_des_direction = Direction(Rover['lat'],Rover['lon'],Destination['lat'],Destination['lon'])

	Direction_adjust = Turning(Rov_to_des_direction , Rover['heading'])

	print('Destination is at : {} , {}'.format(Destination['lat'],Destination['lon']))
	print('Rover is currently at : {} , {}'.format(Rover['lat'],Rover['lon']))
	print('Distance to the destination point is : {} meters'.format(round(Rov_to_des_distance)))
	if Direction_adjust < 0:
		print('Turn left by {} degrees and drive'.format(round(abs(Direction_adjust))))
	else:
		print('Turn right by {} degrees and drive'.format(round(Direction_adjust)))
	print('\n')