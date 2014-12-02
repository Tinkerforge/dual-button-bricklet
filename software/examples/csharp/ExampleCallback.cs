using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	// Callback function for state changed callback
	static void StateChangedCB(BrickletDualButton sender, 
	                           byte buttonL, byte buttonR, 
	                           byte ledL, byte ledR)
	{
		if(buttonL == BrickletDualButton.BUTTON_STATE_PRESSED)
		{
			System.Console.WriteLine("Left button pressed");
		} 
		else
		{
			System.Console.WriteLine("Left button released");
		}

		if(buttonR == BrickletDualButton.BUTTON_STATE_PRESSED)
		{
			System.Console.WriteLine("Right button pressed");
		} 
		else
		{
			System.Console.WriteLine("Right button released");
		}

		System.Console.WriteLine("");
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletDualButton db = new BrickletDualButton(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register state changed callback to function StateChangedCB
		db.StateChanged += StateChangedCB;

		System.Console.WriteLine("Press enter to exit");
		System.Console.ReadLine();
		ipcon.Disconnect();
	}
}
