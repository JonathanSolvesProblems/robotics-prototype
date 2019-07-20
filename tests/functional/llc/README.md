# LLC functional test

`cycleTest.py` switches channels on the mux as well as sends data at 115200 baudrate and waits for a response, after receiving it the data is logged with timestamps to a file `~/llc-test.log`.
`Chatter.ino` listens to the serial data on all four serial channels and relays the information over USB serial.

To test:

1. Connect the outputs of the LLC, DIN and DOUT, 1 to 4, to the _same_ teensy as well as a ground connection from the LLC to the teensy board.
2. Power the odroid through the LLC by connecting the LLC to a power supply between 12-17 V and current limit to 2A.
3. The odroid will log the data on its side, while the teensy will connect to a computer through a usb port and report back all the data it has received on all channels. We can use putty to log all the data from the teensy.
4. Make sure putty is configured to log all the data it receives in its session on a .txt file.
5. Configure a session on putty at the 115200 baudrate and select the correct COM port that the teensy is on, start the putty session.

The odroid send messages every 0.1 seconds and the teensy will simply listen and relay that info to the computer.
These commands contain a time stamp and the channel the odroid is sending this message to.

Ideally let this test run for a few hours. Something inidicative of a situation where LLC simply fails for no reason after a few hours of operation with it integrated in the rover.

We can then later look at this data to see if the failure on the lLC is function of time/signal/pattern or something else.

