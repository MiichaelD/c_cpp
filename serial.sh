#!/bin/sh

# serial.sh
# Usage:
# $ serial.sh <device> <port speed>
# Example: serial.sh /dev/ttyS0 9600
if [ "$#" -ne 2 ]; then
  echo "Usage: serial.sh <device> <baud_rate>\nExample: serial.sh /dev/ttyACM0 9600\n" >&2
  exit 1
else
	echo "Type 'z' to close subprocesses when finished" 
fi
# Usage:
# $ serial.sh <device> <baud_rate>
# Example: serial.sh /dev/ttyACM0 9600

# Set up device
stty -F $1 $2

# Let cat read the device $1 in the background
# cat $1 &
./serialc & # serialc can interact with the input (i.e. react when receiving a string)

# Capture PID of background process so it is possible to terminate it when done
bgPid=$!

# Read commands from user, send them to device $1
while read cmd; do
   	echo "$cmd" > $1
	if [ "$cmd" = "z" ]; then
		echo "Exiting serial.sh and subprocess "$bgPid 
		break
	fi
   	
done

# Terminate background read process
# kill $bgPid
echo "\n";