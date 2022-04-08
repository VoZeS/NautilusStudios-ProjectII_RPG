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
	RENATO,
	CURANDERO,
	HERRERO,
	GRANJERO,
	COMPANION,
	GROUND_ENEMY,
	STATIC_ENEMY
};

class Entity
{
public:
	Entity() {}
	~Entity() {}

	void Init(ENTITY_TYPE type, fPoint p);

	virtual void InitCustomEntity(int npc = 0);
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
	virtual void SetPlayerLookDir(int lookDir);

	virtual fPoint GetCompanion0Position();
	virtual fPoint GetCompanion1Position();
	virtual fPoint GetCompanion2Position();

	virtual void SetCompanion0Position(int new_x, int new_y);
	virtual void SetCompanion1Position(int new_x, int new_y);
	virtual void SetCompanion2Position(int new_x, int new_y);

	virtual void SetCompanion0LookDir(int lookDir);
	virtual void SetCompanion1LookDir(int lookDir);
	virtual void SetCompanion2LookDir(int lookDir);

	virtual bool IsPlayerEnabled();
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

	int FindNPC();

	Entity* GetPlayer();
	
};

#endif