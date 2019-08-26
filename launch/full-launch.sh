#!/bin/bash
# Full launch of astro
# Make sure you have the aliases found here : https://github.com/space-concordia-robotics/robotics-prototype/blob/master/robot/basestation/config/.bash_aliases
GNOME_TERMINAL='gnome-terminal -e'
TERMINAL=$GNOME_TERMINAL
#$TERMINAL 'roslaunch astro-full.launch'
#$TERMINAL startgui
echo $CATKIN_WS/src/aliencontrol
if [ ! -d "$CATKIN_WS/src/aliencontrol" ]
then
    echo "aliencontrol not found, installing package aliencontrol"
    git clone https://github.com/acschaefer/aliencontrol "$CATKIN_WS/src/aliencontrol/"
    catkin_make --directory $CATKIN_WS
fi
echo "Done installing necessary packages"
ls
#roslaunch astro-full.launch
