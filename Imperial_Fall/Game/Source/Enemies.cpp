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

// ENEMY
Enemies::Enemies(int en1, int en2, int en3, int en4) : Entity()
{
	switch (en1)
	{
	case 0: combat_enemies[0] = ENEMIES::NOTHING; break;
	case 1: combat_enemies[0] = ENEMIES::W_TEMPLAR; break;
	case 2: combat_enemies[0] = ENEMIES::MUSHROOM; break;
	case 3: combat_enemies[0] = ENEMIES::GOBLIN; break;
	case 4: combat_enemies[0] = ENEMIES::SKELETON; break;
	}
	switch (en2)
	{
	case 0: combat_enemies[1] = ENEMIES::NOTHING; break;
	case 1: combat_enemies[1] = ENEMIES::W_TEMPLAR; break;
	case 2: combat_enemies[1] = ENEMIES::MUSHROOM; break;
	case 3: combat_enemies[1] = ENEMIES::GOBLIN; break;
	case 4: combat_enemies[1] = ENEMIES::SKELETON; break;
	}
	switch (en3)
	{
	case 0: combat_enemies[2] = ENEMIES::NOTHING; break;
	case 1: combat_enemies[2] = ENEMIES::W_TEMPLAR; break;
	case 2: combat_enemies[2] = ENEMIES::MUSHROOM; break;
	case 3: combat_enemies[2] = ENEMIES::GOBLIN; break;
	case 4: combat_enemies[2] = ENEMIES::SKELETON; break;
	}
	switch (en4)
	{
	case 0: combat_enemies[3] = ENEMIES::NOTHING; break;
	case 1: combat_enemies[3] = ENEMIES::W_TEMPLAR; break;
	case 2: combat_enemies[3] = ENEMIES::MUSHROOM; break;
	case 3: combat_enemies[3] = ENEMIES::GOBLIN; break;
	case 4: combat_enemies[3] = ENEMIES::SKELETON; break;
	}

	// animations
	mushroomAnim.PushBack({ 0, 0, 100, 125 });
	mushroomAnim.PushBack({ 100, 0, 100, 125 });
	mushroomAnim.PushBack({ 200, 0, 100, 125 });
	mushroomAnim.PushBack({ 300, 0, 100, 125 });
	mushroomAnim.speed = 0.03f;
}

// Destructor
Enemies::~Enemies()
{}

void Enemies::InitCustomEntity(int enemy)
{
	enemy_type = enemy;

	switch (enemy_type)
	{
	case 1: currentAnimation = &mushroomAnim; break;
	case 2: currentAnimation = &mushroomAnim; break;
	case 3: currentAnimation = &mushroomAnim; break;
	case 4: currentAnimation = &mushroomAnim; break;
	case 5: currentAnimation = &mushroomAnim; break;
	}

	// body
	b2BodyDef p_body;
	p_body.type = b2_kinematicBody;
	p_body.fixedRotation = true;
	p_body.position.Set(position.x, position.y);

	body = app->physics->world->CreateBody(&p_body);
	body->SetBullet(true);
	body->SetFixedRotation(true);

	b2PolygonShape box;
	box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h));

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.friction = 0.0f;
	b2Fixture* bodyFixture = body->CreateFixture(&fixture);
	bodyFixture->SetSensor(false);
	bodyFixture->SetUserData((void*)0);

	// contact sensor
	box.SetAsBox(PIXELS_TO_METERS((w * 5)), PIXELS_TO_METERS(h * 5), b2Vec2(0, 0), 0);
	fixture.isSensor = true;
	b2Fixture* sensorFixture = body->CreateFixture(&fixture);
	sensorFixture->SetUserData((void*)6); // enemy sensor
}

// Called each loop iteration
bool Enemies::PreUpdate()
{
	if (state != ENEMY_STATE::DEATH)
	{
		position.x = body->GetPosition().x;
		position.y = body->GetPosition().y;
	}
	
	return true;
}

// Called each loop iteration
bool Enemies::Update(float dt)
{
	currentAnimation->Update();

	// update path
	/*switch (state)
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
	}*/

	return true;
}

// Called each loop iteration
bool Enemies::Draw()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	if (plan_to_delete)
	{
		app->physics->world->DestroyBody(body);
		plan_to_delete = false;
	}
	
	if (state != ENEMY_STATE::DEATH)
	{
		switch (enemy_type)
		{
		case 1: 
			app->render->DrawTexture(app->tex->white_templar, METERS_TO_PIXELS(position.x - (rect.w / 2)), METERS_TO_PIXELS(position.y - (rect.h / 1.5f)), &rect);
			break;
		case 2:
			app->render->DrawTexture(app->tex->mushroom, METERS_TO_PIXELS(position.x - (rect.w / 2)), METERS_TO_PIXELS(position.y - (rect.h / 1.5f)), &rect);
			break;
		case 3:
			app->render->DrawTexture(app->tex->goblin, METERS_TO_PIXELS(position.x - (rect.w / 2)), METERS_TO_PIXELS(position.y - (rect.h / 1.5f)), &rect);
			break;
		case 4:
			app->render->DrawTexture(app->tex->skeleton, METERS_TO_PIXELS(position.x - (rect.w / 2)), METERS_TO_PIXELS(position.y - (rect.h / 1.5f)), &rect);
			break;
		}
	}
	else
	{
		alive = false;
	}

	return true;
}

/*void Enemies::MoveGroundEnemy(float dt)
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

void Enemies::CheckPlayer()
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

void Enemies::EnemyHunting(float dt)
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

void Enemies::EnemyReturning(float dt)
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
}*/

bool Enemies::DeleteEntity()
{
	state = ENEMY_STATE::DEATH;
	plan_to_delete = true;
	app->entities->GetPlayer()->ImpulsePlayer();

	return true;
}

bool Enemies::Load(pugi::xml_node& data)
{
	/*std::string p = "ground";
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
	}*/

	return true;
}

bool Enemies::Save(pugi::xml_node& data)
{
	/*std::string p = "ground";
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
	}*/

	return true;
}