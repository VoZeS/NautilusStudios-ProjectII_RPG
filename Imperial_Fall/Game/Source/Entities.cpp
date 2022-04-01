#include "App.h"
#include "Textures.h"
#include "Entities.h"
#include "Scene.h"

#include "Player.h"
#include "Enemies.h"
#include "NPC.h"
#include "Coins.h"
#include "Hearts.h"

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
	ListItem<Entity*>* item;
	item = entities.start;

	while (item != NULL && ret == true)
	{
		switch (item->data->entity_type)
		{
		case ENTITY_TYPE::RENATO:
			item->data->InitCustomEntity(1);
			break;
		case ENTITY_TYPE::CURANDERO:
			item->data->InitCustomEntity(2);
			break;
		case ENTITY_TYPE::HERRERO:
			item->data->InitCustomEntity(3);
			break;
		case ENTITY_TYPE::GRANJERO:
			item->data->InitCustomEntity(4);
			break;
		default:
			item->data->InitCustomEntity();
			break;
		}
		item = item->next;
	}

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

			if (entity->alive == false) {
				continue;
			}

			if (entity->init)
			{
				ret = item->data->Draw();
			}
		}

		sprintf_s(numCoins, 4, "%03d", ncoins);
		sprintf_s(numLifes, 4, "%03d", nlifes);
	}

	return ret;
}

// Called before quitting
bool Entities::CleanUp()
{

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

void Entities::CreateEntity(ENTITY_TYPE entity_type, float x, float y)
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
	case ENTITY_TYPE::GROUND_ENEMY:
	{
		Ground_Enemies* g_enemy = new Ground_Enemies();
		AddEntity(g_enemy, ENTITY_TYPE::GROUND_ENEMY, p);
	}
		break;
	/*case ENTITY_TYPE::AIR_ENEMY:
	{
		Air_Enemies* a_enemy = new Air_Enemies();
		AddEntity(a_enemy, ENTITY_TYPE::AIR_ENEMY, p);
	}
		break;*/
	case ENTITY_TYPE::COIN:
	{
		Coins* coin = new Coins();
		AddEntity(coin, ENTITY_TYPE::COIN, p);
	}
		break;
	case ENTITY_TYPE::HEART:
	{
		Hearts* heart = new Hearts();
		AddEntity(heart, ENTITY_TYPE::HEART, p);
	}
		break;
	default:
		break;
	}
}

void Entities::PickCoin(fPoint pos)
{
	ListItem<Entity*>* item;
	Entity* entity = NULL;

	for (item = entities.start; item != NULL; item = item->next)
	{
		entity = item->data;

		if (pos.x + 1.5f > entity->position.x && pos.x - 1.5f < entity->position.x && pos.y + 2.0f > entity->position.y && pos.y - 2.0f < entity->position.y && entity->entity_type == ENTITY_TYPE::COIN)
		{
			entity->DeleteEntity();

			break;
		}
	}
}

void Entities::PickHeart(fPoint pos)
{
	ListItem<Entity*>* item;
	Entity* entity = NULL;

	for (item = entities.start; item != NULL; item = item->next)
	{
		entity = item->data;

		if (pos.x + 1.5f > entity->position.x && pos.x - 1.5f < entity->position.x && pos.y + 2.0f > entity->position.y && pos.y - 2.0f < entity->position.y && entity->entity_type == ENTITY_TYPE::HEART)
		{
			entity->DeleteEntity();

			break;
		}
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

	init = false;

	switch (type)
	{
	case ENTITY_TYPE::GROUND_ENEMY:
		p_in_array = app->entities->ground_lenght;
		app->entities->ground_lenght++;
		break;
	/*case ENTITY_TYPE::AIR_ENEMY:
		p_in_array = app->entities->air_lenght;
		app->entities->air_lenght++;
		break;*/
	case ENTITY_TYPE::COIN:
		p_in_array = app->entities->coins_lenght;
		app->entities->coins_lenght++;
		break;
	case ENTITY_TYPE::HEART:
		break;
	default:
		break;
	}
}

void Entity::InitCustomEntity()
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

void Entity::PlayerDeath()
{

}

void Entity::ImpulsePlayer()
{

}

void Entity::SwitchDirection()
{

}