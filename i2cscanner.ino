#include <Wire.h>

#define S Serial

void setup()
{
	Wire.begin();

	S.begin(9600);
	while (!S);
}

void loop()
{
	S.println("\n=== Scanning ===");

	int numDevices = 0;
	for (byte address = 1; address < 127; address++)
	{
		Wire.beginTransmission(address);
		byte error = Wire.endTransmission();

		if (error == 0)
		{
			S.print("I2C device found at address 0x");
			if (address<16)
				S.print("0");
			S.println(address, HEX);

			numDevices++;
		}
		else if (error == 4)
		{
			S.print("Unknown error at address 0x");
			if (address < 16)
				S.print("0");
			S.println(address, HEX);
		}		
	}

	if (numDevices == 0)
		S.println("No I2C devices found");

	delay(5000);
}
