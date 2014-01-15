<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletDualButton.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletDualButton;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change to your UID

// Callback function for state_changed callback
function cb_state_changed($button_l, $button_r, $led_l, $led_r)
{
    if($button_l == BrickletDualButton::BUTTON_STATE_PRESSED) {
        echo "Left button pressed\n";
    } else {
        echo "Left button released\n";
    }

    if($button_r == BrickletDualButton::BUTTON_STATE_PRESSED) {
        echo "Right button pressed\n";
    } else {
        echo "Right button released\n";
    }

    echo "\n";
}

$ipcon = new IPConnection(); // Create IP connection
$al = new BrickletDualButton(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register state changed callback to function cb_state_changed
$al->registerCallback(BrickletDualButton::CALLBACK_STATE_CHANGED, 'cb_state_changed');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
