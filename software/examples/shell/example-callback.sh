#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# handle incoming state changed callbacks
tinkerforge dispatch dual-button-bricklet $uid state-changed
