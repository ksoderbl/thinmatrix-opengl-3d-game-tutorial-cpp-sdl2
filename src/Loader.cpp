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

RawModel *Loader::loadToVAO(vector<GLfloat>&positions, vector<GLuint>&indices)
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
    glEnableVertexAttribArray( 1 );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer( 1, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0); // ????
	
	storeDataInAttributeList(0, positions);
	GLuint ibo = bindIndicesBuffer(indices);
	
	GLuint vao = createVAO();
			
	return new RawModel(vao, shaderProgram, ibo, indices.size());
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

void Loader::storeDataInAttributeList(int attributeNumber, vector<GLfloat>&data)
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	vbos->push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
}

void Loader::unbindVAO(GLuint vao)
{
	glDeleteVertexArrays(1, &vao);
}

GLuint Loader::bindIndicesBuffer(vector<GLuint>&indices)
{
	GLuint ibo = 0;
	glGenBuffers(1, &ibo);
	vbos->push_back(ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	return ibo;
}
