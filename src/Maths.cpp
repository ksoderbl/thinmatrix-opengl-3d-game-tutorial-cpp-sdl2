//package toolbox

#include "Maths.h"
#include "entities/Camera.h"

void Maths::printMatrix(glm::mat4& m, string name)
{
	for (int i = 0; i < 4; i++) { // rows
		for (int j = 0; j < 4; j++) { // columns
			cout << name << "[" << i << "," << j << "] = ";
			cout << setiosflags( ios::left ) << setw(10) << setprecision(5);
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

GLfloat Maths::barycentric(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, glm::vec2& pos)
{
	GLfloat det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	GLfloat l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	GLfloat l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	GLfloat l3 = 1.0f - l1  - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

glm::mat4 Maths::createTransformationMatrix(
	glm::vec2& translation,
	glm::vec2& scale)
{
	glm::mat4 unit = glm::mat4(1.0f);
	glm::mat4 t = glm::translate(unit, glm::vec3(translation.x, translation.y, 0.0f));
	glm::mat4 s = glm::scale(unit, glm::vec3(scale.x, scale.y, 1.0f));
	glm::mat4 m = t * s;
	return m;
}


glm::mat4 Maths::createTransformationMatrix(glm::vec3& translation,
	GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale)
{
	glm::mat4 unit = glm::mat4(1.0f); // identity matrix

	glm::mat4 t = glm::translate(unit, glm::vec3(translation[0], translation[1], translation[2]));
	//printMatrix(t, "t");

	glm::mat4 rotx = glm::rotate(unit, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
	//printMatrix(rotx, "rotx");

	glm::mat4 roty = glm::rotate(unit, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
	//printMatrix(roty, "roty");

	glm::mat4 rotz = glm::rotate(unit, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
	//printMatrix(rotz, "rotz");

	glm::mat4 r = rotx * roty * rotz;
	//printMatrix(r, "r");

	glm::mat4 s = glm::scale(unit, glm::vec3(scale));
	//printMatrix(s, "s");

	glm::mat4 m = t * r * s;
	//printMatrix(m, "m");

	return m;
}

// From OpenGL 3D Game Tutorial 8: Model, View & Projection Matrices
glm::mat4 Maths::createViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = glm::mat4(1.0f); // identity matrix

	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getPitch()), glm::vec3(1, 0, 0));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getYaw()), glm::vec3(0, 1, 0));

	glm::vec3 cameraPos = camera.getPosition();
	glm::vec3 negativeCameraPos = glm::vec3(-cameraPos[0], -cameraPos[1], -cameraPos[2]);

	viewMatrix = glm::translate(viewMatrix, negativeCameraPos);

	//printMatrix(viewMatrix, "view");

	return viewMatrix;
}
