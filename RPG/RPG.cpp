#include "stdafx.h"
#include "Main.h"
int main(int argc, char *argv[])
{
		Main *rpg = new Main(WINDOW_WIDTH, WINDOW_HEIGHT);
		
		rpg->GameLoop();

		delete rpg;

		return 0;
}

