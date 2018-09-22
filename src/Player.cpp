#include "Player.h"

Player::Player(	TexturedModel &model,
		glm::vec3 position,
		GLfloat rotX, GLfloat rotY, GLfloat rotZ,
		GLfloat scale) : Entity(model, position, rotX, rotY, rotZ, scale)
{
	
}

void Player::checkInputs()
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

void Player::move(Terrain& terrain, WaterTile* water)
{
	checkInputs();
	increaseRotation(0, currentTurnSpeed * display.getFrameTimeSeconds(), 0);
	GLfloat distance = currentSpeed * display.getFrameTimeSeconds();
	GLfloat dx = distance * sin(glm::radians(getRotY()));
	GLfloat dz = distance * cos(glm::radians(getRotY()));
	increasePosition(dx, 0, dz);
	upwardsSpeed += GRAVITY * display.getFrameTimeSeconds();
	increasePosition(0, upwardsSpeed * display.getFrameTimeSeconds(), 0);
	glm::vec3& pos = getPosition();
	GLfloat terrainHeight = terrain.getHeightOfTerrain(pos.x, pos.z);
	if (pos.y < terrainHeight) {
		upwardsSpeed = 0;
		isInAir = false;
		pos.y = terrainHeight;
	}

	// assume all low places are filled with water
	// make player swim so the head stays above surface
	GLfloat playerHeight = 5;
	if (getPosition().y < water->getHeight() - playerHeight) {
		upwardsSpeed = 0;
		isInAir = false;
		getPosition().y = water->getHeight() - playerHeight;
	}
}

void Player::jump()
{
	if (!isInAir) {
		upwardsSpeed = JUMP_POWER;
		isInAir = true;
	}
}
