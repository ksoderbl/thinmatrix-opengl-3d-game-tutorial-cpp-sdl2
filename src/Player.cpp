#include "Player.h"

Player::Player(	TexturedModel &model,
		glm::vec3 position,
		GLfloat rotX, GLfloat rotY, GLfloat rotZ,
		GLfloat scale) : Entity(model, position, rotX, rotY, rotZ, scale)
{
	
}

void Player::checkInputs(Keyboard& keyboard)
{
	if (keyboard.isKeyDown(SDLK_w)) {
		currentSpeed = RUN_SPEED;
	} else if (keyboard.isKeyDown(SDLK_s)) {
		currentSpeed = -RUN_SPEED;
	} else {
		currentSpeed = 0;
	}
	
	if (keyboard.isKeyDown(SDLK_d)) {
		currentTurnSpeed = -TURN_SPEED;
	} else if (keyboard.isKeyDown(SDLK_a)) {
		currentTurnSpeed = TURN_SPEED;
	} else {
		currentTurnSpeed = 0;
	}
	
	if (keyboard.isKeyDown(SDLK_SPACE)) {
		jump();
	}
}

void Player::move(Keyboard &keyboard, DisplayManager &manager)
{
	checkInputs(keyboard);
	increaseRotation(0, currentTurnSpeed * manager.getFrameTimeSeconds(), 0);
	GLfloat distance = currentSpeed * manager.getFrameTimeSeconds();
	GLfloat dx = distance * sin(glm::radians(getRotY()));
	GLfloat dz = distance * cos(glm::radians(getRotY()));
	increasePosition(dx, 0, dz);
	upwardsSpeed += GRAVITY * manager.getFrameTimeSeconds();
	increasePosition(0, upwardsSpeed * manager.getFrameTimeSeconds(), 0);
	glm::vec3& pos = getPosition();
	if (pos.y < TERRAIN_HEIGHT) {
		upwardsSpeed = 0;
		isInAir = false;
		pos.y = TERRAIN_HEIGHT;
	}
}

void Player::jump()
{
	if (!isInAir) {
		upwardsSpeed = JUMP_POWER;
		isInAir = true;
	}
}
