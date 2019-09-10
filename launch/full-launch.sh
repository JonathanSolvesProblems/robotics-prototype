#!/bin/bash
# Full launch of astro
# Make sure you have the aliases found here : https://github.com/space-concordia-robotics/robotics-prototype/blob/master/robot/basestation/config/.bash_aliases
GNOME_TERMINAL='gnome-terminal -e'
XTERM='xterm -e'
TERMINATOR='terminator -x bash -c'

TERMINAL=$XTERM # Add your terminal above and set it here.

echo "Checking packages..."
if [ -z ${CATKIN_WS+x} ]
then
    echo "CATKIN_WS is not set! Exiting..."
    exit 1
fi
if [ ! -d "$CATKIN_WS/src/aliencontrol" ]
then
    echo "aliencontrol not found, installing package aliencontrol"
    git clone https://github.com/acschaefer/aliencontrol "$CATKIN_WS/src/aliencontrol/"
    catkin_make --directory $CATKIN_WS
    source $CATKIN_WS/devel/setup.sh
fi
echo "Done verifying and installing necessary packages"
echo "Using '$TERMINAL' to launch commands"
roslaunch astro-full.launch term:="$TERMINAL" ws:="$ROBOTICS_WS"
