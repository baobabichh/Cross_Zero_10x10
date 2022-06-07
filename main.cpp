#include "Program.h"
#include <Windows.h>

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	srand(time(0));

	cz::Program *app = new cz::Program();

	while (app->running())
	{
		app->render();
	}
	delete app;
	exit(0);
}


