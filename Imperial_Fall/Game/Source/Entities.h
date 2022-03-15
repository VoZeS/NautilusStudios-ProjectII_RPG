#ifndef __ENTITIES_H__
#define __ENTITIES_H__

#include "Module.h"
#include "Physics.h"
#include "Animation.h"
#include "DynArray.h"
#include "Point.h"
#include "List.h"

enum class ENTITY_TYPE
{
	PLAYER = 0,
	GROUND_ENEMY,
	STATIC_ENEMY, // create one for each diferent enemy
	COIN,
	HEART
};

class Entity
{
public:
	Entity() {}
	~Entity() {}

	void Init(ENTITY_TYPE type, fPoint p);

	virtual void InitCustomEntity();
	virtual bool PreUpdate();
	virtual void HandleInput(float dt);
	virtual bool Update(float dt);
	virtual bool Draw();
	virtual bool DeleteEntity();

	// load-save
	virtual bool Load(pugi::xml_node&);
	virtual bool Save(pugi::xml_node&);

	// custom fuctions
	virtual fPoint GetPlayerPosition();
	virtual void SetPlayerPosition(int new_x, int new_y);
	virtual void ImpulsePlayer();
	virtual void PlayerDeath();
	virtual void SwitchDirection();

public:
	ENTITY_TYPE entity_type;

	fPoint position;

	b2Body* body;

	bool alive;

	bool init;

	int p_in_array;
};

class Entities : public Module
{
public:
	Entities();

	virtual ~Entities();

	void AddEntity(Entity* entity, ENTITY_TYPE type, fPoint p);

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

public:
	void CreateEntity(ENTITY_TYPE entity_type, float x, float y);

	List<Entity*> entities;

	int ground_lenght = 0;
	int air_lenght = 0;
	int coins_lenght = 0;

	void PickCoin(fPoint pos);
	void PickHeart(fPoint pos);

	Entity* GetPlayer();

	//HUD
	int ncoins = 0;
	char numCoins[4] = { "\0" };

	int nlifes = 2;
	char numLifes[3] = { "\0" };
	
};

#endif