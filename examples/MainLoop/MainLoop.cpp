/*
The MIT License

Copyright (c) 2007-2010 Aidin Abedi http://code.google.com/p/shinyprofiler/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "Shiny.h"

#ifdef _WIN32
#include <Windows.h> // Sleep
#else // assume POSIX
#include <unistd.h> // usleep
#endif


/*---------------------------------------------------------------------------*/

void millisleep(unsigned int milliseconds) {
#ifdef _WIN32
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}


/*---------------------------------------------------------------------------*/

PROFILE_SHARED_DEFINE(Physics);

void DoPhysicsSimulation() {
	PROFILE_SHARED_BLOCK(Physics);

	// do stuff
}

void CheckPhysicsRaycast() {
	PROFILE_SHARED_BEGIN(Physics);

	// do stuff

	PROFILE_END();
}


/*---------------------------------------------------------------------------*/

PROFILE_SHARED_DEFINE(Animations);

void UpdateAllCharacters() {
	PROFILE_BLOCK(Gamelogic); // (only supported in c++)

	PROFILE_BEGIN(AI);
		CheckPhysicsRaycast();

		PROFILE_SHARED_BEGIN(Animations);
		// do stuff
		PROFILE_END();

	PROFILE_END();

	PROFILE_BEGIN(Player);
		// do stuff

		PROFILE_SHARED_BEGIN(Animations);
		// do stuff
		PROFILE_END();
	PROFILE_END();

}


/*---------------------------------------------------------------------------*/

void DrawWorldObjects() {
	for (int i = 0; i < 10; i++) {
		PROFILE_BLOCK(Graphics); // (only supported in c++)

		// do stuff
	}
}


/*---------------------------------------------------------------------------*/


int main() {
	int loops = 100;

	while (loops--) {
		UpdateAllCharacters();
		DoPhysicsSimulation();
		DrawWorldObjects();

		PROFILE_UPDATE(); // update all profiles
	}

	PROFILE_OUTPUT(NULL); // print to terminal

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}
