// package toolbox
#ifndef MATHS_H
#define MATHS_H

#include "Headers.h"
#include "Camera.h"

class Maths {
public:
	static void printMatrix(glm::mat4& m, string name);
	static GLfloat barycentric(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, glm::vec2& pos);
	static glm::mat4 createTransformationMatrix(glm::vec2& translation, glm::vec2& scale);
	static glm::mat4 createTransformationMatrix(glm::vec3& translation,
						    GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale);
	static glm::mat4 createViewMatrix(Camera& camera);
};

#endif
