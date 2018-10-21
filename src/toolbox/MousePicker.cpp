#include "MousePicker.h"
#include "Maths.h"

MousePicker::MousePicker(
	Camera& camera,
	glm::mat4& projection,
	Terrain* terrain): camera(camera)
{
	this->projectionMatrix = projection;
	this->viewMatrix = Maths::createViewMatrix(camera);
	this->terrain = terrain;
	this->currentTerrainPointIsOK = false;
}

void MousePicker::update()
{
	viewMatrix = Maths::createViewMatrix(camera);
	currentRay = calculateMouseRay();
	bool ok = false;
	if (intersectionInRange(0, RAY_RANGE, currentRay)) {
		currentTerrainPoint = binarySearch(0, 0, RAY_RANGE, currentRay, ok);
		currentTerrainPointIsOK = ok;
	} else {
		currentTerrainPoint = glm::vec3(0, 0, 0);
		currentTerrainPointIsOK = false;
	}
}

glm::vec3 MousePicker::calculateMouseRay()
{
	// viewport space
	GLfloat mouseX = mouse.getX();
	GLfloat mouseY = mouse.getY();
	// normalized device space
	glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
	// homogenous clip space
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.f, 1.f);
	// eye space
	glm::vec4 eyeCoords = toEyeCoords(clipCoords);
	// world space
	glm::vec3 worldRay = toWorldCoords(eyeCoords);
	return worldRay;
}

glm::vec3 MousePicker::toWorldCoords(glm::vec4 eyeCoords)
{
	glm::mat4 invertedView = glm::inverse(this->viewMatrix);
	glm::vec4 rayWorld = invertedView * eyeCoords;
	glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	mouseRay = glm::normalize(mouseRay);
	return mouseRay;
}

glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords)
{
	glm::mat4 invertedProjection = glm::inverse(this->projectionMatrix);
	glm::vec4 eyeCoords = invertedProjection * clipCoords;
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
}

// convert to opengl coordinate system -1 -> 1, -1 -> 1,
// origin at the center of screen
glm::vec2 MousePicker::getNormalizedDeviceCoords(
	GLfloat mouseX, GLfloat mouseY)
{
	GLfloat x = (2 * mouseX) / display.getWidth() - 1;
	GLfloat y = (2 * mouseY) / display.getHeight() - 1;
	return glm::vec2(x, -y);
}

glm::vec3 MousePicker::getPointOnRay(glm::vec3& ray, GLfloat distance)
{
	glm::vec3& start = camera.getPosition();
	glm::vec3 scaledRay = glm::vec3(ray.x * distance, ray.y * distance, ray.z * distance);
	return glm::vec3(start.x + scaledRay.x, start.y + scaledRay.y, start.z + scaledRay.z);
}

glm::vec3 MousePicker::binarySearch(int count, GLfloat start, GLfloat finish, glm::vec3& ray, bool& ok)
{
	GLfloat half = start + ((finish - start) / 2.0f);
	if (count >= RECURSION_COUNT) {
		glm::vec3 endPoint = getPointOnRay(ray, half);

		Terrain* terrain = getTerrain(endPoint.x, endPoint.z);
		if (terrain != nullptr) {
			ok = true;
		} else {
			ok = false;
		}
		return endPoint;
	}
	if (intersectionInRange(start, half, ray)) {
		return binarySearch(count + 1, start, half, ray, ok);
	} else {
		return binarySearch(count + 1, half, finish, ray, ok);
	}
}

bool MousePicker::intersectionInRange(GLfloat start, GLfloat finish, glm::vec3& ray)
{
	glm::vec3 startPoint = getPointOnRay(ray, start);
	glm::vec3 endPoint = getPointOnRay(ray, finish);
	if (!isUnderGround(startPoint) && isUnderGround(endPoint)) {
		return true;
	} else {
		return false;
	}
}

bool MousePicker::isUnderGround(glm::vec3& testPoint)
{
	Terrain* terrain = getTerrain(testPoint.x, testPoint.z);
	GLfloat height = 0;
	if (terrain != nullptr) {
		height = terrain->getHeightOfTerrain(testPoint.x, testPoint.z);
	}
	if (testPoint.y < height) {
		return true;
	} else {
		return false;
	}
}

Terrain* MousePicker::getTerrain(GLfloat worldX, GLfloat worldZ)
{
	// TODO
	//int x = worldX / Terrain.SIZE;
	//int z = worldZ / Terrain.SIZE;
	//return terrains[x][z];
	return terrain;
}
