import serial.tools.list_ports
import sys
from Nav_funs import Distance , Direction

if sys.platform.startswith('linux'):
    ports = list(serial.tools.list_ports.comports())
    first_port = ports[0].name
    ser = serial.Serial('/dev/' + first_port, 115200)

elif sys.platform.startswith('win'):

    ports = serial.tools.list_ports.comports()
    connected = []
    for element in ports:
        connected.append(element.device)

    if connected[0] == 'COM1':
        ser = serial.Serial(connected[1] , 115200)
    else:
        ser = serial.Serial(connected[0] , 115200)


BS = {'lat':0 , 'lon':0}
Rover = {'lat':0 , 'lon':0}

BS['lat'] = float(input("Enter Base Station Latitude :"))
BS['lon'] = float(input("Enter Base Station Longitude :"))
BS_ant_dir = float(input("Enter Base Station Antenna Starting Direction :"))


while True:
    Data = ser.readline().decode('ascii')[:-1]
    Rover_GPS_data = Data.split('--')[0]

    if Rover_GPS_data.find('GPS-OK') != -1:
        GPS_info_available = True
        temp = Rover_GPS_data.split()
        Rover['lat'] = float(temp[1])
        Rover['lon'] = float(temp[2])
    elif Rover_GPS_data.find('GPS-N/A') != -1:
        GPS_info_available = False
        print('GPS information is not available yet')


    if GPS_info_available == True:
        BS_to_Rover_dir = Direction(BS['lat'],BS['lon'],Rover['lat'],Rover['lon'])
        BS_to_Rover_dis = Distance(BS['lat'],BS['lon'],Rover['lat'],Rover['lon'])

        Rotator = BS_to_Rover_dir - BS_ant_dir + 180

        if Rotator < 0:
            Rotator = Rotator + 360
        elif Rotator > 360:
            Rotator = Rotator - 360


        print('Rover Location : {},{}'.format(Rover['lat'],Rover['lon']))
        print('Starting Direction : {}'.format(BS_ant_dir))
        print('Real Direction : {}'.format(round(BS_to_Rover_dir)))
        print('Needed Rotator Direction : {}'.format(round(Rotator)))
        print('Distance is {} meters'.format(round(BS_to_Rover_dis)))
        print('\n')