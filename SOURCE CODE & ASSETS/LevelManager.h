#pragma once

class LevelManager {
private:
	int currentLevel;
public:
	LevelManager();
	void Update();
	void NextLevel();
	int GetLevel();
};