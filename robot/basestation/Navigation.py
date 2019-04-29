import serial.tools.list_ports
import sys
from Nav_funs import Direction , Distance

if sys.platform.startswith('linux'):
    ports = list(serial.tools.list_ports.comports())
    first_port = ports[0].name
    ser = serial.Serial('/dev/' + first_port, 115200 , timeout = 1)

elif sys.platform.startswith('win'):

    ports = serial.tools.list_ports.comports()
    connected = []
    for element in ports:
        connected.append(element.device)

    if connected[0] == 'COM1':
        ser = serial.Serial(connected[1] , 115200 , timeout = 1)
    else:
        ser = serial.Serial(connected[0] , 115200 , timeout = 1)

Destination = {'lat':0 , 'lon':0}
Rover = {'lat':0 , 'lon':0}

Destination['lat'] = float(input('Enter the destination latitude :'))
Destination['lon'] = float(input('Enter the destination longitude :'))

while True:
    Data = ser.readline().decode('ascii')

    if Data.find('GPS') != -1:
        if Data.find('OK') != -1:
            temp = Data.split()
            Rover['lat'] = temp[1]
            Rover['lon'] = temp[2]
            print('Rover is at : {},{}'.format(Rover['lat'],Rover['lon']))
        elif Data.find('N/A') != -1:
            print('Rover GPS data is not available yet')
    elif Data.find('Heading') != -1:
        print('Rover Heading is : {} degrees'.format(Data.split()[1]))
        print('\n')



