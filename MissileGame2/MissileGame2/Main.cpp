//BECLE DENIS C00254311

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <time.h>

typedef struct Position
{
	int x;
	int y;

	void print()
	{
		std::cout << x << " " << y << std::endl;
	}
}Coordinates;

enum WarHead { EXPLOSIVE, NUCLEAR };

typedef struct Enemy
{
	Coordinates coordinates;
}Target;

struct Missile
{
	WarHead payload;

	Coordinates coordiantes;

	bool armed;

	void arm()
	{
		armed = !armed;
	}

	void update()
	{
		coordiantes.x += 1;
		coordiantes.y += 2;
	}
};

Missile createMissile()
{
	Missile missile;
	int userChoice;
	int sequenceNumber = rand() % 9000000 + 1000000;
	int launchCode = rand() % 90000 + 10000;
	int userCode;

	missile.armed = false;

	std::cout << std::endl;
	std::cout << "Select Payload : " << std::endl;
	std::cout << "0 - Explosive" << std::endl;
	std::cout << "1 - Nuclear" << std::endl;
	std::cin >> userChoice;
	if (userChoice == 0)
	{
		missile.payload = WarHead::EXPLOSIVE;
	}
	else
	{
		missile.payload = WarHead::NUCLEAR;
	}
	std::cout << "Enter Coordinates : " << std::endl;
	std::cout << "X = ";
	std::cin >> missile.coordiantes.x;
	std::cout << "Y = ";
	std::cin >> missile.coordiantes.y;



	system("CLS");
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::cout << "Missile Launch Sequence" << std::endl;
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::cout << "Sequence " << sequenceNumber << std::endl;
	std::cout << "Missile " << missile.payload << std::endl;
	std::cout << "Origin Coordinates ";
	missile.coordiantes.print();
	std::cout << "Launch Code = " << launchCode << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	system("CLS");
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::cout << "Missile Launch Sequence" << std::endl;
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::cout << "ENTER LAUNCH CODE : ";
	std::cin >> userCode;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	if (userCode == launchCode)
	{
		for (int i = 5; i >= 1; i--)
		{
			std::cout << i << "  ";
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		std::cout << "LAUNCHING" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		missile.arm();
	}
	else
	{
		std::cout << "Wrong Code " << std::endl;
	}

	return missile;
}

int fireMissile(Enemy enemy[], bool alive[])
{
	Missile missile = createMissile();
	int index = -1;
	while (missile.armed)
	{

		missile.update();
		std::cout << "Missile Position : ";
		missile.coordiantes.print();
		for (int i = 0; i < 5; i++)
		{
			if (missile.armed && alive[i])
			{
				if (missile.payload == WarHead::NUCLEAR && enemy[i].coordinates.x >= missile.coordiantes.x - 1 && enemy[i].coordinates.x <= missile.coordiantes.x + 1 && enemy[i].coordinates.x >= missile.coordiantes.x - 1 && enemy[i].coordinates.y <= missile.coordiantes.y + 1)
				{
					std::cout << "HIT" << std::endl;
					index = i;
					missile.arm();
				}
				else if (enemy[i].coordinates.x == missile.coordiantes.x && enemy[i].coordinates.y == missile.coordiantes.y)
				{
					std::cout << "HIT" << std::endl;
					index = i;
					missile.arm();
				}
			}

		}
		if (missile.armed && (missile.coordiantes.x > 100 || missile.coordiantes.y > 200))
		{
			std::cout << "OUT" << std::endl;
			missile.arm();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return index;
}

int play()
{
	//variables
	int ENEMY_NUMBER;
	int enemyAlive;
	Enemy enemy[5];
	bool alive[5];

	//enemy creation 
	srand(static_cast<unsigned int>(time(nullptr)));
	ENEMY_NUMBER = rand() % 4 + 1;
	enemyAlive = ENEMY_NUMBER;
	for (int i = 0; i < 5; i++)
	{
		if (i < ENEMY_NUMBER)
		{
			Enemy e;
			e.coordinates.x = rand() % 100 + 1;
			e.coordinates.y = rand() % 200 + 1;
			enemy[i] = e;
			alive[i] = true;
		}
		else
		{
			alive[i] = false;
		}
	}

	//game Loop 
	int userChoice = -1;
	do {
		system("CLS");
		std::cout << "---------------------------------------------------------------------" << std::endl;
		std::cout << "Game" << std::endl;
		std::cout << "---------------------------------------------------------------------\n" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << enemyAlive << " Enemy in the battlefield\n\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (enemyAlive > 0)
		{
			for (int j = 0; j < 5; j++)
			{
				if (alive[j])
				{
					std::cout << "ENEMY " << j + 1 << std::endl;
					std::cout << "Positon : " << enemy[j].coordinates.x << " " << enemy[j].coordinates.y << "\n";
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				}
			}
			std::cout << std::endl;
			std::cout << "Choose an option : " << std::endl;
			std::cout << "0 - Throw missile" << std::endl;
			std::cout << "1 - Exit and fail :p" << std::endl;
			std::cin >> userChoice;
			if (userChoice == 0)
			{
				int indexDestroyedEnemy = fireMissile(enemy,alive);
				if (indexDestroyedEnemy != -1)
				{
					std::cout << "You destroyed the enemy " << indexDestroyedEnemy + 1 << " in ";
					enemy[indexDestroyedEnemy].coordinates.print();
					std::cout << std::endl;
					alive[indexDestroyedEnemy] = false;
					enemyAlive--;
				}
				else
				{
					std::cout << "Your missile is Desactivated" << std::endl;
				}
				system("PAUSE");
			}
		}
		else
		{
			return 0;
		}
	} while (userChoice != 1);
	return 1;
}

int main()
{
	system("CLS");
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::cout << "Welcome to Den's Text Missile Game" << std::endl;
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::cout << "---------------------------------------------------------------------" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	play();
}