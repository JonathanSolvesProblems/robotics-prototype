#!/usr/bin/env bash

# emulate interactive session so that bashrc can actually be sourced from script
# both of these methods are used as a redundancy
# as suggested in https://stackoverflow.com/questions/43659084/source-bashrc-in-a-script-not-working
PS1='.\$'
set -i

#@TODO: test if string interpolation will work in sed regex
# if so then refactor to determine them based off args passed
# and remove repetitive code of updating
#@TODO: add switching of ROS_HOSTNAME var
#@TODO: account for possibly multiple '#'s

if [ -z "$2" ]; then
    bashrc="$HOME/.bashrc"
else
    # check if file exists
    if [ -f "$2" ]; then
        bashrc="$2"
    else
        echo "File $2 does not exist - exiting script"
        exit 1
    fi
fi

# ip of OBC, which is the rosmaster
local_ip="export ROS_MASTER_URI=http:\/\/local"
comp_ip="export ROS_MASTER_URI=http:\/\/172"
local_hostname="export ROS_HOSTNAME=localhost"
comp_hostname="export ROS_HOSTNAME=$USER"

echo "backing up $bashrc as ${bashrc}_backup"
cp $bashrc "${bashrc}_backup"

if [[ $1 == "local" ]]; then
    if ! grep '#export ROS_MASTER_URI=http://local' $bashrc ; then
        echo "already in local mode"
        exit 0
    fi
    echo "switching to local mode"
    sed -i "s/#$local_ip/$local_ip/g" $bashrc
    sed -i "s/$comp_ip/#$comp_ip/g" $bashrc
    sed -i "s/#$local_hostname/$local_hostname/g" $bashrc
    sed -i "s/$comp_hostname/#$comp_hostname/g" $bashrc
    source $bashrc
elif [[ $1 == "comp" ]]; then
    if ! grep '#export ROS_MASTER_URI=http://172' $bashrc ; then
        echo "already in comp mode"
        exit 0
    fi
    echo "switching to comp mode"
    sed -i "s/$local_ip/#$local_ip/g" $bashrc
    sed -i "s/#$comp_ip/$comp_ip/g" $bashrc
    sed -i "s/$local_hostname/#$local_hostname/g" $bashrc
    sed -i "s/#$comp_hostname/$comp_hostname/g" $bashrc
    source $bashrc
else
    if [ -z "$1" ]; then
        echo "No args passed"
    else
        echo "Args not recognized"
    fi
    echo "Please supply 'local' or 'comp' as the first arg to indicate which mode you want to change to - exiting script"
    exit 1
fi

echo "ROS_MASTER_URI: $ROS_MASTER_URI"
echo "ROS_HOSTNAME: $ROS_HOSTNAME"
