use std::{error::Error, io, thread};
use tinkerforge::{dual_button_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Dual Button Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let db = DualButtonBricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    let state_changed_receiver = db.get_state_changed_callback_receiver();

    // Spawn thread to handle received callback messages.
    // This thread ends when the `db` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for state_changed in state_changed_receiver {
            if state_changed.button_l == DUAL_BUTTON_BRICKLET_BUTTON_STATE_PRESSED {
                println!("Left Button: Pressed");
            } else if state_changed.button_l == DUAL_BUTTON_BRICKLET_BUTTON_STATE_RELEASED {
                println!("Left Button: Released");
            }

            if state_changed.button_r == DUAL_BUTTON_BRICKLET_BUTTON_STATE_PRESSED {
                println!("Right Button: Pressed");
            } else if state_changed.button_r == DUAL_BUTTON_BRICKLET_BUTTON_STATE_RELEASED {
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
