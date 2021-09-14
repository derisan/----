#pragma once

enum eEntityID
{
	MinerBob,
	HousewifeElsa,
	DoctorSmith,
	TellerJane,
	BarkeeperJohn
};

enum class eLocation
{
	Shack,
	Goldmine,
	Bank,
	Saloon,
	Hospital
};

class BaseEntity
{
public:
	BaseEntity(int id);
	virtual ~BaseEntity() = default;

	virtual void Update() = 0;

	int GetID() const { return mID; }
	void SetID(int id) { mID = id; }

private:
	int mID;
};