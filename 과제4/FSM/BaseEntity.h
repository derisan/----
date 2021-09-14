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

	eLocation GetLocation() const { return mLocation; }
	void SetLocation(eLocation location) { mLocation = location; }

private:
	int mID;
	eLocation mLocation;
};