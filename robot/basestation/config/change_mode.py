#!/usr/bin/env python3
import sys

if len(sys.argv) == 3:
    bashrc = sys.argv[2]
elif len(sys.argv) == 2:
    bashrc = "~/.bashrc"
elif len(sys.argv) < 2 or len(sys.argv) > 3:
    print('illegal number of parameters')
    print('exiting script')
    sys.exit(1)

# in any correct case, always the first arg is target mode: local or comp
target_mode = sys.argv[1]

print("bashrc:", bashrc)
print("target_mode:", target_mode)
