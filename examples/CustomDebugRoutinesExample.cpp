#include <Arduino.h>

#include <Debug.h>
#include <IOStream.h>

#if INO_DEBUG // only for debug builds

// This creates a debug routine that is run through every time INO_DEBUG_ROUTINE() is called
ino::Debug::NewRoutine SayHiRoutine([]() {
	static auto LastMillis = millis();
	constexpr int Period = 2000;
	if (millis() > LastMillis + Period)
	{	
		LastMillis = millis();
		ino::out << "Hi" << ino::endl;
	}
});

// This creates a debug routine that will run when "\pSomeText" is entered into the console. The parameter string of the lambda is "SomeText"
// This currently only works when "\p" are the first characters in the Stream
ino::Debug::NewUserRoutine PrintStringRoutine('p', [](const String& string) {
	ino::out << "PrintStringRoutine: " << string << ino::endl;
});

#endif

void setup() {
	// Preparing the streams is required
	ino::out.begin(9600);
	ino::in.begin(9600);

}

void loop() {
	// This is where all the debug code runs
	INO_DEBUG_ROUTINE();
}
