#include "InoCore.h"
#include "Log.h"

#include "Debug.h"

#if INO_DEBUG

namespace ino {
	namespace Log {

		DynamicArray<RoutineAdjust::AdjustVarBase*> RoutineAdjust::AdjustVariables;
		DynamicArray<RoutinePrintVar::PrintVarBase*> RoutinePrintVar::PrintVariables;
		
		RoutinePrintVar::PrintVarBase::PrintVarBase(const String& Name)
		{
			for (int C = 0; C < PrintVariables.GetLength(); C++)
			{
				if (PrintVariables[C]->GetName() == Name)
				{
					INO_ERROR("ino runtime debug error: ""ino::Log::RoutinePrintVar::PrintVarBase""s should be constructed with an already used ""Name""", endl);
					this->Name = "";
					return;
				}
			}
			this->Name = Name;
		}

		RoutineAdjust::AdjustVarBase::AdjustVarBase(const String& Name)
		{
			for (int C = 0; C < AdjustVariables.GetLength(); C++)
			{
				if (AdjustVariables[C]->GetName() == Name)
				{
					INO_ERROR("ino runtime debug error: ""ino::Log::RoutineAdjust::AdjustVarBase""s should be constructed with an already used ""Name""", endl);
					this->Name = "";
					return;
				}
			}
			this->Name = Name;
		}
		
		static Debug::NewUserRoutine DebugPrintVarRoutine('p', RoutinePrintVar::Routine);
		static Debug::NewUserRoutine DebugAdjustmentRoutine('a', RoutineAdjust::Routine);

	}
}

#endif
