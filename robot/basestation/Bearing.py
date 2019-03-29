import math

BS = [0 , 0]
Rover = [0 , 0]

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


BS = [(math.pi/180)*x for x in BS]
Rover = [(math.pi/180)*x for x in Rover]


X = math.cos(Rover[0]) * math.sin(Rover[1]-BS[1])
Y = math.cos(BS[0]) * math.sin(Rover[0]) - math.sin(BS[0]) * math.cos(Rover[0]) * math.cos(Rover[1] - BS[1])

RD = math.atan2(X,Y)

RD = RD * (180/math.pi)

if RD < 0:
    RD = RD + 360

Rotator = RD - SD + 180

if Rotator < 0:
    Rotator = Rotator + 360
elif Rotator > 360:
    Rotator = Rotator - 360


print('Starting Direction : {}'.format(SD))
print('Real Direction : {}'.format(RD))
print('Rotator Direction : {}'.format(Rotator))




