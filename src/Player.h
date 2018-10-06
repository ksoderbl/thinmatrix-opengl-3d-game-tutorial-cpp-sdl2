#ifndef PLAYER_H
#define PLAYER_H

#include "Headers.h"
#include "Entity.h"
#include "Keyboard.h"
#include "renderEngine/DisplayManager.h"
#include "Terrain.h"
#include "water/WaterTile.h"

class Player : public Entity
{
public:
	Player(	TexturedModel &model,
		glm::vec3 position,
		GLfloat rotX, GLfloat rotY, GLfloat rotZ,
		GLfloat scale);
	void move(Terrain& terrain, WaterTile* water);

	static constexpr GLfloat GRAVITY = -50;
	
private:
	void jump();
	void checkInputs();

	static constexpr GLfloat RUN_SPEED = 40;
	static constexpr GLfloat TURN_SPEED = 160;
	static constexpr GLfloat JUMP_POWER = 18;
	
	GLfloat currentSpeed = 0;
	GLfloat currentTurnSpeed = 0;
	GLfloat upwardsSpeed = 0;
	
	bool isInAir = false;
};

#endif
