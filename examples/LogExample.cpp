#include <Arduino.h>

#include <Log.h>

int Frequency = 2000;
int LastMillis = millis();

// with \aFrequency the variable Frequency can be adjusted with minimum 120 and maximum 2500
INO_ROUTINE_RANGEADJUST(Frequency, 120, 2500);

// with \pFrequency and \pLastMillis the value of these two variables can be printed
INO_ROUTINE_PRINTVAR(Frequency);
INO_ROUTINE_PRINTVAR(LastMillis);

void setup() {
	// setting up the streams is very important
	ino::out.begin(9600);
	ino::in.begin(9600);

}

void loop() {
	// this is where all the debug help runs
	INO_DEBUG_ROUTINE();

	if (millis() > LastMillis + Frequency)
	{
		LastMillis = millis();
		ino::out << "Hello World!" << ino::endl;

		INO_IF_DEBUG(static int Count = 0;)
		INO_NOTE("Count: ", ++Count, ino::endl);
		INO_IF_DEBUG(
			if (LastMillis > 20000)
				INO_WARNING("when LastMillis overflow this will stop working", ino::endl);
			if (LastMillis > 25000)
				INO_ERROR("LastMillis are getting close to overflow", ino::endl);
			if (LastMillis > 29000)
				INO_FATAL("LastMillis will overflow very soon", ino::endl);
		)
	}

}
