#pragma once
#ifndef INO_DEBUG_INCLUDED
#define INO_DEBUG_INCLUDED

#include "InoCore.h"

#define INO_DEBUG_ROUTINE() INO_IF_DEBUG(::ino::Debug::Routine())

#if INO_DEBUG

#include <Arduino.h>
#include "DynamicArray.h"

namespace ino {

	class Debug
	{
	public:
		using RoutineFnT = void(*)();
		using CallBackFnT = void(*)(const String&);

		class NewRoutine
		{
		private:
			int ID = -1;
			static int IDCount;
			RoutineFnT RoutineFn;

		public:
			NewRoutine() : ID(-1) {}
			NewRoutine(RoutineFnT RoutineFn);
			NewRoutine(const NewRoutine&) = delete;
			~NewRoutine();

			NewRoutine& operator=(const NewRoutine&) = delete;

			inline void CallRoutine() const { RoutineFn(); }

			void Activate();
			void Deactivate();
		};

		class NewUserRoutine
		{
		private:
			int ID = -1;
			static int IDCount;
			char TriggerChar;
			CallBackFnT CallBackFn;

		public:
			NewUserRoutine() : ID(-1) {}
			NewUserRoutine(char TriggerChar, CallBackFnT CallBackFn);
			NewUserRoutine(const NewUserRoutine&) = delete;
			~NewUserRoutine();

			NewUserRoutine& operator=(const NewUserRoutine&) = delete;

			inline char GetTriggerChar() const { return TriggerChar; }
			inline void CallRoutine(const String& Data) const { CallBackFn(Data); }

			void Activate();
			void Deactivate();
		};

		static DynamicArray<NewRoutine*> Routines;
		static DynamicArray<NewUserRoutine*> UserRoutines;
	private:

		Debug() = default;

	public:
		static void Routine();

	};

}

#endif

#endif