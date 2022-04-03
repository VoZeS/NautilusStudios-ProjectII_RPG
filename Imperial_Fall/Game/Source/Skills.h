#ifndef __SKILLS_H__
#define __SKILLS_H__

#include <string>
using namespace std;

struct Skill
{
public:
	int owner; // 0 --> assassin, 1 --> tank, 2 --> healer, 3 --> wizard

	const char* skill_name = "name";
	int mana_cost = 0;
	// true --> enemy, false --> ally
	bool objective = true;
	// true --> single target, false --> multi-target
	bool attack_type = true;
	// 0 --> physic, 1 --> fire, 2 --> lightning, 3 --> water
	int element = 0;
	// 0 --> low damage, 1 --> mid damage, 2 --> high damage
	int strenght = 0;
};

#endif