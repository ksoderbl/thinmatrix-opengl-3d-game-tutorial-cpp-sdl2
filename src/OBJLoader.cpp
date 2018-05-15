#include "OBJLoader.h"



static void processVertex(
	GLuint u0,
	GLuint u1,
	GLuint u2,
	vector<GLuint>& indices,
	vector<glm::vec2>& textures,
	vector<glm::vec3>& normals,
	vector<GLfloat>& textureArray,
	vector<GLfloat>& normalsArray)
{
	GLuint currentVertexPointer = u0 - 1;
	indices.push_back(currentVertexPointer);
	glm::vec2 currentTex = textures[u1 - 1];
	textureArray[currentVertexPointer * 2] = currentTex[0];
	textureArray[currentVertexPointer * 2 + 1] = 1 - currentTex[1];
	glm::vec3 currentNorm = normals[u2 - 1];
	normalsArray[currentVertexPointer * 3] = currentNorm[0];
	normalsArray[currentVertexPointer * 3 + 1] = currentNorm[1];
	normalsArray[currentVertexPointer * 3 + 2] = currentNorm[2];
}

// OBJ file format is explained in
// https://www.youtube.com/watch?v=KMWUjNE0fYI&list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP&index=8

RawModel *OBJLoader::loadObjModel(string fileName, Loader& loader)
{
	fileName = "../res/" + fileName + ".obj";
	
	ifstream inFile(fileName, ios::in);
	
	if (!inFile) {
		cerr << "File " << fileName << " could not be opened" << endl;
		exit(1);
	}

	string line;
	vector<glm::vec3> vertices;
	vector<glm::vec2> textures;
	vector<glm::vec3> normals;
	vector<GLuint> indices;
	vector<GLfloat> verticesArray;
	vector<GLfloat> normalsArray;
	vector<GLfloat> textureArray;
	vector<GLuint> indicesArray;
	
	// This loop collects the vertices, texture coords and normals from
	// the obj file.
	while ( !inFile.eof() ) {
		getline(inFile, line);
		
		istringstream iss(line);
		string starts;
		GLfloat x, y, z;
		
		// starts contains e.g. v, vt, tv, s, f
		iss >> starts;
		
		if (starts == "v") {
			// e.g. v 3.227124 -0.065127 -1.000000
			iss >> x >> y >> z;
			// cout << "got: v " << setprecision(8) << x << " " << y << " " << z << endl;
			glm::vec3 vertex(x, y, z);
			vertices.push_back(vertex);
		}
		else if (starts == "vt") {
			// e.g. vt 0.905299 0.942320
			iss >> x >> y;
			// cout << "got: vt " << setprecision(8) << x << " " << y << endl;
			glm::vec2 texture(x, y);
			textures.push_back(texture);
		}
		else if (starts == "vn") {
			// e.g. vn -1.000000 0.000000 0.000000
			iss >> x >> y >> z;
			// cout << "got: vn " << setprecision(8) << x << " " << y << " " << z << endl;
			glm::vec3 normal(x, y, z);
			normals.push_back(normal);
		}
		else if (starts == "f") {
			// break when faces start
			cout << "OBJLoader: Read " << vertices.size() << " vertices from " << fileName << endl;
			cout << "OBJLoader: Read " << textures.size() << " texture coords from " << fileName << endl;
			cout << "OBJLoader: Read " << normals.size() << " normals from " << fileName << endl;
			textureArray.resize(vertices.size() * 2);
			normalsArray.resize(vertices.size() * 3);
			break;
		}
	}
	
	// read the faces in a second loop
	while ( !inFile.eof() ) {
		if (line == "")
			break;
		
		istringstream iss(line);
		string starts;
		GLuint u[9];
		
		iss >> starts;
		
		if (starts == "f") {
			// e.g. f 41/1/1 38/2/1 45/3/1
			string tmp, f = "";
			iss >> tmp;
			f += tmp + " ";
			iss >> tmp;
			f += tmp + " ";
			iss >> tmp;
			f += tmp;
					
			// replace /'s with space.
			size_t x = f.find("/");
			while (x < string::npos) {
				f.replace (x, 1, " ");
				x = f.find("/", x + 1);
			}
			istringstream iss2(f);
			for (int i = 0; i < 9; i++) {
				iss2 >> u[i];
			}
			
			/*
			cout << "f ";
			for (int i = 0; i < 9; i++) {
				cout << u[i] << " ";
			}
			cout << endl;
			*/
			processVertex(u[0], u[1], u[2], indices, textures, normals, textureArray, normalsArray);
			processVertex(u[3], u[4], u[5], indices, textures, normals, textureArray, normalsArray);
			processVertex(u[6], u[7], u[8], indices, textures, normals, textureArray, normalsArray);
		}
		
		getline(inFile, line);
	}
	
	//verticesArray.resize(vertices.size() * 3);
	//indicesArray.resize(indices.size());
	
	for (int i = 0; i < (int) vertices.size(); i++) {
		glm::vec3 v = vertices[i];
		verticesArray.push_back(v[0]);
		verticesArray.push_back(v[1]);
		verticesArray.push_back(v[2]);
	}
	
	for (int i = 0; i < (int) indices.size(); i++) {
		GLuint u = indices[i];
		indicesArray.push_back(u);
	}
	
	return loader.loadToVAO(verticesArray, textureArray, indicesArray);
}
