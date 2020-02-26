#include "InoCore.h"

#if INO_DEBUG

#include "Debug.h"
#include "Log.h"
#include "IOStream.h"

namespace ino {

	int Debug::NewRoutine::IDCount = 0;
	int Debug::NewUserRoutine::IDCount = 0;

	DynamicArray<Debug::NewRoutine*> Debug::Routines;
	DynamicArray<Debug::NewUserRoutine*> Debug::UserRoutines;

	Debug::NewRoutine::NewRoutine(RoutineFnT RoutineFn) : RoutineFn(RoutineFn)
	{
		Activate();
	}

	Debug::NewRoutine::~NewRoutine()
	{
		Deactivate();
	}

	void Debug::NewRoutine::Activate()
	{
		if (ID == -1)
		{
			ID = IDCount++;
			Routines.PushBack(this);
		}
	}

	void Debug::NewRoutine::Deactivate()
	{
		if (ID != -1)
		{
			int C = 0;
			while(Routines[C]->ID != ID)
				C++;
			Routines.Erase(C, 1);
			ID = -1;
		}
	}

	Debug::NewUserRoutine::NewUserRoutine(char TriggerChar, CallBackFnT CallBackFn) : TriggerChar(TriggerChar), CallBackFn(CallBackFn)
	{
		Activate();
	}

	Debug::NewUserRoutine::~NewUserRoutine()
	{
		Deactivate();
	}

	void Debug::NewUserRoutine::Activate()
	{
		Serial.begin(9600);
		if (ID == -1)
		{
			for (auto& UserRoutine : UserRoutines)

			ID = IDCount++;
			UserRoutines.PushBack(this);
		}
	}

	void Debug::NewUserRoutine::Deactivate()
	{
		if (ID != -1)
		{
			int C = 0;
			while(UserRoutines[C]->ID != ID)
				C++;
			Routines.Erase(C, 1);
			ID = -1;
		}
	}

	void Debug::Routine()
	{
	#ifdef INO_PLATFORMIOIN
		in.Run();
	#endif
		for (int C = 0; C < Routines.GetLength(); C++)
			Routines[C]->CallRoutine();
		//This just works, when there are no other characters before '\\'
		//possible solution: Get all of in and put everything back, that is not a UserRoutine call (add functionality for InStream to put sth back for Debug mode) 
		if (in.Available() && in.Peek() == '\\')
		{
			String Data;
			in >> Data;
			if (Data.length() > 1)
			{
				const char Trigger = Data[1];
				Data.remove(0, 2);
				for (int C = 0; C < UserRoutines.GetLength(); C++)
				{
					if (Trigger == UserRoutines[C]->GetTriggerChar())
						UserRoutines[C]->CallRoutine(Data);
				}
			}
		}
	}

}

#endif
