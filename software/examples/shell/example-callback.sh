#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change to your UID

# Handle incoming state changed callbacks
tinkerforge dispatch dual-button-bricklet $uid state-changed &

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
