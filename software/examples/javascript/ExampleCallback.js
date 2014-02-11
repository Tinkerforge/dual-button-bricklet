var IPConnection = require('Tinkerforge/IPConnection');
var BrickletDualButton = require('Tinkerforge/BrickletDualButton');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'fdd'; // Change to your UID

var ipcon = new IPConnection(); // Create IP connection
var db = new BrickletDualButton(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        if(error === IPConnection.ERROR_ALREADY_CONNECTED) {
            console.log('Error: Already connected');        
        }
    }
); // Connect to brickd
// Don't use device before ipcon is connected

// Register state changed callback
db.on(BrickletDualButton.CALLBACK_STATE_CHANGED,
    function(buttonL, buttonR, ledL, ledR) {
        if(buttonL === BrickletDualButton.BUTTON_STATE_PRESSED) {
            console.log('Left button pressed');
        }
        else {
            console.log('Left button Released');
        }
        if(buttonR === BrickletDualButton.BUTTON_STATE_PRESSED) {
            console.log('Right button pressed');
        }
        else{
            console.log('Right button Released');
        }
        console.log();
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data', function(data) {
	    ipcon.disconnect(
            function(error) {
                if(error === IPConnection.ERROR_NOT_CONNECTED) {
                    console.log('Error: Already disconnected');        
                }
            }
        );
process.exit(0);
});

