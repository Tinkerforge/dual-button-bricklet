using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Dual Button Bricklet

	// Callback function for state changed callback
	static void StateChangedCB(BrickletDualButton sender, byte buttonL, byte buttonR,
	                           byte ledL, byte ledR)
	{
		if(buttonL == BrickletDualButton.BUTTON_STATE_PRESSED)
		{
			Console.WriteLine("Left Button: Pressed");
		}
		else if(buttonL == BrickletDualButton.BUTTON_STATE_RELEASED)
		{
			Console.WriteLine("Left Button: Released");
		}

		if(buttonR == BrickletDualButton.BUTTON_STATE_PRESSED)
		{
			Console.WriteLine("Right Button: Pressed");
		}
		else if(buttonR == BrickletDualButton.BUTTON_STATE_RELEASED)
		{
			Console.WriteLine("Right Button: Released");
		}

		Console.WriteLine("");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletDualButton db = new BrickletDualButton(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register state changed callback to function StateChangedCB
		db.StateChangedCallback += StateChangedCB;

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
