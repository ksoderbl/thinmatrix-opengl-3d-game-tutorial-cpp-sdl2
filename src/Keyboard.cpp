#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < NUM_KEYS; i++)
		keyIsDown[i] = false;
}

bool Keyboard::isKeyDown(SDL_Keycode sym)
{
	int num = (int) sym;
	bool ret = false;

	if (num >= NUM_KEYS)
		return false;
	ret = keyIsDown[num];
	//if (ret)
	//	cout << "key " << num << " is down." << endl;
	return ret;
}

void Keyboard::setKeyDown(SDL_Keycode sym, bool isDown)
{
	int num = (int) sym;

	if (num >= NUM_KEYS) {
		cerr << "warning: setKeyDown: " << num << " >= " << NUM_KEYS << endl;
		return;
	}

	//cout << "key " << num << " pressed" << endl;
	//cout << "is down: " << (isDown ? "true" : "false") << endl;
	keyIsDown[num] = isDown;
}
