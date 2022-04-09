#include "App.h"
#include "Textures.h"
#include "Entities.h"
#include "Scene.h"
#include "Menu.h"
#include "Frontground.h"

#include "Player.h"
#include "Enemies.h"
#include "NPC.h"

#include "Defs.h"
#include "Log.h"

#include <time.h>

Entities::Entities() : Module()
{
	name.Create("entities");
}

// Destructor
Entities::~Entities()
{}

void Entities::AddEntity(Entity* entity, ENTITY_TYPE type, fPoint p)
{
	entity->Init(type, p);
	entities.Add(entity);
	entities_state.Insert(true, )
}

// Called before render is available
bool Entities::Awake()
{
	srand(time(NULL));

	return true;
}

// Called before the first frame
bool Entities::Start()
{
	bool ret = true;
	
	app->entities->CreateEntity(ENTITY_TYPE::PLAYER, 500, 500);

	return ret;
}

// Called each loop iteration
bool Entities::PreUpdate()
{
	bool ret = true;

	ListItem<Entity*>* item;
	Entity* entity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		entity = item->data;

		if (entity->alive == false) {
			continue;
		}

		if (!entity->init)
		{
			switch (entity->entity_type)
			{
			case ENTITY_TYPE::RENATO:
				entity->InitCustomEntity(1);
				break;
			case ENTITY_TYPE::CURANDERO:
				entity->InitCustomEntity(2);
				break;
			case ENTITY_TYPE::HERRERO:
				entity->InitCustomEntity(3);
				break;
			case ENTITY_TYPE::GRANJERO:
				entity->InitCustomEntity(4);
				break;
			case ENTITY_TYPE::W_TEMPLAR:
				entity->InitCustomEntity(1);
				break;
			case ENTITY_TYPE::MUSHROOM:
				entity->InitCustomEntity(2);
				break;
			case ENTITY_TYPE::GOBLIN:
				entity->InitCustomEntity(3);
				break;
			case ENTITY_TYPE::SKELETON:
				entity->InitCustomEntity(4);
				break;
			default:
				entity->InitCustomEntity();
				break;
			}
			entity->init = true;
		}
		else
		{
			ret = item->data->PreUpdate();
		}
	}

	return ret;
}

// Called each loop iteration
bool Entities::Update(float dt)
{
	bool ret = true;

	ListItem<Entity*>* item;
	Entity* entity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		entity = item->data;

		if (entity->alive == false) {
			continue;
		}

		if (entity->init)
		{
			if (entity->entity_type == ENTITY_TYPE::PLAYER)
			{
				item->data->HandleInput(dt);
			}

			ret = item->data->Update(dt);
		}
	}

	return ret;
}

// Called each loop iteration
bool Entities::PostUpdate()
{
	bool ret = true;

	if (!app->scene->GetStartScreenState())
	{
		ListItem<Entity*>* item;
		Entity* entity = NULL;

		for (item = entities.start; item != NULL && ret == true; item = item->next)
		{
			entity = item->data;

			if (entity->alive == false)
			{
				if (entity->plan_to_delete)
				{
					app->physics->world->DestroyBody(entity->body);
					entity->plan_to_delete = false;
				}
				continue;
			}

			if (entity->init)
			{
				ret = item->data->Draw();
			}
		}
	}

	return ret;
}

bool Entities::CleanUp()
{
	ListItem<Entity*>* item;
	Entity* entity = NULL;

	for (item = entities.start; item != NULL; item = item->next)
	{
		entity = item->data;

		if (entity->entity_type != ENTITY_TYPE::PLAYER)
		{
			//app->physics->world->DestroyBody(entity->body);
			entities.Del(item);
		}
	}
	enemies_lenght = 0;

	return true;
}

bool Entities::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	ListItem<Entity*>* item;
	Entity* entity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		entity = item->data;

		if (entity->init)
		{
			ret = item->data->Load(data);
		}
	}

	return true;
}

bool Entities::SaveState(pugi::xml_node& data)
{
	bool ret = true;

	ListItem<Entity*>* item;
	Entity* entity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		entity = item->data;

		if (entity->init)
		{
			ret = item->data->Save(data);
		}
	}

	return true;
}

void Entities::CreateEntity(ENTITY_TYPE entity_type, float x, float y, int index, int en1, int en2, int en3, int en4)
{
	fPoint p = { x, y };

	switch (entity_type)
	{
	case ENTITY_TYPE::PLAYER:
	{
		Player* player = new Player();
		AddEntity(player, ENTITY_TYPE::PLAYER, p);
	}
		break;
	case ENTITY_TYPE::RENATO:
	{
		NPC* npc = new NPC();
		AddEntity(npc, ENTITY_TYPE::RENATO, p);
	}
		break;
	case ENTITY_TYPE::CURANDERO:
	{
		NPC* npc = new NPC();
		AddEntity(npc, ENTITY_TYPE::CURANDERO, p);
	}
		break;
	case ENTITY_TYPE::HERRERO:
	{
		NPC* npc = new NPC();
		AddEntity(npc, ENTITY_TYPE::HERRERO, p);
	}
		break;
	case ENTITY_TYPE::GRANJERO:
	{
		NPC* npc = new NPC();
		AddEntity(npc, ENTITY_TYPE::GRANJERO, p);
	}
		break;
	case ENTITY_TYPE::W_TEMPLAR:
	{
		Enemies* enemy = new Enemies(index, en1, en2, en3, en4);
		AddEntity(enemy, ENTITY_TYPE::W_TEMPLAR, p);
	}
		break;
	case ENTITY_TYPE::MUSHROOM:
	{
		Enemies* enemy = new Enemies(index, en1, en2, en3, en4);
		AddEntity(enemy, ENTITY_TYPE::MUSHROOM, p);
	}
		break;
	case ENTITY_TYPE::GOBLIN:
	{
		Enemies* enemy = new Enemies(index, en1, en2, en3, en4);
		AddEntity(enemy, ENTITY_TYPE::GOBLIN, p);
	}
		break;
	case ENTITY_TYPE::SKELETON:
	{
		Enemies* enemy = new Enemies(index, en1, en2, en3, en4);
		AddEntity(enemy, ENTITY_TYPE::SKELETON, p);
	}
		break;
	default:
		break;
	}
}

int Entities::FindNPC()
{
	ListItem<Entity*>* item;
	Entity* entity = NULL;

	float max = 9999;
	int ret = -1;

	for (item = entities.start; item != NULL; item = item->next)
	{
		entity = item->data;

		if ((entity->entity_type == ENTITY_TYPE::RENATO || entity->entity_type == ENTITY_TYPE::CURANDERO
			|| entity->entity_type == ENTITY_TYPE::HERRERO || entity->entity_type == ENTITY_TYPE::GRANJERO)
			&& (GetPlayer()->GetPlayerPosition().DistanceTo(entity->position) < max))
		{
			switch (entity->entity_type)
			{
			case ENTITY_TYPE::RENATO: ret = 1;
				break;
			case ENTITY_TYPE::CURANDERO: ret = 2;
				break;
			case ENTITY_TYPE::HERRERO: ret = 3;
				break;
			case ENTITY_TYPE::GRANJERO: ret = 4;
				break;
			}

			max = GetPlayer()->GetPlayerPosition().DistanceTo(entity->position);
		}
	}

	return ret;
}

void Entities::StartCombat()
{
	ListItem<Entity*>* item;
	Entity* entity = NULL;

	float max = 9999;
	Entity* combat_entity = NULL;

	for (item = entities.start; item != NULL; item = item->next)
	{
		entity = item->data;

		if ((entity->entity_type == ENTITY_TYPE::W_TEMPLAR || entity->entity_type == ENTITY_TYPE::MUSHROOM
			|| entity->entity_type == ENTITY_TYPE::GOBLIN || entity->entity_type == ENTITY_TYPE::SKELETON)
			&& (GetPlayer()->GetPlayerPosition().DistanceTo(entity->position) < max))
		{
			combat_entity = entity;
			max = GetPlayer()->GetPlayerPosition().DistanceTo(entity->position);
		}
	}

	if (combat_entity != NULL)
	{
		ENEMIES enemies[4];
		enemies[0] = combat_entity->GetCombatEnemy(0);
		enemies[1] = combat_entity->GetCombatEnemy(1);
		enemies[2] = combat_entity->GetCombatEnemy(2);
		enemies[3] = combat_entity->GetCombatEnemy(3);
		app->frontground->FadeInCombat(enemies);
	}
}

void Entities::KillEnemy()
{
	ListItem<Entity*>* item;
	Entity* entity = NULL;

	float max = 9999;
	Entity* combat_entity = NULL;

	for (item = entities.start; item != NULL; item = item->next)
	{
		entity = item->data;

		if ((entity->entity_type == ENTITY_TYPE::W_TEMPLAR || entity->entity_type == ENTITY_TYPE::MUSHROOM
			|| entity->entity_type == ENTITY_TYPE::GOBLIN || entity->entity_type == ENTITY_TYPE::SKELETON)
			&& (GetPlayer()->GetPlayerPosition().DistanceTo(entity->position) < max))
		{
			combat_entity = entity;
			max = GetPlayer()->GetPlayerPosition().DistanceTo(entity->position);
		}
	}

	if (combat_entity != NULL)
	{
		combat_entity->alive = false;
		combat_entity->plan_to_delete = true;
		combat_entity->SaveSingleEnemy();
		app->menu->kill_enemy = false;
	}
}

Entity* Entities::GetPlayer()
{
	ListItem<Entity*>* item;
	Entity* entity = NULL;

	for (item = entities.start; item != NULL; item = item->next)
	{
		entity = item->data;

		if (entity->entity_type == ENTITY_TYPE::PLAYER)
		{
			return entity;
		}
	}

	return NULL;
}

void Entity::Init(ENTITY_TYPE type, fPoint p)
{
	entity_type = type;

	position.x = PIXELS_TO_METERS(p.x);
	position.y = PIXELS_TO_METERS(p.y);

	body = NULL;

	alive = true;
	plan_to_delete = false;

	init = false;

	/*if (type == ENTITY_TYPE::W_TEMPLAR || type == ENTITY_TYPE::MUSHROOM || type == ENTITY_TYPE::GOBLIN || type == ENTITY_TYPE::SKELETON)
	{
		p_in_array = app->entities->enemies_lenght;
		app->entities->enemies_lenght++;
	}*/
}

void Entity::InitCustomEntity(int npc)
{

}

bool Entity::PreUpdate()
{
	return true;
}

void Entity::HandleInput(float dt)
{

}

bool Entity::Update(float dt)
{
	return true;
}

bool Entity::Draw()
{
	return true;
}

bool Entity::DeleteEntity()
{
	return true;
}

bool Entity::Load(pugi::xml_node&)
{
	return true;
}

bool Entity::Save(pugi::xml_node&)
{
	return true;
}

fPoint Entity::GetPlayerPosition()
{
	return { 0, 0 };
}

void Entity::SetPlayerPosition(int new_x, int new_y)
{

}

void Entity::SetPlayerLookDir(int lookDir)
{
}

fPoint Entity::GetCompanion0Position()
{
	return { 0,0 };
}

fPoint Entity::GetCompanion1Position()
{
	return { 0,0 };
}

fPoint Entity::GetCompanion2Position()
{
	return { 0,0 };
}

void Entity::SetCompanion0Position(int new_x, int new_y)
{
}

void Entity::SetCompanion1Position(int new_x, int new_y)
{
}

void Entity::SetCompanion2Position(int new_x, int new_y)
{
}

void Entity::SetCompanion0LookDir(int lookDir)
{
}

void Entity::SetCompanion1LookDir(int lookDir)
{
}

void Entity::SetCompanion2LookDir(int lookDir)
{
}

bool Entity::IsPlayerEnabled()
{
	return true;
}

void Entity::ImpulsePlayer()
{

}

ENEMIES Entity::GetCombatEnemy(int n)
{
	return ENEMIES::NOTHING;
}

bool Entity::SaveSingleEnemy()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(SAVE_STATE_FILENAME);

	Save(saveGame.child("game_state").child("entities"));
	saveGame.save_file(SAVE_STATE_FILENAME);

	return result;
}