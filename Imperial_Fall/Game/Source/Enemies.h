#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "Module.h"
#include "Entities.h"
#include "Physics.h"
#include "Animation.h"
#include "DynArray.h"

enum class ENEMY_STATE
{
	IDLE,
	//HUNT,
	//RETURN,
	DEATH
};

class Enemies : public Entity
{
public:
	Enemies(int en1, int en2, int, int en4);

	virtual ~Enemies();

private:
	void InitCustomEntity(int enemy);

	bool PreUpdate();

	bool Update(float dt);

	bool Draw();

	/*void MoveGroundEnemy(float dt);
	void CheckPlayer();

	void EnemyHunting(float dt);
	void EnemyReturning(float dt);*/

	bool DeleteEntity();

	// load-save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	ENEMIES GetCombatEnemy(int n)
	{
		return combat_enemies[n];
	}

public:
	int w = 16, h = 16;

	Animation* currentAnimation = NULL;

	Animation mushroomAnim;

	ENEMY_STATE state;

	bool plan_to_delete = false;

	ENEMIES combat_enemies[4];

	//PathFinding* path_save = NULL;
};

#endif
