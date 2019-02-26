#include <stdint.h>
#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include <glut/glut.h>
#include <memory.h>
#include "Classes.h"
#include <iostream>


float* SetColorValues(float r, float g, float b)
{
	float* temp = new float[3];
	temp[0] = r;
	temp[1] = g;
	temp[2] = b;
	return temp;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Global variables
// width and height of the input and output datas

int width = 0;
int height = 0;
// start and end position for path finding. These are found automatically from input file.
int startX = 0;
int startY = 0;
int endX = 125;
int endY = 50;
unsigned int windowID;
float xRotated = 90.0;
// OpenGL texture ids for rendering.
GLuint  inputTexture = 0;
GLuint  outputTexture = 0;
// Input and output data in pixels. outputData is updated to outputTexture each frame
uint8_t* inputData = 0;
uint8_t* outputData = 0;

namespace
{
	// STUDENT_TODO: Make implementation for doPathFinding function, which writes found path to outputData
	void doPathFinding(const uint8_t* inputData, int width, int height,
		uint8_t* outputData, int startX, int startY, int endX, int endY)
	{

		OpenList list;
		ClosedList listA;
		SearchLevel levelSearcher(inputData);
		SearchNode StartNode(Position(startX, startY), 0, 0, NULL);
		SearchNode prev(StartNode);
		SearchNode curnode(StartNode);
		SearchNode EndNode(Position(endX, endY), 0, 0, NULL);
		SearchNode * n = new SearchNode(curnode.pos, levelSearcher.GetH(curnode.pos, EndNode.pos), levelSearcher.GetG(curnode.pos, StartNode.pos), 0);
		list.insertToOpenList(n);
		// Make noise for now
		for (size_t i = 0; i < 3 * width*height; i += 3)
		{
			SearchNode* result;
			prev = *(list.RemoveSmallestFFromOpenList());

			if (prev.pos == EndNode.pos)
			{
				curnode = prev;
				return;
			}

			listA.AddToClosedList(&prev);
			std::vector<Position> asdf = levelSearcher.GetAdjancentNodes(curnode.pos.first, curnode.pos.second);

			for (size_t i = 0; i < asdf.size(); ++i)
			{
				Position curpos = asdf[i];

				if (levelSearcher.IsWalkable(curpos.first, curpos.second) && !listA.IsInClosedList(curpos))
				{
					SearchNode * newNode = new SearchNode(curpos, levelSearcher.GetH(curpos, prev.pos),
						levelSearcher.GetG(curpos, StartNode.pos), &prev);

					SearchNode * nn = list.findFromOpenList(curpos);

					if (nn == 0)
					{
						list.insertToOpenList(newNode);
					}
					else
					{
						if (n->getDistance() >= newNode->getDistance())
						{
							n->resetPrev(newNode->prevNode, levelSearcher.GetG(newNode->prevNode->pos, n->pos));
							list.SortOpenList();
						}
					}
				}
			}

		}
	}
}



// Quick and dirty function for reading bmp-files to opengl textures.
GLuint loadBMPTexture(const char *fileName, int* w, int* h, uint8_t** data)
{
	assert(w != 0);
	assert(h != 0);
	assert(data != 0);
	FILE *file;
	if ((file = fopen(fileName, "rb")) == NULL)
		return 0;
	fseek(file, 18, SEEK_SET);

	fread(&width, 2, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&height, 2, 1, file);
	printf("Image \"%s\" (%dx%d)\n", fileName, width, height);

	*data = new uint8_t[3 * width * height];
	assert(data != 0);
	fseek(file, 30, SEEK_CUR);
	fread(*data, 3, width * height, file);
	fclose(file);

	GLuint  texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, *data);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (w) *w = width;
	if (h) *h = height;
	return texId;
}



bool init()
{
	glMatrixMode(GL_MODELVIEW);
	glOrtho(0, 512 + 4, 256 + 2, 0, -1, 1);
	inputData = NULL;
	// Load input file
	inputTexture = loadBMPTexture("input.bmp", &width, &height, &inputData);
	if (0 == inputTexture)
	{
		printf("Error! Cannot open file: \"input.bmp\"\n");
		return false;
	}

	// Make outputTexture
	glGenTextures(1, &outputTexture);
	glBindTexture(GL_TEXTURE_2D, outputTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Copy inputData also to outputData
	outputData = new uint8_t[3 * width*height];
	memcpy(outputData, inputData, 3 * width*height);

	// find start and end
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			uint8_t* pix = GetPixel(x, y, inputData, width); // get pixel
			uint8_t r = pix[0];
			uint8_t g = pix[1];
			uint8_t b = pix[2];
			if (255 == r && g == 0 && b == 0) // Red?
			{
				// Start
				startX = x;
				startY = y;
				printf("Start position: <%d,%d>\n", x, y);
			}
			if (255 == b && r == 0 && g == 0) // Blue?
			{
				// End
				endX = x;
				endY = y;
				printf("End position: <%d,%d>\n", x, y);
			}
		}
	}

	if (startX < 0 || startY < 0)
	{
		printf("Error! Start position not found\n");
		return false;
	}

	if (endX < 0 || endY < 0)
	{
		printf("Error! End position not found\n");
		return false;
	}

	return true;
}

template<typename T>
void CreateSolidSphere(T* position, T* colorvalues)
{
	glColor3f(colorvalues[0], colorvalues[1], colorvalues[2]);

	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	glRotatef(60.0, 1, 0, 0);
	glRotatef(xRotated* 2.0, 0, 0, 1);   // Red ball rotates at twice the rate of blue ball.
	glutSolidSphere(1.0, 20, 50);
}

float* SetPosition(float x, float y, float z)
{
	float* temp = new float[3];
	temp[0] = x;
	temp[1] = y;
	temp[2] = z;
	return temp;
}

void draw2(void)
{
	glMatrixMode(GL_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -15.0);
	CreateSolidSphere(SetPosition(0.5, 0.5, 0.5), SetColorValues(0.5, 0.5, 0.5));
	CreateSolidSphere(SetPosition(1.5, 0.5, -0.5), SetColorValues(0.0, 0.8, 0.5));
	CreateSolidSphere(SetPosition(0.0, 1.5, 0.5), SetColorValues(0.8, 0.0, 0.5));
	CreateSolidSphere(SetPosition(0.5, 0.1, 0.5), SetColorValues(0.5, 0.8, 0.5));
	glPopMatrix();
	glutSwapBuffers();

}

void idleFunc(void)
{
	xRotated += 0.3;
	glutPostRedisplay();
}

// Draw/Render
void draw()
{
	doPathFinding(inputData, width, height, outputData, startX, startY, endX, endY);

	// Copy outputData to outputTexture
	glBindTexture(GL_TEXTURE_2D, outputTexture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, outputData);
	glBindTexture(GL_TEXTURE_2D, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	// Draw input texture to left half of the screen
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, inputTexture);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); glVertex2d(1, 1);
	glTexCoord2d(0, 0); glVertex2d(1, 1 + 256);
	glTexCoord2d(1, 0); glVertex2d(1 + 256, 1 + 256);
	glTexCoord2d(1, 1); glVertex2d(1 + 256, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Draw output texture to right half of the screen
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, outputTexture);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1); glVertex2d(2 + 256, 1);
	glTexCoord2d(0, 0); glVertex2d(2 + 256, 1 + 256);
	glTexCoord2d(1, 0); glVertex2d(2 + 512, 1 + 256);
	glTexCoord2d(1, 1); glVertex2d(2 + 512, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}
// end - anonymous namespace

void keyBoardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		glutDestroyWindow(windowID);
		exit(0);
		break;
	case 's':
		break;

	default:
		break;
	}
}

void Reshape(int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}

// Main
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	windowID = glutCreateWindow("Pathfinding Demo");
	if (!init()) return -1;
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyBoardFunc);
	glutMainLoop();
	delete inputData;
	delete outputData;
	return 0;
}