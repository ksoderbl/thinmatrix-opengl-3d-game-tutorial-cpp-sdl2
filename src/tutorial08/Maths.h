// package toolbox
#ifndef MATHS_H
#define MATHS_H

#include "Headers.h"
#include "Camera.h"

class Maths {
public:
	static void printMatrix(glm::mat4& m, string name);
	static glm::mat4 createTransformationMatrix(glm::vec3& translation,
						    GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale);
	static glm::mat4 createViewMatrix(Camera& camera);
};

#endif
