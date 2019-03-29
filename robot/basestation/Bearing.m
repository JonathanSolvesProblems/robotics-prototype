clear all
clc

BS=[45.3015 -73.2911];  % Base station antenna coordinates (entered manually)
Rover=[45.3023 -73.3454];   % Rover coordinates (from GPS)
starting_direction = 300;   % the direction where the 180 of the rotator is pointed




BS = BS*(pi/180);   % change to radians
Rover = Rover*(pi/180);

X = cos(Rover(1))*sin(Rover(2)-BS(2));
Y = cos(BS(1))*sin(Rover(1))-sin(BS(1))*cos(Rover(1))*cos(Rover(2)-BS(2));

real_direction = atan2(X,Y);      % calculate the direction (result in radians)

real_direction = real_direction*(180/pi);   % change back to degrees

if real_direction < 0                 % correct to have values between 0 and 360 instead of -180 and 180
    real_direction = real_direction + 360;           
end



rotator_direction = real_direction - starting_direction + 180;

if rotator_direction < 0                   %corrections to keep the number between 0 and 360
    rotator_direction = rotator_direction + 360;
elseif rotator_direction > 360
    rotator_direction = rotator_direction - 360;
end

starting_direction            % print
real_direction
rotator_direction