#ifndef PLAYER_H
#define PLAYER_H

#include "Headers.h"
#include "Entity.h"
#include "Keyboard.h"
#include "DisplayManager.h"
#include "Terrain.h"

class Player : public Entity
{
public:
	Player(	TexturedModel &model,
		glm::vec3 position,
		GLfloat rotX, GLfloat rotY, GLfloat rotZ,
		GLfloat scale);
	void move(Keyboard &keyboard, DisplayManager &manager, Terrain& terrain);
	
private:
	void jump();
	void checkInputs(Keyboard& keyboard);

	GLfloat RUN_SPEED = 20;
	GLfloat TURN_SPEED = 160;
	GLfloat GRAVITY = -50;
	GLfloat JUMP_POWER = 30;
	GLfloat TERRAIN_HEIGHT = 0;
	
	GLfloat currentSpeed = 0;
	GLfloat currentTurnSpeed = 0;
	GLfloat upwardsSpeed = 0;
	
	bool isInAir = false;
};

#endif
