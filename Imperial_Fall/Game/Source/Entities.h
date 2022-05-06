#ifndef __ENTITIES_H__
#define __ENTITIES_H__

#include "Module.h"
#include "Physics.h"
#include "Animation.h"
#include "Combat_Entities.h"
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
	ALDEANO,
	SIGNAL,
	W_TEMPLAR,
	MUSHROOM,
	GOBLIN,
	SKELETON,
	R_TEMPLAR
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
	
	virtual ENEMIES GetCombatEnemy(int n);

	bool SaveSingleEnemy();

public:
	ENTITY_TYPE entity_type;

	fPoint position;

	b2Body* body;

	bool alive;
	bool plan_to_delete;

	bool init;

	int p_in_array;
};

class Entities : public Module
{
public:
	Entities(bool enabled);

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

	fPoint GetPlayerSavedPos();
	void SetPlayerSavedPos(float x, float y, float c0x, float c0y, float c1x, float c1y, float c2x, float c2y);

public:
	void CreateEntity(ENTITY_TYPE entity_type, float x, float y, int index = -1, int en1 = -1, int en2 = -1, int en3 = -1, int en4 = -1);

	List<Entity*> entities;
	DynArray<bool> entities_state;

	int FindNPC();
	fPoint GetEnemyPos();
	void StartCombat();
	void KillEnemy();

	Entity* GetPlayer();
	bool player_init = true;
	bool freeze = false;

	bool in_boss = false;
	fPoint enter_combat_pos;

	SDL_Texture* assassin_texture = NULL;
	SDL_Texture* tank_texture = NULL;
	SDL_Texture* healer_texture = NULL;
	SDL_Texture* wizard_texture = NULL;
	SDL_Texture* curandero = NULL;
	SDL_Texture* herrero = NULL;
	SDL_Texture* granjero = NULL;
	SDL_Texture* aldeano = NULL;
	SDL_Texture* signal = NULL;
	SDL_Texture* renato_bueno = NULL;
	SDL_Texture* white_templar = NULL;
	SDL_Texture* mushroom = NULL;
	SDL_Texture* goblin = NULL;
	SDL_Texture* skeleton = NULL;
	SDL_Texture* red_templar = NULL;
	
};

#endif