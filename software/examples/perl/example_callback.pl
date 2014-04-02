#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletDualButton;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'fdd'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
our $db = Tinkerforge::BrickletDualButton->new(&UID, $ipcon); # Create device object

# Callback function for state changed callback
sub cb_state_changed
{
    my ($button_l, $button_r, $led_l, $led_r) = @_;

    if ($button_l == $db->BUTTON_STATE_PRESSED)
    {
        print "Left button pressed\n";
    }    
    else
    {
        print "Left button released\n";
    }

    if ($button_r == $db->BUTTON_STATE_PRESSED)
    {
        print "Right button pressed\n";
    }
    else
    {
        print "Right button released\n";
    }
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register state changed callback to function cb_state_changed
$db->register_callback($db->CALLBACK_STATE_CHANGED, 'cb_state_changed');

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

