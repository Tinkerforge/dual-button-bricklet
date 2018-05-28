import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletDualButton;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Dual Button Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletDualButton db = new BrickletDualButton(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add state changed listener
		db.addStateChangedListener(new BrickletDualButton.StateChangedListener() {
			public void stateChanged(short buttonL, short buttonR, short ledL,
			                         short ledR) {
				if(buttonL == BrickletDualButton.BUTTON_STATE_PRESSED) {
					System.out.println("Left Button: Pressed");
				} else if(buttonL == BrickletDualButton.BUTTON_STATE_RELEASED) {
					System.out.println("Left Button: Released");
				}

				if(buttonR == BrickletDualButton.BUTTON_STATE_PRESSED) {
					System.out.println("Right Button: Pressed");
				} else if(buttonR == BrickletDualButton.BUTTON_STATE_RELEASED) {
					System.out.println("Right Button: Released");
				}

				System.out.println("");
			}
		});

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
