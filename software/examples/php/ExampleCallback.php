<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletDualButton.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletDualButton;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Dual Button Bricklet

// Callback function for state changed callback
function cb_stateChanged($button_l, $button_r, $led_l, $led_r)
{
    if ($button_l == BrickletDualButton::BUTTON_STATE_PRESSED) {
        echo "Left Button: Pressed\n";
    } elseif ($button_l == BrickletDualButton::BUTTON_STATE_RELEASED) {
        echo "Left Button: Released\n";
    }

    if ($button_r == BrickletDualButton::BUTTON_STATE_PRESSED) {
        echo "Right Button: Pressed\n";
    } elseif ($button_r == BrickletDualButton::BUTTON_STATE_RELEASED) {
        echo "Right Button: Released\n";
    }

    echo "\n";
}

$ipcon = new IPConnection(); // Create IP connection
$db = new BrickletDualButton(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register state changed callback to function cb_stateChanged
$db->registerCallback(BrickletDualButton::CALLBACK_STATE_CHANGED, 'cb_stateChanged');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
