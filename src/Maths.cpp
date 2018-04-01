//package toolbox

#include "Maths.h"


glm::mat4 createTransformationMatrix(vector<GLfloat>& translation,
				     GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale)
{
	glm::mat4 matrix = glm::mat4(1.0f); // identity matrix

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "matrix[" << i << "," << j << "] = " << matrix[j][i] << " ";
		}
		cout << endl;
	}

	glm::mat4 t = glm::translate(matrix, glm::vec3(translation[0], translation[1], translation[2]));

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "t[" << i << "," << j << "] = " << t[j][i] << " ";
		}
		cout << endl;
	}
	
	
	//matrix = glm::translate(matrix, glm::vec3(
	return matrix;
}

