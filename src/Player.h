#ifndef PLAYER_H
#define PLAYER_H

#include "Headers.h"
#include "Entity.h"
#include "Keyboard.h"
#include "DisplayManager.h"
#include "Terrain.h"
#include "WaterTile.h"

class Player : public Entity
{
public:
	Player(	TexturedModel &model,
		glm::vec3 position,
		GLfloat rotX, GLfloat rotY, GLfloat rotZ,
		GLfloat scale);
	void move(Terrain& terrain, WaterTile* water);
	
private:
	void jump();
	void checkInputs();

	GLfloat RUN_SPEED = 40;
	GLfloat TURN_SPEED = 160;
	GLfloat GRAVITY = -50;
	GLfloat JUMP_POWER = 18;
	
	GLfloat currentSpeed = 0;
	GLfloat currentTurnSpeed = 0;
	GLfloat upwardsSpeed = 0;
	
	bool isInAir = false;
};

#endif
