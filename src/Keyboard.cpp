#include "Keyboard.h"

Keyboard::Keyboard()
{
	keys = new map<SDL_Keycode,bool>;
}

bool Keyboard::isKeyDown(SDL_Keycode sym)
{
	map<SDL_Keycode,bool>::iterator it = keys->find(sym);
	if (it == keys->end()) {
		return false;
	}
	return it->second == true;
}

void Keyboard::setKeyDown(SDL_Keycode sym, bool isDown)
{
	map<SDL_Keycode,bool>::iterator it = keys->find(sym);
	
	if (it == keys->end()) {
		// was not in map, insert it
		keys->insert( std::pair<SDL_Keycode, bool>(sym,isDown) );
	}
	else {
		keys->at( sym ) = isDown;
	}
}
