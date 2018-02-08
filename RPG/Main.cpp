
#include "Main.h"

Main::Main(int passedScreenWidth, int passedScreenHeight)
{
	properties = PropertiesParser::Read("GameConfig.properties");
	quit = properties.stringToBool(properties.getProperty("Quit"));;
	cameraX = 0;
	cameraY = 0;
	screenWidth = passedScreenWidth;
	screenHeight = passedScreenHeight;
	sdlSetup = new SDL_setup(&quit, screenWidth, screenHeight);
	forestArea = new Environment(sdlSetup, screenWidth, screenHeight, &cameraX, &cameraY);
	character = new MainCharacter(sdlSetup->getRenderer(), "data/character.png", (screenWidth) / 2, (screenHeight) / 2,100,120, &cameraX, &cameraY, 6, 4, CollisionRectangle((screenWidth) / 2, (screenHeight) / 2 *1.25, 100, 120*0.3));
	/*enemies.push_back(new Character(sdlSetup->getRenderer(), "data/enemyCharacter.png", 857, 126, 150, 150, &cameraX, &cameraY, 1, 1, CollisionRectangle(0, 0, 150, 150),1));
	enemies.push_back(new Character(sdlSetup->getRenderer(), "data/enemyCharacter.png", 1210, 423, 150,150, &cameraX, &cameraY, 1, 1, CollisionRectangle(0,0,150,150),2));
	enemies.push_back(new Character(sdlSetup->getRenderer(), "data/enemyCharacter.png", 747, 570, 150, 150, &cameraX, &cameraY, 1, 1, CollisionRectangle(0, 0, 150, 150),3));
	enemies.push_back(new Character(sdlSetup->getRenderer(), "data/enemyCharacter.png", 456, 984, 150, 150, &cameraX, &cameraY, 1, 1, CollisionRectangle(0, 0, 150, 150),4));
	enemies.push_back(new Character(sdlSetup->getRenderer(), "data/enemyCharacter.png", 140, 140, 150, 150, &cameraX, &cameraY, 1, 1, CollisionRectangle(0, 0, 150, 150),5));
	saveToFile();*/
	loadFromFile();
}
Main::Main()
{
	quit = false;
}
Main::~Main()
{
	delete sdlSetup;
	delete character;
	delete forestArea;
	delete character;
	for (vector<Character*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
		delete (*i);
	enemies.clear();
}
void Main::GameLoop(void)
{
	while (!quit && sdlSetup->getMainEvent()->type != SDL_QUIT)// if player dont push X
	{
		sdlSetup->beginRender();
		character->update(forestArea);
		forestArea -> drawBack();
		if(enemies.empty() == false)
			for (int i = enemies.size() - 1; i >= 0; i--)
			{
				enemies.at(i)->draw();
				if (character->checkIfEnemyisColidingCharacter(enemies.at(i)))
				{
					MainCharacter tempMainCharacter = *character;
					Character tempEnemy = *enemies.at(i);
		
					Fight *fight;
					fight = new Fight(sdlSetup, &tempMainCharacter, &tempEnemy, forestArea);
					while (fight->fightLoop());
					if (tempMainCharacter.getHealth() > 0 && tempEnemy.getHealth() == 0)
					{
						character->setExperience(tempEnemy.getLevel()*100);
						enemies.erase(enemies.begin() + i);
					}
					else if (tempEnemy.getHealth() > 0 && tempMainCharacter.getHealth() > 0)
						character->setHealth(tempMainCharacter.getHealth());
					character->brushAsideCharacter(5);
			}
		}
		character->drawStady();
		character->ResetKeyState();
		forestArea -> drawFront(character->getY());
		forestArea->update();
		sdlSetup -> endRender();
	}
}
void Main::saveToFile()
{
	string enemiesPosition = "";

	Properties properties;

	for (vector<Character*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
		enemiesPosition += to_string((*i)->getLevel()) + "@" + to_string((*i)->getX()) + "$" + to_string((*i)->getY()) + "$";

	properties.AddProperty("Enemies", enemiesPosition);
	PropertiesParser::Write("Map.properties", properties);

	cout << "Level saved!" << endl;
}
void Main::loadFromFile()
{
	Properties properties = PropertiesParser::Read("Map.properties");
	vector<string> enemy;
	string line = properties.getProperty("Enemies");
	char x[] = "$@";
	int y = sizeof(x);
	enemy = PropertiesParser::Split(line, x);
	properties = PropertiesParser::Read("GameConfig.properties");
	int enemyWidth = stoi(properties.getProperty("EnemyCharacterWidth"));
	int enemyHeight = stoi(properties.getProperty("EnemyCharacterHeight"));
	int enemyMapXFrmaes = stoi(properties.getProperty("EnemyCharacterMapXFrames"));
	int enemyMapYFrames = stoi(properties.getProperty("EnemyCharacterMapYFrames"));
	//current number of iteration
	int iteration = 0;
	//temp X for enemy
	int tempX = 0;
	//temp Y for enemy
	int tempY = 0;
	//temp lvl for enemy
	int tempLevel = 0;
	for (vector<string>::iterator i = enemy.begin(); i != enemy.end(); ++i)
	{
		if (iteration % 3 == 0 || iteration == 0) // every third (and 0) value is level 
			tempLevel = stoi((*i));
		else if ((iteration - 1)% 3 == 0 )	//second, fifth,eighth so if i substract 1 i will get (iteration starts with 0) 0,3,6,
			 tempX = stoi((*i));
		else
		{
			tempY = stoi((*i));
			enemies.push_back(new Character(sdlSetup->getRenderer(), "data/enemyCharacter.png", tempX, tempY, enemyWidth, 
											enemyHeight, &cameraX, &cameraY, enemyMapXFrmaes, enemyMapYFrames, 
											CollisionRectangle(0, 0, enemyWidth, enemyHeight), tempLevel));
		}
		iteration++;
	}
}
bool Main::getQuit(void)
{
	return quit;
}
void Main::setQuit(bool updateQuit)
{
	quit = updateQuit;
}