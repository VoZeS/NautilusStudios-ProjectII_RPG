#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "Module.h"
#include "Animation.h"

class Dialog : public Module
{
public:
	Dialog(bool enabled);

	virtual ~Dialog();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	int limitLenght = 0;
	int limitLenght2 = 0;

	uint letlengh = 0;
	uint letlengh2 = 0;

	int letter_cd = 0;

	bool inDialog = false;
	bool inDialogRenato = false;
	bool inDialogAlly = false;
	bool inDialogEnemy = false;

private:
	
	pugi::xml_document dialogFile;
	pugi::xml_node dialog;
	pugi::xml_node renato;
	pugi::xml_node text1;

	std::string linea1String_Renato;
	std::string linea2String_Renato;
	const char* linea1Char_Renato;
	const char* linea2Char_Renato;

	std::string linea1String_Ally;
	std::string linea2String_Ally;
	const char* linea1Char_Ally;
	const char* linea2Char_Ally;

	std::string linea1String_Enemy;
	const char* linea1Char_Enemy;

	bool LoadDialog();

	SDL_Texture* whitemark_300x80 = NULL;
	SDL_Texture* whitemark_1200x140 = NULL;

};

#endif
