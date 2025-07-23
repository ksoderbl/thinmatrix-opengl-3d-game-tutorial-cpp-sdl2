#include "MetaFile.h"
#include "TextMeshCreator.h"
#include "../DisplayManager.h"

/**
 * Opens a font file in preparation for reading.
 * 
 * @param file
 *	    - the font file.
 */
MetaFile::MetaFile(string file)
{
	this->aspectRatio = (double) display.getWidth() / (double) display.getHeight();
	openFile(file);
	loadPaddingData();
	loadLineSizes();
	int imageWidth = getValueOfVariable("scaleW");
	
	//cout << "MetaFile: got imagewidth = " << imageWidth << endl;
	
	loadCharacterData(imageWidth);
	close();
}

double MetaFile::getSpaceWidth()
{
	return spaceWidth;
}

Character* MetaFile::getCharacter(int ascii)
{
	map<int, Character*>::iterator it = metaData.find(ascii);
	if (it == metaData.end()) {
		return nullptr;
	}
	return it->second;
}

/**
 * Read in the next line and store the variable values.
 * 
 * @return {@code true} if the end of the file hasn't been reached.
 */
bool MetaFile::processNextLine()
{
	values.clear();
	
	//cout << "processNextLine()" << endl;
	
	string line;
	if (!getline(ifs, line)) {
		cout << "processNextLine() returned false" << endl;
		return false;
	}
	
	//cout << "processNextLine() got line " << line << endl;
	
	
	// TODO: this doesn't work right for lines containing e.g.
	// face="Verdana Bold", but it works for my purposes.
	
	istringstream iss(line);
	string str;
	
	while (iss >> str) {
		//cout << "==== processNextLine() key=value: " << str << endl;
		stringstream ss(str);
		string key, value;
		if (getline(ss, key, '=')) {
			getline(ss, value);
			//cout << "processNextLine() key=" << key << ", value=" << value << endl;
			if (key != "" && value != "") {
				values.insert(pair<string, string>(key, value));
			}
		}
	}
		
	return true;
}

/**
 * Gets the {@code int} value of the variable with a certain name on the
 * current line.
 * 
 * @param variable
 *	    - the name of the variable.
 * @return The value of the variable.
 */
int MetaFile::getValueOfVariable(string variable)
{
	int result;	
	map<string, string>::iterator it = values.find(variable);
	if (it == values.end()) {
		return 0;
	}
	string value = it->second;
	stringstream ss(value);
	
	if (ss >> result) {
		return result;
	}
	return 0;
}

/**
 * Gets the vector of ints associated with a variable on the current line.
 * 
 * @param variable
 *	    - the name of the variable.
 * @return The vector of int values associated with the variable.
 */
vector<int> MetaFile::getValuesOfVariable(string variable)
{
	vector<int> result;
	
	map<string, string>::iterator it = values.find(variable);
	if (it == values.end()) {
		return result;
	}
	string values = it->second;
	
	//cout << "Values of variable " << variable << " are " << values << endl;
	
	// replace commas with space.
	auto x = values.find(",");
	while (x < string::npos) {
		values.replace (x, 1, " ");
		x = values.find(",", x + 1);
	}
	
	//cout << "Values of variable " << variable << " are after replace " << values << endl;
	
	istringstream iss(values);
	
	int number;
	while (iss >> number) {
		result.push_back(number);
	}

	return result;
}

/**
 * Closes the font file after finishing reading.
 */
void MetaFile::close()
{
	ifs.close();
}

/**
 * Opens the font file, ready for reading.
 * 
 * @param file
 *	    - the font file.
 */
bool MetaFile::openFile(string file)
{
	ifs.open(file, ifstream::in);
	if (ifs.good()) {
		//cout << "MetaFile: openFile " << file << " OK" << endl;
		return true;
	} else {
		cerr << "MetaFile: Font meta file " << file << " could not be opened" << endl;
		return false;
	}
}

/**
 * Loads the data about how much padding is used around each character in
 * the texture atlas.
 */
void MetaFile::loadPaddingData()
{
	processNextLine();
	padding = getValuesOfVariable("padding");
	
	//cout << "got values: left   : " << padding[PAD_LEFT] << endl;
	//cout << "got values: right  : " << padding[PAD_RIGHT] << endl;
	//cout << "got values: top    : " << padding[PAD_TOP] << endl;
	//cout << "got values: bottom : " << padding[PAD_BOTTOM] << endl;
	
	paddingWidth = padding[PAD_LEFT] + padding[PAD_RIGHT];
	paddingHeight = padding[PAD_TOP] + padding[PAD_BOTTOM];
}

/**
 * Loads information about the line height for this font in pixels, and uses
 * this as a way to find the conversion rate between pixels in the texture
 * atlas and screen-space.
 */
void MetaFile::loadLineSizes()
{
	processNextLine();
	
	cout << "MetaFile: lineHeight = " << getValueOfVariable("lineHeight") << endl;
	
	int lineHeightPixels = getValueOfVariable("lineHeight") - paddingHeight;
	verticalPerPixelSize = TextMeshCreator::LINE_HEIGHT / (double) lineHeightPixels;
	horizontalPerPixelSize = verticalPerPixelSize / aspectRatio;
}

/**
 * Loads in data about each character and stores the data in the
 * {@link Character} class.
 * 
 * @param imageWidth
 *	    - the width of the texture atlas in pixels.
 */
void MetaFile::loadCharacterData(int imageWidth)
{
	processNextLine();
	processNextLine();
	int count = 0;
	while (processNextLine()) {
		Character* c = loadCharacter(imageWidth);
		if (c != nullptr) {
			metaData.insert(pair<int, Character*>(c->getId(), c));
		}
		count++;
	}
	//cout << "MetaFile: loaded " << count << " characters" << endl;
}

/**
 * Loads all the data about one character in the texture atlas and converts
 * it all from 'pixels' to 'screen-space' before storing. The effects of
 * padding are also removed from the data.
 * 
 * @param imageSize
 *	    - the size of the texture atlas in pixels.
 * @return The data about the character.
 */
Character* MetaFile::loadCharacter(int imageSize)
{
	int id = getValueOfVariable("id");
    if (id == TextMeshCreator::SPACE_ASCII) {
		this->spaceWidth = (getValueOfVariable("xadvance") - paddingWidth) * horizontalPerPixelSize;
		return nullptr;
    }
	double xTex = ((double) getValueOfVariable("x") + (padding[PAD_LEFT] - DESIRED_PADDING)) / imageSize;
	double yTex = ((double) getValueOfVariable("y") + (padding[PAD_TOP] - DESIRED_PADDING)) / imageSize;
	int width = getValueOfVariable("width") - (paddingWidth - (2 * DESIRED_PADDING));
	int height = getValueOfVariable("height") - ((paddingHeight) - (2 * DESIRED_PADDING));
	double quadWidth = width * horizontalPerPixelSize;
	double quadHeight = height * verticalPerPixelSize;
	double xTexSize = (double) width / imageSize;
	double yTexSize = (double) height / imageSize;
	double xOff = (getValueOfVariable("xoffset") + padding[PAD_LEFT] - DESIRED_PADDING) * horizontalPerPixelSize;
	double yOff = (getValueOfVariable("yoffset") + (padding[PAD_TOP] - DESIRED_PADDING)) * verticalPerPixelSize;
	double xAdvance = (getValueOfVariable("xadvance") - paddingWidth) * horizontalPerPixelSize;
	return new Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
}
