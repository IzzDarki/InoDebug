---------------------------------------------------------------
#                         Ino Library                         #
#                            Debug                            #
---------------------------------------------------------------

Preprocessor definitions (users can modify)

INO_LOG_STATE_ALL       - default: defined in debug, always undefined in release    - when defined everything is going to be logged

INO_LOG_STATE_WARNING   - default: undefined, always undefined in release           - when defined warnings, errors and fatal errors are going to be logged

INO_LOG_STATE_ERROR     - default: undefined, always undefined in release           - when defined errors and fatal errors are going to be logged

INO_LOG_STATE_FATAL     - default: undefined, always undefined in release           - when defined just fatal errors are going to be logged

INO_LOG_STATE_NONE      - default: undefined in debug, defined in release           - when defined logging is off


---------------------------------------------------------------

Preprocessor macros

INO_DEBUG_ROUTINE()                 - does nothing in release, should run as continuously as possible in debug

INO_IF_NOTE(x)                      - will expand to x when notes are going to be logged

INO_IF_WARNING(x)                   - will expand to x when warnings are going to be logged

INO_IF_ERROR(x)                     - will expand to x when errors are going to be logged

INO_IF_FATAL(x)                     - will expand to x when fatal errors are going to be logged

INO_NOTE(...)                       - will log all arguments when notes are going to be logged

INO_WARNING(...)                    - will log all arguments when warnings are going to be logged

INO_ERROR(...)                      - will log all arguments when errors are going to be logged

INO_FATAL(...)                      - will log all arguments when fatal errors are going to be logged

INO_PRINTVAR(Var)                   - prints Var (with it's name) when in debug

INO_ROUTINE_PRINTVAR(Var)           - when in debug, will make Var printable while INO_DEBUG_ROUTINE runs always, when user enters \pVar through ino::in

INO_ADJUST(Var)                     - will open a dialogue in the serial monitor to adjust the value of Var when in debug

INO_RANGEADJUST(Var, Min, Max)      - will open a dialogue in the serial monitor to adjust the value of Var in the boundaries of Min and Max when in debug

INO_SPECIFICADJUST(Var, VerifyFn)   - when in debug, will open a dialogue in the serial monitor to adjust the value of Var and test it's new value with the given function VerifyFn, which takes the new value as const reference to type of Var (without reference) and returns true when new value is accepted

INO_ROUTINE_ADJUST(Var)             - when in debug, will open a dialogue like in INO_ADJUST while INO_DEBUG_ROUTINE runs always, when user enters \aVar through ino::in

INO_ROUTINE_RANGEADJUST(Var)        - when in debug, will open a dialogue like in INO_RANGEADJUST while INO_DEBUG_ROUTINE runs always, when user enters \aVar through ino::in

INO_ROUTINE_ADJUST(Var)             - when in debug, will open a dialogue like in INO_SPECIFICADJUST while INO_DEBUG_ROUTINE runs always, when user enters \aVar through ino::in
