#include "ObjectManager.h"

// adds an object to the list of objects
void ObjectManager::Add(GameObject* pObject)
{
	pObjectList.push_back(pObject);
}

// calls the render method of all objects in the list
void ObjectManager::RenderAll()
{
	for (GameObject*& pNextObject : pObjectList) {
		if (pNextObject->IsActive()) {
			pNextObject->Render();
		}
	}
}

// calls the update method of all objects
void ObjectManager::UpdateAll(float frametime)
{
	for (GameObject*& pNextObject : pObjectList) {
		if (pNextObject->IsActive()) {
			pNextObject->Update(frametime);
		}
	}
}

// calls the collision handler method of all objects
void ObjectManager::CheckAllCollisions() {
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;

	for (it1 = pObjectList.begin(); it1 != pObjectList.end(); it1++) {
		for (it2 = std::next(it1); it2 != pObjectList.end(); it2++) {
			if ((*it1)->GetShape().Intersects((*it2)->GetShape())) {
				(*it1)->HandleCollision((**it2));
				(*it2)->HandleCollision((**it1));
			}
		}
	}
}

// deletes all objects that have been set to inactive
void ObjectManager::DeleteInactiveObjects()
{
	for (GameObject*& pNext : pObjectList) {
		if (!pNext->IsActive()) {
			delete pNext;
			pNext = nullptr;
		}
	}

	// move any nullptrs to the end of pObjectList, then remove them so the pointers are deleted too
	auto it = std::remove(pObjectList.begin(), pObjectList.end(), nullptr);
	pObjectList.erase(it, pObjectList.end());
}

// deletes all objects and pointers
void ObjectManager::DeleteAll()
{
	for (GameObject*& pNextObject : pObjectList) {
		delete pNextObject;
		pNextObject = nullptr;
	}
	pObjectList.clear();
}

// returns pObjectList, for use in LevelManager class
std::list <GameObject*>& ObjectManager::GetObjectList()
{
	return pObjectList;
}
