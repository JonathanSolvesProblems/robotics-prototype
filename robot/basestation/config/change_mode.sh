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
bashrc="$HOME/.bashrc"
local_line="export ROS_MASTER_URI=http:\/\/localhost"
comp_line="export ROS_MASTER_URI=http:\/\/172"

echo "backing up $bashrc as ${bashrc}_backup"
cp $bashrc "${bashrc}_backup"

if [[ $1 == "local" ]]; then
    if ! grep '#export ROS_MASTER_URI=http://local' $bashrc ; then
        echo "already in local mode"
        exit 0
    fi
    echo "switching to local mode"
    sed -i 's/#export ROS_MASTER_URI=http:\/\/local/export ROS_MASTER_URI=http:\/\/local/g' $bashrc
    sed -i 's/export ROS_MASTER_URI=http:\/\/172/#export ROS_MASTER_URI=http:\/\/172/g' $bashrc
    source $bashrc
elif [[ $1 == "comp" ]]; then
    if ! grep '#export ROS_MASTER_URI=http://172' $bashrc ; then
        echo "already in comp mode"
        exit 0
    fi
    echo "switching to comp mode"
    sed -i 's/export ROS_MASTER_URI=http:\/\/local/#export ROS_MASTER_URI=http:\/\/local/g' $bashrc
    sed -i 's/#export ROS_MASTER_URI=http:\/\/172/export ROS_MASTER_URI=http:\/\/172/g' $bashrc
    source $bashrc
else
    echo "no arguments, please supply 'local' or 'comp' to indicate which mode you want to change to"
fi

echo "ROS_MASTER_URI: $ROS_MASTER_URI"
