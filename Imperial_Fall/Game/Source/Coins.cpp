#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "Coins.h"
#include "Defs.h"
#include "Log.h"

Coins::Coins() : Entity()
{
	int pix = 32;

	// idle animation
	idleAnim.PushBack({ pix * 0, pix * 0, pix, pix });
	idleAnim.PushBack({ pix * 1, pix * 0, pix, pix });
	idleAnim.PushBack({ pix * 2, pix * 0, pix, pix });
	idleAnim.PushBack({ pix * 3, pix * 0, pix, pix });
	idleAnim.PushBack({ pix * 4, pix * 0, pix, pix });
	idleAnim.speed = 0.15f;
}

// Destructor
Coins::~Coins()
{}

void Coins::InitCustomEntity()
{
	currentAnimation = &idleAnim;

	b2BodyDef c_body;
	c_body.type = b2_staticBody;
	c_body.position.Set(position.x, position.y);

	body = app->physics->world->CreateBody(&c_body);

	b2PolygonShape box;
	box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h), b2Vec2(PIXELS_TO_METERS(16), PIXELS_TO_METERS(16)), 0);

	b2FixtureDef fixture;
	fixture.shape = &box;
	b2Fixture* bodyFixture = body->CreateFixture(&fixture);
	bodyFixture->SetSensor(true);
	bodyFixture->SetUserData((void*)8); // coin collision
}

// Called each loop iteration
bool Coins::PreUpdate()
{
	position.x = body->GetPosition().x;
	position.y = body->GetPosition().y;

	return true;
}

// Called each loop iteration
bool Coins::Update(float dt)
{
	currentAnimation->Update();
	
	return true;
}

// Called each loop iteration
bool Coins::Draw()
{
	bool ret = true;

	if (plan_to_delete)
	{
		app->physics->world->DestroyBody(body);
		plan_to_delete = false;
	}

	if (!picked)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		app->render->DrawTexture(app->tex->coin_texture, METERS_TO_PIXELS(position.x), METERS_TO_PIXELS(position.y), &rect);
	}

	return ret;
}

bool Coins::DeleteEntity()
{
	app->entities->ncoins++;
	sprintf_s(app->entities->numCoins, 4, "%03d", app->entities->ncoins);
	picked = true;
	position.x = body->GetPosition().x;
	position.y = body->GetPosition().y;
	plan_to_delete = true;

	return true;
}

bool Coins::Load(pugi::xml_node& data)
{
	/*std::string p = "position";
	std::string s = std::to_string(p_in_array);
	std::string t = p + s;
	const char* c = t.c_str();

	if (data.child("coins").child(c).attribute("state").as_int() == 0)
	{
		if (picked)
		{
			ReloadCoin();
			app->entities->ncoins--;
		}
	}
	else
	{
		picked = true;
	}*/

	return true;
}

bool Coins::Save(pugi::xml_node& data)
{
	/*std::string p = "position";
	std::string s = std::to_string(p_in_array);
	std::string t = p + s;
	const char* c = t.c_str();

	if (!picked)
	{
		data.child("coins").child(c).attribute("state").set_value("0");
	}
	else
	{
		data.child("coins").child(c).attribute("state").set_value("1");
	}*/

	return true;
}

void Coins::ReloadCoin()
{
	// coin
	b2BodyDef c_body;
	c_body.type = b2_staticBody;
	c_body.position.Set(position.x, position.y);

	body = app->physics->world->CreateBody(&c_body);

	b2PolygonShape box;
	box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h), b2Vec2(PIXELS_TO_METERS(16), PIXELS_TO_METERS(16)), 0);

	b2FixtureDef fixture;
	fixture.shape = &box;
	b2Fixture* bodyFixture = body->CreateFixture(&fixture);
	bodyFixture->SetSensor(true);
	bodyFixture->SetUserData((void*)8); // coin collision

	picked = false;
}