#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "Hearts.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"

Hearts::Hearts() : Entity()
{}

// Destructor
Hearts::~Hearts()
{}

void Hearts::InitCustomEntity()
{
	b2BodyDef c_body;
	c_body.type = b2_staticBody;
	c_body.position.Set(position.x,position.y);

	body = app->physics->world->CreateBody(&c_body);

	b2PolygonShape box;
	box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h), b2Vec2(PIXELS_TO_METERS(16), PIXELS_TO_METERS(16)), 0);

	b2FixtureDef fixture;
	fixture.shape = &box;
	b2Fixture* bodyFixture = body->CreateFixture(&fixture);
	bodyFixture->SetSensor(true);
	bodyFixture->SetUserData((void*)10); // heart collision

	picked = false;
}

// Called each loop iteration
bool Hearts::PreUpdate()
{
	position.x = body->GetPosition().x;
	position.y = body->GetPosition().y;

	return true;
}

// Called each loop iteration
bool Hearts::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool Hearts::Draw()
{
	bool ret = true;

	if (plan_to_delete)
	{
		app->physics->world->DestroyBody(body);
		plan_to_delete = false;
	}

	if (!picked)
	{
		app->render->DrawTexture(app->tex->heart_texture, METERS_TO_PIXELS(position.x), METERS_TO_PIXELS(position.y));
	}

	return ret;
}

bool Hearts::DeleteEntity()
{
	app->entities->nlifes++;
	sprintf_s(app->entities->numLifes, 3, "%02d", app->entities->nlifes);
	picked = true;
	position.x = body->GetPosition().x;
	position.y = body->GetPosition().y;
	plan_to_delete = true;

	return true;
}