//reader.cpp
#include <GL/freeglut.h>
#include <fstream>
#include <iostream>
#include <string>

#include "reader.h"

using namespace std;

Reader::Reader()
{
	numPts = 0;
	for (int i = 0; i < 5000; i++) {
		vertex[i].x = 0;
		vertex[i].y = 0;
		vertex[i].z = 0;

		normal[i].x = 0;
		normal[i].y = 0;
		normal[i].z = 0;
	}

	for (int i = 0; i < 5000; i++) {
		faces[i].id1 = 0;
		faces[i].id2 = 0;
		faces[i].id3 = 0;
		faces[i].id4 = 0;
	}
}

Reader::~Reader()
{

}

void Reader::loadVertex(char* filename)
{
	ifstream file;
	file.open(filename);

	string str;

	while (!file.eof()) //while we are still in the file
	{
		getline(file, str); //move one line down
		if (str[0] == 'v') break; //if we have a vertex line, stop
	}

	int v = 0;

	while (str[0] == 'v') {

		//convert data into X,Y,Z
		str[0] = ' ';
		sscanf(str.c_str(), "%f %f %f ",							// Read floats from the line: v X Y Z
			&vertex[v].x,
			&vertex[v].y,
			&vertex[v].z);

		v++;
		getline(file, str);
	}

	numPts = v;
}

void Reader::LoadFace(char *filename)
{
	int count;
	ifstream file;
	file.open(filename);

	string str;

	while (true)
	{
		getline(file, str);
		if (str[0] == 'f') {
			break;
		}
	}

	count = 0;
	while (str[0] == 'f')
	{
		str[0] = ' ';
		sscanf_s(str.c_str(), "%d %d %d",
			&faces[count].id1,
			&faces[count].id2,
			&faces[count].id3);

		///this is for four vertice polygon
		/*sscanf_s(str.c_str(), "%d %d %d %d",
			&faces[count].id1,
			&faces[count].id2,
			&faces[count].id3,
			&faces[count].id4);*/

		faces[count].id1--;
		faces[count].id2--;
		faces[count].id3--;
		faces[count].id4--;

		count++;

		getline(file, str);
	}

	numFaces = count;
}

void Reader::LoadModel(char *filename)
{
	loadVertex(filename);
	LoadFace(filename);

	CalNormal();
}

void Reader::CalNormal(void)
{
	int i,id1,id2,id3;
	Vertex edge1,edge2;
	Vertex testNor,unitNor;
	float len;

	for (i = 0; i < numFaces; i++)
	{
		id1 = faces[i].id1;
		id2 = faces[i].id2;
		id3 = faces[i].id3;

		edge1.x = vertex[id2].x - vertex[id1].x;
		edge1.y = vertex[id2].y - vertex[id1].y;
		edge1.z = vertex[id2].z - vertex[id1].z;

		edge2.x = vertex[id3].x - vertex[id2].x;
		edge2.y = vertex[id3].y - vertex[id2].y;
		edge2.z = vertex[id3].z - vertex[id2].z;

		testNor.x = edge1.y*edge2.z - edge1.z*edge2.y;
		testNor.y = edge1.z*edge2.x - edge1.x*edge2.z;
		testNor.z = edge1.x*edge2.y - edge1.y*edge2.x;

		len = sqrt(testNor.x*testNor.x + testNor.y*testNor.y + testNor.z*testNor.z);
		unitNor.x = testNor.x / len;
		unitNor.y = testNor.y / len;
		unitNor.z = testNor.z / len;

		normal[id1].x = unitNor.x;
		normal[id1].y = unitNor.y;
		normal[id1].z = unitNor.z;

		normal[id2].x = unitNor.x;
		normal[id2].y = unitNor.y;
		normal[id2].z = unitNor.z;

		normal[id3].x = unitNor.x;
		normal[id3].y = unitNor.y;
		normal[id3].z = unitNor.z;
	}
}