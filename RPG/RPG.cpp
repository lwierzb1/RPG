#include "stdafx.h"
#include "Main.h"
class Ksztalt
{
public:
	virtual void obliczPole() = 0;
};
class Kwadrat : public Ksztalt
{
	float r;
public :
	virtual void obliczPole()
	{
		std::cout << "elo" << std::endl;
	}

};
class Kolo :public Ksztalt
{
	float x;
public:
	virtual void obliczPole()
	{
		std::cout << "HAJ";
	}
};
int main(int argc, char *argv[])
{
	Ksztalt *wsk;
	Kwadrat k;
	Kolo i;
	wsk = &k;
	std::string x = typeid(*wsk).name();
	std::cout << x;
	//while (1);


		Main *rpg = new Main(WINDOW_WIDTH, WINDOW_HEIGHT);
		
		rpg->GameLoop();

		delete rpg;

		return 0;
}

