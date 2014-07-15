import com.tinkerforge.BrickletDualButton;
import com.tinkerforge.IPConnection;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "XYZ"; // Change to your UID
	
	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletDualButton db = new BrickletDualButton(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add and implement state changed listener
		db.addStateChangedListener(new BrickletDualButton.StateChangedListener() {
			public void stateChanged(short buttonL, short buttonR, short ledL, short ledR) {
				if(buttonL == BrickletDualButton.BUTTON_STATE_PRESSED) {
					System.out.println("Left button pressed");
				} else {
					System.out.println("Left button released");
				}

				if(buttonR == BrickletDualButton.BUTTON_STATE_PRESSED) {
					System.out.println("Right button pressed");
				} else {
					System.out.println("Right button released");
				}

				System.out.println("");
			}
		});

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
