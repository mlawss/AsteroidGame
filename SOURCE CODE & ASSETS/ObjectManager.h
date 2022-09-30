#pragma once
#include <list>
#include "GameObject.h"

class ObjectManager {
private:
	std::list<GameObject*> pObjectList;
public:
	void Add(GameObject* pObject);
	void RenderAll();
	void UpdateAll(float frametime);
	void CheckAllCollisions();
	void DeleteInactiveObjects();
	void DeleteAll();
	std::list <GameObject*>& GetObjectList();
};