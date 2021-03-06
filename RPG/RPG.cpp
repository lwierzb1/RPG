#include "stdafx.h"
#include "Main.h"
int main(int argc, char *argv[])
{
		Properties properties = PropertiesParser::Read("GameConfig.properties");
		Main *rpg = new Main(stoi(properties.getProperty("GameWindowWidth")), stoi(properties.getProperty("GameWindowHeight")));
		
		rpg->GameLoop();

		delete rpg;

		return 0;
}

