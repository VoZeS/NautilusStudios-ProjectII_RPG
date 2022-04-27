#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Physics.h"
#include "Player.h"
#include "Pathfinding.h"
#include "Menu.h"
#include "Frontground.h"

#include "Defs.h"
#include "Log.h"

Player::Player() : Entity()
{
	// main idle animation
	idleAnimD.PushBack({ 5, 2, 50, 72 });
	idleAnimD.PushBack({ 65, 2, 50, 72 });
	idleAnimD.speed = 0.03f;

	idleAnimU.PushBack({ 5, 242, 50, 72 });
	idleAnimU.PushBack({ 65, 242, 50, 72 });
	idleAnimU.speed = 0.03f;

	idleAnimL.PushBack({ 5, 82, 50, 72 });
	idleAnimL.PushBack({ 65, 82, 50, 72 });
	idleAnimL.speed = 0.03f;

	idleAnimR.PushBack({ 5, 161, 50, 72 });
	idleAnimR.PushBack({ 65, 161, 50, 72 });
	idleAnimR.speed = 0.03f;

	// main walk animation
	walkAnimD.PushBack({ 5, 2, 50, 72 });
	walkAnimD.PushBack({ 65, 2, 50, 72 });
	walkAnimD.PushBack({ 125, 2, 50, 72 });
	walkAnimD.speed = 0.1f;

	walkAnimU.PushBack({ 5, 242, 50, 72 });
	walkAnimU.PushBack({ 65, 242, 50, 72 });
	walkAnimU.PushBack({ 125, 242, 50, 72 });
	walkAnimU.speed = 0.1f;

	walkAnimL.PushBack({ 5, 82, 50, 72 });
	walkAnimL.PushBack({ 65, 82, 50, 72 });
	walkAnimL.PushBack({ 125, 82, 50, 72 });
	walkAnimL.speed = 0.1f;

	walkAnimR.PushBack({ 5, 161, 50, 72 });
	walkAnimR.PushBack({ 65, 161, 50, 72 });
	walkAnimR.PushBack({ 125, 161, 50, 72 });
	walkAnimR.speed = 0.1f;

	// c0 idle animation
	c0_idleAnimD.PushBack({ 5, 2, 50, 72 });
	c0_idleAnimD.PushBack({ 65, 2, 50, 72 });
	c0_idleAnimD.speed = 0.03f;

	c0_idleAnimU.PushBack({ 5, 242, 50, 72 });
	c0_idleAnimU.PushBack({ 65, 242, 50, 72 });
	c0_idleAnimU.speed = 0.03f;

	c0_idleAnimL.PushBack({ 5, 82, 50, 72 });
	c0_idleAnimL.PushBack({ 65, 82, 50, 72 });
	c0_idleAnimL.speed = 0.03f;

	c0_idleAnimR.PushBack({ 5, 161, 50, 72 });
	c0_idleAnimR.PushBack({ 65, 161, 50, 72 });
	c0_idleAnimR.speed = 0.03f;

	// c0 walk animation
	c0_walkAnimD.PushBack({ 5, 2, 50, 72 });
	c0_walkAnimD.PushBack({ 65, 2, 50, 72 });
	c0_walkAnimD.PushBack({ 125, 2, 50, 72 });
	c0_walkAnimD.speed = 0.1f;

	c0_walkAnimU.PushBack({ 5, 242, 50, 72 });
	c0_walkAnimU.PushBack({ 65, 242, 50, 72 });
	c0_walkAnimU.PushBack({ 125, 242, 50, 72 });
	c0_walkAnimU.speed = 0.1f;

	c0_walkAnimL.PushBack({ 5, 82, 50, 72 });
	c0_walkAnimL.PushBack({ 65, 82, 50, 72 });
	c0_walkAnimL.PushBack({ 125, 82, 50, 72 });
	c0_walkAnimL.speed = 0.1f;

	c0_walkAnimR.PushBack({ 5, 161, 50, 72 });
	c0_walkAnimR.PushBack({ 65, 161, 50, 72 });
	c0_walkAnimR.PushBack({ 125, 161, 50, 72 });
	c0_walkAnimR.speed = 0.1f;

	// c1 idle animation
	c1_idleAnimD.PushBack({ 5, 2, 50, 72 });
	c1_idleAnimD.PushBack({ 65, 2, 50, 72 });
	c1_idleAnimD.speed = 0.03f;

	c1_idleAnimU.PushBack({ 5, 242, 50, 72 });
	c1_idleAnimU.PushBack({ 65, 242, 50, 72 });
	c1_idleAnimU.speed = 0.03f;

	c1_idleAnimL.PushBack({ 5, 82, 50, 72 });
	c1_idleAnimL.PushBack({ 65, 82, 50, 72 });
	c1_idleAnimL.speed = 0.03f;

	c1_idleAnimR.PushBack({ 5, 161, 50, 72 });
	c1_idleAnimR.PushBack({ 65, 161, 50, 72 });
	c1_idleAnimR.speed = 0.03f;

	// c1 walk animation
	c1_walkAnimD.PushBack({ 5, 2, 50, 72 });
	c1_walkAnimD.PushBack({ 65, 2, 50, 72 });
	c1_walkAnimD.PushBack({ 125, 2, 50, 72 });
	c1_walkAnimD.speed = 0.1f;

	c1_walkAnimU.PushBack({ 5, 242, 50, 72 });
	c1_walkAnimU.PushBack({ 65, 242, 50, 72 });
	c1_walkAnimU.PushBack({ 125, 242, 50, 72 });
	c1_walkAnimU.speed = 0.1f;

	c1_walkAnimL.PushBack({ 5, 82, 50, 72 });
	c1_walkAnimL.PushBack({ 65, 82, 50, 72 });
	c1_walkAnimL.PushBack({ 125, 82, 50, 72 });
	c1_walkAnimL.speed = 0.1f;

	c1_walkAnimR.PushBack({ 5, 161, 50, 72 });
	c1_walkAnimR.PushBack({ 65, 161, 50, 72 });
	c1_walkAnimR.PushBack({ 125, 161, 50, 72 });
	c1_walkAnimR.speed = 0.1f;

	// c2 idle animation
	c2_idleAnimD.PushBack({ 5, 2, 50, 72 });
	c2_idleAnimD.PushBack({ 65, 2, 50, 72 });
	c2_idleAnimD.speed = 0.03f;

	c2_idleAnimU.PushBack({ 5, 242, 50, 72 });
	c2_idleAnimU.PushBack({ 65, 242, 50, 72 });
	c2_idleAnimU.speed = 0.03f;

	c2_idleAnimL.PushBack({ 5, 82, 50, 72 });
	c2_idleAnimL.PushBack({ 65, 82, 50, 72 });
	c2_idleAnimL.speed = 0.03f;

	c2_idleAnimR.PushBack({ 5, 161, 50, 72 });
	c2_idleAnimR.PushBack({ 65, 161, 50, 72 });
	c2_idleAnimR.speed = 0.03f;

	// c2 walk animation
	c2_walkAnimD.PushBack({ 5, 2, 50, 72 });
	c2_walkAnimD.PushBack({ 65, 2, 50, 72 });
	c2_walkAnimD.PushBack({ 125, 2, 50, 72 });
	c2_walkAnimD.speed = 0.1f;

	c2_walkAnimU.PushBack({ 5, 242, 50, 72 });
	c2_walkAnimU.PushBack({ 65, 242, 50, 72 });
	c2_walkAnimU.PushBack({ 125, 242, 50, 72 });
	c2_walkAnimU.speed = 0.1f;

	c2_walkAnimL.PushBack({ 5, 82, 50, 72 });
	c2_walkAnimL.PushBack({ 65, 82, 50, 72 });
	c2_walkAnimL.PushBack({ 125, 82, 50, 72 });
	c2_walkAnimL.speed = 0.1f;

	c2_walkAnimR.PushBack({ 5, 161, 50, 72 });
	c2_walkAnimR.PushBack({ 65, 161, 50, 72 });
	c2_walkAnimR.PushBack({ 125, 161, 50, 72 });
	c2_walkAnimR.speed = 0.1f;
}

// Destructor
Player::~Player()
{}

void Player::InitCustomEntity(int npc)
{
	currentAnimation = &idleAnimD;
	look_dir = 1;
	collision_active = true;
	player_enabled = true;

	walk_sound = app->audio->LoadFx("Assets/audio/fx/step_sound.wav");

	// body
	b2BodyDef p_body;
	p_body.type = b2_dynamicBody;
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
	bodyFixture = body->CreateFixture(&fixture);
	bodyFixture->SetSensor(false);
	bodyFixture->SetUserData((void*)1); // player collision

	// companion 0
	c0.comp_number = 0;
	c0.currentAnimation = &c0_idleAnimD;

	b2BodyDef c0_body;
	c0_body.type = b2_kinematicBody;
	c0_body.fixedRotation = true;
	c0_body.position.Set(position.x - 2, position.y);

	c0.body = app->physics->world->CreateBody(&c0_body);

	b2Fixture* c0_Fixture = body->CreateFixture(&fixture);
	c0_Fixture->SetSensor(true);

	// companion 1
	c1.comp_number = 1;
	c1.currentAnimation = &c1_idleAnimD;

	b2BodyDef c1_body;
	c1_body.type = b2_kinematicBody;
	c1_body.fixedRotation = true;
	c1_body.position.Set(position.x - 4, position.y);

	c1.body = app->physics->world->CreateBody(&c1_body);

	b2Fixture* c1_Fixture = body->CreateFixture(&fixture);
	c1_Fixture->SetSensor(true);

	// companion 2
	c2.comp_number = 2;
	c2.currentAnimation = &c2_idleAnimD;

	b2BodyDef c2_body;
	c2_body.type = b2_dynamicBody;
	c2_body.fixedRotation = true;
	c2_body.position.Set(position.x - 6, position.y);

	c2.body = app->physics->world->CreateBody(&c2_body);

	b2Fixture* c2_Fixture = body->CreateFixture(&fixture);
	c2_Fixture->SetSensor(true);
}

// Called each loop iteration
bool Player::PreUpdate()
{
	if (player_enabled)
	{
		position.x = body->GetPosition().x;
		position.y = body->GetPosition().y;

		// companions
		c0.position.x = c0.body->GetPosition().x;
		c0.position.y = c0.body->GetPosition().y;
		c1.position.x = c1.body->GetPosition().x;
		c1.position.y = c1.body->GetPosition().y;
		c2.position.x = c2.body->GetPosition().x;
		c2.position.y = c2.body->GetPosition().y;
	}

	return true;
}

void Player::HandleInput(float dt)
{
	if (player_enabled)
	{
		if (app->frontground->controller)
		{
			// Get gamepad info
			GamePad& pad = app->input->pads[0];

			if (pad.left_y < -0.5f)
			{
				app->input->SetKey(SDL_SCANCODE_W, KEY_REPEAT);
			}
			if (pad.left_y > 0.5f)
			{
				app->input->SetKey(SDL_SCANCODE_S, KEY_REPEAT);
			}
			if (pad.left_x < -0.5f)
			{
				app->input->SetKey(SDL_SCANCODE_A, KEY_REPEAT);
			}
			if (pad.left_x > 0.5f)
			{
				app->input->SetKey(SDL_SCANCODE_D, KEY_REPEAT);
			}
		}

		float fixedSpeed = speed * dt;

		if (app->frontground->godmode)
		{
			fixedSpeed *= 2;
			if (collision_active)
			{
				body->DestroyFixture(bodyFixture);
				b2PolygonShape box;
				box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h));
				b2FixtureDef fixture;
				fixture.shape = &box;
				fixture.density = 1.0f;
				fixture.friction = 0.0f;
				bodyFixture = body->CreateFixture(&fixture);
				bodyFixture->SetSensor(true);
				bodyFixture->SetUserData((void*)1); // player without collision

				collision_active = false;
			}
		}
		else
		{
			if (!collision_active)
			{
				body->DestroyFixture(bodyFixture);
				b2PolygonShape box;
				box.SetAsBox(PIXELS_TO_METERS(w), PIXELS_TO_METERS(h));
				b2FixtureDef fixture;
				fixture.shape = &box;
				fixture.density = 1.0f;
				fixture.friction = 0.0f;
				bodyFixture = body->CreateFixture(&fixture);
				bodyFixture->SetSensor(false);
				bodyFixture->SetUserData((void*)1); // player collision

				collision_active = true;
			}
		}

		if (!app->menu->GetGameState())
		{
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE || app->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE)
			{
				// move up
				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
				{
					body->SetLinearVelocity({ body->GetLinearVelocity().x, -fixedSpeed });
					look_dir = 0;

					if (currentAnimation != &walkAnimU && body->GetLinearVelocity().x == 0)
					{
						walkAnimU.Reset();
						currentAnimation = &walkAnimU;
					}
				}
				else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
				{
					body->SetLinearVelocity({ body->GetLinearVelocity().x, 0 });

					if (currentAnimation != &idleAnimU)
					{
						idleAnimU.Reset();
						currentAnimation = &idleAnimU;
					}
				}

				// move down
				if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
				{
					body->SetLinearVelocity({ body->GetLinearVelocity().x, fixedSpeed });
					look_dir = 1;

					if (currentAnimation != &walkAnimD && body->GetLinearVelocity().x == 0)
					{
						walkAnimD.Reset();
						currentAnimation = &walkAnimD;
					}
				}
				else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
				{
					body->SetLinearVelocity({ body->GetLinearVelocity().x, 0 });

					if (currentAnimation != &idleAnimD)
					{
						idleAnimD.Reset();
						currentAnimation = &idleAnimD;
					}
				}
			}
			else
			{
				body->SetLinearVelocity({ body->GetLinearVelocity().x, 0 });
			}

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE || app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
			{
				// move left
				if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
				{
					body->SetLinearVelocity({ -fixedSpeed, body->GetLinearVelocity().y });
					look_dir = 2;

					if (currentAnimation != &walkAnimL)
					{
						walkAnimL.Reset();
						currentAnimation = &walkAnimL;
					}
				}
				else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
				{
					body->SetLinearVelocity({ 0, body->GetLinearVelocity().y });

					if (currentAnimation != &idleAnimL)
					{
						idleAnimL.Reset();
						currentAnimation = &idleAnimL;
					}
				}

				//Move Right
				if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
				{
					body->SetLinearVelocity({ fixedSpeed, body->GetLinearVelocity().y });
					look_dir = 3;

					if (currentAnimation != &walkAnimR)
					{
						walkAnimR.Reset();
						currentAnimation = &walkAnimR;
					}
				}
				else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
				{
					body->SetLinearVelocity({ 0, body->GetLinearVelocity().y });

					if (currentAnimation != &idleAnimR)
					{
						idleAnimR.Reset();
						currentAnimation = &idleAnimR;
					}
				}
			}
			else
			{
				body->SetLinearVelocity({ 0, body->GetLinearVelocity().y });
			}


			if (body->GetLinearVelocity().x != 0 || body->GetLinearVelocity().y != 0)
			{
				walk_cd -= dt;
				if (walk_cd <= 0)
				{
					app->audio->PlayFx(walk_sound);
					walk_cd = 320;
				}
			}


			if (body->GetLinearVelocity().x == 0 && body->GetLinearVelocity().y == 0)
			{
				switch (look_dir)
				{
				case 0:
					if (currentAnimation != &idleAnimU)
					{
						idleAnimU.Reset();
						currentAnimation = &idleAnimU;
					}
					break;
				case 1:
					if (currentAnimation != &idleAnimD)
					{
						idleAnimD.Reset();
						currentAnimation = &idleAnimD;
					}
					break;
				case 2:
					if (currentAnimation != &idleAnimL)
					{
						idleAnimL.Reset();
						currentAnimation = &idleAnimL;
					}
					break;
				case 3:
					if (currentAnimation != &idleAnimR)
					{
						idleAnimR.Reset();
						currentAnimation = &idleAnimR;
					}
					break;
				}
			}

			currentAnimation->Update();
		}

		if (app->entities->freeze)
		{
			body->SetLinearVelocity({ 0, 0 });
		}


		// Charge character
		/*if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			char_control = 0;
		}
		else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			char_control = 1;
		}
		else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{
			char_control = 2;
		}
		else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			char_control = 3;
		}*/
	}
}

// Called each loop iteration
bool Player::Update(float dt)
{
	if (player_enabled)
	{
		FollowPlayer(c0, c0, dt);
		FollowPlayer(c1, c0, dt);
		FollowPlayer(c2, c1, dt);

		// c0 animation
		if (abs(c0.body->GetLinearVelocity().x) > abs(c0.body->GetLinearVelocity().y))
		{
			if (c0.body->GetLinearVelocity().x > 0)
			{
				if (c0.currentAnimation != &c0_walkAnimR)
				{
					c0_walkAnimR.Reset();
					c0.currentAnimation = &c0_walkAnimR;
				}
				c0.look_dir = 3;
			}
			else
			{
				if (c0.currentAnimation != &c0_walkAnimL)
				{
					c0_walkAnimL.Reset();
					c0.currentAnimation = &c0_walkAnimL;
				}
				c0.look_dir = 2;
			}
		}
		else if (abs(c0.body->GetLinearVelocity().x) < abs(c0.body->GetLinearVelocity().y))
		{
			if (c0.body->GetLinearVelocity().y > 0)
			{
				if (c0.currentAnimation != &c0_walkAnimD)
				{
					c0_walkAnimD.Reset();
					c0.currentAnimation = &c0_walkAnimD;
				}
				c0.look_dir = 1;
			}
			else
			{
				if (c0.currentAnimation != &c0_walkAnimU)
				{
					c0_walkAnimU.Reset();
					c0.currentAnimation = &c0_walkAnimU;
				}
				c0.look_dir = 0;
			}
		}
		else
		{
			switch (c0.look_dir)
			{
			case 0:
				if (c0.currentAnimation != &c0_idleAnimU)
				{
					c0_idleAnimU.Reset();
					c0.currentAnimation = &c0_idleAnimU;
				}
				break;
			case 1:
				if (c0.currentAnimation != &c0_idleAnimD)
				{
					c0_idleAnimD.Reset();
					c0.currentAnimation = &c0_idleAnimD;
				}
				break;
			case 2:
				if (c0.currentAnimation != &c0_idleAnimL)
				{
					c0_idleAnimL.Reset();
					c0.currentAnimation = &c0_idleAnimL;
				}
				break;
			case 3:
				if (c0.currentAnimation != &c0_idleAnimR)
				{
					c0_idleAnimR.Reset();
					c0.currentAnimation = &c0_idleAnimR;
				}
				break;
			}
		}

		c0.currentAnimation->Update();

		// c1 animation
		if (abs(c1.body->GetLinearVelocity().x) > abs(c1.body->GetLinearVelocity().y))
		{
			if (c1.body->GetLinearVelocity().x > 0)
			{
				if (c1.currentAnimation != &c1_walkAnimR)
				{
					c1_walkAnimR.Reset();
					c1.currentAnimation = &c1_walkAnimR;
				}
				c1.look_dir = 3;
			}
			else
			{
				if (c1.currentAnimation != &c1_walkAnimL)
				{
					c1_walkAnimL.Reset();
					c1.currentAnimation = &c1_walkAnimL;
				}
				c1.look_dir = 2;
			}
		}
		else if (abs(c1.body->GetLinearVelocity().x) < abs(c1.body->GetLinearVelocity().y))
		{
			if (c1.body->GetLinearVelocity().y > 0)
			{
				if (c1.currentAnimation != &c1_walkAnimD)
				{
					c1_walkAnimD.Reset();
					c1.currentAnimation = &c1_walkAnimD;
				}
				c1.look_dir = 1;
			}
			else
			{
				if (c1.currentAnimation != &c1_walkAnimU)
				{
					c1_walkAnimU.Reset();
					c1.currentAnimation = &c1_walkAnimU;
				}
				c1.look_dir = 0;
			}
		}
		else
		{
			switch (c1.look_dir)
			{
			case 0:
				if (c1.currentAnimation != &c1_idleAnimU)
				{
					c1_idleAnimU.Reset();
					c1.currentAnimation = &c1_idleAnimU;
				}
				break;
			case 1:
				if (c1.currentAnimation != &c1_idleAnimD)
				{
					c1_idleAnimD.Reset();
					c1.currentAnimation = &c1_idleAnimD;
				}
				break;
			case 2:
				if (c1.currentAnimation != &c1_idleAnimL)
				{
					c1_idleAnimL.Reset();
					c1.currentAnimation = &c1_idleAnimL;
				}
				break;
			case 3:
				if (c1.currentAnimation != &c1_idleAnimR)
				{
					c1_idleAnimR.Reset();
					c1.currentAnimation = &c1_idleAnimR;
				}
				break;
			}
		}

		c1.currentAnimation->Update();

		// c2 animation
		if (abs(c2.body->GetLinearVelocity().x) > abs(c2.body->GetLinearVelocity().y))
		{
			if (c2.body->GetLinearVelocity().x > 0)
			{
				if (c2.currentAnimation != &c2_walkAnimR)
				{
					c2_walkAnimR.Reset();
					c2.currentAnimation = &c2_walkAnimR;
				}
				c2.look_dir = 3;
			}
			else
			{
				if (c2.currentAnimation != &c2_walkAnimL)
				{
					c2_walkAnimL.Reset();
					c2.currentAnimation = &c2_walkAnimL;
				}
				c2.look_dir = 2;
			}
		}
		else if (abs(c2.body->GetLinearVelocity().x) < abs(c2.body->GetLinearVelocity().y))
		{
			if (c2.body->GetLinearVelocity().y > 0)
			{
				if (c2.currentAnimation != &c2_walkAnimD)
				{
					c2_walkAnimD.Reset();
					c2.currentAnimation = &c2_walkAnimD;
				}
				c2.look_dir = 1;
			}
			else
			{
				if (c2.currentAnimation != &c2_walkAnimU)
				{
					c2_walkAnimU.Reset();
					c2.currentAnimation = &c2_walkAnimU;
				}
				c2.look_dir = 0;
			}
		}
		else
		{
			switch (c2.look_dir)
			{
			case 0:
				if (c2.currentAnimation != &c2_idleAnimU)
				{
					c2_idleAnimU.Reset();
					c2.currentAnimation = &c2_idleAnimU;
				}
				break;
			case 1:
				if (c2.currentAnimation != &c2_idleAnimD)
				{
					c2_idleAnimD.Reset();
					c2.currentAnimation = &c2_idleAnimD;
				}
				break;
			case 2:
				if (c2.currentAnimation != &c2_idleAnimL)
				{
					c2_idleAnimL.Reset();
					c2.currentAnimation = &c2_idleAnimL;
				}
				break;
			case 3:
				if (c2.currentAnimation != &c2_idleAnimR)
				{
					c2_idleAnimR.Reset();
					c2.currentAnimation = &c2_idleAnimR;
				}
				break;
			}
		}

		c2.currentAnimation->Update();
	}

	return true;
}

// Called each loop iteration
bool Player::Draw()
{
	if (plan_to_delete)
	{
		app->physics->world->DestroyBody(body);
		app->physics->world->DestroyBody(c0.body);
		app->physics->world->DestroyBody(c1.body);
		app->physics->world->DestroyBody(c2.body);
		plan_to_delete = false;
	}

	if (player_enabled)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		SDL_Rect c0_rect = c0.currentAnimation->GetCurrentFrame();
		SDL_Rect c1_rect = c1.currentAnimation->GetCurrentFrame();
		SDL_Rect c2_rect = c2.currentAnimation->GetCurrentFrame();


		switch (char_control)
		{
		case 0:
			app->render->AddrenderObject(app->entities->wizard_texture, { METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 60.0f) }, c2_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->healer_texture, { METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 60.0f) }, c1_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->tank_texture, { METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 60.0f) }, c0_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->assassin_texture, { METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 60.0f) }, rect, 2, 1.0f, 0.0f);
			
			// ------------------------------------------------------------------------------------------------------- PRINT ORDER
			/*if (position.y >= c0.position.y && c0.position.y >= c1.position.y && c1.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c1.position.y && c1.position.y >= c0.position.y && c0.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c1.position.y && c1.position.y >= c2.position.y && c2.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c0.position.y && c0.position.y >= c2.position.y && c2.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c2.position.y && c2.position.y >= c0.position.y && c0.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c2.position.y && c2.position.y >= c1.position.y && c1.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			//---
			else if (c0.position.y >= position.y && position.y >= c1.position.y && c1.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
			}
			else if (c0.position.y >= c1.position.y && c1.position.y >= position.y && position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= c1.position.y && c1.position.y >= c2.position.y && c2.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= position.y && position.y >= c2.position.y && c2.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
			}
			else if (c0.position.y >= c2.position.y && c2.position.y >= position.y && position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= c2.position.y && c2.position.y >= c1.position.y && c1.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			//---
			else if (c1.position.y >= c0.position.y && c0.position.y >= position.y && position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= position.y && position.y >= c0.position.y && c0.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
			}
			else if (c1.position.y >= position.y && position.y >= c2.position.y && c2.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
			}
			else if (c1.position.y >= c0.position.y && c0.position.y >= c2.position.y && c2.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= c2.position.y && c2.position.y >= c0.position.y && c0.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= c2.position.y && c2.position.y >= position.y && position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			//---
			if (c2.position.y >= c0.position.y && c0.position.y >= c1.position.y && c1.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c1.position.y && c1.position.y >= c0.position.y && c0.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c1.position.y && c1.position.y >= position.y && position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c0.position.y && c0.position.y >= position.y && position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= position.y && position.y >= c0.position.y && c0.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
			}
			else if (c2.position.y >= position.y && position.y >= c1.position.y && c1.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
			}*/
			break;
		case 1:
			app->render->AddrenderObject(app->entities->wizard_texture, {METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 60.0f)}, c2_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->healer_texture, { METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 60.0f) }, c1_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->assassin_texture, { METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 60.0f) }, c0_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->tank_texture, { METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 60.0f) }, rect, 2, 1.0f, 0.0f);
			
			// ------------------------------------------------------------------------------------------------------- PRINT ORDER
			/*if (position.y >= c0.position.y && c0.position.y >= c1.position.y && c1.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c1.position.y && c1.position.y >= c0.position.y && c0.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c1.position.y && c1.position.y >= c2.position.y && c2.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c0.position.y && c0.position.y >= c2.position.y && c2.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c2.position.y && c2.position.y >= c0.position.y && c0.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c2.position.y && c2.position.y >= c1.position.y && c1.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			//---
			else if (c0.position.y >= position.y && position.y >= c1.position.y && c1.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
			}
			else if (c0.position.y >= c1.position.y && c1.position.y >= position.y && position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= c1.position.y && c1.position.y >= c2.position.y && c2.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= position.y && position.y >= c2.position.y && c2.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
			}
			else if (c0.position.y >= c2.position.y && c2.position.y >= position.y && position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= c2.position.y && c2.position.y >= c1.position.y && c1.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			//---
			else if (c1.position.y >= c0.position.y && c0.position.y >= position.y && position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= position.y && position.y >= c0.position.y && c0.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
			}
			else if (c1.position.y >= position.y && position.y >= c2.position.y && c2.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
			}
			else if (c1.position.y >= c0.position.y && c0.position.y >= c2.position.y && c2.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= c2.position.y && c2.position.y >= c0.position.y && c0.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= c2.position.y && c2.position.y >= position.y && position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			//---
			if (c2.position.y >= c0.position.y && c0.position.y >= c1.position.y && c1.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c1.position.y && c1.position.y >= c0.position.y && c0.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c1.position.y && c1.position.y >= position.y && position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c0.position.y && c0.position.y >= position.y && position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= position.y && position.y >= c0.position.y && c0.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
			}
			else if (c2.position.y >= position.y && position.y >= c1.position.y && c1.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
			}*/
			break;
		case 2:
			app->render->AddrenderObject(app->entities->wizard_texture, {METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 60.0f)}, c2_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->tank_texture, { METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 60.0f) }, c1_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->assassin_texture, { METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 60.0f) }, c0_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->healer_texture, { METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 60.0f) }, rect, 2, 1.0f, 0.0f);
			
			// ------------------------------------------------------------------------------------------------------- PRINT ORDER
			/*if (position.y >= c0.position.y && c0.position.y >= c1.position.y && c1.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c1.position.y && c1.position.y >= c0.position.y && c0.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c1.position.y && c1.position.y >= c2.position.y && c2.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c0.position.y && c0.position.y >= c2.position.y && c2.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c2.position.y && c2.position.y >= c0.position.y && c0.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c2.position.y && c2.position.y >= c1.position.y && c1.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			//---
			else if (c0.position.y >= position.y && position.y >= c1.position.y && c1.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
			}
			else if (c0.position.y >= c1.position.y && c1.position.y >= position.y && position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= c1.position.y && c1.position.y >= c2.position.y && c2.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= position.y && position.y >= c2.position.y && c2.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
			}
			else if (c0.position.y >= c2.position.y && c2.position.y >= position.y && position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= c2.position.y && c2.position.y >= c1.position.y && c1.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			//---
			else if (c1.position.y >= c0.position.y && c0.position.y >= position.y && position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= position.y && position.y >= c0.position.y && c0.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
			}
			else if (c1.position.y >= position.y && position.y >= c2.position.y && c2.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
			}
			else if (c1.position.y >= c0.position.y && c0.position.y >= c2.position.y && c2.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= c2.position.y && c2.position.y >= c0.position.y && c0.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= c2.position.y && c2.position.y >= position.y && position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			//---
			if (c2.position.y >= c0.position.y && c0.position.y >= c1.position.y && c1.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c1.position.y && c1.position.y >= c0.position.y && c0.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c1.position.y && c1.position.y >= position.y && position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c0.position.y && c0.position.y >= position.y && position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= position.y && position.y >= c0.position.y && c0.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
			}
			else if (c2.position.y >= position.y && position.y >= c1.position.y && c1.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
			}*/
			break;
		case 3:
			app->render->AddrenderObject(app->entities->healer_texture, {METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 60.0f)}, c2_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->tank_texture, { METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 60.0f) }, c1_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->assassin_texture, { METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 60.0f) }, c0_rect, 2, 1.0f, 0.0f);
			app->render->AddrenderObject(app->entities->wizard_texture, { METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 60.0f) }, rect, 2, 1.0f, 0.0f);
			
			// ------------------------------------------------------------------------------------------------------- PRINT ORDER
			/*if (position.y >= c0.position.y && c0.position.y >= c1.position.y && c1.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c1.position.y && c1.position.y >= c0.position.y && c0.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c1.position.y && c1.position.y >= c2.position.y && c2.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c0.position.y && c0.position.y >= c2.position.y && c2.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c2.position.y && c2.position.y >= c0.position.y && c0.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			else if (position.y >= c2.position.y && c2.position.y >= c1.position.y && c1.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
			}
			//---
			else if (c0.position.y >= position.y && position.y >= c1.position.y && c1.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
			}
			else if (c0.position.y >= c1.position.y && c1.position.y >= position.y && position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= c1.position.y && c1.position.y >= c2.position.y && c2.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= position.y && position.y >= c2.position.y && c2.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
			}
			else if (c0.position.y >= c2.position.y && c2.position.y >= position.y && position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			else if (c0.position.y >= c2.position.y && c2.position.y >= c1.position.y && c1.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);

			}
			//---
			else if (c1.position.y >= c0.position.y && c0.position.y >= position.y && position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= position.y && position.y >= c0.position.y && c0.position.y >= c2.position.y)
			{
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
			}
			else if (c1.position.y >= position.y && position.y >= c2.position.y && c2.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
			}
			else if (c1.position.y >= c0.position.y && c0.position.y >= c2.position.y && c2.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= c2.position.y && c2.position.y >= c0.position.y && c0.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			else if (c1.position.y >= c2.position.y && c2.position.y >= position.y && position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);

			}
			//---
			if (c2.position.y >= c0.position.y && c0.position.y >= c1.position.y && c1.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c1.position.y && c1.position.y >= c0.position.y && c0.position.y >= position.y)
			{
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c1.position.y && c1.position.y >= position.y && position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= c0.position.y && c0.position.y >= position.y && position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);

			}
			else if (c2.position.y >= position.y && position.y >= c0.position.y && c0.position.y >= c1.position.y)
			{
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
			}
			else if (c2.position.y >= position.y && position.y >= c1.position.y && c1.position.y >= c0.position.y)
			{
				app->render->DrawTexture(app->entities->tank_texture, METERS_TO_PIXELS(c0.position.x - 25.0f), METERS_TO_PIXELS(c0.position.y - 36.0f), &c0_rect);
				app->render->DrawTexture(app->entities->healer_texture, METERS_TO_PIXELS(c1.position.x - 25.0f), METERS_TO_PIXELS(c1.position.y - 36.0f), &c1_rect);
				app->render->DrawTexture(app->entities->wizard_texture, METERS_TO_PIXELS(position.x - 25.0f), METERS_TO_PIXELS(position.y - 36.0f), &rect);
				app->render->DrawTexture(app->entities->assassin_texture, METERS_TO_PIXELS(c2.position.x - 25.0f), METERS_TO_PIXELS(c2.position.y - 36.0f), &c2_rect);
			}*/
			break;
		}
	}
	
	return true;
}

bool Player::Load(pugi::xml_node& data)
{
	position.x = data.child("player").child("position").attribute("x").as_int();
	position.y = data.child("player").child("position").attribute("y").as_int();
	c0.position.x = data.child("player").child("comp0").attribute("x").as_int();
	c0.position.y = data.child("player").child("comp0").attribute("y").as_int();
	c1.position.x = data.child("player").child("comp1").attribute("x").as_int();
	c1.position.y = data.child("player").child("comp1").attribute("y").as_int();
	c2.position.x = data.child("player").child("comp2").attribute("x").as_int();
	c2.position.y = data.child("player").child("comp2").attribute("y").as_int();

	body->SetTransform({ position.x + PIXELS_TO_METERS(w), position.y + PIXELS_TO_METERS(h) }, body->GetAngle());
	c0.body->SetTransform({ c0.position.x + PIXELS_TO_METERS(w), c0.position.y + PIXELS_TO_METERS(h) }, c0.body->GetAngle());
	c1.body->SetTransform({ c1.position.x + PIXELS_TO_METERS(w), c1.position.y + PIXELS_TO_METERS(h) }, c1.body->GetAngle());
	c2.body->SetTransform({ c2.position.x + PIXELS_TO_METERS(w), c2.position.y + PIXELS_TO_METERS(h) }, c2.body->GetAngle());

	look_dir = 1;

	return true;
}

bool Player::Save(pugi::xml_node& data)
{
	data.child("player").child("position").attribute("x").set_value(position.x);
	data.child("player").child("position").attribute("y").set_value(position.y);
	data.child("player").child("comp0").attribute("x").set_value(c0.position.x);
	data.child("player").child("comp0").attribute("y").set_value(c0.position.y);
	data.child("player").child("comp1").attribute("x").set_value(c1.position.x);
	data.child("player").child("comp1").attribute("y").set_value(c1.position.y);
	data.child("player").child("comp2").attribute("x").set_value(c2.position.x);
	data.child("player").child("comp2").attribute("y").set_value(c2.position.y);

	return true;
}

fPoint Player::GetPlayerPosition()
{
	return position;
}
fPoint Player::GetCompanion0Position()
{
	return c0.position;

}
fPoint Player::GetCompanion1Position()
{
	return c1.position;
}
fPoint Player::GetCompanion2Position()
{
	return c2.position;
}

void Player::SetPlayerPosition(int new_x, int new_y)
{
	position.x = new_x;
	position.y = new_y;

	body->SetTransform({ position.x, position.y }, body->GetAngle());
	body->ApplyForceToCenter({ 0, 1 }, true);
}

void Player::SetCompanion0Position(int new_x, int new_y)
{
	c0.position.x = new_x;
	c0.position.y = new_y;

	c0.body->SetTransform({ c0.position.x, c0.position.y }, c0.body->GetAngle());
	c0.body->ApplyForceToCenter({ 0, 1 }, true);
}

void Player::SetCompanion1Position(int new_x, int new_y)
{
	c1.position.x = new_x;
	c1.position.y = new_y;

	c1.body->SetTransform({ c1.position.x, c1.position.y }, c1.body->GetAngle());
	c1.body->ApplyForceToCenter({ 0, 1 }, true);
}

void Player::SetCompanion2Position(int new_x, int new_y)
{
	c2.position.x = new_x;
	c2.position.y = new_y;

	c2.body->SetTransform({ c2.position.x, c2.position.y }, c2.body->GetAngle());
	c2.body->ApplyForceToCenter({ 0, 1 }, true);
}

void Player::SetCompanion0LookDir(int lookDir)
{
	c0.look_dir = lookDir;
}

void Player::SetCompanion1LookDir(int lookDir)
{
	c1.look_dir = lookDir;
}

void Player::SetCompanion2LookDir(int lookDir)
{
	c2.look_dir = lookDir;
}

void Player::SetPlayerLookDir(int lookDir)
{
	look_dir = lookDir;
}

bool Player::DeleteEntity()
{
	player_enabled = false;
	plan_to_delete = true;

	return true;
}

void Player::ImpulsePlayer()
{
	body->SetLinearVelocity({ 0, 0 });
	body->ApplyForceToCenter({ -250.0f * app->GetDT(), 0 }, true);
}

int Player::GetCharControl()
{
	return char_control;
}

void Player::FollowPlayer(Companion c, Companion pre_c, float dt)
{
	fPoint obj;

	if (c.comp_number == 0)
	{
		switch (look_dir)
		{
		case 0:
			obj.x = position.x;
			obj.y = position.y + 1;
			break;
		case 1:
			obj.x = position.x;
			obj.y = position.y - 1;
			break;
		case 2:
			obj.x = position.x + 1;
			obj.y = position.y;
			break;
		case 3:
			obj.x = position.x - 1;
			obj.y = position.y;
			break;
		}
	}
	else
	{
		switch (look_dir)
		{
		case 0:
			obj.x = pre_c.position.x;
			obj.y = pre_c.position.y + 1;
			break;
		case 1:
			obj.x = pre_c.position.x;
			obj.y = pre_c.position.y - 1;
			break;
		case 2:
			obj.x = pre_c.position.x + 1;
			obj.y = pre_c.position.y;
			break;
		case 3:
			obj.x = pre_c.position.x - 1;
			obj.y = pre_c.position.y;
			break;
		}
	}


	PathFinding* path = new PathFinding(true);
	float distx;
	float disty;

	Entity* player = app->entities->GetPlayer();
	path->CreatePath({ (int)c.position.x, (int)c.position.y }, { (int)obj.x, (int)obj.y });

	if (c.position.x < obj.x + 1 && c.position.x > obj.x - 1)
	{
		distx = 0.0f;
	}
	else
	{
		int ob_x = path->GetLastPath()->At(path->GetLastPath()->Count() - 1)->x;

		if ((ob_x - c.position.x) > 0)
		{
			distx = 1.0f;
		}
		else
		{
			distx = -1.0f;
		}
	}

	if (c.position.y < obj.y + 1 && c.position.y > obj.y - 1)
	{
		disty = 0.0f;
	}
	else
	{
		int ob_y = path->GetLastPath()->At(path->GetLastPath()->Count() - 1)->y;

		if ((ob_y - c.position.y) > 0)
		{
			disty = 1.0f;
		}
		else
		{
			disty = -1.0f;
		}
	}

	if (app->frontground->godmode)
	{
		distx *= 2;
		disty *= 2;
	}

	c.body->SetLinearVelocity({ distx * speed * dt,  disty * speed * dt });
}