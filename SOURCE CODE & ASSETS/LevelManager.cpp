#include "LevelManager.h"
#include "gamecode.h"

// initialise current level value
LevelManager::LevelManager()
{
	currentLevel = 1;
}

// method called every frame
void LevelManager::Update()
{
	// if only object left is spaceship, end the level and progress
	if (Game::instance.GetObjectManager().GetObjectList().size() == 1) {
		NextLevel();
	}

	// draw int in top left showing level number
	MyDrawEngine::GetInstance()->WriteInt(50, 50, currentLevel, MyDrawEngine::GREEN);
}

// method that calls when the level ends
// and goes to the next level
void LevelManager::NextLevel()
{
	// delete all objects on screen
	Game::instance.GetObjectManager().DeleteAll();

	// increment the level number by 1
	currentLevel++;
	// restart the game with new level number
	Game::instance.StartOfGame();
}

// getter method to allow StartOfGame() to get the level number
int LevelManager::GetLevel()
{
	return currentLevel;
}
