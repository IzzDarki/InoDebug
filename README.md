---------------------------------------------------------------
#                         Ino Library                         #
#                            Debug                            #
---------------------------------------------------------------

This library is intended to simplify debugging and logging for Arduinos.

---------------------------------------------------------------

This library is dependent on the InoTiming library: https://github.com/IzzDarki/InoTiming.git
and on the InoStreams library: https://github.com/IzzDarki/InoStreams.git,
which itself is dependent on the Ino (core) library: https://github.com/IzzDarki/Ino.git
and the SoftwareSerial library from Arduino (which is installed with the Arduino IDE and other Arduino development environments)

---------------------------------------------------------------

Preprocessor definitions (users can modify)

INO_LOG_STATE_ALL       - default: defined in debug, always undefined in release    - when defined everything is going to be logged

INO_LOG_STATE_WARNING   - default: undefined, always undefined in release           - when defined warnings, errors and fatal errors are going to be logged

INO_LOG_STATE_ERROR     - default: undefined, always undefined in release           - when defined errors and fatal errors are going to be logged

INO_LOG_STATE_FATAL     - default: undefined, always undefined in release           - when defined just fatal errors are going to be logged

INO_LOG_STATE_NONE      - default: undefined in debug, defined in release           - when defined logging is off

INO_LOG_CYCLE_DURATION	- default: 1000												- specifies the duration in milliseconds for the cycle in which INO_NOTE_CYCLE(...), INO_WARNING_CYCLE(...), INO_ERROR_CYCLE(...) and INO_FATAL_CYCLE(...) log their arguments


---------------------------------------------------------------

Preprocessor macros

INO_DEBUG_ROUTINE()                	- does nothing in release, should run as continuously as possible in debug

INO_IF_NOTE(x)                     	- will expand to x when notes are going to be logged

INO_IF_WARNING(x)                  	- will expand to x when warnings are going to be logged

INO_IF_ERROR(x)                    	- will expand to x when errors are going to be logged

INO_IF_FATAL(x)                    	- will expand to x when fatal errors are going to be logged

INO_NOTE(...), INO_WARNING(...), INO_ERROR(...), INO_FATAL(...)   							- will log all arguments when the given error stage is going to be logged

INO_NOTE_ONCE(...), INO_WARNING_ONCE(...), INO_ERROR_ONCE(...), INO_FATAL_ONCE(...)   		- will log all arguments only in the first call when the given error stage is going to be logged

INO_NOTE_CYCLE(...), INO_WARNING_CYCLE(...), INO_ERROR_CYCLE(...), INO_FATAL_CYCLE(...)   	- will log all arguments only once in the time INO_LOG_CYCLE_DURATION when the given error stage is going to be logged

INO_PRINTVAR(Var)                  	- prints Var (with it's name) when in debug

INO_ROUTINE_PRINTVAR(Var)          	- when in debug, will make Var printable while INO_DEBUG_ROUTINE runs always, when user enters \pVar through ino::in

INO_ADJUST(Var)                    	- will open a dialogue in the serial monitor to adjust the value of Var when in debug

INO_RANGEADJUST(Var, Min, Max)     	- will open a dialogue in the serial monitor to adjust the value of Var in the boundaries of Min and Max when in debug

INO_SPECIFICADJUST(Var, VerifyFn)  	- when in debug, will open a dialogue in the serial monitor to adjust the value of Var and test it's new value with the given function VerifyFn, which takes the new value as const reference to type of Var (without reference) and returns true when new value is accepted

INO_ROUTINE_ADJUST(Var)            	- when in debug, will open a dialogue like in INO_ADJUST while INO_DEBUG_ROUTINE runs always, when user enters \aVar through ino::in

INO_ROUTINE_RANGEADJUST(Var)       	- when in debug, will open a dialogue like in INO_RANGEADJUST while INO_DEBUG_ROUTINE runs always, when user enters \aVar through ino::in

INO_ROUTINE_ADJUST(Var)            	- when in debug, will open a dialogue like in INO_SPECIFICADJUST while INO_DEBUG_ROUTINE runs always, when user enters \aVar through ino::in
