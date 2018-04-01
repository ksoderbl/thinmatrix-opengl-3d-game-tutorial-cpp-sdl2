#include "Loader.h"

#include <png.h>

Loader::Loader()
{
	vaos = new vector<GLuint>();
	vbos = new vector<GLuint>();
	textures = new vector<GLuint>();
}

Loader::~Loader()
{
	delete vaos;
	delete vbos;
	delete textures;
}

RawModel *Loader::loadToVAO(
	vector<GLfloat>&positions,
	vector<GLfloat>&textureCoords,
	vector<GLuint>&indices)
{
	GLuint vaoID = createVAO();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	unbindVAO();
	return new RawModel(vaoID, indices.size());
}

GLuint Loader::loadTexture(string fileName)
{
	GLuint textureID; /* texture name (from glGenTextures) */
	GLint tx_w;       /* width in pixels */
	GLint tx_h;       /* height in pixels */
	GLenum tx_fmt;    /* format: RGB or RGBA */
	GLubyte *tx_data; /* image data */
	
	fileName = "../res/" + fileName + ".png";

	tx_data = LoadPNGImage(fileName, &tx_w, &tx_h, &tx_fmt);
	if (!tx_data) {
		cerr << "loadTexture failed for " << fileName << "\n";
		exit(1);
	}

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, tx_fmt, tx_w, tx_h, 0, tx_fmt, GL_UNSIGNED_BYTE, tx_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	textures->push_back(textureID);
	return textureID;
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
	
	for (p = textures->begin(); p != textures->end(); p++)
		glDeleteTextures(1, &*p);
	textures->clear();
}

GLuint Loader::createVAO()
{
	GLuint vaoID = 0;
	glGenVertexArrays(1, &vaoID);
	vaos->push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

GLuint Loader::createVBO(GLenum target)
{
	GLuint vboID = 0;
	glGenBuffers(1, &vboID);
	vbos->push_back(vboID);
	glBindBuffer(target, vboID);
	return vboID;
}

void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, vector<GLfloat>&data)
{
	GLuint vboID = createVBO(GL_ARRAY_BUFFER);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);	
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(vector<GLuint>&indices)
{
	GLuint vboID = createVBO(GL_ELEMENT_ARRAY_BUFFER);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}



/*
 * Load an PNG file and return a pointer to the image data.
 * Input:  imageFile - name of .png to read
 * Output:  width - width of image
 *          height - height of image
 *          format - format of image (GL_RGB or GL_RGBA)
 * Return:  pointer to image data or NULL if error
 */

// Based on https://gist.github.com/niw/5963798

GLubyte* Loader::LoadPNGImage(string imageFile,
			     GLint *width, GLint *height,
			     GLenum *format)
{
	FILE *fp = fopen(imageFile.c_str(), "rb");

	int w, h;
	png_byte color_type;
	png_byte bit_depth;
	png_bytep *row_pointers;

	//cout << "Loading " << imageFile.c_str() << endl;

	if (!fp) {
		cerr << "LoadPNGImage: fopen of "
		     << imageFile.c_str() << " failed." << endl;
		return 0;
	}

	png_structp png = png_create_read_struct(
		PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png) abort();
	
	png_infop info = png_create_info_struct(png);
	if(!info) abort();
	
	if(setjmp(png_jmpbuf(png))) abort();
	
	png_init_io(png, fp);
	
	png_read_info(png, info);

	w = png_get_image_width(png, info);
	h = png_get_image_height(png, info);
	color_type = png_get_color_type(png, info);
	bit_depth = png_get_bit_depth(png, info);
	
	// Read any color_type into 8bit depth, RGBA format.
	// See http://www.libpng.org/pub/png/libpng-manual.txt
	
	if(bit_depth == 16)
		png_set_strip_16(png);
	
	if(color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);
	
	// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);
	
	if(png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);
	
	// These color_type don't have an alpha channel then fill it with 0xff.
	if(color_type == PNG_COLOR_TYPE_RGB ||
	   color_type == PNG_COLOR_TYPE_GRAY ||
	   color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
	
	if(color_type == PNG_COLOR_TYPE_GRAY ||
	   color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);
	
	png_read_update_info(png, info);
	
	row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * h);
	for(int y = 0; y < h; y++) {
		row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
	}
	
	png_read_image(png, row_pointers);
	
	fclose(fp);
	
	GLint bytes, bytes_per_row;
	GLubyte *buffer;
	
	bytes_per_row = w * 4;  // 4 = RGBA bytes
	bytes = h * bytes_per_row;
	buffer = (GLubyte *) malloc(bytes);
	if (!buffer)
		return 0;
	
	for(int y = 0 ; y < h; y++) {
		memcpy(buffer + y * bytes_per_row,
		       row_pointers[y], bytes_per_row);
		free(row_pointers[y]);
	}
	free(row_pointers);

	*width = w;
	*height = h;
	*format = GL_RGBA;
	
	return buffer;
}


