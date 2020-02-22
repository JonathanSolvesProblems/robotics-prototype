cd ~/ouster_example/ouster_ros
roslaunch os1.launch os1_hostname:=10.5.5.94 os1_udp_dest:=10.5.5.1 lidar_mode:="$1" viz:=true
