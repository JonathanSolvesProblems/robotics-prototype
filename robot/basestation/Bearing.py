import serial
import math

ser = serial.Serial('COM3', 115200 , timeout = 1)

BS = {'lat':0 , 'lon':0}
Rover = {'lat':0 , 'lon':0}

temp1 = float(input("Enter Base Station Latitude :"))
temp2 = float(input("Enter Base Station Longitude :"))
BS_ant_dir = float(input("Enter Base Station Antenna Starting Direction :"))

R = 6371000
while True:
    GPS = ser.readline().decode('ascii')

    if len(GPS) > 5:
        GPS = GPS.split()
        Rover_lat_deg = float(GPS[0])
        Rover_lon_deg = float(GPS[1])



        BS['lat'] = temp1
        BS['lon'] = temp2

        Rover['lat'] = Rover_lat_deg * (math.pi / 180)
        Rover['lon'] = Rover_lon_deg * (math.pi / 180)
        BS['lat'] = BS['lat'] * (math.pi / 180)
        BS['lon'] = BS['lon'] * (math.pi / 180)

        delta_lat = Rover['lat'] - BS['lat']
        delta_lon = Rover['lon'] - BS['lon']

        X = math.cos(Rover['lat']) * math.sin(delta_lon)
        Y = math.cos(BS['lat']) * math.sin(Rover['lat']) - math.sin(BS['lat']) * math.cos(Rover['lat']) * math.cos(delta_lon)

        Real_dir = math.atan2(X, Y)

        Real_dir = Real_dir * (180 / math.pi)

        if Real_dir < 0:
            Real_dir = Real_dir + 360

        Rotator = Real_dir - BS_ant_dir + 180

        if Rotator < 0:
            Rotator = Rotator + 360
        elif Rotator > 360:
            Rotator = Rotator - 360

        A = ((math.sin(delta_lat / 2)) ** 2) + math.cos(Rover['lat']) * math.cos(BS['lat']) * ((math.sin(delta_lon / 2)) ** 2)
        C = 2 * math.atan2(math.sqrt(A), math.sqrt(1 - A))
        Distance = R * C


        print('Rover Location : {},{}'.format(Rover_lat_deg,Rover_lon_deg))
        print('Starting Direction : {}'.format(BS_ant_dir))
        print('Real Direction : {}'.format(round(Real_dir)))
        print('Needed Rotator Direction : {}'.format(round(Rotator)))
        print('Distance is {} meters'.format(round(Distance)))
        print('\n')

