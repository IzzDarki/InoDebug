#include <Arduino.h>

#include <Log.h>

int Value = 5;

// By entering \aValue to the console the variable Value can be adjusted in the range between 120 and 2500
INO_ROUTINE_RANGEADJUST(Value, 2, 30);

// other types of adjustments:
//INO_ROUTINE_ADJUST(Value); // Accepts every number
//INO_ROUTINE_SPECIFICADJUST(Value, [](const int& ValueRef) { return ValueRef % 2 == 0; }); // Accepts just even numbers

// By entering \pValue to the console the value of the variable Value can be printed
INO_ROUTINE_PRINTVAR(Value);

void setup() {
	// Preparing the streams is required
	ino::out.begin(9600);
	ino::in.begin(9600);

	INO_NOTE("Note", ino::endl);
	INO_WARNING("Warning", ino::endl);
	INO_ERROR("Error", ino::endl);
	INO_FATAL("Fatal", ino::endl);

}

void loop() {
	// This is where all the debug code runs
	INO_DEBUG_ROUTINE();

	INO_NOTE_CYCLE("Note cylce", ino::endl); // This will print a note every 1000ms (see INO_LOG_CYCLE_DURATION) (see INO_NOTE_CYCLE_PERIOD() for custom period), prevents spamming the console
	INO_NOTE_ONCE("Note only once", ino::endl); // This will print a note only once
}
