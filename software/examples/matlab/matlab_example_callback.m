function matlab_example_callback
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletDualButton;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'fdd'; % Change to your UID
    
    ipcon = IPConnection(); % Create IP connection
    db = BrickletDualButton(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register state changed callback to function cb_state_changed
    set(db, 'StateChangedCallback', @(h, e)cb_state_changed(e));

    input('\nPress any key to exit...\n', 's');
    ipcon.disconnect();
end

% Callback function for state changed callback
function cb_state_changed(states)
    if states.buttonL == com.tinkerforge.BrickletDualButton.BUTTON_STATE_PRESSED
        fprintf('Left button pressed\n');
    else
        fprintf('Left button released\n');
    end
    if states.buttonR == com.tinkerforge.BrickletDualButton.BUTTON_STATE_PRESSED
        fprintf('Right button pressed\n');
    else
        fprintf('Right button released\n');
    end
end