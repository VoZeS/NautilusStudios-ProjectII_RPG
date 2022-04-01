#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Physics.h"
#include "NPC.h"
#include "Scene.h"
#include "Menu.h"

#include "Defs.h"
#include "Log.h"

NPC::NPC() : Entity()
{
	// main idle animation
	//idleAnim_renato.PushBack({ 10, 3, 51, 78 });
	idleAnim_renato.PushBack({ 62, 3, 51, 78 });
	idleAnim_renato.speed = 0.03f;

	idleAnim_vendedores.PushBack({ 0, 0, 64, 80 });
	idleAnim_vendedores.PushBack({ 64, 0, 64, 80 });
	idleAnim_vendedores.speed = 0.03f;
}

// Destructor
NPC::~NPC()
{}

void NPC::InitCustomEntity(int npc)
{
	npc_type = npc;

	if (npc_type == 1)
	{
		currentAnimation = &idleAnim_renato;
	}
	else
	{
		currentAnimation = &idleAnim_vendedores;
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
	box.SetAsBox(PIXELS_TO_METERS((w * 3)), PIXELS_TO_METERS(h * 3), b2Vec2(0, 0), 0);
	fixture.isSensor = true;
	b2Fixture* sensorFixture = body->CreateFixture(&fixture);
	sensorFixture->SetUserData((void*)2); // NPC sensor
}

// Called each loop iteration
bool NPC::PreUpdate()
{
	position.x = body->GetPosition().x;
	position.y = body->GetPosition().y;

	return true;
}

// Called each loop iteration
bool NPC::Update(float dt)
{
	if (!app->menu->GetGameState() && !app->scene->GetStartScreenState())
	{
		currentAnimation->Update();
	}

	return true;
}

// Called each loop iteration
bool NPC::Draw()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	 
	if (!app->scene->GetStartScreenState())
	{
		switch (npc_type)
		{
		case 1: app->render->DrawTexture(app->tex->renato_bueno, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 40.0f), &rect);
			break;
		case 2: app->render->DrawTexture(app->tex->curandero, METERS_TO_PIXELS(position.x - 30.0f), METERS_TO_PIXELS(position.y - 42.0f), &rect);
			break;
		case 3: app->render->DrawTexture(app->tex->herrero, METERS_TO_PIXELS(position.x - 30.0f), METERS_TO_PIXELS(position.y - 42.0f), &rect);
			break;
		case 4: app->render->DrawTexture(app->tex->granjero, METERS_TO_PIXELS(position.x - 30.0f), METERS_TO_PIXELS(position.y - 42.0f), &rect);
			break;
		default:
			break;
		}
	}
	
	return true;
}

bool NPC::Load(pugi::xml_node& data)
{
	/*position.x = data.child("player").child("position").attribute("x").as_int();
	position.y = data.child("player").child("position").attribute("y").as_int();

	body->SetTransform({ position.x + PIXELS_TO_METERS(w), position.y }, body->GetAngle());
	body->ApplyForceToCenter({ 0, 1 }, true);

	currentAnimation = &idleAnimD;
	if (app->menu->dead)
	{
		app->menu->dead = false;
	}*/

	return true;
}

bool NPC::Save(pugi::xml_node& data)
{
	/*data.child("player").child("position").attribute("x").set_value(position.x);
	data.child("player").child("position").attribute("y").set_value(position.y);*/

	return true;
}