#include "Window.h"

int main(int argc, char** argv[])
{
	Window window("Window Title", {1280, 720});
	while (window.isOpen())
	{
		window.update();
		window.clear();
		window.display();
	}
}
