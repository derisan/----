// ***********************************************
// **            �ΰ����� ����4. FSM				**
// **            2016180007����               **
// ***********************************************

#include <algorithm>
#include <cassert>

#include "EntityManager.h"
#include "Miner.h"
#include "Housewife.h"
#include "Doctor.h"
#include "Teller.h"
#include "Barkeeper.h"

EntityManager* EntityManager::Instance()
{
	static EntityManager instance;
	return &instance;
}

void EntityManager::Update()
{
	for (auto& entity : m_Entities)
	{
		entity.second->Update();
	}
}

void EntityManager::RegisterEntity(BaseEntity* entity)
{
	if (entity)
	{
		m_Entities[entity->GetID()] = entity;
	}
}

void EntityManager::RemoveEntity(BaseEntity* entity)
{
	int targetID = entity->GetID();

	auto iter = m_Entities.find(targetID);
	if (iter != m_Entities.end())
	{
		m_Entities.erase(targetID);
	}
}

BaseEntity* EntityManager::CreateEntity(int id)
{
	BaseEntity* entity = nullptr;

	switch (id)
	{
	case MinerBob:
		entity = new Miner(id);
		RegisterEntity(entity);
		return entity;
		break;

	case HousewifeElsa:
		entity = new Housewife(id);
		RegisterEntity(entity);
		return entity;
		break;

	case DoctorSmith:
		entity = new Doctor(id);
		RegisterEntity(entity);
		return entity;
		break;

	case TellerJane:
		entity = new Teller(id);
		RegisterEntity(entity);
		return entity;
		break;

	case BarkeeperJohn:
		entity = new Barkeeper(id);
		RegisterEntity(entity);
		return entity;
		break;

	default:
		assert(nullptr && "Error. Unknown entity ID.");
	}

	return nullptr;
}

BaseEntity* EntityManager::GetEntityFromID(int id) const
{
	auto iter = m_Entities.find(id);
	if (iter != m_Entities.end())
	{
		return iter->second;
	}
	else
	{
		return nullptr;
	}
}

std::string EntityManager::GetNameOfEntity(int id) const
{
	switch (id)
	{
	case MinerBob:
		return "���� ��";
		break;

	case HousewifeElsa:
		return "�ֺ� ����";
		break;

	case DoctorSmith:
		return "�ǻ� ���̽�";
		break;

	case TellerJane:
		return "����� ����";
		break;

	case BarkeeperJohn:
		return "�������� ��";
		break;

	default:
		assert(nullptr && "Error. Unknown entity ID.");
	}

	return "";

}
