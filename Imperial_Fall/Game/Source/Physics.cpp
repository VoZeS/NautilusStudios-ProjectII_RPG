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
#include "Inventory.h"
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

	coin_picked = false;
	coins_number = 0;
	book_picked = false;

	return true;
}

// Called each loop iteration
bool Physics::PreUpdate()
{
	
	if (!app->menu->GetGameState() && app->inventory->hide)
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
	if (coin_picked)
	{		
		DestroyCoins();
		coin_picked = false;
	}
	else if (book_picked)
	{
		DestroyBook();
		book_picked = false;
	}

	if (app->inventory->misc != NULL)
	{
		SDL_Rect rect = { 256, 0, 64, 64 };
		for (size_t i = 0; i < MAX_COINS; i++)
		{
			if (coins_in_floor[i].alive)
			{
				app->render->AddrenderObject(app->inventory->misc, { METERS_TO_PIXELS(coins_in_floor[i].body->GetPosition().x - 32.0f), METERS_TO_PIXELS(coins_in_floor[i].body->GetPosition().y - 32.0f) }, rect, 1, 1.0f, 0.0f);
				//app->render->DrawTexture(app->inventory->misc, METERS_TO_PIXELS(coins_in_floor[i].body->GetPosition().x) - 32, METERS_TO_PIXELS(coins_in_floor[i].body->GetPosition().y) - 32, &rect);
			}
		}

		for (size_t i = 0; i < MAX_BOOKS; i++)
		{
			if (books_in_floor0[i].alive)
			{
				rect = { 0, 0, 64, 64 };

				app->render->AddrenderObject(app->inventory->misc, { METERS_TO_PIXELS(books_in_floor0[i].body->GetPosition().x - 32.0f), METERS_TO_PIXELS(books_in_floor0[i].body->GetPosition().y - 32.0f) }, rect, 1, 1.0f, 0.0f);
			}
			else if (books_in_floor1[i].alive)
			{
				rect = { 64, 0, 64, 64 };

				app->render->AddrenderObject(app->inventory->misc, { METERS_TO_PIXELS(books_in_floor1[i].body->GetPosition().x - 32.0f), METERS_TO_PIXELS(books_in_floor1[i].body->GetPosition().y - 32.0f) }, rect, 1, 1.0f, 0.0f);
			}
			else if (books_in_floor2[i].alive)
			{
				rect = { 128, 0, 64, 64 };

				app->render->AddrenderObject(app->inventory->misc, { METERS_TO_PIXELS(books_in_floor2[i].body->GetPosition().x - 32.0f), METERS_TO_PIXELS(books_in_floor2[i].body->GetPosition().y - 32.0f) }, rect, 1, 1.0f, 0.0f);
			}
			else if (books_in_floor3[i].alive)
			{
				rect = { 192, 0, 64, 64 };

				app->render->AddrenderObject(app->inventory->misc, { METERS_TO_PIXELS(books_in_floor3[i].body->GetPosition().x - 32.0f), METERS_TO_PIXELS(books_in_floor3[i].body->GetPosition().y - 32.0f) }, rect, 1, 1.0f, 0.0f);
			}
		}
	}
	
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
					case 5: // sabio interaction
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
					case 8: // granjero interaction
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
					case 20: // coins in floor
						c_r = 0;
						c_g = 0;
						c_b = 0;
						break;
					case 22: // book0 in floor
						c_r = 0;
						c_g = 0;
						c_b = 0;
						break;
					case 26: // book1 in floor
						c_r = 0;
						c_g = 0;
						c_b = 0;
						break;
					case 27: // book2 in floor
						c_r = 0;
						c_g = 0;
						c_b = 0;
						break;
					case 28: // book3 in floor
						c_r = 0;
						c_g = 0;
						c_b = 0;
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

	else if (collision == 231) fixture.isSensor = true;
	else if (collision == 232) fixture.isSensor = true;
	else if (collision == 233) fixture.isSensor = true;

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
	// miscelanea
	else if (collision == 20) fixture.isSensor = true;
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
	fix->SetUserData((void*)10);

	return fix;
}

bool Physics::CreateMiscelanea(int x, int y, int w, int h, int collision, int book_id)
{
	b2BodyDef g;
	g.type = b2_staticBody;
	g.position.Set(PIXELS_TO_METERS(x), PIXELS_TO_METERS(y));

	if (collision == 20)
	{
		coins_in_floor[coins_number].body = world->CreateBody(&g);
		coins_in_floor[coins_number].number = coins_number;
		coins_in_floor[coins_number].alive = true;
		coins_in_floor[coins_number].misc_type = 0;
	}
	else if (collision == 22)
	{
		books_in_floor0[book_id].body = world->CreateBody(&g);
		books_in_floor0[book_id].number = book_id;
		books_in_floor0[book_id].alive = true;
		books_in_floor0[book_id].misc_type = 1;
	}
	else if (collision == 26)
	{
		books_in_floor1[book_id].body = world->CreateBody(&g);
		books_in_floor1[book_id].number = book_id;
		books_in_floor1[book_id].alive = true;
		books_in_floor1[book_id].misc_type = 2;
	}
	else if (collision == 27)
	{
		books_in_floor2[book_id].body = world->CreateBody(&g);
		books_in_floor2[book_id].number = book_id;
		books_in_floor2[book_id].alive = true;
		books_in_floor2[book_id].misc_type = 3;
	}
	else if (collision == 28)
	{
		books_in_floor3[book_id].body = world->CreateBody(&g);
		books_in_floor3[book_id].number = book_id;
		books_in_floor3[book_id].alive = true;
		books_in_floor3[book_id].misc_type = 4;
	}
	// PALANCAS
	else if (collision == 60)
	{
		lever[0].body = world->CreateBody(&g);
		lever[0].number = 0;
		lever[0].alive = true;
		lever[0].misc_type = 5;
	}
	else if (collision == 70)
	{
		lever[1].body = world->CreateBody(&g);
		lever[1].number = 1;
		lever[1].alive = true;
		lever[1].misc_type = 5;
	}

	b2PolygonShape box;
	box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h));

	b2FixtureDef fixture;
	fixture.shape = &box;
	// miscelanea
	if (collision == 20) fixture.isSensor = true;
	else if (collision == 60) fixture.isSensor = true;
	else if (collision == 70) fixture.isSensor = true;
	else if (collision == 22) fixture.isSensor = true;
	else if (collision == 26) fixture.isSensor = true;
	else if (collision == 27) fixture.isSensor = true;
	else if (collision == 28) fixture.isSensor = true;

	b2Fixture* fix;
	if (collision == 20)
	{
		fix = coins_in_floor[coins_number].body->CreateFixture(&fixture);
		coins_number++;
		fix->SetUserData((void*)collision);
	}
	else if (collision == 60)
	{
		fix = lever[0].body->CreateFixture(&fixture);
		fix->SetUserData((void*)collision);
	}
	else if (collision == 70)
	{
		fix = lever[1].body->CreateFixture(&fixture);
		fix->SetUserData((void*)collision);
	}
	else if (collision == 22)
	{
		fix = books_in_floor0[book_id].body->CreateFixture(&fixture);
		fix->SetUserData((void*)collision);
	}
	else if (collision == 26)
	{
		fix = books_in_floor1[book_id].body->CreateFixture(&fixture);
		fix->SetUserData((void*)collision);
	}
	else if (collision == 27)
	{
		fix = books_in_floor2[book_id].body->CreateFixture(&fixture);
		fix->SetUserData((void*)collision);
	}
	else if (collision == 28)
	{
		fix = books_in_floor3[book_id].body->CreateFixture(&fixture);
		fix->SetUserData((void*)collision);
	}

	return true;
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
			// sabio contact
			app->dialog->SetPressE_Hide(false);
			inSabio = true;
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
		else if ((int)fixtureUserDataB == 8)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(false);
			inGranjero = true;
		}
		else if ((int)fixtureUserDataB == 9)
		{
			// signal contact
			app->dialog->SetPressE_Hide(false);
			inSignal = true;
		}
		else if ((int)fixtureUserDataB == 20)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(false);
			inCoins = true;
		}
		else if ((int)fixtureUserDataB == 60)
		{
			// lever 1 in floor contact
			app->dialog->SetPressE_Hide(false);
			inLever1 = true;
		}
		else if ((int)fixtureUserDataB == 70)
		{
			// lever 1 in floor contact
			app->dialog->SetPressE_Hide(false);
			inLever2 = true;
		}
		else if ((int)fixtureUserDataB == 22)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(false);
			inBook = true;
			book_type = 0;
		}
		else if ((int)fixtureUserDataB == 26)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(false);
			inBook = true;
			book_type = 1;
		}
		else if ((int)fixtureUserDataB == 27)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(false);
			inBook = true;
			book_type = 2;
		}
		else if ((int)fixtureUserDataB == 28)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(false);
			inBook = true;
			book_type = 3;
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
			// sabio contact
			app->dialog->SetPressE_Hide(false);
			inSabio = true;
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
		else if ((int)fixtureUserDataA == 8)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(false);
			inGranjero = true;
		}
		else if ((int)fixtureUserDataA == 9)
		{
			// signal contact
			app->dialog->SetPressE_Hide(false);
			inSignal = true;
		}
		else if ((int)fixtureUserDataA == 20)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(false);
			inCoins = true;
		}
		else if ((int)fixtureUserDataA == 60)
		{
			// lever 1 in floor contact
			app->dialog->SetPressE_Hide(false);
			inLever1 = true;
		}
		else if ((int)fixtureUserDataA == 70)
		{
			// lever 1 in floor contact
			app->dialog->SetPressE_Hide(false);
			inLever2 = true;
		}
		else if ((int)fixtureUserDataA == 22)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(false);
			inBook = true;
			book_type = 0;
		}
		else if ((int)fixtureUserDataA == 26)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(false);
			inBook = true;
			book_type = 1;
		}
		else if ((int)fixtureUserDataA == 27)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(false);
			inBook = true;
			book_type = 2;
		}
		else if ((int)fixtureUserDataA == 28)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(false);
			inBook = true;
			book_type = 3;
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
		else if ((int)fixtureUserDataA == 42)
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

	if ((int)fixtureUserDataA == 10)
	{
		// COLLIDERS --> SENSORS (RIVER) SOUKOBAN PUZZLE
		if ((int)fixtureUserDataB == 201)
		{
			app->map->S1_Coll->SetSensor(true);


		}
		else if ((int)fixtureUserDataB == 202)
		{
			app->map->S2_Coll->SetSensor(true);

		}
		else if ((int)fixtureUserDataB == 231)
		{
			contact->GetFixtureA()->SetSensor(true);
			contact->GetFixtureB()->GetBody()->SetActive(false);
		}
		else if ((int)fixtureUserDataB == 203)
		{
			app->map->S3_Coll->SetSensor(true);

		}
		else if ((int)fixtureUserDataB == 232)
		{
			contact->GetFixtureA()->SetSensor(true);
			contact->GetFixtureB()->GetBody()->SetActive(false);
		}
		else if ((int)fixtureUserDataB == 204)
		{
			app->map->S4_Coll->SetSensor(true);
		}
		else if ((int)fixtureUserDataB == 233)
		{
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

	if ((int)fixtureUserDataB == 10)
	{
		// COLLIDERS --> SENSORS (RIVER) SOUKOBAN PUZZLE
		if ((int)fixtureUserDataA == 201)
		{
			app->map->S1_Coll->SetSensor(true);


		}
		else if ((int)fixtureUserDataA == 202)
		{
			app->map->S2_Coll->SetSensor(true);

		}
		else if ((int)fixtureUserDataA == 231)
		{
			contact->GetFixtureB()->SetSensor(true);
			contact->GetFixtureA()->GetBody()->SetActive(false);
		}
		else if ((int)fixtureUserDataA == 203)
		{
			app->map->S3_Coll->SetSensor(true);

		}
		else if ((int)fixtureUserDataA == 232)
		{
			contact->GetFixtureB()->SetSensor(true);
			contact->GetFixtureA()->GetBody()->SetActive(false);
		}
		else if ((int)fixtureUserDataA == 204)
		{
			app->map->S4_Coll->SetSensor(true);
		}
		else if ((int)fixtureUserDataA == 233)
		{
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
			// sabio contact
			app->dialog->SetPressE_Hide(true);
			inSabio = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataB == 6)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(true);
			inAldeano = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataB == 8)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(true);
			inGranjero = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataB == 9)
		{
			// signal contact
			app->dialog->SetPressE_Hide(true);
			inSignal = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataB == 20)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(true);
			inCoins = false;
		}
		else if ((int)fixtureUserDataB == 60)
		{
			// lever 1 in floor contact
			app->dialog->SetPressE_Hide(true);
			inLever1 = false;
		}
		else if ((int)fixtureUserDataB == 70)
		{
			// lever 1 in floor contact
			app->dialog->SetPressE_Hide(true);
			inLever2 = false;
		}
		else if ((int)fixtureUserDataB == 22)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(true);
			inBook = false;
			book_type = -1;
		}
		else if ((int)fixtureUserDataB == 26)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(true);
			inBook = false;
			book_type = -1;
		}
		else if ((int)fixtureUserDataB == 27)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(true);
			inBook = false;
			book_type = -1;
		}
		else if ((int)fixtureUserDataB == 28)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(true);
			inBook = false;
			book_type = -1;
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
			// sabio contact
			app->dialog->SetPressE_Hide(false);
			inSabio = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataA == 6)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(true);
			inAldeano = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataA == 8)
		{
			// granjero contact
			app->dialog->SetPressE_Hide(false);
			inGranjero = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataA == 9)
		{
			// signal contact
			app->dialog->SetPressE_Hide(true);
			inSignal = false;
			app->dialog->QuitDialogs();
		}
		else if ((int)fixtureUserDataA == 20)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(true);
			inCoins = false;
		}
		else if ((int)fixtureUserDataA == 60)
		{
			// lever 1 in floor contact
			app->dialog->SetPressE_Hide(true);
			inLever1 = false;
		}
		else if ((int)fixtureUserDataA == 70)
		{
			// lever 1 in floor contact
			app->dialog->SetPressE_Hide(true);
			inLever2 = false;
		}
		else if ((int)fixtureUserDataA == 22)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(true);
			inBook = false;
			book_type = -1;
		}
		else if ((int)fixtureUserDataA == 26)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(true);
			inBook = false;
			book_type = -1;
		}
		else if ((int)fixtureUserDataA == 27)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(true);
			inBook = false;
			book_type = -1;
		}
		else if ((int)fixtureUserDataA == 28)
		{
			// coins in floor contact
			app->dialog->SetPressE_Hide(true);
			inBook = false;
			book_type = -1;
		}
	}
}

void Physics::DestroyCoins()
{
	float max = 9999;
	b2Body* body = NULL;
	int number = -1;

	fPoint pos1 = app->entities->GetPlayer()->GetPlayerPosition();

	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			fPoint pos2 = { b->GetPosition().x, b->GetPosition().y };
			if ((int)f->GetUserData() == 20 && (abs(pos1.DistanceTo(pos2)) < max))
			{
				body = b;
				max = abs(pos1.DistanceTo(pos2));
			}
		}
	}

	for (size_t i = 0; i < MAX_COINS; i++)
	{
		if (coins_in_floor[i].body == body)
		{
			number = coins_in_floor[i].number;
			coins_in_floor[i].alive = false;
			break;
		}
	}

	world->DestroyBody(body);

	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(MISCELANEA_FILENAME);

	std::string p1 = "coins_in_room";
	std::string s1;
	switch (app->frontground->current_level)
	{
	case 1: s1 = std::to_string(0); break;
	case 2: s1 = std::to_string(1); break;
	case 3: s1 = std::to_string(2); break;
	case 4: s1 = std::to_string(3); break;
	case 5: s1 = std::to_string(4); break;
	case 6: s1 = std::to_string(5); break;
	case 7: s1 = std::to_string(6); break;
	default: break;
	}
	std::string t1 = p1 + s1;
	const char* c1 = t1.c_str();

	std::string p2 = "picked";
	std::string s2 = std::to_string(number);
	std::string t2 = p2 + s2;
	const char* c2 = t2.c_str();

	saveGame.child("miscelanea").child("coins").child(c1).attribute(c2).set_value(true);

	saveGame.save_file(MISCELANEA_FILENAME);
}

void Physics::DestroyBook()
{
	float max = 9999;
	b2Body* body = NULL;
	int number = -1;
	int book_owner = -1;

	fPoint pos1 = app->entities->GetPlayer()->GetPlayerPosition();

	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			fPoint pos2 = { b->GetPosition().x, b->GetPosition().y };
			if (((int)f->GetUserData() == 22 || (int)f->GetUserData() == 26 || (int)f->GetUserData() == 27 || (int)f->GetUserData() == 28)
				&& (abs(pos1.DistanceTo(pos2)) < max))
			{
				body = b;
				max = abs(pos1.DistanceTo(pos2));
				book_owner = (int)f->GetUserData();
			}
		}
	}

	for (size_t i = 0; i < MAX_BOOKS; i++)
	{
		if (books_in_floor0[i].body == body)
		{
			number = books_in_floor0[i].number;
			books_in_floor0[i].alive = false;
			break;
		}
		else if (books_in_floor1[i].body == body)
		{
			number = books_in_floor1[i].number;
			books_in_floor1[i].alive = false;
			break;
		}
		else if (books_in_floor2[i].body == body)
		{
			number = books_in_floor2[i].number;
			books_in_floor2[i].alive = false;
			break;
		}
		else if (books_in_floor3[i].body == body)
		{
			number = books_in_floor3[i].number;
			books_in_floor3[i].alive = false;
			break;
		}
	}

	world->DestroyBody(body);

	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(MISCELANEA_FILENAME);

	std::string p1 = "books_in_room";
	std::string s1;
	switch (app->frontground->current_level)
	{
	case 1: s1 = std::to_string(0); break;
	case 2: s1 = std::to_string(1); break;
	case 3: s1 = std::to_string(2); break;
	case 4: s1 = std::to_string(3); break;
	case 5: s1 = std::to_string(4); break;
	case 6: s1 = std::to_string(5); break;
	case 7: s1 = std::to_string(6); break;
	default: break;
	}
	std::string t1 = p1 + s1;
	const char* c1 = t1.c_str();

	std::string p3 = "books";
	std::string s3;
	switch (book_owner)
	{
	case 22: s3 = std::to_string(0); break;
	case 26: s3 = std::to_string(1); break;
	case 27: s3 = std::to_string(2); break;
	case 28: s3 = std::to_string(3); break;
	default: break;
	}
	std::string t3 = p3 + s3;
	const char* c3 = t3.c_str();

	std::string p2 = "picked";
	std::string s2 = std::to_string(number);
	std::string t2 = p2 + s2;
	const char* c2 = t2.c_str();

	saveGame.child("miscelanea").child(c3).child(c1).attribute(c2).set_value(true);

	saveGame.save_file(MISCELANEA_FILENAME);
}

void Physics::ResetMiscelanea()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(MISCELANEA_FILENAME);

	for (size_t i = 0; i < MAX_COINS; i++)
	{
		std::string p1 = "picked";
		std::string s1 = std::to_string(i);
		std::string t1 = p1 + s1;
		const char* c1 = t1.c_str();

		for (size_t j = 0; j < 7; j++)
		{
			std::string p2 = "coins_in_room";
			std::string s2 = std::to_string(j);
			std::string t2 = p2 + s2;
			const char* c2 = t2.c_str();
			saveGame.child("miscelanea").child("coins").child(c2).attribute(c1).set_value(false);
		}
	}
	
	for (size_t i = 0; i < MAX_BOOKS; i++)
	{
		std::string p1 = "picked";
		std::string s1 = std::to_string(i);
		std::string t1 = p1 + s1;
		const char* c1 = t1.c_str();

		for (size_t j = 0; j < 7; j++)
		{
			std::string p2 = "books_in_room";
			std::string s2 = std::to_string(j);
			std::string t2 = p2 + s2;
			const char* c2 = t2.c_str();

			for (size_t k = 0; k < 4; k++)
			{
				std::string p3 = "books";
				std::string s3 = std::to_string(k);
				std::string t3 = p3 + s3;
				const char* c3 = t3.c_str();

				saveGame.child("miscelanea").child(c3).child(c2).attribute(c1).set_value(false);
			}
		}
	}

	saveGame.save_file(MISCELANEA_FILENAME);
}