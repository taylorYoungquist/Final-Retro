#include "AIE.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "main.h"
#include "Bullets.h"
#include "Enemies.h"
#include "Player.h"
#include "Time.h"


using namespace std;

//functions
void CollisionCheck();
void AddBullets(float a_deltaTime);
void MoveBullets(float a_deltaTime);
void BulletCollideEnemy();
void AddEnemies(float a_deltaTime);
void MoveEnemies(float a_deltaTime);
void WriteHighScore();
void LoadHighScore();
void GameUI();
void UpdateMainMenu();
void UpdateHowToPlay();
void UpdateGamePlay();
void UpdateSplashScreen();
//Globals
const int screenWidth = 600;
const int screenHeight = 800;
const char* gameTitle = "Retro Game";
float reloadTime, currentReloadTime;
float spawnTime, currentSpawnTime;


struct SplashScreen
{
	unsigned int splashID;
	float width;
	float height;
	float x, y;

	void SetSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
	}

	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}
};
SplashScreen splash;

Player player;

std::vector<Enemies> enemy;

std::vector<Bullets> bullet;
//highscore variable declaration
int mHighScore;
//enum
enum GAMESTATES
{
	SPLASHSCREEN,
	MAINMENU,
	HOWTOPLAY,
	GAMEPLAY,
	HIGHSCORES,
	END
};
GAMESTATES currentState = SPLASHSCREEN;



int main( int argc, char* argv[] )
{	
	Initialise(screenWidth, screenHeight, false, gameTitle);
	bool runGame = true;
    
	player.Init();
    SetBackgroundColour(SColour(0, 0, 0, 255));
	//Timer
	srand(time(NULL));
	reloadTime = .15f;
	currentReloadTime = reloadTime;
	spawnTime = .5f;
	currentSpawnTime = spawnTime;

	//splash screen
	splash.SetPosition(340, 450);
	splash.splashID = CreateSprite("./images/SplashScreen.png", screenWidth, screenHeight, true);
	MoveSprite(splash.splashID, 300, 400);
    //Game Loop
    do
    {
        ClearScreen();
		float deltaTime = GetDeltaTime();
		//states manager
		switch (currentState)
		{
		case SPLASHSCREEN:
			UpdateSplashScreen();
			if (IsKeyDown(32))
			{
				currentState = MAINMENU;
			}
			if (IsKeyDown(256))
			{
				runGame = false;
			}
			break;
		case MAINMENU:
			UpdateMainMenu();
			if (IsKeyDown(256))
			{
				runGame = false;
			}
			break;
		case HOWTOPLAY:
			UpdateHowToPlay();
			if (IsKeyDown(256))
			{
				runGame = false;
			}
			break;
		case HIGHSCORES:
		{
			DrawString("HIGH SCORE", screenWidth * .5f - 100.f, screenHeight *0.75f);
			char buff[30];	
			DrawString(itoa(mHighScore, buff, 10), screenWidth *.5f - 25, screenHeight *.66f);		
			DrawString("Q to main menu", screenWidth *.375f, 50);
			if (IsKeyDown('Q'))
			{
				currentState = MAINMENU;
			}
			if (IsKeyDown(256))
			{
				runGame = false;
			}
		}
			break;
		case GAMEPLAY:
			UpdateGamePlay();
			GameUI();
			AddBullets(deltaTime);
			MoveBullets(deltaTime);
			BulletCollideEnemy();

			//player functions
			player.MovementKeys(deltaTime);

			//enemy functions
			AddEnemies(deltaTime);
			MoveEnemies(deltaTime);
			CollisionCheck();
			if(IsKeyDown(256))
			{
				runGame = false;
			}
			break;
		default:
			break;
		}
	} while (!FrameworkUpdate() && runGame);

    Shutdown();

    return 0;
}


void UpdateMainMenu()
{
	//Giving the options
	DrawString("Play(P)", screenWidth *.375f, 500);
	DrawString("How to Play(Enter)", screenWidth *.375f, 400);
	DrawString("Highscores(H)", screenWidth *.375f, 300);
	DrawString("Quit(Esc)", screenWidth * .375f, 200);
	if (IsKeyDown('P'))
	{
		currentState = GAMEPLAY;
	}
	if (IsKeyDown('H'))
	{
		currentState = HIGHSCORES;
	}
	if (IsKeyDown(257))
	{
		currentState = HOWTOPLAY;
	}
}

void UpdateHowToPlay()
{
	//Need to Draw all the instructions.
	DrawString("HOW TO PLAY", screenWidth * .375f, 650);
	DrawString("The objective of this game is to kill as many", 25, 600);
	DrawString("enemies as possible without dying. You will gain", 25, 550);
	DrawString("50 points for each enemy you mangage to kill!", 25, 500);
	DrawString("CONTROLS", screenWidth * .375f, 400);
	DrawString("Player:", screenWidth * .38f, 350);
	DrawString("Left: A", screenWidth * .4f, 300);
	DrawString("Right: D", screenWidth * .4f, 250);
	DrawString("GOOD LUCK", screenWidth * .375f, 150);
	DrawString("Press Q to go back....", screenWidth * .33f, 50);
	//Need to return to the main menu from here to be able to access the game
	if (IsKeyDown('Q'))
	{
		currentState = MAINMENU;
	}
}

void GameUI()
{
	char playerScore[10];
	char buff[30];
	player.GetScore(playerScore);

	if (player.score >= mHighScore)
	{
		mHighScore = player.score;
	}

	DrawString("HIGHSCORE:", screenWidth * .05f, 875);
	DrawString(itoa(mHighScore, buff, 10), screenWidth * .4f, 875);
	DrawString("YOUR SCORE:", screenWidth * .05f, 850);
	DrawString(playerScore, screenWidth * .4f, 850);
}

void UpdateGamePlay()
{
	float delta = GetDeltaTime();
	MoveSprite(player.player, player.x, player.y);
	DrawSprite(player.player);
}

void LoadHighScore()
{
	fstream file;
	file.open("file.txt", ios::in);
	char buffer[10];
	file.getline(buffer, 10);
	mHighScore = atoi(buffer);
	file.close();
}

void WriteHighScore()
{
	fstream file;
	file.open("file.txt", ios::out);
	file << mHighScore;
	file.close();
}

void UpdateSplashScreen()
{
	DrawSprite(splash.splashID);
}

void AddBullets(float a_deltaTime)
{
	if (IsKeyDown(32))
	{
		if (currentReloadTime <= 0.f)
		{
			//left
			bullet.emplace_back();
			bullet.back().spriteID = CreateSprite("./images/bullets.png", bullet.back().width, bullet.back().height, true);
			bullet.back().x = player.x - 12.f;
			bullet.back().y = player.y + 10.f;

			//right
			bullet.emplace_back();
			bullet.back().spriteID = CreateSprite("./images/bullets.png", bullet.back().width, bullet.back().height, true);
			bullet.back().x = player.x + 12.f;
			bullet.back().y = player.y + 10.f;
			currentReloadTime = reloadTime;
		}
		else
		{
			currentReloadTime -= a_deltaTime;
		}
	}
}

void MoveBullets(float a_deltaTime)
{
	for (int i = 0; i < bullet.size(); i++)
	{
		bullet[i].y += 4.5f + a_deltaTime;
		MoveSprite(bullet[i].spriteID, bullet[i].x, bullet[i].y);
		DrawSprite(bullet[i].spriteID);
	}
}

void AddEnemies(float a_deltaTime)
{
	if (currentSpawnTime <= 0.f)
	{
		enemy.emplace_back();
		enemy.back().x += rand() % 550;

		currentSpawnTime = spawnTime;
	}
	else
	{
		currentSpawnTime -= a_deltaTime;
	}
}

void MoveEnemies(float a_deltaTime)
{
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i].Movement(a_deltaTime);
	}
}

void CollisionCheck()
{
	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].Collide() == true)
		{
			currentState = MAINMENU;
			WriteHighScore();
		}
	}
}

void BulletCollideEnemy()
{
	for (int i = 0; i < enemy.size(); i++)
	{
		for (int j = 0; j < bullet.size(); j++)
		{
			if (bullet[j].x >= enemy[i].x - enemy[i].width * .5f &&
				bullet[j].x <= enemy[i].x + enemy[i].width * .5f &&
				bullet[j].y >= enemy[i].y - enemy[i].height * .5f &&
				bullet[j].y <= enemy[i].y + enemy[i].height *.5f)
			{
				bullet[j].x += 500.f;
				enemy[i].x += 500.f;
				player.AddScore(50);
			}
		}
	}
}