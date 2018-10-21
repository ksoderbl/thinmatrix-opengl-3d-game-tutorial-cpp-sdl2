#include "Headers.h"
#include "entities/Camera.h"
#include "Mouse.h"
#include "terrains/Terrain.h"

class MousePicker
{
public:
	MousePicker(Camera& camera, glm::mat4& projection, Terrain* terrain);

	glm::vec3* getCurrentTerrainPoint() {
		if (currentTerrainPointIsOK) {
			return &currentTerrainPoint;
		} else {
			return nullptr;
		}
	}
	glm::vec3& getCurrentRay() {
		return currentRay;
	}
	void update();
private:
	glm::vec3 calculateMouseRay();
	glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
	glm::vec4 toEyeCoords(glm::vec4 clipCoords);
	glm::vec2 getNormalizedDeviceCoords(GLfloat mouseX, GLfloat mouseY);
	glm::vec3 getPointOnRay(glm::vec3& ray, GLfloat distance);
	glm::vec3 binarySearch(int count, GLfloat start, GLfloat finish, glm::vec3& ray, bool& ok);
	bool intersectionInRange(GLfloat start, GLfloat finish, glm::vec3& ray);
	bool isUnderGround(glm::vec3& testPoint);
	Terrain* getTerrain(GLfloat worldX, GLfloat worldZ);

	static constexpr int RECURSION_COUNT = 200;
	static constexpr GLfloat RAY_RANGE = 1000; // 600;

	glm::vec3 currentRay;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	Camera& camera;
	Terrain* terrain;
	glm::vec3 currentTerrainPoint;
	bool currentTerrainPointIsOK;
};
