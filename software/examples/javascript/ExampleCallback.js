var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'fdd'; // Change to your UID

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var db = new Tinkerforge.BrickletDualButton(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);        
    }
);// Connect to brickd
// Don't use device before ipcon is connected

// Register state changed callback
db.on(Tinkerforge.BrickletDualButton.CALLBACK_STATE_CHANGED,
    function(buttonL, buttonR, ledL, ledR) {
        if(buttonL === Tinkerforge.BrickletDualButton.BUTTON_STATE_PRESSED) {
            console.log('Left button pressed');
        }
        else {
            console.log('Left button Released');
        }
        if(buttonR === Tinkerforge.BrickletDualButton.BUTTON_STATE_PRESSED) {
            console.log('Right button pressed');
        }
        else{
            console.log('Right button Released');
        }
        console.log();
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

