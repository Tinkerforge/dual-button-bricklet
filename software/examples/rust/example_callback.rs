use std::{error::Error, io, thread};
use tinkerforge::{dual_button_bricklet::*, ipconnection::IpConnection};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Dual Button Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let dual_button_bricklet = DualButtonBricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    //Create listener for state changed events.
    let state_changed_listener = dual_button_bricklet.get_state_changed_receiver();
    // Spawn thread to handle received events. This thread ends when the dual_button_bricklet
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for event in state_changed_listener {
            if event.button_l == DUAL_BUTTON_BRICKLET_BUTTON_STATE_PRESSED {
                println!("Left Button: Pressed");
            } else if event.button_l == DUAL_BUTTON_BRICKLET_BUTTON_STATE_RELEASED {
                println!("Left Button: Released");
            }

            if event.button_r == DUAL_BUTTON_BRICKLET_BUTTON_STATE_PRESSED {
                println!("Right Button: Pressed");
            } else if event.button_r == DUAL_BUTTON_BRICKLET_BUTTON_STATE_RELEASED {
                println!("Right Button: Released");
            }

            println!();
        }
    });

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
