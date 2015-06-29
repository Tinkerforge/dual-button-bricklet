function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "fdd"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    db = java_new("com.tinkerforge.BrickletDualButton", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register state changed callback to function cb_state_changed
    db.addStateChangedCallback(@cb_state_changed);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback function for state changed callback
function cb_state_changed(e)
    if short2int(e.buttonL) == 0
        fprintf("Left button pressed\n");
    else
        fprintf("Left button released\n");
    end
    if short2int(e.buttonR) == 0
        fprintf("Right button pressed\n");
    else
        fprintf("Right button released\n");
    end
end

function int = short2int(short)
    if compare_versions(version(), "3.8", "<=")
        int = short.intValue();
    else
        int = short;
    end
end
