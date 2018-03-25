#include "Loader.h"

Loader::Loader()
{
	vaos = new vector<GLuint>();
	vbos = new vector<GLuint>();
}

Loader::~Loader()
{
	delete vaos;
	delete vbos;
}

RawModel *Loader::loadToVAO(GLfloat positions[], int numPositions)
{
	const char* vertex_shader =
		"#version 150\n"
		"in vec3 vp;"
		"void main() {"
		"  gl_Position = vec4(vp, 1.0);"
		"}";
	
	const char* fragment_shader =
		"#version 150\n"
		"out vec4 frag_color;"
		"void main() {"
		"  frag_color = vec4(1.0, 1.0, 1.0, 1.0);"
		"}";

    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
    
    
    GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fs);
	glAttachShader(shaderProgram, vs);
	glLinkProgram(shaderProgram);
	
    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	storeDataInAttributeList(0, positions, numPositions);
	
	GLuint vao = createVAO();
		
	return new RawModel(vao, shaderProgram, numPositions / 3);
}

void Loader::cleanUp()
{
	vector<GLuint>::iterator p;
	
	for (p = vaos->begin(); p != vaos->end(); p++)
		glDeleteVertexArrays(1, &*p);
	vaos->clear();
		
	for (p = vbos->begin(); p != vbos->end(); p++)
		glDeleteBuffers(1, &*p);
	vbos->clear();
}

GLuint Loader::createVAO()
{
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	vaos->push_back(vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	return vao;
}

GLuint Loader::storeDataInAttributeList(int attributeNumber, GLfloat data[], int numData)
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	vbos->push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numData * sizeof(GLfloat), data, GL_STATIC_DRAW);
	
	return vbo;
}

void Loader::unbindVAO(GLuint vao)
{
	glDeleteVertexArrays(1, &vao);
}
