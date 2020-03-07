#pragma once
#ifndef INO_LOG_INCLUDED
#define INO_LOG_INCLUDED

#include "InoCore.h"
#include "std/TypeTraits.h"
#include "IOStream.h"
#include "StringStream.h"
#include "Debug.h"
#include "DynamicArray.h"
#include "MillisTimer.h"

#include <Arduino.h>

#if INO_DEBUG
	#if !defined(INO_LOG_STATE_ALL) && !defined(INO_LOG_STATE_WARNING) && !defined(INO_LOG_STATE_ERROR) && !defined(INO_LOG_STATE_FATAL) && !defined(INO_LOG_STATE_NONE)
		#define INO_LOG_STATE_ALL
	#endif
#else
		#undef INO_LOG_STATE_ALL
		#undef INO_LOG_STATE_WARNING
		#undef INO_LOG_STATE_ERROR
		#undef INO_LOG_STATE_FATAL
		
		#define INO_LOG_STATE_NONE
#endif

#if defined(INO_LOG_STATE_ALL)
	#define INO_IF_NOTE(...) __VA_ARGS__
#else
	#define INO_IF_NOTE(...)
#endif

#if defined(INO_LOG_STATE_ALL) || defined(INO_LOG_STATE_WARNING)
	#define INO_IF_WARNING(...) __VA_ARGS__
#else
	#define INO_IF_WARNING(...)
#endif

#if defined(INO_LOG_STATE_ALL) || defined(INO_LOG_STATE_WARNING) || defined(INO_LOG_STATE_ERROR)
	#define INO_IF_ERROR(...) __VA_ARGS__
#else
	#define INO_IF_ERROR(...)
#endif

#if defined(INO_LOG_STATE_ALL) || defined(INO_LOG_STATE_WARNING) || defined(INO_LOG_STATE_ERROR) || defined(INO_LOG_STATE_FATAL)
	#define INO_IF_FATAL(...) __VA_ARGS__
#else
	#define INO_IF_FATAL(...)
#endif

#define INO_NOTE(...) INO_IF_NOTE(::ino::Log::Print("Note: ", __VA_ARGS__))
#define INO_WARNING(...) INO_IF_WARNING(::ino::Log::Print("Warning: ", __VA_ARGS__))
#define INO_ERROR(...) INO_IF_ERROR(::ino::Log::Print("Error: ", __VA_ARGS__))
#define INO_FATAL(...) INO_IF_FATAL(::ino::Log::Print("Fatal: ", __VA_ARGS__))

#define INO_NOTE_ONCE(...) INO_IF_NOTE({ static bool FirstRunVariable = true; if (FirstRunVariable) { FirstRunVariable = false; INO_NOTE(__VA_ARGS__); } })
#define INO_WARNING_ONCE(...) INO_IF_WARNING({ static bool FirstRunVariable = true; if (FirstRunVariable) { FirstRunVariable = false; INO_WARNING(__VA_ARGS__); } })
#define INO_ERROR_ONCE(...) INO_IF_ERROR({ static bool FirstRunVariable = true; if (FirstRunVariable) { FirstRunVariable = false; INO_ERROR(__VA_ARGS__); } })
#define INO_FATAL_ONCE(...) INO_IF_FATAL({ static bool FirstRunVariable = true; if (FirstRunVariable) { FirstRunVariable = false; INO_FATAL(__VA_ARGS__); } })

#ifndef INO_LOG_CYCLE_DURATION
#define INO_LOG_CYCLE_DURATION 1000
#endif

#define INO_NOTE_CYCLE(...) INO_IF_NOTE({ static ::ino::MillisTimer Timer(INO_LOG_CYCLE_DURATION); if (Timer.Cycle()) { INO_NOTE(__VA_ARGS__); } })
#define INO_WARNING_CYCLE(...) INO_IF_WARNING({ static ::ino::MillisTimer Timer(INO_LOG_CYCLE_DURATION); if (Timer.Cycle()) { INO_WARNING(__VA_ARGS__); } })
#define INO_ERROR_CYCLE(...) INO_IF_ERROR({ static ::ino::MillisTimer Timer(INO_LOG_CYCLE_DURATION); if (Timer.Cycle()) { INO_ERROR(__VA_ARGS__); } })
#define INO_FATAL_CYCLE(...) INO_IF_FATAL({ static ::ino::MillisTimer Timer(INO_LOG_CYCLE_DURATION); if (Timer.Cycle()) { INO_FATAL(__VA_ARGS__); } })

#define INO_ASSERT(Assertion, ...) INO_IF_ERROR(if (!(Assertion)) ::ino::Log::Print("Assertion error: ", __VA_ARGS__))

#define INO_PRINTVAR(Variable) INO_IF_DEBUG(::ino::Log::PrintVar(Variable, #Variable))

#define INO_ROUTINE_PRINTVAR(Variable) INO_IF_DEBUG(::ino::Log::RoutinePrintVar::PrintVar<decltype(Variable)> Variable##PrintRoutine_generated_by_call_to_macro_INO_ROUTINE_PRINTVAR(Variable, #Variable));

#define INO_ADJUST(Variable) INO_IF_DEBUG(::ino::Log::Adjust(Variable, #Variable))
#define INO_RANGEADJUST(Variable, Minimum, Maximum) INO_IF_DEBUG(::ino::Log::Adjust(Variable, Minimum, Maximum, #Variable))
#define INO_SPECIFICADJUST(Variable, VerifyFunc) INO_IF_DEBUG(::ino::Log::Adjust(Variable, VerifyFunc, #Variable))

#define INO_ROUTINE_ADJUST(Variable) INO_IF_DEBUG(static ino::Log::RoutineAdjust::AdjustVar<decltype(Variable)> Variable##AdjustRoutine_generated_by_call_to_macro_INO_ROUTINE_ADJUST(Variable, #Variable))
#define INO_ROUTINE_RANGEADJUST(Variable, Minimum, Maximum) INO_IF_DEBUG(static ino::Log::RoutineAdjust::RangeAdjustVar<decltype(Variable)> Variable##AdjustRoutine_generated_by_call_to_macro_INO_ROUTINE_RANGEADJUST(Variable, Minimum, Maximum, #Variable))
#define INO_ROUTINE_SPECIFICADJUST(Variable, VerifyFunc) INO_IF_DEBUG(static ino::Log::RoutineAdjust::SpecificAdjustVar<decltype(Variable)> Variable##AdjustRoutine_generated_by_call_to_macro_INO_ROUTINE_SPECIFICADJUST(Variable, VerifyFunc, #Variable))

#if INO_DEBUG

namespace ino {
	namespace Log {

		inline void Print() {}

		template <typename T, typename... Ts>
		void Print(T&& OutFirst, Ts&&... OutOthers)
		{
			out << std::forward<T>(OutFirst);
			Print(std::forward<Ts>(OutOthers)...);
		}

		template <typename T>
		void PrintVar(const T& Variable, const char* Name)
		{
			out << "Variable " << Name << ": " << Variable;
		}

		template <typename T>
		void Adjust(T& Variable, const char* VariableName = nullptr)
		{
#ifdef INO_OUTSTREAM_CURSORTRACKER
			if (out.GetCursor().Num > 0)
				out << endl;
#endif
			out << "-------------------------------" << endl
					<< "Adjustment";
			if (VariableName)
				out << " of " << VariableName;
			out << ": ";

			String Buffer;
			in >> Buffer;

			if (Buffer != "\\")
			{
				StringStream SStream(std::move(Buffer));
				SStream >> Variable;
				out << Variable << endl;
			}
			out << "-------------------------------" << endl;
		}

		template <typename T>
		void Adjust(T& Variable, const typename std::remove_reference<T>::type& Min, const typename std::remove_reference<T>::type& Max, const char* VariableName = nullptr)
		{
#ifdef INO_OUTSTREAM_CURSORTRACKER
			if (out.GetCursor().Num > 0)
				out << endl;
#endif
			if (Min > Max)
			{
				if (VariableName != nullptr)
					INO_ERROR("ino runtime debug error: ", "Adjustment of ", VariableName, " is impossible, because allowed minimum is greater than allowed maximum.", endl);
				else
					INO_ERROR("ino runtime debug error: ", "Adjustment is impossible, because allowed minimum is greater than allowed maximum.", endl);
			}
			
			out << "-------------------------------" << endl;
			while (true)
			{
				out << "Adjustment ";
				if (VariableName)
					out << "of " << VariableName;
				out << " (min: " << Min << ", max: " << Max << "): ";

				String Buffer;
				in >> Buffer;

				if (Buffer != "\\")
				{
					StringStream SStream(std::move(Buffer));
					SStream >> Variable;
					out << Variable << endl;
				}
				else
					break;
				if (Variable < Min || Variable > Max)
					out << "The entered data is not within given range." << endl;
				else
					break;	
			}
			out << "-------------------------------" << endl;
		}

		template <typename T>
		void Adjust(T& Variable, bool(*VerifyEntry)(const typename std::remove_reference<T>::type&), const char* VariableName = nullptr)
		{
#ifdef INO_OUTSTREAM_CURSORTRACKER
			if (out.GetCursor().Num > 0)
				out << endl;
#endif
			out << "-------------------------------" << endl;
			while (true)
			{
				out << "Specific adjustment";
				if (VariableName)
					out << " of " << VariableName;
				out << ": ";
				
				String Buffer;
				in >> Buffer;

				if (Buffer != "\\")
				{
					StringStream SStream(std::move(Buffer));
					SStream >> Variable;
					out << Variable << endl;
				}
				else
				{
					out << Variable << endl;
					break;
				}
				if (VerifyEntry(Variable))
					break;
				else
					out << "The entered data is not allowed." << endl;
			}
			out << "-------------------------------" << endl;
		}

		class RoutinePrintVar
		{
		private:
			class PrintVarBase
			{
			protected:
				String Name;
				PrintVarBase(const String& Name);
			
			public:
				inline const String& GetName() { return Name; } 
				virtual void Print() = 0;
			};

			static DynamicArray<PrintVarBase*> PrintVariables;

		public:
			template <typename T>
			class PrintVar : public PrintVarBase
			{
			private:
				const T& Var;

			public:
				PrintVar(T& Var, const String& Name) : PrintVarBase(Name), Var(Var)
				{
					PrintVariables.PushBack(this);
				}
				void Print() override { ::ino::Log::PrintVar(Var, Name.c_str()); }
			};

		public:
			static void Routine(const String& Name)
			{
				for (int C = 0; C < PrintVariables.GetLength(); C++)
				{
					if (PrintVariables[C]->GetName() == Name)
					{
						PrintVariables[C]->Print();
						break;
					}
				}
			}

		};

		class RoutineAdjust
		{
		private:
			class AdjustVarBase
			{
			protected:
				String Name;
				AdjustVarBase(const String& Name);
			
			public:
				inline const String& GetName() { return Name; } 
				virtual void Adjust() = 0;
			};

			static DynamicArray<AdjustVarBase*> AdjustVariables;

		public:
			template <typename T>
			class AdjustVar : public AdjustVarBase
			{
			private:
				T& Var;

			public:
				AdjustVar(T& Var, const String& Name) : AdjustVarBase(Name), Var(Var)
				{
					AdjustVariables.PushBack(this);
				}
				void Adjust() override { ::ino::Log::Adjust(Var, Name.c_str()); }
			};

			template <typename T>
			class RangeAdjustVar : public AdjustVarBase
			{
			private:
				T& Var;
				using RangeType = const typename std::remove_reference<T>::type;
				RangeType Min;
				RangeType Max;

			public:
				RangeAdjustVar(T& Var, const RangeType& Min, const RangeType& Max, const String& Name) : AdjustVarBase(Name), Var(Var), Min(Min), Max(Max)
				{
					AdjustVariables.PushBack(this);
				}
				void Adjust() override { ::ino::Log::Adjust(Var, Min, Max, Name.c_str()); }
			};

			template <typename T>
			class SpecificAdjustVar : public AdjustVarBase
			{
			private:
				T& Var;
				using VerifyFnType = bool(*)(const typename std::remove_reference<T>::type&);
				VerifyFnType VerifyEntry;

			public:
				SpecificAdjustVar(T& Var, VerifyFnType VerifyEntry, const String& Name) : AdjustVarBase(Name), Var(Var), VerifyEntry(VerifyEntry)
				{
					AdjustVariables.PushBack(this);
				}
				void Adjust() override { ::ino::Log::Adjust(Var, VerifyEntry, Name.c_str()); }
			};

		public:
			static void Routine(const String& Name)
			{
				for (int C = 0; C < AdjustVariables.GetLength(); C++)
				{
					if (AdjustVariables[C]->GetName() == Name)
					{
						AdjustVariables[C]->Adjust();
						break;
					}
				}
			}
		};

	}
}

#endif

#endif
