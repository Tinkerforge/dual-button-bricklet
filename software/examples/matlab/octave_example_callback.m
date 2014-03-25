function octave_example_callback
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "fdd"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    db = java_new("com.tinkerforge.BrickletDualButton", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register state changed callback to function cb_state_changed
    db.addStateChangedListener("cb_state_changed");

    input("\nPress any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback function for state changed callback
function cb_state_changed(buttonL, buttonR, ledL, ledR)
    if str2double(buttonL.toString()) == 0
        fprintf("Left button pressed\n");
    else
        fprintf("Left button released\n");
    end
    if str2double(buttonR.toString()) == 0
        fprintf("Right button pressed\n");
    else
        fprintf("Right button released\n");
    end
end
