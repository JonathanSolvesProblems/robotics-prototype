#!/usr/bin/env python3
import pytest
import os
from robot.basestation.app import run_shell

# Warning: if the location of mock data or the change_mode.sh script are changed,
# the following relative paths must be adjusted accordingly
current_dir = os.path.dirname(os.path.abspath(__file__))
ideal_mock = current_dir + "/mock_data/ideal.data"
#multiple_hashtags_mock = current_dir + "/mock_data/multiple_hashtags.data"
rel_path = "/../../../robot/basestation/config/change_mode.sh"
change_mode = current_dir + rel_path

# key output messages from change_mode script
already_local_msg = 'already in local mode'
already_comp_msg = 'already in comp mode'
switch_local_msg = 'switching to local mode'
switch_comp_msg = 'switching to comp mode'

@pytest.fixture(autouse=True)
def run_around_tests():
    # Code that will run before your test, for example:
    #files_before = # ... do something to check the existing files
    # A test function will be run at this point
    print("START")
    yield
    # Code that will run after your test, for example:
    #files_after = # ... do something to check the existing files
    print("END")

def test_ideal():
    # this shouldn't work, we should get 'already in local mode'
    exec_string = "bash " + change_mode + " local " + ideal_mock
    out, err = run_shell(exec_string)
    out = out.decode()
    print('output', out)
    print('error', err)

    assert already_local_msg in out

    # this should work, we should get 'switching to comp mode'
    exec_string = "bash " + change_mode + " comp " + ideal_mock
    out, err = run_shell(exec_string)
    out = out.decode()
    print('output', out)
    print('error', err)

    assert switch_comp_msg in out

    # this shouldn't work, we should get 'already in comp mode'
    exec_string = "bash " + change_mode + " comp " + ideal_mock
    out, err = run_shell(exec_string)
    out = out.decode()
    print('output', out)
    print('error', err)
    assert already_comp_msg in out

    # this should work, we should get 'switching to local mode'
    exec_string = "bash " + change_mode + " local " + ideal_mock
    out, err = run_shell(exec_string)
    out = out.decode()
    print('output', out)
    print('error', err)

    assert switch_local_msg in out

#test_ideal()
