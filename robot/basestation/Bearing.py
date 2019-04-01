import math

BS = {'lat':0 , 'lon':0}
#place holder for Base Station Antenna location [Latitude , Longitude]
Rover = {'lat':0 , 'lon':0}
#place holder for Rover location [Latitude , Longitude]
print("Enter Base Station latitude:")
BS[0] = float(input())

print("Enter Base Station longitude:")
BS[1] = float(input())

print("Enter Rover latitude:")
Rover[0] = float(input())


print("Enter Rover longitude:")
Rover[1] = float(input())


print("Enter Starting Direction:")
SD = float(input())


for k in BS:
	BS[k] = BS[k] * (math.pi/180)

for k in Rover:
	Rover[k] = Rover[k] * (math.pi/180)
#change coordinates into radians

X = math.cos(Rover['lat']) * math.sin(Rover['lon']-BS['lon'])
Y = math.cos(BS['lat']) * math.sin(Rover['lat']) - math.sin(BS['lat']) * 
math.cos(Rover['lat']) * math.cos(Rover['lon'] - BS['lon'])
#X and Y are transitional variables in the calculations

RD = math.atan2(X,Y)
#Direction calculation from Base Station Antenna to Rover


RD = RD * (180/math.pi)
#change back into degrees

if RD < 0:
    RD = RD + 360
#change the result range from [-180,180] to [0,360]

Rotator = RD - SD + 180
#calculate the rotator's own direction
#it's a function of its starting direction, and the real direction to rover

if Rotator < 0:
    Rotator = Rotator + 360
elif Rotator > 360:
    Rotator = Rotator - 360
#make corrections to keep the result output in the [0,360] range

print('Starting Direction : {}'.format(SD))
print('Real Direction : {}'.format(RD))
print('Rotator Direction : {}'.format(Rotator))
#show all results 



