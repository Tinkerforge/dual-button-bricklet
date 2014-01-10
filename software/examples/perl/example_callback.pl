#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletDualButton;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'fdd'; # Change to your UID

my $ipcon = IPConnection->new(); # Create IP connection
my $db = BrickletDualButton->new(&UID, $ipcon); # Create device object

# Callback function for state changed callback
sub cb_state_changed
{
    my ($button_l, $button_r, $led_l, $led_r) = @_;

    if ($button_l == $db->BUTTON_STATE_PRESSED)
    {
        print "\nLeft button pressed\n";
    }    
    else
    {
        print "\nLeft button released\n";
    }

    if ($button_r == $db->BUTTON_STATE_PRESSED)
    {
        print "\nRight button pressed\n";
    }
    else
    {
        print "\nRight button released\n";
    }
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register state changed callback to function cb_state_changed
$db->register_callback($db->CALLBACK_STATE_CHANGED, 'cb_state_changed');

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

