#include <Arduino.h>

#include <Debug.h>
#include <IOStream.h>

#if INO_DEBUG
ino::Debug::NewRoutine SayHiRoutine([]() {
	static auto LastMillis = millis();
	constexpr int Frequency = 2000;
	if (millis() > LastMillis + Frequency)
	{	
		LastMillis = millis();
		ino::out << "Hi" << ino::endl;
	}
});

// when \pText is entered the lambda is called and parameter string will be Text
ino::Debug::NewUserRoutine PrintStringRoutine('p', [](const String& string) {
	ino::out << "PrintStringRoutine: " << string << ino::endl;
});
#endif

void setup() {
	// setting up the streams is very important
	ino::out.begin(9600);
	ino::in.begin(9600);

}

void loop() {
	// this is where all the debug help runs
	INO_DEBUG_ROUTINE();
}
