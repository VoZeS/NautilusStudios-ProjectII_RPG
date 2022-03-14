#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Physics.h"
#include "Player.h"
#include "Enemies.h"
#include "Pathfinding.h"
#include "Menu.h"

#include "Defs.h"
#include "Log.h"

#include <time.h>

// GROUND ENEMY
Ground_Enemies::Ground_Enemies() : Entity()
{
	
}

// Destructor
Ground_Enemies::~Ground_Enemies()
{}

void Ground_Enemies::InitCustomEntity()
{
	origin_x = position.x;
	origin_y = position.y;
	speed = 0.05f;

	currentAnimation = &slime_walkAnimR;

	lookLeft = true;

	detectionRange = 5.0f;
	enemy_spoted = false;

	state = ENEMY_STATE::IDLE;
	obLeft = false;

	// body
	b2BodyDef e_body;
	e_body.type = b2_dynamicBody;
	e_body.fixedRotation = true;
	e_body.position.Set(position.x, position.y);

	body = app->physics->world->CreateBody(&e_body);
	body->SetFixedRotation(true);

	b2PolygonShape box;
	box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h));

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.friction = 0.0f;
	b2Fixture* bodyFixture = body->CreateFixture(&fixture);
	bodyFixture->SetSensor(false);
	bodyFixture->SetUserData((void*)4); // enemy body collision
}

// Called each loop iteration
bool Ground_Enemies::PreUpdate()
{
	if (state != ENEMY_STATE::DEATH)
	{
		position.x = body->GetPosition().x;
		position.y = body->GetPosition().y;


		//path without spot the player
		if (obLeft)
		{
			idleOb_x = origin_x - PIXELS_TO_METERS(32 * 5);
		}
		else
		{
			idleOb_x = origin_x + PIXELS_TO_METERS(32 * 5);
		}
	}
	
	return true;
}

// Called each loop iteration
bool Ground_Enemies::Update(float dt)
{
	currentAnimation->Update();

	// update path
	switch (state)
	{
	case ENEMY_STATE::IDLE:
		MoveGroundEnemy(dt);
		break;
	case ENEMY_STATE::HUNT:
		EnemyHunting(dt);
		break;
	case ENEMY_STATE::RETURN:
		EnemyReturning(dt);
		break;
	default:
		break;
	}

	if (body->GetLinearVelocity().x >= 0)
	{
		lookLeft = false;
	}
	else
	{
		lookLeft = true;
	}

	if (state != ENEMY_STATE::DEATH)
	{
		CheckPlayer();
	}

	return true;
}

// Called each loop iteration
bool Ground_Enemies::Draw()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	if (plan_to_delete)
	{
		app->physics->world->DestroyBody(body);
		plan_to_delete = false;
	}
	
	if (state != ENEMY_STATE::DEATH)
	{
		if (lookLeft)
		{
			app->render->DrawTexture(app->tex->slime_textureL, METERS_TO_PIXELS(position.x - (40)), METERS_TO_PIXELS(position.y - (45)), &rect);
		}
		else
		{
			app->render->DrawTexture(app->tex->slime_textureR, METERS_TO_PIXELS(position.x - (40)), METERS_TO_PIXELS(position.y - (45)), &rect);
		}

		if (state == ENEMY_STATE::HUNT || state == ENEMY_STATE::RETURN)
		{
			if (app->physics->debug && path_save)
			{
				app->pathfinding->DrawPath(path_save, position, ENTITY_TYPE::GROUND_ENEMY);
			}
		}
	}
	else
	{
		alive = false;
	}

	return true;
}

void Ground_Enemies::MoveGroundEnemy(float dt)
{
	if (!obLeft)
	{
		if (position.x < idleOb_x)
		{
			body->SetLinearVelocity({ speed * dt, body->GetLinearVelocity().y });
		}
		else
		{
			obLeft = true;
		}

	}
	else if (obLeft)
	{
		if (position.x > idleOb_x)
		{
			body->SetLinearVelocity({ -speed * dt, body->GetLinearVelocity().y });
		}
		else
		{
			obLeft = false;
		}
	}
}

void Ground_Enemies::CheckPlayer()
{
	Entity* player = app->entities->GetPlayer();

	if (position.x + detectionRange > player->GetPlayerPosition().x && position.x - detectionRange < player->GetPlayerPosition().x
		&& position.y + detectionRange > player->GetPlayerPosition().y && position.y - detectionRange < player->GetPlayerPosition().y)
	{
		if (state != ENEMY_STATE::HUNT)
		{
			state = ENEMY_STATE::HUNT;
		}
	}
	else
	{
		if (state == ENEMY_STATE::HUNT)
		{
			state = ENEMY_STATE::RETURN;
		}
	}
}

void Ground_Enemies::EnemyHunting(float dt)
{
	PathFinding* path = new PathFinding();
	float dist;

	Entity* player = app->entities->GetPlayer();
	path->CreatePath({ (int)position.x, 0 }, { (int)player->GetPlayerPosition().x, 0 });
	int ob_x = path->GetLastPath()->At(path->GetLastPath()->Count() - 1)->x;

	if ((ob_x - position.x) > 0)
	{
		dist = 1.5f;
	}
	else
	{
		dist = -1.5f;
	}
	body->SetLinearVelocity({ dist * speed * dt, body->GetLinearVelocity().y });

	path_save = path;
}

void Ground_Enemies::EnemyReturning(float dt)
{
	PathFinding* path = new PathFinding();
	
	path->CreatePath({ (int)position.x, 0 }, { (int)origin_x, 0 });
	int ob_x = path->GetLastPath()->At(path->GetLastPath()->Count() - 1)->x;

	body->SetLinearVelocity({ (ob_x - position.x) * speed * dt, body->GetLinearVelocity().y });

	if (position.x + 1.5f > origin_x && position.x - 1.5f < origin_x)
	{
		state = ENEMY_STATE::IDLE;
	}

	if (position.y + 1.5f > origin_y || position.y - 1.5f < origin_y)
	{
		origin_x = position.x;
		origin_y = position.y;
	}

	path_save = path;
}

bool Ground_Enemies::DeleteEntity()
{
	state = ENEMY_STATE::DEATH;
	plan_to_delete = true;
	app->entities->GetPlayer()->ImpulsePlayer();

	return true;
}

bool Ground_Enemies::Load(pugi::xml_node& data)
{
	std::string p = "ground";
	std::string s = std::to_string(p_in_array);
	std::string t = p + s;
	const char* c = t.c_str();
	
	if (data.child("enemies").child(c).attribute("state").as_int() == 0)
	{
		if (state == ENEMY_STATE::DEATH)
		{
			
		}

		position.x = data.child("enemies").child(c).attribute("x").as_int();
		position.y = data.child("enemies").child(c).attribute("y").as_int();

		body->SetTransform({ position.x + PIXELS_TO_METERS(w), position.y }, body->GetAngle());
		body->ApplyForceToCenter({ 0, 1000 }, true);
	}
	else
	{
		state = ENEMY_STATE::DEATH;
	}

	return true;
}

bool Ground_Enemies::Save(pugi::xml_node& data)
{
	std::string p = "ground";
	std::string s = std::to_string(p_in_array);
	std::string t = p + s;
	const char* c = t.c_str();

	data.child("enemies").child(c).attribute("x").set_value(position.x);
	data.child("enemies").child(c).attribute("y").set_value(position.y);

	if (state != ENEMY_STATE::DEATH)
	{
		data.child("enemies").child(c).attribute("state").set_value("0");
	}
	else
	{
		data.child("enemies").child(c).attribute("state").set_value("1");
	}

	return true;
}

void Ground_Enemies::SwitchDirection()
{
	obLeft = !obLeft;
}