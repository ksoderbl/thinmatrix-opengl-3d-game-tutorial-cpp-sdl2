#include "NormalMappedObjLoader.h"

RawModel *NormalMappedObjLoader::loadOBJ(string objFileName, Loader& loader)
{
	string RES_LOC = "../../res/";
	string fileName = RES_LOC + objFileName + ".obj";
	ifstream inFile(fileName, ios::in);

	if (!inFile) {
		cerr << "NormalMappedObjLoader: File " << fileName << " could not be opened" << endl;
		exit(1);
	}

	string line;
	vector<Vertex*> vertices;
	vector<glm::vec2> textures;
	vector<glm::vec3> normals;
	vector<glm::vec3> tangents;
	vector<GLuint> indices;

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
			Vertex* newVertex = new Vertex(vertices.size(), vertex);
			vertices.push_back(newVertex);
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
			//cout << "NormalMappedObjLoader: Read " << vertices.size() << " vertices from " << fileName << endl;
			//cout << "NormalMappedObjLoader: Read " << textures.size() << " texture coords from " << fileName << endl;
			//cout << "NormalMappedObjLoader: Read " << normals.size() << " normals from " << fileName << endl;
			break;
		}
	}

	int faces = 0;

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
				// the indices in the obj file start from 1, ours start from 0
				u[i]--;
			}

			Vertex* v0 = processVertex(u[0], u[1], u[2], vertices, indices);
			Vertex* v1 = processVertex(u[3], u[4], u[5], vertices, indices);
			Vertex* v2 = processVertex(u[6], u[7], u[8], vertices, indices);
			calculateTangents(v0, v1, v2, textures);

			faces++;
		}

		getline(inFile, line);
	}

	//cout << "NormalMappedObjLoader: Read " << faces << " faces from " << fileName << endl;

	removeUnusedVertices(vertices);
	vector<GLfloat> verticesArray;
	vector<GLfloat> texturesArray;
	vector<GLfloat> normalsArray;
	vector<GLfloat> tangentsArray;
	convertDataToArrays(
		vertices, textures, normals,
		verticesArray, texturesArray, normalsArray, tangentsArray);

	vector<GLuint> indicesArray;
	for (int i = 0; i < (int) indices.size(); i++) {
		GLuint u = indices[i];
		indicesArray.push_back(u);
	}

	// free allocated Vertex objects
	for (int i = 0; i < (int) vertices.size(); i++) {
		delete vertices[i];
	}

	return loader.loadToVAO(verticesArray, texturesArray, normalsArray,
				tangentsArray, indicesArray);
}

void NormalMappedObjLoader::calculateTangents(
	Vertex* v0, Vertex* v1, Vertex* v2,
	vector<glm::vec2>& textures)
{
	glm::vec3 deltaPos1 = v1->getPosition() - v0->getPosition();
	glm::vec3 deltaPos2 = v2->getPosition() - v0->getPosition();
	glm::vec2 uv0 = textures[v0->getTextureIndex()];
	glm::vec2 uv1 = textures[v1->getTextureIndex()];
	glm::vec2 uv2 = textures[v2->getTextureIndex()];
	glm::vec2 deltaUv1 = uv1 - uv0;
	glm::vec2 deltaUv2 = uv2 - uv0;

	GLfloat r = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
	deltaPos1 *= deltaUv2.y;
	deltaPos2 *= deltaUv1.y;
	glm::vec3 tangent = deltaPos1 - deltaPos2;
	tangent *= r;
	v0->addTangent(tangent);
	v1->addTangent(tangent);
	v2->addTangent(tangent);
}

Vertex* NormalMappedObjLoader::processVertex(
	int index,
	int textureIndex,
	int normalIndex,
	vector<Vertex*>& vertices,
	vector<GLuint>& indices)
{
	Vertex* currentVertex = vertices[index];
	if (!currentVertex->isSet()) {
		currentVertex->setTextureIndex(textureIndex);
		currentVertex->setNormalIndex(normalIndex);
		indices.push_back(index);
		return currentVertex;
	}
	else {
		return dealWithAlreadyProcessedVertex(
			currentVertex, textureIndex, normalIndex, indices, vertices);
	}
}

GLfloat NormalMappedObjLoader::convertDataToArrays(
	vector<Vertex*>& vertices,
	vector<glm::vec2>& textures,
	vector<glm::vec3>& normals,
	vector<GLfloat>& verticesArray,
	vector<GLfloat>& texturesArray,
	vector<GLfloat>& normalsArray,
	vector<GLfloat>& tangentsArray)
{
	GLfloat furthestPoint = 0;

	for (int i = 0; i < (int) vertices.size(); i++) {
		Vertex* currentVertex = vertices[i];
		if (currentVertex->getLength() > furthestPoint) {
			furthestPoint = currentVertex->getLength();
		}
		glm::vec3 position = currentVertex->getPosition();
		glm::vec2 textureCoord = textures[currentVertex->getTextureIndex()];
		glm::vec3 normalVector = normals[currentVertex->getNormalIndex()];
		glm::vec3 tangent = currentVertex->getAverageTangent();

		verticesArray.push_back(position.x);
		verticesArray.push_back(position.y);
		verticesArray.push_back(position.z);
		texturesArray.push_back(textureCoord.x);
		texturesArray.push_back(1.0 - textureCoord.y);
		normalsArray.push_back(normalVector.x);
		normalsArray.push_back(normalVector.y);
		normalsArray.push_back(normalVector.z);
		tangentsArray.push_back(tangent.x);
		tangentsArray.push_back(tangent.y);
		tangentsArray.push_back(tangent.z);
	}
	return furthestPoint;
}

Vertex* NormalMappedObjLoader::dealWithAlreadyProcessedVertex(
	Vertex *previousVertex,
	int newTextureIndex,
	int newNormalIndex,
	vector<GLuint>& indices,
	vector<Vertex*>& vertices)
{
	if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
		indices.push_back(previousVertex->getIndex());
		return previousVertex;
	} else {
		Vertex* anotherVertex = previousVertex->getDuplicateVertex();
		if (anotherVertex != nullptr) {
			return dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex,
				indices, vertices);
		} else {
			Vertex* duplicateVertex = new Vertex(vertices.size(), previousVertex->getPosition());
			duplicateVertex->setTextureIndex(newTextureIndex);
			duplicateVertex->setNormalIndex(newNormalIndex);
			previousVertex->setDuplicateVertex(duplicateVertex);
			vertices.push_back(duplicateVertex);
			indices.push_back(duplicateVertex->getIndex());
			return duplicateVertex;
		}
	}
}

void NormalMappedObjLoader::removeUnusedVertices(vector<Vertex*>& vertices)
{
	/*
	vector<Vertex*>::iterator it;

	for (it = vertices.begin(); it != vertices.end(); it++) {
		Vertex* vertex = *it;
		if (!vertex->isSet()) {
			vertex->setTextureIndex(0);
			vertex->setNormalIndex(0);
		}
	}
	*/
	for (Vertex* vertex : vertices) {
		// TODO: should be done in an own function
		vertex->averageTangents();
		if (!vertex->isSet()) {
			vertex->setTextureIndex(0);
			vertex->setNormalIndex(0);
		}
	}
}
