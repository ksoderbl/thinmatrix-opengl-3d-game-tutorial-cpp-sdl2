#include "Headers.h"
#include "Camera.h"
#include "Mouse.h"

class MousePicker
{
public:
	MousePicker(
		DisplayManager& display, Mouse& mouse,
		Camera& camera, glm::mat4& projection);
	glm::vec3& getCurrentRay() {
		return currentRay;
	}
	void update();
private:
	glm::vec3 calculateMouseRay();
	glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
	glm::vec4 toEyeCoords(glm::vec4 clipCoords);
	glm::vec2 getNormalizedDeviceCoords(GLfloat mouseX, GLfloat mouseY);

	glm::vec3 currentRay;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	DisplayManager& display;
	Mouse& mouse;
	Camera& camera;
};
