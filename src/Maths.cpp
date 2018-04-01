//package toolbox

#include "Maths.h"


static void printMatrix(glm::mat4& m, string name)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << name << "[" << i << "," << j << "] = " << m[j][i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

glm::mat4 createTransformationMatrix(glm::vec3& translation,
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

	glm::mat4 m = s * r * t;
	//printMatrix(m, "m");

	return m;
}

