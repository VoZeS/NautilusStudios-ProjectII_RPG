#ifndef __SKILLS_H__
#define __SKILLS_H__

#include <string>
using namespace std;

struct Skill
{
public:
	int owner; // 0 --> assassin, 1 --> tank, 2 --> healer, 3 --> wizard

	string skill_name;
	int mana_cost;
	bool objective; // true --> enemy, false --> ally
	bool attack_type; // true --> single target, false --> multi-target
	int element; // 0 --> physic, 1 --> fire, 2 --> lightning, 3 --> water
	int strenght; // 0 --> low damage, 3 --> extreme damage
};

#endif