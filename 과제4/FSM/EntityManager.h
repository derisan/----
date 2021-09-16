// ***********************************************
// **            인공지능 과제4. FSM				**
// **            2016180007김명규               **
// ***********************************************

#pragma once

#include <unordered_map>

#include "BaseEntity.h"

#define EntityMgr EntityManager::Instance()



class EntityManager
{
public:
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;

	static EntityManager* Instance();

	void Update();

	void RegisterEntity(BaseEntity* entity);
	void RemoveEntity(BaseEntity* entity);
	BaseEntity* CreateEntity(int id);

	BaseEntity* GetEntityFromID(int id) const;
	std::string GetNameOfEntity(int id) const;

private:
	EntityManager() = default;

private:
	std::unordered_map<int, BaseEntity*> m_Entities;
};

