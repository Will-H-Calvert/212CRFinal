//reader.h

#ifndef READER_H
#define READER_H

#define MAX_VERT 100000

struct Vertex {
	float x;
	float y;
	float z;
};

struct Face
{
	int id1;
	int id2;
	int id3;
	int id4;
};

class Reader {
public:
	int numPts;
	int numFaces;
	Vertex vertex[5000];
	Vertex normal[5000];
	Face faces[5000];

public:
	Reader();
	~Reader();

	void loadVertex(char* filename);
	void LoadFace(char* filename);
	void LoadModel(char* filename);
	void CalNormal(void);

};

#endif
