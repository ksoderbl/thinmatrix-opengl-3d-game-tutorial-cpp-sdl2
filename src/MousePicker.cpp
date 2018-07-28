#include "MousePicker.h"
#include "Maths.h"

MousePicker::MousePicker(
	DisplayManager& display,
	Mouse& mouse,
	Camera& camera,
	glm::mat4& projection): display(display), mouse(mouse), camera(camera)
{
	this->projectionMatrix = projection;
	this->viewMatrix = Maths::createViewMatrix(camera);
}

void MousePicker::update()
{
	viewMatrix = Maths::createViewMatrix(camera);
	currentRay = calculateMouseRay();
}

glm::vec3 MousePicker::calculateMouseRay()
{
	GLfloat mouseX = mouse.getX();
	GLfloat mouseY = mouse.getY();
	glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.f, 1.f);
	glm::vec4 eyeCoords = toEyeCoords(clipCoords);
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

glm::vec2 MousePicker::getNormalizedDeviceCoords(
	GLfloat mouseX, GLfloat mouseY)
{
	GLfloat x = (2 * mouseX) / display.getWidth() - 1;
	GLfloat y = (2 * mouseY) / display.getHeight() - 1;
	return glm::vec2(x, -y);
}
