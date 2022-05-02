#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Physics.h"
#include "Entities.h"
#include "Player.h"
#include "Enemies.h"
#include "Menu.h"
#include "Frontground.h"
#include "Town1.h"
#include "Town2.h"
#include "Forest.h"
#include "Battlefield.h"
#include "Dungeon.h"
#include "Outside_Castle.h"
#include "Inside_Castle.h"
#include "Dialog.h"

#include "Defs.h"
#include "Log.h"

#ifdef _DEBUG
#pragma comment( lib, "Source/External/Box2D/libx86/Release/Box2D.lib" )
#else
#pragma comment( lib, "Source/External/Box2D/libx86/Release/Box2D.lib" )
#endif

Physics::Physics(bool enabled) : Module(enabled)
{
	name.Create("physics");
	debug = false;
}

// Destructor
Physics::~Physics()
{}

// Called before render is available
bool Physics::Awake()
{

	return true;
}

// Called before the first frame
bool Physics::Start()
{
	b2Vec2 gravity(GRAVITY_X, -GRAVITY_Y);
	world = new b2World(gravity);
	world->SetContactListener(this);

	on_collosion = 0;

	save_sound = app->audio->LoadFx("Assets/audio/fx/save_sound.wav");;

	return true;
}

// Called each loop iteration
bool Physics::PreUpdate()
{

	if (!app->menu->GetGameState())
	{
		world->Step(1.0f / 60.0f, 6, 2);
	}
	else
	{
		world->Step(0, 6, 2);
	}

	return true;
}

// Called each loop iteration
bool Physics::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		debug = !debug;
	}

	return true;
}

// Called each loop iteration
bool Physics::PostUpdate()
{
	if (!debug)
		return true;

	Uint8 c_r, c_g, c_b;
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
			int32 count = polygonShape->GetVertexCount();
			b2Vec2 prev, v;

			for (int32 i = 0; i < count; ++i)
			{
				v = b->GetWorldPoint(polygonShape->GetVertex(i));
				if (i > 0)
				{
					void* userData = f->GetUserData();

					switch ((int)userData)
					{
					case 1: // player
						c_r = 255;
						c_g = 128;
						c_b = 0;
						break;
					case 2: // renato interaction
						c_r = 128;
						c_g = 0;
						c_b = 255;
						break;
					case 3: // curandero interaction
						c_r = 0;
						c_g = 255;
						c_b = 0;
						break;
					case 4: // herrero interaction
						c_r = 255;
						c_g = 0;
						c_b = 0;
						break;
					case 5: // granjero interaction
						c_r = 255;
						c_g = 200;
						c_b = 0;
						break;
					case 6: // aldeano interaction
						c_r = 200;
						c_g = 200;
						c_b = 200;
						break;
					case 7: // enemies interaction
						c_r = 100;
						c_g = 100;
						c_b = 100;
						break;
					case 8:
						c_r = 50;
						c_g = 200;
						c_b = 200;
						break;
					case 9:
						c_r = 50;
						c_g = 50;
						c_b = 50;
						break;
					case 10:
						c_r = 100;
						c_g = 100;
						c_b = 100;
						break;
					case 30:
						return true;
						break;
					default:
						c_r = 100;
						c_g = 100;
						c_b = 100;
						break;
					}
					app->render->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), c_r, c_g, c_b);
				}
					
				prev = v;
			}

			v = b->GetWorldPoint(polygonShape->GetVertex(0));
			app->render->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), c_r, c_g, c_b);
		}
	}

	return true;
}

// Called before quitting
bool Physics::CleanUp()
{

	return true;
}

b2Fixture* Physics::CreateMapBox(int x, int y, int w, int h, int collision)
{
	b2BodyDef g;
	g.type = b2_staticBody;
	g.position.Set(PIXELS_TO_METERS(x), PIXELS_TO_METERS(y));

	b2Body* p = world->CreateBody(&g);

	b2PolygonShape box;
	box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h));

	b2FixtureDef fixture;
	fixture.shape = &box;

	if (collision == 5) fixture.isSensor = true;
	else if (collision == 6) fixture.isSensor = true;
	else if (collision == 7) fixture.isSensor = true;
	else if (collision == 12) fixture.isSensor = true;
	else if (collision == 21) fixture.isSensor = true;
	else if (collision == 30) fixture.isSensor = true;

	// SOUKOBAN PUZZLE SENSORS
	else if (collision == 201) fixture.isSensor = true;
	else if (collision == 202) fixture.isSensor = true;
	else if (collision == 203) fixture.isSensor = true;
	else if (collision == 204) fixture.isSensor = true;
	else if (collision == 205) fixture.isSensor = true;
	else if (collision == 206) fixture.isSensor = true;

	else if (collision == 23) fixture.isSensor = true;
	else if (collision == 32) fixture.isSensor = true;
	else if (collision == 24) fixture.isSensor = true;
	else if (collision == 42) fixture.isSensor = true;
	else if (collision == 52) fixture.isSensor = true;
	else if (collision == 25) fixture.isSensor = true;
	else if (collision == 16) fixture.isSensor = true;
	else if (collision == 61) fixture.isSensor = true;
	else if (collision == 67) fixture.isSensor = true;
	else if (collision == 76) fixture.isSensor = true;

	b2Fixture* fix = p->CreateFixture(&fixture);

	fix->SetUserData((void*)collision);


	return fix;
}

b2Fixture* Physics::CreateDynamicBox(int x, int y, int w, int h)
{
	b2BodyDef g;
	g.type = b2_dynamicBody;
	g.position.Set(PIXELS_TO_METERS(x), PIXELS_TO_METERS(y));
	g.fixedRotation = true;
	g.linearDamping = 100.0f;

	b2Body* p = world->CreateBody(&g);

	b2PolygonShape box;
	box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h));

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.friction = 1.0f;
	fixture.restitution = 0.0f;
	
	b2Fixture* fix = p->CreateFixture(&fixture);
	fix->SetUserData((void*)8);

	return fix;
}

bool Physics::CleanMapBoxes()
{
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			if ((int)f->GetUserData() >= 2)
			{
				b->DestroyFixture(f);
				world->DestroyBody(b);
			}
		}
	}

	return true;
}

void Physics::BeginContact(b2Contact* contact)
{
	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	if ((int)fixtureUserDataA == 1)
	{

		if ((int)fixtureUserDataB == 30)
		{
			//dungeon sensor
			app->dungeon->in_ice++;
		}


		if ((int)fixtureUserDataB == 2)
		{
			// renato contact
			app->dialog->SetPressE_Hide(false);
			inRenato = true;
		}
		else if ((int)fixtureUserDataB == 3)
		{
			// curandero contact
			app->dialog->SetPressE_Hide(false);
			inCurandero = true;
		}
		else if ((int)fixtureUserDataB == 4)
		{
			// herrero contact
			app->dialog->SetPressE_Hide(false);
			inHerrero = true;
		}
		else if ((int)fixtureUserDataB == 5)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(false);
			inGranjero = true;
		}
		else if ((int)fixtureUserDataB == 6)
		{
			// aldeano contact
			app->dialog->SetPressE_Hide(false);
			inAldeano = true;
		}
		else if ((int)fixtureUserDataB == 7)
		{
			// enemy contact
			app->entities->StartCombat();
		}

		// --------------------------------------------------------------- PASS LEVELS
		else if ((int)fixtureUserDataB == 12)
		{
			// town_1 --> town_2
			app->frontground->move_to = MOVE_TO::TOWN1_TOWN2;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 21)
		{
			// town_2 --> town_1
			app->frontground->move_to = MOVE_TO::TOWN2_TOWN1;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 23)
		{
			// town_2 --> forest
			app->frontground->move_to = MOVE_TO::TOWN2_FOREST;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 32)
		{
			// forest --> town_2
			app->frontground->move_to = MOVE_TO::FOREST_TOWN2;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 24)
		{
			// town_2 --> battlefield
			app->frontground->move_to = MOVE_TO::TOWN2_BATTLEFIELD;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 42)
		{
			// battlefield --> town_2
			app->frontground->move_to = MOVE_TO::BATTLEFIELD_TOWN2;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 25)
		{
			// town_2 --> dungeon
			app->frontground->move_to = MOVE_TO::TOWN2_DUNGEON;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 52)
		{
			// dungeon --> town_2
			app->frontground->move_to = MOVE_TO::DUNGEON_TOWN2;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 16)
		{
			// town_1 --> outside_castle
			app->frontground->move_to = MOVE_TO::TOWN1_OUTSIDE;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 61)
		{
			// outside_castle -->  town_1
			app->frontground->move_to = MOVE_TO::OUTSIDE_TOWN1;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 67)
		{
			// outside_castle --> inside_castle
			app->frontground->move_to = MOVE_TO::OUTSIDE_INSIDE;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 76)
		{
			// inside_castle -->  outside_castle
			app->frontground->move_to = MOVE_TO::INSIDE_OUTSIDE;

			app->frontground->FadeToBlack();
		}
	}

	if ((int)fixtureUserDataB == 1)
	{
		if ((int)fixtureUserDataA == 30)
		{
			//dungeon sensor
			app->dungeon->in_ice++;


		}

		if ((int)fixtureUserDataA == 2)
		{
			// renato contact
			app->dialog->SetPressE_Hide(false);
			inRenato = true;
		}
		else if ((int)fixtureUserDataA == 3)
		{
			// curandero contact
			app->dialog->SetPressE_Hide(false);
			inCurandero = true;
		}
		else if ((int)fixtureUserDataA == 4)
		{
			// herrero contact
			app->dialog->SetPressE_Hide(false);
			inHerrero = true;
		}
		else if ((int)fixtureUserDataA == 5)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(false);
			inGranjero = true;
		}
		else if ((int)fixtureUserDataA == 6)
		{
			// aldeano contact
			app->dialog->SetPressE_Hide(false);
			inAldeano = true;
		}
		else if ((int)fixtureUserDataA == 7)
		{
			// enemy contact
			app->entities->StartCombat();
		}

		// --------------------------------------------------------------- PASS LEVELS
		else if ((int)fixtureUserDataA == 12)
		{
			// town_1 --> town_2
			app->frontground->move_to = MOVE_TO::TOWN1_TOWN2;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataA == 21)
		{
			// town_2 --> town_1
			app->frontground->move_to = MOVE_TO::TOWN2_TOWN1;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataA == 23)
		{
			// town_2 --> forest
			app->frontground->move_to = MOVE_TO::TOWN2_FOREST;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataA == 32)
		{
			// forest --> town_2
			app->frontground->move_to = MOVE_TO::FOREST_TOWN2;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataA == 24)
		{
			// town_2 --> battlefield
			app->frontground->move_to = MOVE_TO::TOWN2_BATTLEFIELD;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataB == 42)
		{
			// battlefield --> town_2
			app->frontground->move_to = MOVE_TO::BATTLEFIELD_TOWN2;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataA == 25)
		{
			// town_2 --> dungeon
			app->frontground->move_to = MOVE_TO::TOWN2_DUNGEON;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataA == 52)
		{
			// dungeon --> town_2
			app->frontground->move_to = MOVE_TO::DUNGEON_TOWN2;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataA == 16)
		{
			// town_1 --> outside_castle
			app->frontground->move_to = MOVE_TO::TOWN1_OUTSIDE;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataA == 61)
		{
			// outside_castle -->  town_1
			app->frontground->move_to = MOVE_TO::OUTSIDE_TOWN1;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataA == 67)
		{
			// outside_castle --> inside_castle
			app->frontground->move_to = MOVE_TO::OUTSIDE_INSIDE;

			app->frontground->FadeToBlack();
		}
		else if ((int)fixtureUserDataA == 76)
		{
			// inside_castle -->  outside_castle
			app->frontground->move_to = MOVE_TO::INSIDE_OUTSIDE;

			app->frontground->FadeToBlack();
		}
	}

	if ((int)fixtureUserDataA == 8)
	{
		// COLLIDERS --> SENSORS (RIVER) SOUKOBAN PUZZLE
		if ((int)fixtureUserDataB == 201)
		{
			app->map->S1_Coll->SetSensor(true);

			
		}
		else if ((int)fixtureUserDataB == 202)
		{
			app->map->S2_Coll->SetSensor(true);

			contact->GetFixtureA()->SetSensor(true);
			contact->GetFixtureB()->GetBody()->SetActive(false);


		}
		else if ((int)fixtureUserDataB == 203)
		{
			app->map->S3_Coll->SetSensor(true);

			contact->GetFixtureA()->SetSensor(true);
			contact->GetFixtureB()->GetBody()->SetActive(false);

		}
		else if ((int)fixtureUserDataB == 204)
		{
			app->map->S4_Coll->SetSensor(true);

			contact->GetFixtureA()->SetSensor(true);
			contact->GetFixtureB()->GetBody()->SetActive(false);

		}
		else if ((int)fixtureUserDataB == 205)
		{
			app->map->S5_Coll->SetSensor(true);

			contact->GetFixtureA()->SetSensor(true);
			contact->GetFixtureB()->GetBody()->SetActive(false);

		}
		else if ((int)fixtureUserDataB == 206)
		{
			app->map->S6_Coll->SetSensor(true);

			contact->GetFixtureA()->SetSensor(true);
			contact->GetFixtureB()->GetBody()->SetActive(false);

		}
	}

	if ((int)fixtureUserDataB == 8)
	{
		// COLLIDERS --> SENSORS (RIVER) SOUKOBAN PUZZLE
		if ((int)fixtureUserDataA == 201)
		{
			app->map->S1_Coll->SetSensor(true);

		}
		else if ((int)fixtureUserDataA == 202)
		{
			app->map->S2_Coll->SetSensor(true);

			contact->GetFixtureB()->SetSensor(true);
			contact->GetFixtureA()->GetBody()->SetActive(false);

		}
		else if ((int)fixtureUserDataA == 203)
		{
			app->map->S3_Coll->SetSensor(true);

			contact->GetFixtureB()->SetSensor(true);
			contact->GetFixtureA()->GetBody()->SetActive(false);

		}
		else if ((int)fixtureUserDataA == 204)
		{
			app->map->S4_Coll->SetSensor(true);

			contact->GetFixtureB()->SetSensor(true);
			contact->GetFixtureA()->GetBody()->SetActive(false);

		}
		else if ((int)fixtureUserDataA == 205)
		{
			app->map->S5_Coll->SetSensor(true);

			contact->GetFixtureB()->SetSensor(true);
			contact->GetFixtureA()->GetBody()->SetActive(false);

		}
		else if ((int)fixtureUserDataA == 206)
		{
			app->map->S6_Coll->SetSensor(true);

			contact->GetFixtureB()->SetSensor(true);
			contact->GetFixtureA()->GetBody()->SetActive(false);

		}
	}
	
}

void Physics::EndContact(b2Contact* contact)
{
	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	if ((int)fixtureUserDataA == 1)
	{
		if ((int)fixtureUserDataB == 30)
		{
			//dungeon sensor
			app->dungeon->in_ice--;
		}
		if ((int)fixtureUserDataB == 2)
		{
			// renato contact
			app->dialog->SetPressE_Hide(true);
			inRenato = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataB == 3)
		{
			// curandero contact
			app->dialog->SetPressE_Hide(true);
			inCurandero = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataB == 4)
		{
			// herrero contact
			app->dialog->SetPressE_Hide(true);
			inHerrero = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataB == 5)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(true);
			inGranjero = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataB == 6)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(true);
			inAldeano = false;
			app->dialog->QuitDialogs();
		}
	}

	if ((int)fixtureUserDataB == 1)
	{
		if ((int)fixtureUserDataA == 30)
		{
			//dungeon sensor
			app->dungeon->in_ice--;
		}
		if ((int)fixtureUserDataA == 2)
		{
			// renato contact
			app->dialog->SetPressE_Hide(false);
			inRenato = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataA == 3)
		{
			// curandero contact
			app->dialog->SetPressE_Hide(false);
			inCurandero = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataA == 4)
		{
			// herrero contact
			app->dialog->SetPressE_Hide(false);
			inHerrero = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataA == 5)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(false);
			inGranjero = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataA == 6)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(true);
			inAldeano = false;
			app->dialog->QuitDialogs();
		}
	}
}
