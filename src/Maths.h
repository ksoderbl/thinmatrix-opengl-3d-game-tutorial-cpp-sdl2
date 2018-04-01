// package toolbox

#include "Headers.h"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp> 

glm::mat4 createTransformationMatrix(
	vector<GLfloat>& translation,
	GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale);

class Maths {
public:

};
