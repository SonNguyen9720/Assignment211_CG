/*
	Ho va ten: Le Kha
	MSSV     : 1810976
*/


#include <math.h>
#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <glut.h>

#define PI			3.1415926
#define	COLORNUM		14
using namespace std;

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}
	void set(Color3& c)
	{
		r = c.r; g = c.g; b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}

};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw() {
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
	Point2 lineIntersection(Point2 p1, Point2 p2, Point2 p3, Point2 p4) {
		Point2 t;
		float A1, B1, A2, B2;

		A1 = (p2.y - p1.y) / (p2.x - p1.x);
		B1 = p1.y - A1 * p1.x;

		A2 = (p4.y - p3.y) / (p4.x - p3.x);
		B2 = p3.y - A2 * p3.x;

		t.x = (B2 - B1) / (A1 - A2);
		t.y = A1 * t.x + B1;

		return t;
	}
private:
	float 	x, y;
};
class IntRect
{
public:
	IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void draw() {
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int  getWidth() { return (r - l); }
	int  getHeight() { return (t - b); }
private:
	int	l, r, b, t;
};


class RealRect
{
public:
	RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	float  getWidth() { return (r - l); }
	float  getHeight() { return (t - b); }
	void draw() {
		glRectf(l, b, r, t);
		glFlush();
	};// draw this rectangle using OpenGL
private:
	float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	void flip()
	{
		x = -x; y = -y; z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID* vert;
	Vector3		norm;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3* pt;

	int		numFaces;
	Face* face;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();

	void CreateTetrahedron();
	void CreateCube(float fSize);
	void CreateCylinder(float fHeight, float fRadius);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateShape1(int N, float radius);
	void CreateShape2();
	void CreateShape3();
	void CreateShape4();
	void CreateShape5();
	void SetColor(int colorIndex);
	void DrawSmooth();
	void CalculateNorms();
	void setupMaterial(float ambient[], float diffuse[], float specular[], float shininess);

	void create_truc_quay();
	//void create_truc_quay_1();
	void create_goi_do(float fHeight, float fRadius);
	void create_thanh_lien_ket(float fLength, float fHeight, float fBig_radius, float fSmall_radius);
	void create_canh_quat(float fHeight);
};

float	ColorArr[COLORNUM][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} };





void Mesh::CreateCylinder(float fHeight, float fRadius)
{
	int nSegment = 36;
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, 0, fHeight / 2);
	for (i = 0; i < nSegment; i++)
	{
		x = fRadius * cos(fAngle * (double)i);
		y = fRadius * sin(fAngle * (double)i);
		z = fHeight / 2;
		pt[i + 1].set(x, y, z);

		z = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, 0, -fHeight / 2);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2;
		else
			face[idx].vert[2].vertIndex = 1;
		face[idx].vert[1].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i < nSegment - 1)
			face[idx].vert[3].vertIndex = i + 2;
		else
			face[idx].vert[3].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[1].vertIndex = 1 + nSegment;
		face[idx].vert[2].vertIndex = i + 1 + nSegment;
		idx++;
	}

}

void Mesh::CreateCube(float	fSize)
{

	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;
	////
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

}


void Mesh::CreateTetrahedron()
{
	int i;
	numVerts = 4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces = 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;


	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;


	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;
}
void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{

	int i;
	numVerts = 8;
	pt = new Point3[numVerts];

	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(fSizeX, -fSizeY, fSizeZ);
	pt[6].set(fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);

	numFaces = 6;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 3;
	face[0].vert[2].vertIndex = 7;
	face[0].vert[3].vertIndex = 4;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 3;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 7;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 1;
	face[2].vert[1].vertIndex = 5;
	face[2].vert[2].vertIndex = 6;
	face[2].vert[3].vertIndex = 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 0;
	face[3].vert[1].vertIndex = 4;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 1;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 6;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 4;
	face[4].vert[3].vertIndex = 7;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 2;
	face[5].vert[1].vertIndex = 3;
	face[5].vert[2].vertIndex = 0;
	face[5].vert[3].vertIndex = 1;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}
void Mesh::CreateShape1(int N, float radius)
{
	// N: so diem tren mot nua hinh tron

	GLdouble angle = PI / (2 * ((double)N - 2.0));

	int i = 0;
	numVerts = N * 2 + 4;
	pt = new Point3[numVerts];

	float y = 3.0 / 12;

	pt[0].set(radius, y, 0);
	for (i = 1; i < N; i++) // [0,N-1]
	{
		double h = (double)i - 1.0;
		pt[i].set(radius - radius * cos(h * angle), y, radius * sin(h * angle));

	}
	pt[N].set(radius, 0.0, 0.0);
	for (i = N + 1; i < 2 * N; i++) // [N,2N-1]
	{
		double h = (double)i - N - 1.0;
		pt[i].set(radius - radius * cos(h * angle), 0, radius * sin(h * angle));

	}
	pt[2 * N].set(7 * pt[0].x, y, 0);
	pt[2 * N + 1].set(7 * pt[0].x, y, pt[N - 1].z);
	pt[2 * N + 2].set(7 * pt[0].x, 0, pt[N - 1].z);
	pt[2 * N + 3].set(7 * pt[0].x, 0, 0);

	numFaces = 200;
	face = new Face[numFaces];

	int color = 0;
	i = 0;

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2 * N;
	face[0].vert[2].vertIndex = 2 * N + 3;
	face[0].vert[3].vertIndex = N + 1;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 2 * N;
	face[1].vert[1].vertIndex = 2 * N + 1;
	face[1].vert[2].vertIndex = 2 * N + 2;
	face[1].vert[3].vertIndex = 2 * N + 3;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 2 * N + 1;
	face[2].vert[1].vertIndex = N - 1;
	face[2].vert[2].vertIndex = 2 * N - 1;
	face[2].vert[3].vertIndex = 2 * N + 2;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 0;
	face[3].vert[1].vertIndex = N - 1;
	face[3].vert[2].vertIndex = 2 * N - 1;
	face[3].vert[3].vertIndex = N;
	for (i = 0; i < face[0].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 2 * N + 2;
	face[4].vert[1].vertIndex = 2 * N - 1;
	face[4].vert[2].vertIndex = N;
	face[4].vert[3].vertIndex = 2 * N + 3;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 0;
	face[5].vert[1].vertIndex = N - 1;
	face[5].vert[2].vertIndex = 2 * N + 1;
	face[5].vert[3].vertIndex = 2 * N;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	i = 6;
	color = 6;



	for (int j = 1; j < N - 1; j++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = 0;
		face[i].vert[1].vertIndex = j;
		face[i].vert[2].vertIndex = j + 1;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}

	for (int j = N + 1; j < 2 * N - 1; j++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = N;
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}

	//cac mat hinh chu nhat ngoai
	for (int j = 1; j < N - 1; j++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = j + N + 1;
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j;
		face[i].vert[3].vertIndex = j + N;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}
}

void Mesh::CreateShape2() {
	int N = 36;
	float angle = PI / ((double)N - 2.0);
	int i = 0;
	numVerts = 4 * N + 8;
	pt = new Point3[numVerts];
	GLfloat x = 5.0 / 4;
	float y = 3.0 / 12;
	float z = 1.0 / 4;
	float radius2 = 1.25 / 4;
	float radius = radius2 / 1.5;

	//quat nho tren
	pt[0].set(0, y, 0);
	for (i = 1; i < N; i++) // [0,N-1]
	{
		double h = (double)i - 1.0;
		pt[i].set(-radius * sin(h * angle), y, radius * cos(h * angle));
	}
	//quat nho duoi
	pt[N].set(0, 0, 0);
	for (i = N + 1; i < 2 * N; i++) // [N,2N-1]
	{
		double h = (double)i - (double)N - 1.0;
		pt[i].set(pt[i - N].x, 0, pt[i - N].z);
	}

	//tren
	pt[2 * N].set(x / 2, y, pt[1].z * 1.5);
	pt[2 * N + 1].set(x / 2, y, pt[2 * N].z / 2);
	pt[2 * N + 2].set(x / 2, y, -pt[2 * N + 1].z);
	pt[2 * N + 3].set(x / 2, y, -pt[2 * N].z);

	//quat to tren
	pt[2 * N + 4].set(4 * x, y, 0);
	for (i = 2 * N + 5; i < 3 * N + 4; i++) // [2N+4,3N+3]
	{
		double h = (double)i - 2.0 * (double)N - 5.0;
		pt[i].set(4 * x + radius2 * sin(h * angle), y, radius2 * cos(h * angle));
	}

	//quat to duoi
	pt[3 * N + 4].set(4 * x, 0, 0);
	for (i = 3 * N + 5; i < 4 * N + 4; i++) // [3N+4,4N+4]
	{
		double h = (double)i - (double)3 * (double)N - 5.0;
		pt[i].set(pt[i - N].x, 0, pt[i - N].z);
	}
	//duoi
	pt[4 * N + 4].set(pt[2 * N].x, 0, pt[2 * N].z);
	pt[4 * N + 5].set(pt[2 * N + 1].x, 0, pt[2 * N + 1].z);
	pt[4 * N + 6].set(pt[2 * N + 2].x, 0, pt[2 * N + 2].z);
	pt[4 * N + 7].set(pt[2 * N + 3].x, 0, pt[2 * N + 3].z);

	numFaces = 250;
	face = new Face[numFaces];
	int color = 0;
	i = 0;
	//quat nho tren
	for (int j = 1; j < N - 1; j++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = 0;//tam
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}
	//quat nho duoi
	for (int j = N + 1; j < 2 * N - 1; j++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = N;//tam
		face[i].vert[1].vertIndex = j;
		face[i].vert[2].vertIndex = j + 1;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}
	//mat chu nhat nho ngoai
	for (int j = 1; j < N - 1; j++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = j + N + 1;
		face[i].vert[1].vertIndex = j + N;
		face[i].vert[2].vertIndex = j;
		face[i].vert[3].vertIndex = j + 1;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}
	//mat tren gan quat nho
	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 0;
	face[i].vert[1].vertIndex = 2 * N + 2;
	face[i].vert[2].vertIndex = N - 1;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 0;
	face[i].vert[1].vertIndex = 2 * N + 1;
	face[i].vert[2].vertIndex = 2 * N + 2;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 0;
	face[i].vert[1].vertIndex = 1;
	face[i].vert[2].vertIndex = 2 * N + 1;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 2 * N + 4;
	face[i].vert[1].vertIndex = 2 * N + 1;
	face[i].vert[2].vertIndex = 2 * N;
	face[i].vert[3].vertIndex = 2 * N + 5;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 2 * N + 4;
	face[i].vert[1].vertIndex = 3 * N + 3;
	face[i].vert[2].vertIndex = 2 * N + 3;
	face[i].vert[3].vertIndex = 2 * N + 2;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	//tam giac tren gan quat to
	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 2 * N + 2;
	face[i].vert[1].vertIndex = 2 * N + 1;
	face[i].vert[2].vertIndex = 2 * N + 4;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	//quat to tren
	for (int j = 2 * N + 5; j < 3 * N + 3; j++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = 2 * N + 4;//tam
		face[i].vert[1].vertIndex = j;
		face[i].vert[2].vertIndex = j + 1;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}

	//quat to duoi
	for (int j = 3 * N + 5; j < 4 * N + 3; j++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = 3 * N + 4;//tam
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}
	//mat chu nhat lon ngoai
	for (int j = 2 * N + 5; j < 3 * N + 3; j++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = j + N + 1;
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j;
		face[i].vert[3].vertIndex = j + N;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}
	//tu giac gan quat to duoi
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 4 * N + 5;
	face[i].vert[1].vertIndex = 3 * N + 4;
	face[i].vert[2].vertIndex = 3 * N + 5;
	face[i].vert[3].vertIndex = 4 * N + 4;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	//tu giac gan quat to duoi
	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 4 * N + 7;
	face[i].vert[1].vertIndex = 4 * N + 3;
	face[i].vert[2].vertIndex = 3 * N + 4;//3*N+4
	face[i].vert[3].vertIndex = 4 * N + 6;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;
	//tam giac gan quat to duoi
	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 3 * N + 4;
	face[i].vert[1].vertIndex = 4 * N + 5;
	face[i].vert[2].vertIndex = 4 * N + 6;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	//tam giac gan quat nho duoi
	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 4 * N + 5;
	face[i].vert[1].vertIndex = N + 1;
	face[i].vert[2].vertIndex = N;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;
	//tam giac duoi gan quat nho
	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 4 * N + 5;
	face[i].vert[1].vertIndex = N;
	face[i].vert[2].vertIndex = 4 * N + 6;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;
	//tam giac duoi gan quat nho
	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 4 * N + 6;
	face[i].vert[1].vertIndex = N;
	face[i].vert[2].vertIndex = 2 * N - 1;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 2 * N;
	face[i].vert[1].vertIndex = 2 * N + 1;
	face[i].vert[2].vertIndex = 4 * N + 5;
	face[i].vert[3].vertIndex = 4 * N + 4;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 2 * N + 2;
	face[i].vert[1].vertIndex = 2 * N + 3;
	face[i].vert[2].vertIndex = 4 * N + 7;
	face[i].vert[3].vertIndex = 4 * N + 6;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 3 * N + 5;
	face[i].vert[1].vertIndex = 2 * N + 5;
	face[i].vert[2].vertIndex = 2 * N;
	face[i].vert[3].vertIndex = 4 * N + 4;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 2 * N + 3;
	face[i].vert[1].vertIndex = 3 * N + 3;
	face[i].vert[2].vertIndex = 4 * N + 3;
	face[i].vert[3].vertIndex = 4 * N + 7;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 2 * N + 1;
	face[i].vert[1].vertIndex = 1;
	face[i].vert[2].vertIndex = N + 1;
	face[i].vert[3].vertIndex = 4 * N + 5;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 2 * N - 1;
	face[i].vert[1].vertIndex = N - 1;
	face[i].vert[2].vertIndex = 2 * N + 2;
	face[i].vert[3].vertIndex = 4 * N + 6;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;
}

void Mesh::CreateShape3() {
	int N = 36;
	GLdouble angle = 5.0 * PI / (6.0 * ((double)N - 2.0));
	int i = 0;
	numVerts = 2 * N + 8;
	pt = new Point3[numVerts];
	float x = 20.0 / 8;
	float y = 3.0 / 12;
	float z = 6.0 / 12;
	float radius = 3.0 / 8;
	pt[0].set(0, 0, 0);
	pt[1].set(0, y, 0);
	pt[2].set(x, y, 0);
	pt[3].set(x, 0, 0);
	pt[3].set(x, 0, 0);
	pt[4].set(0, y, z);
	pt[5].set(x / 2, y, z);
	pt[6].set(x / 2, 0, z);
	pt[7].set(0, 0, z);


	pt[8].set(x * 0.7, y, z * 1.5);
	for (i = 9; i < N + 8; i++) // [8,N+7]
	{
		double h = (double)i - 9.0;
		pt[i].set(pt[8].x - radius * cos(PI / 10 + h * angle), y, pt[8].z + radius * sin(PI / 10 + h * angle));

	}

	pt[N + 8].set(pt[8].x, 0, pt[8].z);
	for (i = N + 9; i < 2 * N + 8; i++) // [N+8,2N+7]
	{
		double h = (double)i - (double)N - 9.0;
		pt[i].set(pt[N + 8].x - radius * cos(PI / 10 + h * angle), 0, pt[N + 8].z + radius * sin(PI / 10 + h * angle));

	}

	numFaces = 200;
	face = new Face[numFaces];
	int color = 0;
	i = 0;
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 2;
	face[0].vert[3].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 4;
	face[1].vert[1].vertIndex = 1;
	face[1].vert[2].vertIndex = 0;
	face[1].vert[3].vertIndex = 7;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[1].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 6;
	face[2].vert[1].vertIndex = 5;
	face[2].vert[2].vertIndex = 4;
	face[2].vert[3].vertIndex = 7;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 5;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 3;
	face[3].vert[3].vertIndex = 2;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 1;
	face[4].vert[1].vertIndex = 4;
	face[4].vert[2].vertIndex = 5;
	face[4].vert[3].vertIndex = 2;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 6;
	face[5].vert[1].vertIndex = 7;
	face[5].vert[2].vertIndex = 0;
	face[5].vert[3].vertIndex = 3;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 5;
	face[6].vert[1].vertIndex = 6;
	face[6].vert[2].vertIndex = N + 9;
	face[6].vert[3].vertIndex = 9;
	for (i = 0; i < face[6].nVerts; i++)
		face[6].vert[i].colorIndex = 6;

	face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 2 * N + 7;
	face[7].vert[1].vertIndex = 3;
	face[7].vert[2].vertIndex = 2;
	face[7].vert[3].vertIndex = N + 7;
	for (i = 0; i < face[7].nVerts; i++)
		face[7].vert[i].colorIndex = 7;

	face[8].nVerts = 3;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 5;
	face[8].vert[1].vertIndex = 8;
	face[8].vert[2].vertIndex = 2;
	for (i = 0; i < face[8].nVerts; i++)
		face[8].vert[i].colorIndex = 8;

	face[9].nVerts = 3;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 5;
	face[9].vert[1].vertIndex = 8;
	face[9].vert[2].vertIndex = 9;
	for (i = 0; i < face[9].nVerts; i++)
		face[9].vert[i].colorIndex = 9;

	face[10].nVerts = 3;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 8;
	face[10].vert[1].vertIndex = N + 7;
	face[10].vert[2].vertIndex = 2;
	for (i = 0; i < face[10].nVerts; i++)
		face[10].vert[i].colorIndex = 10;

	face[11].nVerts = 3;
	face[11].vert = new VertexID[face[9].nVerts];
	face[11].vert[0].vertIndex = N + 8;
	face[11].vert[1].vertIndex = N + 9;
	face[11].vert[2].vertIndex = 6;
	for (i = 0; i < face[11].nVerts; i++)
		face[11].vert[i].colorIndex = 11;

	face[12].nVerts = 3;
	face[12].vert = new VertexID[face[10].nVerts];
	face[12].vert[0].vertIndex = N + 8;
	face[12].vert[1].vertIndex = 6;
	face[12].vert[2].vertIndex = 3;
	for (i = 0; i < face[12].nVerts; i++)
		face[12].vert[i].colorIndex = 12;

	face[13].nVerts = 3;
	face[13].vert = new VertexID[face[10].nVerts];
	face[13].vert[0].vertIndex = N + 8;
	face[13].vert[1].vertIndex = 3;
	face[13].vert[2].vertIndex = 2 * N + 7;
	for (i = 0; i < face[13].nVerts; i++)
		face[13].vert[i].colorIndex = 13;

	//cac mat hinh chu nhat ngoai
	color = 14;
	i = 14;

	for (int j = 9; j < N + 7; j++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = j + N + 1;
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j;
		face[i].vert[3].vertIndex = j + N;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}


	for (int j = 9; j < N + 7; j++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = 8;//tam
		face[i].vert[1].vertIndex = j;
		face[i].vert[2].vertIndex = j + 1;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}

	for (int j = N + 9; j < 2 * N + 7; j++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = N + 8;//tam
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}

}
void Mesh::CreateShape4() {
	int N = 36;
	GLfloat angle = PI / ((double)N - 2.0);
	int i = 0;
	numVerts = 2 * N + 6;
	pt = new Point3[numVerts];
	float x = 3.0 / 1.75;
	float y = 3.0 / 12;
	float z = 4.3 / 2;
	float radius = 1.25 / 4;
	pt[0].set(0, 0, 0);
	pt[1].set(0, y, 0);
	pt[2].set(x, y, 0);
	pt[3].set(x, 0, 0);
	pt[4].set(x, y, z * 0.9);
	pt[5].set(x, 0, z * 0.9);


	double angle2 = PI / 8;
	pt[6].set(x * 0.9, y, z * 1.25);
	for (i = 7; i < N + 6; i++) // [6,N+5]
	{

		double h = (double)i - 7.0;
		pt[i].set(pt[6].x - radius * cos(h * angle + angle2), y, pt[6].z + radius * sin(h * angle + angle2));

	}
	pt[N + 6].set(pt[6].x, 0, pt[6].z);
	for (i = N + 7; i < 2 * N + 6; i++) //[N+6,2*N+5]
	{
		double h = (double)i - (double)N - 7.0;
		pt[i].set(pt[N + 6].x - radius * cos(h * angle + angle2), 0, pt[N + 6].z + radius * sin(h * angle + angle2));
	}

	numFaces = 200;
	face = new Face[numFaces];
	int color = 0;

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 2;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 0;
	face[0].vert[3].vertIndex = 3;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 5;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 2;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[1].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 4;
	face[2].vert[1].vertIndex = 5;
	face[2].vert[2].vertIndex = N + 7;
	face[2].vert[3].vertIndex = 7;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 1;
	face[3].vert[2].vertIndex = 0;
	face[3].vert[3].vertIndex = N + 7;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 2;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 7;
	for (i = 0; i < face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 0;
	face[5].vert[1].vertIndex = 3;
	face[5].vert[2].vertIndex = 5;
	face[5].vert[3].vertIndex = N + 7;
	for (i = 0; i < face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 4;
	face[6].vert[1].vertIndex = N + 5;
	face[6].vert[2].vertIndex = 2 * N + 5;
	face[6].vert[3].vertIndex = 5;
	for (i = 0; i < face[6].nVerts; i++)
		face[6].vert[i].colorIndex = 6;

	face[7].nVerts = 3;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 4;
	face[7].vert[1].vertIndex = 7;
	face[7].vert[2].vertIndex = 6;
	for (i = 0; i < face[7].nVerts; i++)
		face[7].vert[i].colorIndex = 7;

	face[8].nVerts = 3;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 4;
	face[8].vert[1].vertIndex = 6;
	face[8].vert[2].vertIndex = N + 5;
	for (i = 0; i < face[8].nVerts; i++)
		face[8].vert[i].colorIndex = 8;


	color = 9;
	i = 9;
	for (int j = 7; j < N + 5; j++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = j + N + 1;
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j;
		face[i].vert[3].vertIndex = j + N;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}

	for (int j = 7; j < N + 5; j++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = 6;//tam
		face[i].vert[1].vertIndex = j;
		face[i].vert[2].vertIndex = j + 1;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}

	for (int j = N + 7; j < 2 * N + 5; j++) {
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = N + 6;//tam
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}

	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 5;//tam
	face[i].vert[1].vertIndex = N + 6;
	face[i].vert[2].vertIndex = N + 7;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	face[i].nVerts = 3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = N + 6;//tam
	face[i].vert[1].vertIndex = 5;
	face[i].vert[2].vertIndex = 2 * N + 5;
	for (int k = 0; k < face[i].nVerts; k++) {
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;


}

void Mesh::CreateShape5() {
	int N = 36;
	GLdouble angle = PI / (((double)N - 2.0));
	int i = 0;
	numVerts = 4 * N;
	pt = new Point3[numVerts];
	float x = 6.0 / 4 - 0.1;
	float y = 3.0 / 12;
	float z = 3.0 / 4;
	float radius = 1.25 / 4;
	pt[0].set(0, y, 0);
	for (i = 1; i < N; i++) // [0,N - 1]
	{
		double h = (double)i - 1.0;
		pt[i].set(-radius * sin(h * angle), y, radius * cos(h * angle));

	}
	pt[N].set(pt[0].x, 0, pt[0].z);
	for (i = N + 1; i < 2 * N; i++) //[N,2N-1]
	{
		double h = (double)i - (double)N - 1.0;
		pt[i].set(-radius * sin(h * angle), 0, radius * cos(h * angle));
	}

	pt[2 * N].set(pt[0].x + x, y, 0);
	for (i = 2 * N + 1; i < 3 * N; i++) //[2N,3N-1]
	{
		double h = (double)i - 2.0 * N - 1.0;
		pt[i].set(x + radius * sin(h * angle), y, radius * cos(h * angle));
	}

	pt[3 * N].set(pt[0].x + x, 0, 0);
	for (i = 3 * N + 1; i < 4 * N; i++) //[3N,4N-1]
	{
		double h = (double)i - 3.0 * N - 1.0;
		pt[i].set(x + radius * sin(h * angle), 0, radius * cos(h * angle));
	}

	numFaces = 300;
	face = new Face[numFaces];
	int color = 0;

	i = 0;
	for (int j = 1; j < N - 1; j++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = j;
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j + N + 1;
		face[i].vert[3].vertIndex = j + N;
		for (int k = 0; k < face[i].nVerts; k++) {
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}

	for (int j = 2 * N + 1; j < 3 * N - 1; j++)
	{
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = j + N + 1;
		face[i].vert[1].vertIndex = j + 1;
		face[i].vert[2].vertIndex = j;
		face[i].vert[3].vertIndex = j + N;
		for (int k = 0; k < face[i].nVerts; k++)
		{
			face[i].vert[k].colorIndex = color;
		}
		color++;
		i++;
	}

	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 1;
	face[i].vert[1].vertIndex = N + 1;
	face[i].vert[2].vertIndex = 3 * N + 1;
	face[i].vert[3].vertIndex = 2 * N + 1;
	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = color;
	}

	color++;
	i++;

	face[i].nVerts = 4;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex = 4 * N - 1;
	face[i].vert[1].vertIndex = 2 * N - 1;
	face[i].vert[2].vertIndex = N - 1;
	face[i].vert[3].vertIndex = 3 * N - 1;
	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;

	int diem = 0;
	face[i].nVerts = 2 * N - 2;
	face[i].vert = new VertexID[face[i].nVerts];
	for (int j = 0; j < 2 * N - 2; j++) {

		if (j < N - 1)
			face[i].vert[j].vertIndex = N + 1 + j;
		else {
			face[i].vert[j].vertIndex = 4 * N - 1 - diem;
			diem++;
		}
	}
	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = color;
	}
	color++;
	i++;
	diem = 0;
	face[i].nVerts = 2 * N - 2;
	face[i].vert = new VertexID[face[i].nVerts];
	for (int j = 0; j < 2 * N - 2; j++) {

		if (j < N - 1)
			face[i].vert[j].vertIndex = N - 1 - j;
		else {
			face[i].vert[j].vertIndex = 2 * N + 1 + diem;
			diem++;
		}
	}
	for (int k = 0; k < face[i].nVerts; k++)
	{
		face[i].vert[k].colorIndex = color;
	}
}

void Mesh::create_truc_quay() {
	int i;

	numVerts = 16;
	pt = new Point3[numVerts];

	pt[0].set(-0.5 * 0.1, 1.5 * 0.1, 3 * 0.1);
	pt[1].set(0.5 * 0.1, 1.5 * 0.1, 3 * 0.1);
	pt[2].set(1.5 * 0.1, 0.5 * 0.1, 3 * 0.1);
	pt[3].set(1.5 * 0.1, -0.5 * 0.1, 3 * 0.1);
	pt[4].set(0.5 * 0.1, -1.5 * 0.1, 3 * 0.1);
	pt[5].set(-0.5 * 0.1, -1.5 * 0.1, 3 * 0.1);
	pt[6].set(-1.5 * 0.1, -0.5 * 0.1, 3 * 0.1);
	pt[7].set(-1.5 * 0.1, 0.5 * 0.1, 3 * 0.1);

	pt[8].set(-0.5 * 0.1, 1.5 * 0.1, -3 * 0.1);
	pt[9].set(0.5 * 0.1, 1.5 * 0.1, -3 * 0.1);
	pt[10].set(1.5 * 0.1, 0.5 * 0.1, -3 * 0.1);
	pt[11].set(1.5 * 0.1, -0.5 * 0.1, -3 * 0.1);
	pt[12].set(0.5 * 0.1, -1.5 * 0.1, -3 * 0.1);
	pt[13].set(-0.5 * 0.1, -1.5 * 0.1, -3 * 0.1);
	pt[14].set(-1.5 * 0.1, -0.5 * 0.1, -3 * 0.1);
	pt[15].set(-1.5 * 0.1, 0.5 * 0.1, -3 * 0.1);


	numFaces = 10;
	face = new Face[numFaces];

	face[0].nVerts = 8;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 2;
	face[0].vert[3].vertIndex = 3;
	face[0].vert[4].vertIndex = 4;
	face[0].vert[5].vertIndex = 5;
	face[0].vert[6].vertIndex = 6;
	face[0].vert[7].vertIndex = 7;
	/*for (int i = 0; i < face[0].nVerts; i++) {
		face[0].vert[i].colorIndex = 0;
	}*/

	face[1].nVerts = 8;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 8;
	face[1].vert[1].vertIndex = 9;
	face[1].vert[2].vertIndex = 10;
	face[1].vert[3].vertIndex = 11;
	face[1].vert[4].vertIndex = 12;
	face[1].vert[5].vertIndex = 13;
	face[1].vert[6].vertIndex = 14;
	face[1].vert[7].vertIndex = 15;

	for (int i = 2; i < 9; i++) {
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = i - 2;
		face[i].vert[1].vertIndex = i - 1;
		face[i].vert[2].vertIndex = i + 7;
		face[i].vert[3].vertIndex = i + 6;
	}

	face[9].nVerts = 4;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 7;
	face[9].vert[1].vertIndex = 0;
	face[9].vert[2].vertIndex = 15;
	face[9].vert[3].vertIndex = 8;

}
void Mesh::create_goi_do(float fHeight, float fRadius) {
	int i;
	int nSegment = 36;
	int idx;
	float fAngle = 2 * PI / nSegment;
	float x, y, z;
	float fEdge = fRadius + 0.2;

	numVerts = nSegment * 4 + 2;
	pt = new Point3[numVerts];

	pt[0].set(0, 0, fHeight / 2);
	for (i = 0; i < nSegment; i++) {
		x = fRadius * cos(fAngle * (double)i);
		y = fRadius * sin(fAngle * (double)i);
		z = fHeight / 2;
		pt[i + 1].set(x, y, z);

		z = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	
	//73-75
	for (i = 0; i < 3; i++) {
		int j = i % 3;
		x = fEdge;
		y = fEdge / 6 * i;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	pt[nSegment * 2 + 1 + 3].set(fEdge, fEdge / 2, fHeight / 2);//76
	pt[nSegment * 3 + 1 + 3].set(fEdge, fEdge / 2, -fHeight / 2);

	pt[nSegment * 2 + 1 + 4].set(fEdge * 5 / 6, fEdge * 4 / 6, fHeight / 2);//77
	pt[nSegment * 3 + 1 + 4].set(fEdge * 5 / 6, fEdge * 4 / 6, -fHeight / 2);

	pt[nSegment * 2 + 1 + 5].set(fEdge * 4 / 6, fEdge * 5 / 6, fHeight / 2);//78
	pt[nSegment * 3 + 1 + 5].set(fEdge * 4 / 6, fEdge * 5 / 6, -fHeight / 2);

	//79-81
	for (i = 6; i < 9; i++) {
		int j = i % 3;
		x = fEdge / 2 - fEdge * j / 6;
		y = fEdge;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	//82-84
	for (i = 9; i < 12; i++) {
		int j = i % 3;
		x = 0 - fEdge * j / 6;
		y = fEdge;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	//85-87
	for (i = 12; i < 15; i++) {
		int j = i % 3;
		x = -fEdge / 2 - fEdge * j / 6;
		y = fEdge - fEdge * j / 6;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	//88-90
	for (i = 15; i < 18; i++) {
		int j = i % 3;
		x = -fEdge;
		y = fEdge / 2 - fEdge * j / 6;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	//91 - 93
	for (i = 18; i < 21; i++) {
		int j = i % 3;
		x = -fEdge;
		y = 0 - fEdge * j / 6;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	//94 - 96
	for (i = 21; i < 24; i++) {
		int j = i % 3;
		x = -fEdge + fEdge * j / 6;
		y = -fEdge / 2 - fEdge * j / 6;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	//97-99
	for (i = 24; i < 27; i++) {
		int j = i % 3;
		x = -fEdge / 2 + fEdge * j / 6;
		y = -fEdge;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	//100-102
	for (int i = 27; i < 30; i++) {
		int j = i % 3;
		x = 0 + fEdge * j / 6;
		y = -fEdge;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	//103-105
	for (int i = 30; i < 33; i++) {
		int j = i % 3;
		x = fEdge / 2 + fEdge * j / 6;
		y = -fEdge + fEdge * j / 6;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	//106-108
	for (int i = 33; i < 36; i++) {
		int j = i % 3;
		x = fEdge;
		y = -fEdge / 2 + fEdge * j / 6;
		z = fHeight / 2;
		pt[nSegment * 2 + 1 + i].set(x, y, z);

		z = -fHeight / 2;
		pt[nSegment * 3 + 1 + i].set(x, y, z);
	}

	pt[numVerts - 1].set(0, 0, -fHeight / 2);

	numFaces = nSegment * 4;
	face = new Face[numFaces];

	idx = 0;
	//mat tren
	for (int i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 1 + i;
		
		if (i < nSegment - 1)
			face[idx].vert[3].vertIndex = i + 2;
		else
			face[idx].vert[3].vertIndex = 1;

		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 2 * nSegment;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + 2 * nSegment;
		
		idx++;
	}
	//mat ngoai
	for (int i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 1 + 2 * nSegment;

		if (i < nSegment - 1)
			face[idx].vert[3].vertIndex = i + 2 + 2 * nSegment;
		else
			face[idx].vert[3].vertIndex = 1 + 2 * nSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment;
		idx++;
	}
	//mat duoi
	for (int i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1 + nSegment;

		if (i < nSegment - 1)
			face[idx].vert[3].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[3].vertIndex = 1 + nSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 2 * nSegment;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + 2 * nSegment;

		idx++;
	}
	//mat trong
	for (int i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 1;

		if (i < nSegment - 1)
			face[idx].vert[3].vertIndex = i + 2;
		else
			face[idx].vert[3].vertIndex = 1;

		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment;
		idx++;
	}
}
void Mesh::create_thanh_lien_ket(float fLength, float fHeight, float fBig_radius, float fSmall_radius) {
	int nSegment = 36;
	numVerts = nSegment * 6 + 8;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	//Phan tren ben tren
	pt[0].set(0, fLength / 2, fHeight / 2);
	//1-36 mat tren 37 - 72
	for (i = 0; i < nSegment; i++) {
		x = fSmall_radius * cos(fAngle * (double)i);
		y = fLength / 2 + fSmall_radius * sin(fAngle * (double)i);
		z = fHeight / 2;

		pt[i + 1].set(x, y, z);

		z = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	//73-108 mat tren 109-144 mat duoi
	for (i = 0; i < nSegment; i++) {
		x = fSmall_radius * cos(fAngle * (double)i);
		y = -fLength / 2 - fSmall_radius * sin(fAngle * (double)i);
		z = fHeight / 2;

		pt[i + 1 + nSegment * 2].set(x, y, z);

		z = -fHeight / 2;
		pt[i + 1 + nSegment * 3].set(x, y, z);
	}
	//145-163 mat tren 164 - 182 mat duoi
	for (i = 0; i <= nSegment / 2; i++) {
		x = fBig_radius * cos(fAngle * (double)i);
		y = fLength / 2 + fBig_radius * sin(fAngle * (double)i);
		z = fHeight / 2;

		pt[i + 1 + nSegment * 4].set(x, y, z);

		z = -fHeight / 2;
		pt[i + 1 + nSegment * 4 + 19].set(x, y, z);
	}
	//183-201 mat tren 202 - 220 mat duoi
	for (i = 0; i <= nSegment / 2; i++) {
		x = fBig_radius * cos(fAngle * (double)i);
		y = -fLength / 2 - fBig_radius * sin(fAngle * (double)i);
		z = fHeight / 2;

		pt[i + 1 + nSegment * 4 + 38].set(x, y, z);

		z = -fHeight / 2;
		pt[i + 1 + nSegment * 4 + 38 + 19].set(x, y, z);
	}
	//phan tren ben duoi
	pt[221].set(0, -fLength / 2, fHeight / 2);
	//phan duoi ben tren
	pt[222].set(0, fLength / 2, -fHeight / 2);
	//phan duoi ben duoi
	pt[223].set(0, -fLength / 2, -fHeight / 2);

	numFaces = nSegment * 6 + 6;
	face = new Face[numFaces];
	idx = 0;

	//ve mat hinh tron nho tren
	for (int i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i < nSegment - 1)
			face[idx].vert[3].vertIndex = i + 2;
		else
			face[idx].vert[3].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	//ve mat hinh tron nho duoi
	for (int i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1 + nSegment * 2;
		if (i < nSegment - 1)
			face[idx].vert[3].vertIndex = i + 2 + nSegment * 2;
		else
			face[idx].vert[3].vertIndex = 1 + nSegment * 2;
		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	//ve vong cung tren dang truoc
	for (int i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		face[idx].vert[3].vertIndex = i + 2;
		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment * 4;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment * 4;
		idx++;
	}
	//ve vong cung tren dang sau
	for (int i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1 + nSegment;
		face[idx].vert[3].vertIndex = i + 2 + nSegment;
		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment * 3 + 19;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment * 3 + 19;
		idx++;
	}
	//ve mat ngoai vong cung tren
	for (int i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1 + nSegment * 4;
		face[idx].vert[3].vertIndex = i + 2 + nSegment * 4;
		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 19;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + 19;
		idx++;
	}

	//ve vong cung duoi dang truoc
	for (int i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1 + nSegment * 2;
		face[idx].vert[3].vertIndex = i + 2 + nSegment * 2;
		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment * 2 + 38;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment * 2 + 38;
		idx++;
	}

	//ve vong cung duoi dang sau
	for (int i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1 + nSegment * 3;
		face[idx].vert[3].vertIndex = i + 2 + nSegment * 3;
		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment + 19 * 3;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment + 19 * 3;
		idx++;
	}
	//ve mat ngoai vong cung duoi
	for (int i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1 + nSegment * 4 + 19 * 2;
		face[idx].vert[3].vertIndex = i + 2 + nSegment * 4 + 19 * 2;
		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + 19;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + 19;
		idx++;
	}
	//ve mat noi hai hinh tron nho bên ngoai
	for (int i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 19;
		if (i < nSegment / 2 - 1)
			face[idx].vert[3].vertIndex = i + 20;
		else
			face[idx].vert[3].vertIndex = 1;

		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment * 2;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment * 2;
		idx++;
	}
	//ve mat noi hai hinh tron nho ben trong
	for (int i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 19 + nSegment;
		if (i < nSegment / 2 - 1)
			face[idx].vert[3].vertIndex = i + 20 + nSegment;
		else
			face[idx].vert[3].vertIndex = 1 + nSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[3].vertIndex + nSegment * 2;
		face[idx].vert[1].vertIndex = face[idx].vert[0].vertIndex + nSegment * 2;
		idx++;
	}
	//hcn ngoai ben trai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];

	face[idx].vert[0].vertIndex = 19;
	face[idx].vert[1].vertIndex = 91;
	face[idx].vert[2].vertIndex = 201;
	face[idx].vert[3].vertIndex = 163;
	idx++;

	//hcn ngoai ben phai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];

	face[idx].vert[0].vertIndex = 1;
	face[idx].vert[1].vertIndex = 145;
	face[idx].vert[2].vertIndex = 183;
	face[idx].vert[3].vertIndex = 73;
	idx++;

	//hcn trong ben trai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];

	face[idx].vert[0].vertIndex = 19 + nSegment;
	face[idx].vert[1].vertIndex = 91 + nSegment;
	face[idx].vert[2].vertIndex = 201 + 19;
	face[idx].vert[3].vertIndex = 163 + 19;
	idx++;

	//hcm trong ben phai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];

	face[idx].vert[0].vertIndex = 1 + nSegment;
	face[idx].vert[1].vertIndex = 145 + 19;
	face[idx].vert[2].vertIndex = 183 + 19;
	face[idx].vert[3].vertIndex = 73 + nSegment;
	idx++;
	
	//hcn canh trai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];

	face[idx].vert[0].vertIndex = 163;
	face[idx].vert[1].vertIndex = 201;
	face[idx].vert[2].vertIndex = 201 + 19;
	face[idx].vert[3].vertIndex = 163 + 19;
	idx++;

	//hcn canh phai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];

	face[idx].vert[0].vertIndex = 145;
	face[idx].vert[1].vertIndex = 183;
	face[idx].vert[2].vertIndex = 183 + 19;
	face[idx].vert[3].vertIndex = 145 + 19;
	idx++;
}
void Mesh::create_canh_quat(float fHeight) {
	int i;
	int nSegment = 36;
	int idx;
	float fAngle = 2 * PI / nSegment;
	float x, y, z;
	float k = 0.7;
	float fRadius = 0.4 * k;
	
	numVerts = 12 + 17 * 2;
	
	pt = new Point3[numVerts];

	pt[0].set(0, 0, fHeight / 2);
	pt[1].set(sqrt(3) / 2 * k, 0.5 * k, fHeight / 2);
	pt[2].set(-sqrt(3) / 2 * k, 0.5 * k, fHeight / 2);
	pt[3].set(0.4 * k, 3.6 * k, fHeight / 2);
	pt[4].set(-0.4 * k, 3.6 * k, fHeight / 2);
	pt[5].set(0, 3.6 * k, fHeight / 2);
	pt[6].set(sqrt(3) / 2 * k, 0.5 * k, -fHeight / 2);
	pt[7].set(-sqrt(3) / 2 * k, 0.5 * k, -fHeight / 2);
	pt[8].set(0.4 * k, 3.6 * k, -fHeight / 2);
	pt[9].set(-0.4 * k, 3.6 * k, -fHeight / 2);
	pt[10].set(0, 3.6 * k, -fHeight / 2);
	pt[numVerts - 1].set(0, 0, -fHeight / 2);

	idx = 10;
	for (i = 1; i < nSegment / 2; i++)
	{
		x = fRadius * cos(fAngle * (double)i);
		y = 3.6 * k + fRadius * sin(fAngle * (double)i);
		z = fHeight / 2;
		pt[i + idx].set(x, y, z);

		z = -fHeight / 2;
		pt[i + idx + nSegment / 2 - 1].set(x, y, z);
	}

	numFaces = 3 * nSegment + 6;

	face = new Face[numFaces];

	//mat 1
	idx = 0;
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 1;
	face[idx].vert[2].vertIndex = 3;
	face[idx].vert[3].vertIndex = 5;
	idx++;

	//mat 2
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 5;
	face[idx].vert[2].vertIndex = 4;
	face[idx].vert[3].vertIndex = 2;
	idx++;

	//mat tron tren ben ngoai
	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 5;
	face[idx].vert[1].vertIndex = 3;
	face[idx].vert[2].vertIndex = 11;
	idx++;

	for (i = 0; i < nSegment / 2 - 2; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 5;
			face[idx].vert[2].vertIndex = i + 12;
		face[idx].vert[1].vertIndex = i + 11;
		//printf("%d%d%d\n", face[idx].vert[0].vertIndex, face[idx].vert[1].vertIndex, face[idx].vert[2].vertIndex);
		idx++;
	}

	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 5;
	face[idx].vert[1].vertIndex = 27;
	face[idx].vert[2].vertIndex = 4;
	idx++;

	//mat duoi 1
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numVerts - 1;
	face[idx].vert[1].vertIndex = 1 + 5;
	face[idx].vert[2].vertIndex = 3 + 5;
	face[idx].vert[3].vertIndex = 5 + 5;
	idx++;

	//mat duoi 2
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = numVerts - 1;
	face[idx].vert[1].vertIndex = 5 + 5;
	face[idx].vert[2].vertIndex = 4 + 5;
	face[idx].vert[3].vertIndex = 2 + 5;
	idx++;

	//mat trong ben duoi
	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 10;
	face[idx].vert[1].vertIndex = 3 + 5;
	face[idx].vert[2].vertIndex = 11 + 17;
	idx++;

	for (i = 0; i < nSegment / 2 - 2; i++) {
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 5 + 5;
		face[idx].vert[2].vertIndex = i + 12 + 17;
		face[idx].vert[1].vertIndex = i + 11 + 17;
		//printf("%d%d%d\n", face[idx].vert[0].vertIndex, face[idx].vert[1].vertIndex, face[idx].vert[2].vertIndex);
		idx++;
	}

	face[idx].nVerts = 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 10;
	face[idx].vert[1].vertIndex = 27 + 17;
	face[idx].vert[2].vertIndex = 4 + 5;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 1;
	face[idx].vert[1].vertIndex = 3;
	face[idx].vert[2].vertIndex = 3 + 5;
	face[idx].vert[3].vertIndex = 1 + 5;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 2;
	face[idx].vert[1].vertIndex = 4;
	face[idx].vert[2].vertIndex = 4 + 5;
	face[idx].vert[3].vertIndex = 2 + 5;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3;
	face[idx].vert[1].vertIndex = 11;
	face[idx].vert[2].vertIndex = 11 + 17;
	face[idx].vert[3].vertIndex = 3 + 5;
	idx++;

	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 27;
	face[idx].vert[1].vertIndex = 4;
	face[idx].vert[2].vertIndex = 4 + 5;
	face[idx].vert[3].vertIndex = 27 + 17;
	idx++;

	for (i = 0; i < nSegment / 2 - 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 11;
		face[idx].vert[1].vertIndex = i + 12;
		face[idx].vert[2].vertIndex = i + 12 + 17;
		face[idx].vert[3].vertIndex = i + 11 + 17;
		//printf("%d%d%d\n", face[idx].vert[0].vertIndex, face[idx].vert[1].vertIndex, face[idx].vert[2].vertIndex);
		idx++;
	}
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int	iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			face[f].vert[v].colorIndex = colorIdx;
			int		ic = face[f].vert[v].colorIndex;

			ic = ic % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawSmooth()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glNormal3f(face[f].norm.x, face[f].norm.y, face[f].norm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
void Mesh::CalculateNorms()
{
	float	mx, my, mz;
	int		idx, next;


	for (int f = 0; f < numFaces; f++)
	{
		mx = 0;
		my = 0;
		mz = 0;
		for (int v = 0; v < face[f].nVerts; v++)
		{
			idx = v;
			next = (idx + 1) % face[f].nVerts;

			int		p1 = face[f].vert[idx].vertIndex;
			int		p2 = face[f].vert[next].vertIndex;

			mx = mx + (pt[p1].y - pt[p2].y) * (pt[p1].z + pt[p2].z);
			my = my + (pt[p1].z - pt[p2].z) * (pt[p1].x + pt[p2].x);
			mz = mz + (pt[p1].x - pt[p2].x) * (pt[p1].y + pt[p2].y);

		}
		face[f].norm.set(mx, my, mz);
		face[f].norm.normalize();
	}
}

void Mesh::setupMaterial(float ambient[], float diffuse[], float specular[], float shininess)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x * b.x + y * b.y + z * b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(double(x) * double(x) + double(y) * double(y) + double(z) * double(z));
	x = x / temp;
	y = y / temp;
	z = z / temp;
}



float camera_angle;
float camera_height;
float camera_distance;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool b2Dlook = false;
bool bWireFrame = false;
bool bLight1 = true;

float ANG3 = 8;
float ANG = 0;
float ANG1 = -10;

int		screenWidth = 1200;
int		screenHeight = 1200;

Mesh	tetrahedron;
Mesh	cube;
Mesh	cylinder;
Mesh	cuboid;
Mesh	Shape1;
Mesh	Shape2;
Mesh	Shape3;
Mesh	Shape4;
Mesh	Shape5;
Mesh	trucquay;
Mesh	trucquay_1;
Mesh	goi_do;
Mesh	thanh_lien_ket;
Mesh	canh_quat;
Mesh	canh_quat_1;
Mesh	canh_quat_2;
Mesh	canh_quat_g;
Mesh	canh_quat_g_1;
Mesh	canh_quat_g_2;
void drawAll();


void drawFigure() {
	float x = 0.0, z = 0.0;
	glDisable(GL_LIGHTING);
	for (x = -108.0; x < 108.0; x += 12)
	{
		for (z = -132.0; z < 132.0; z += 12)
		{
			//Figure 1
			glColor3f(0.5, 0.5, 0.5);
			glBegin(GL_POLYGON);
			glVertex3f(0 + x, 0, 0 + z);
			glVertex3f(-1.86 + x, 0, 0.62 + z);
			glVertex3f(-1.64 + x, 0, 1.64 + z);//a2
			glVertex3f(-0.62 + x, 0, 1.86 + z);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(-4 + x, 0, 0 + z);//H
			glVertex3f(-2 + x, 0, 0 + z);//I
			glVertex3f(-1.86 + x, 0, 0.62 + z);//a3
			glVertex3f(-3.6 + x, 0, 1.2 + z);//a5
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(-0.62 + x, 0, 1.86 + z);//a4
			glVertex3f(-1.2 + x, 0, 3.6 + z);//a1
			glVertex3f(0 + x, 0, 4 + z);//D
			glVertex3f(0 + x, 0, 2 + z);//K	
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(-3 + x, 0, 3 + z);//C
			glVertex3f(-1.2 + x, 0, 3.6 + z);//a1
			glVertex3f(-2 + x, 0, 6 + z);//A
			glVertex3f(-4 + x, 0, 6 + z);//G
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(-3 + x, 0, 3 + z);//C
			glVertex3f(-6 + x, 0, 4 + z);//E
			glVertex3f(-6 + x, 0, 2 + z);//F
			glVertex3f(-3.6 + x, 0, 1.2 + z);//a5
			glEnd();

			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex3f(-2 + x, 0, 6 + z); glVertex3f(0 + x, 0, 0 + z);//AB
			glVertex3f(-3 + x, 0, 3 + z); glVertex3f(0 + x, 0, 4 + z);//CD
			glVertex3f(-4 + x, 0, 0 + z); glVertex3f(-3 + x, 0, 3 + z);//CH
			glVertex3f(0 + x, 0, 0 + z); glVertex3f(-6 + x, 0, 2 + z);//BF
			glVertex3f(-3 + x, 0, 3 + z); glVertex3f(-6 + x, 0, 4 + z);//CE
			glVertex3f(-3 + x, 0, 3 + z); glVertex3f(-4 + x, 0, 6 + z);//CG
			glVertex3f(-1.64 + x, 0, 1.64 + z); glVertex3f(0 + x, 0, 2 + z);//a2K
			glVertex3f(-1.64 + x, 0, 1.64 + z); glVertex3f(-2 + x, 0, 0 + z);//a2I
			glEnd();

			//Figure2	
			glColor3f(0.5, 0.5, 0.5);
			glBegin(GL_POLYGON);
			glVertex3f(0 + x, 0, 0 + z);
			glVertex3f(1.86 + x, 0, -0.62 + z);
			glVertex3f(1.64 + x, 0, -1.64 + z);//a2
			glVertex3f(0.62 + x, 0, -1.86 + z);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(4 + x, 0, 0 + z);//H
			glVertex3f(2 + x, 0, 0 + z);//I
			glVertex3f(1.86 + x, 0, -0.62 + z);//a3
			glVertex3f(3.6 + x, 0, -1.2 + z);//a5
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0.62 + x, 0, -1.86 + z);//a4
			glVertex3f(1.2 + x, 0, -3.6 + z);//a1
			glVertex3f(0 + x, 0, -4 + z);//D
			glVertex3f(0 + x, 0, -2 + z);//K	
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(3 + x, 0, -3 + z);//C
			glVertex3f(1.2 + x, 0, -3.6 + z);//a1
			glVertex3f(2 + x, 0, -6 + z);//A
			glVertex3f(4 + x, 0, -6 + z);//G
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(3 + x, 0, -3 + z);//C
			glVertex3f(6 + x, 0, -4 + z);//E
			glVertex3f(6 + x, 0, -2 + z);//F
			glVertex3f(3.6 + x, 0, -1.2 + z);//a5
			glEnd();

			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex3f(2 + x, 0, -6 + z); glVertex3f(0 + x, 0, 0 + z);//AB
			glVertex3f(3 + x, 0, -3 + z); glVertex3f(0 + x, 0, -4 + z);//CD
			glVertex3f(4 + x, 0, 0 + z); glVertex3f(3 + x, 0, -3 + z);//CH
			glVertex3f(0 + x, 0, 0 + z); glVertex3f(6 + x, 0, -2 + z);//BF
			glVertex3f(3 + x, 0, -3 + z); glVertex3f(6 + x, 0, -4 + z);//CE
			glVertex3f(3 + x, 0, -3 + z); glVertex3f(4 + x, 0, -6 + z);//CG
			glVertex3f(1.64 + x, 0, -1.64 + z); glVertex3f(0 + x, 0, -2 + z);//a2K
			glVertex3f(1.64 + x, 0, -1.64 + z); glVertex3f(2 + x, 0, 0 + z);//a2I
			glEnd();

			//Figure 3
			glColor3f(0.5, 0.5, 0.5);
			glBegin(GL_POLYGON);
			glVertex3f(0 - 6 + x, 0, 0 - 6 + z);
			glVertex3f(1.86 - 6 + x, 0, 0.62 - 6 + z);
			glVertex3f(1.64 - 6 + x, 0, 1.64 - 6 + z);//a2
			glVertex3f(0.62 - 6 + x, 0, 1.86 - 6 + z);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(4 - 6 + x, 0, 0 - 6 + z);//H
			glVertex3f(2 - 6 + x, 0, 0 - 6 + z);//I
			glVertex3f(1.86 - 6 + x, 0, 0.62 - 6 + z);//a3
			glVertex3f(3.6 - 6 + x, 0, 1.2 - 6 + z);//a5
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0.62 - 6 + x, 0, 1.86 - 6 + z);//a4
			glVertex3f(1.2 - 6 + x, 0, 3.6 - 6 + z);//a1
			glVertex3f(0 - 6 + x, 0, 4 - 6 + z);//D
			glVertex3f(0 - 6 + x, 0, 2 - 6 + z);//K	
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(3 - 6 + x, 0, 3 - 6 + z);//C
			glVertex3f(1.2 - 6 + x, 0, 3.6 - 6 + z);//a1
			glVertex3f(2 - 6 + x, 0, 6 - 6 + z);//A
			glVertex3f(4 - 6 + x, 0, 6 - 6 + z);//G
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(3 - 6 + x, 0, 3 - 6 + z);//C
			glVertex3f(6 - 6 + x, 0, 4 - 6 + z);//E
			glVertex3f(6 - 6 + x, 0, 2 - 6 + z);//F
			glVertex3f(3.6 - 6 + x, 0, 1.2 - 6 + z);//a5
			glEnd();

			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex3f(2 - 6 + x, 0, 6 - 6 + z); glVertex3f(0 - 6 + x, 0, 0 - 6 + z);//AB
			glVertex3f(3 - 6 + x, 0, 3 - 6 + z); glVertex3f(0 - 6 + x, 0, 4 - 6 + z);//CD
			glVertex3f(4 - 6 + x, 0, 0 - 6 + z); glVertex3f(3 - 6 + x, 0, 3 - 6 + z);//CH
			glVertex3f(0 - 6 + x, 0, 0 - 6 + z); glVertex3f(6 - 6 + x, 0, 2 - 6 + z);//BF
			glVertex3f(3 - 6 + x, 0, 3 - 6 + z); glVertex3f(6 - 6 + x, 0, 4 - 6 + z);//CE
			glVertex3f(3 - 6 + x, 0, 3 - 6 + z); glVertex3f(4 - 6 + x, 0, 6 - 6 + z);//CG
			glVertex3f(1.64 - 6 + x, 0, 1.64 - 6 + z); glVertex3f(0 - 6 + x, 0, 2 - 6 + z);//a2K
			glVertex3f(1.64 - 6 + x, 0, 1.64 - 6 + z); glVertex3f(2 - 6 + x, 0, 0 - 6 + z);//a2I
			glEnd();

			//Figure 4
			glColor3f(0.5, 0.5, 0.5);
			glBegin(GL_POLYGON);
			glVertex3f(0 + 6 + x, 0, 0 + 6 + z);
			glVertex3f(-1.86 + 6 + x, 0, -0.62 + 6 + z);
			glVertex3f(-1.64 + 6 + x, 0, -1.64 + 6 + z);//a2
			glVertex3f(-0.62 + 6 + x, 0, -1.86 + 6 + z);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(-4 + 6 + x, 0, 0 + 6 + z);//H
			glVertex3f(-2 + 6 + x, 0, 0 + 6 + z);//I
			glVertex3f(-1.86 + 6 + x, 0, -0.62 + 6 + z);//a3
			glVertex3f(-3.6 + 6 + x, 0, -1.2 + 6 + z);//a5
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(-0.62 + 6 + x, 0, -1.86 + 6 + z);//a4
			glVertex3f(-1.2 + 6 + x, 0, -3.6 + 6 + z);//a1
			glVertex3f(0 + 6 + x, 0, -4 + 6 + z);//D
			glVertex3f(0 + 6 + x, 0, -2 + 6 + z);//K	
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(-3 + 6 + x, 0, -3 + 6 + z);//C
			glVertex3f(-1.2 + 6 + x, 0, -3.6 + 6 + z);//a1
			glVertex3f(-2 + 6 + x, 0, -6 + 6 + z);//A
			glVertex3f(-4 + 6 + x, 0, -6 + 6 + z);//G
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(-3 + 6 + x, 0, -3 + 6 + z);//C
			glVertex3f(-6 + 6 + x, 0, -4 + 6 + z);//E
			glVertex3f(-6 + 6 + x, 0, -2 + 6 + z);//F
			glVertex3f(-3.6 + 6 + x, 0, -1.2 + 6 + z);//a5
			glEnd();

			glColor3f(0, 0, 0);
			glBegin(GL_LINES);
			glVertex3f(-2 + 6 + x, 0, -6 + 6 + z); glVertex3f(0 + 6 + x, 0, 0 + 6 + z);//AB
			glVertex3f(-3 + 6 + x, 0, -3 + 6 + z); glVertex3f(0 + 6 + x, 0, -4 + 6 + z);//CD
			glVertex3f(-4 + 6 + x, 0, 0 + 6 + z); glVertex3f(-3 + 6 + x, 0, -3 + 6 + z);//CH
			glVertex3f(0 + 6 + x, 0, 0 + 6 + z); glVertex3f(-6 + 6 + x, 0, -2 + 6 + z);//BF
			glVertex3f(-3 + 6 + x, 0, -3 + 6 + z); glVertex3f(-6 + 6 + x, 0, -4 + 6 + z);//CE
			glVertex3f(-3 + 6 + x, 0, -3 + 6 + z); glVertex3f(-4 + 6 + x, 0, -6 + 6 + z);//CG
			glVertex3f(-1.64 + 6 + x, 0, -1.64 + 6 + z); glVertex3f(0 + 6 + x, 0, -2 + 6 + z);//a2K
			glVertex3f(-1.64 + 6 + x, 0, -1.64 + 6 + z); glVertex3f(-2 + 6 + x, 0, 0 + 6 + z);//a2I
			glEnd();
		}
	}
	glEnable(GL_LIGHTING);

}

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
}

void myDisplay() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	if (!b2Dlook) {
		float fsize = 2.0 / 6.8;
		const float ar = (float)screenWidth / (float)screenHeight;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-ar, ar, -1.0 + fsize, 1.0 + fsize, 1.5, 1000.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		camera_X = camera_distance * sinf(camera_angle * PI / 180);
		camera_Y = camera_height;
		camera_Z = camera_distance * cosf(camera_angle * PI / 180);


		if (camera_distance == 0)
		{
			gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sinf(camera_angle * PI / 180), 0, cosf(camera_angle * PI / 180));
		}
		else
		{
			gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
		}
	}
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-20.0 / 2, 20.0 / 2, -20.0 / 2 + 5.0, 20.0 / 2 + 5.0, -1000.0, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	GLfloat light_position0[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	if (bLight1 == true)
	{
		glEnable(GL_LIGHT1);
		GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat position1[] = { -10.0, 10.0, -10.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	}
	else
		glDisable(GL_LIGHT1);

	glViewport(0, 0, screenWidth, screenHeight);

	drawAll();
	//drawFigure();


	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//drawFigure();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glPushMatrix();
	glScalef(1, -1, 1);
	drawAll();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	glPushMatrix();
	glScalef(1, -1, 1);
	//drawAll();
	//drawFigure();
	glPopMatrix();

	glFlush();

	glutSwapBuffers();
}

void key(int key, int x, int y) {

	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.5;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.5;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 5;
		break;
	case GLUT_KEY_LEFT:
		camera_angle -= 5;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void movement(unsigned char key, int x, int y) {
	if (key == '1') {
		if (ANG <= 16) {
			ANG += 1;
			ANG1 -= 1.5;
			ANG3 += 15.0 / 22;
		}

	}
	else if (key == '2') {
		if (ANG >= 1) {
			ANG -= 1;
			ANG1 += 1.5;
			ANG3 -= 15.0 / 22;
		}
	}

	else if (key == '+')
		camera_distance += 0.5;

	else if (key == '-')
		camera_distance -= 0.5;

	else if (key == 'w' || key == 'W')
		bWireFrame = !bWireFrame;

	else if (key == 'd' || key == 'D')
		bLight1 = !bLight1;
	else if (key == 'v' || key == 'V')
		b2Dlook = !b2Dlook;

	glutPostRedisplay();
}

void myInit()
{

	float	fHalfSize = 9;
	camera_angle = 120;
	camera_height = 5.5;
	camera_distance = 15.0;

	lookAt_X = 0;
	lookAt_Y = 1;
	lookAt_Z = 0;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);

}

void create() {
	trucquay.create_truc_quay();
	trucquay.SetColor(12);
	trucquay.CalculateNorms();

	trucquay_1.CreateCylinder(10 * 0.1, 2 * 0.1);
	trucquay_1.CalculateNorms();

	goi_do.create_goi_do(5 * 0.1, 2 * 0.1);
	goi_do.CalculateNorms();

	/*thanh_lien_ket.create_thanh_lien_ket(18 * 0.2, 2 * 0.2, 2 * 0.2, 1 * 0.2);
	thanh_lien_ket.SetColor(2);
	thanh_lien_ket.CalculateNorms();*/

	canh_quat.create_canh_quat(2 * 0.2);
	canh_quat.SetColor(0);
	canh_quat.CalculateNorms();

	canh_quat_1.create_canh_quat(2 * 0.2);
	canh_quat_1.SetColor(0);
	canh_quat_1.CalculateNorms();

	canh_quat_2.create_canh_quat(2 * 0.2);
	canh_quat_2.SetColor(0);
	canh_quat_2.CalculateNorms();

}
GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess = 40.0;


GLfloat diffuse_red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat diffuse_orange[] = { 1.0,153.0 / 255,104.0 / 255 };
GLfloat diffuse_blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat diffuse_black[] = { 0.01, 0.01, 0.01, 1.0 };
GLfloat diffuse_green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat diffuse_yellow[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat diffuse_pink[] = { 1.0, 128.0 / 255, 192.0 / 255, 1.0 };
GLfloat diffuse_silver[] = { 0.5, 0.5, 0.5, 1.0 };
void drawAll() {

	if (!bWireFrame) {
		glPushMatrix();
		/*glTranslatef(-15.0 / 4, 2.0 / 4, 0.0);

		glPushMatrix();
		cuboid.setupMaterial(ambient, diffuse_red, specular, shininess);
		glTranslatef(15.0 / 4, 0.0, 2.0 / 4);
		cuboid.DrawSmooth();
		glPopMatrix();


		glPushMatrix();
		cylinder.setupMaterial(ambient, diffuse_black, specular, shininess);
		glTranslatef(8 * 0.25, 5 * 0.25, 2.0 / 8 + 1.0 - 3.0 / 6);
		cylinder.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		Shape3.setupMaterial(ambient, diffuse_orange, specular, shininess);
		glTranslatef(15.0 / 64, 0.0, 0.0);
		glTranslatef(0.0, 2.0 / 4, 0.0);
		glTranslatef(0.0, 0.0, 1.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		Shape3.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		cylinder.setupMaterial(ambient, diffuse_black, specular, shininess);
		glTranslatef(22 * 0.25, 16 * 0.2, 2.0 / 8 + 1.0 - 3.0 / 6);
		cylinder.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		Shape4.setupMaterial(ambient, diffuse_orange, specular, shininess);
		glTranslatef(3.0 / 2 + 5.0 + 2.5 / 4, 2.0 / 4, 1.0 - 3.0 / 12);
		glRotatef(-180, 0.0, 1.0, 0.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		Shape4.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		cylinder.setupMaterial(ambient, diffuse_black, specular, shininess);
		glTranslatef(8 * 0.25, 5 * 0.25, 0.0);
		glRotatef(ANG, 0.0, 0.0, 1.0);
		glTranslatef(-8 * 0.25, -5 * 0.25, 0.0);
		glTranslatef(0.25 * 16, 0.18 * 5, 2.0 / 8 + 1.0 - 3.0 / 6);
		cylinder.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		Shape1.setupMaterial(ambient, diffuse_blue, specular, shininess);
		glTranslatef(8 * 0.25, 5 * 0.25, 0.0);
		glRotatef(ANG, 0.0, 0.0, 1.0);
		glTranslatef(-8 * 0.25, -5 * 0.25, 0.0);
		glTranslatef(15.0 / 64, 2.0 / 4 + 3.0 / 5 + 1.0 / 7, 2.0 / 8 + 1.0 - 3.0 / 6);
		glRotatef(-10, 0.0, 0.0, 1.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		Shape1.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		cylinder.setupMaterial(ambient, diffuse_black, specular, shininess);
		glTranslatef(22 * 0.25, 16 * 0.25, 0.0);
		glRotatef(ANG1 + 10.0, 0.0, 0.0, 1.0);
		glTranslatef(-22 * 0.25, -16 * 0.25, 0.0);
		glTranslatef(17 * 0.25 + 0.06, 9 * 0.25 - 0.05, 2.0 / 8 + 1.0 - 3.0 / 6);
		cylinder.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		Shape2.setupMaterial(ambient, diffuse_green, specular, shininess);
		glTranslatef(22 * 0.25, 16 * 0.25, 0.0);
		glRotatef(ANG1, 0.0, 0.0, 1.0);
		glTranslatef(-22 * 0.25, -16 * 0.25, 0.0);
		glTranslatef(5.5 / 2, 5.0 - 1.25 / 1.7, 3.0 / 12 * 2);
		glTranslatef(1.25 + 15.0 / 64 + 8 * 2.3 / 5 - 1.0 / 20, 2 * (1.25 / 4 + 2.0 / 4), 0.0);
		glRotatef(50, 0.0, 0.0, 1.0);
		glRotatef(180, 0.0, 0.0, 1.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		Shape2.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		Shape5.setupMaterial(ambient, diffuse_pink, specular, shininess);
		glTranslatef(8 * 0.25, 5 * 0.25, 0.0);
		glRotatef(ANG, 0.0, 0.0, 1.0);
		glTranslatef(-8 * 0.25, -5 * 0.25, 0.0);
		glTranslatef(16 * 0.25, 5 * 0.18, 0.0);
		glRotatef(ANG3, 0.0, 0.0, 1.0);
		glTranslatef(-16 * 0.25, -5 * 0.18, 0.0);
		glTranslatef(1.25 / 4 + 15.0 / 64 + 8 * 2.3 / 5 - 2.2 / 8, 1.25 / 4 + 2.0 / 4 + 1.0 / 12, 3.0 / 12 * 3);
		glRotatef(-25, 0.0, 0.0, 1.0);
		glRotatef(90, 0.0, 0.0, 1.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		Shape5.DrawSmooth();
		glPopMatrix();*/

		glPushMatrix();
		trucquay.setupMaterial(ambient, diffuse_silver, specular, shininess);
		glTranslatef(0, 3, 2.0 / 4 - 2);
		trucquay.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		trucquay_1.setupMaterial(ambient, diffuse_silver, specular, shininess);
		glTranslatef(0, 3, 6 * 0.2 - 2);
		trucquay_1.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		goi_do.setupMaterial(ambient, diffuse_blue, specular, shininess);
		glTranslatef(0, 3, 6 * 0.2 - 2.2);
		goi_do.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		canh_quat.setupMaterial(ambient, diffuse_red, specular, shininess);
		glTranslatef(0, 3, 6 * 0.2 - 1.4);
		canh_quat.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		canh_quat_1.setupMaterial(ambient, diffuse_red, specular, shininess);
		glTranslatef(0, 3, 6 * 0.2 - 1.4);
		glRotatef(120, 0, 0, 1);
		canh_quat_1.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		canh_quat_2.setupMaterial(ambient, diffuse_red, specular, shininess);
		glTranslatef(0, 3, 6 * 0.2 - 1.4);
		glRotatef(-120, 0, 0, 1);
		canh_quat_2.DrawSmooth();
		glPopMatrix();

		glPushMatrix();
		thanh_lien_ket.setupMaterial(ambient, diffuse_orange, specular, shininess);
		glTranslatef(0, 0, 6 * 0.2);
		thanh_lien_ket.DrawSmooth();
		glPopMatrix();

		glPopMatrix();
	}
	else {
		glDisable(GL_LIGHTING);
		glPushMatrix();
		/*glTranslatef(-15.0 / 4, 2.0 / 4, 0.0);
		glPushMatrix();
		glTranslatef(15.0 / 4, 0.0, 2.0 / 4);
		cuboid.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(8 * 0.25, 5 * 0.25, 2.0 / 8 + 1.0 - 3.0 / 6);
		cylinder.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(15.0 / 64, 0.0, 0.0);
		glTranslatef(0.0, 2.0 / 4, 0.0);
		glTranslatef(0.0, 0.0, 1.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		Shape3.DrawWireframe();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(22 * 0.25, 16 * 0.2, 2.0 / 8 + 1.0 - 3.0 / 6);
		cylinder.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(3.0 / 2 + 5.0 + 2.5 / 4, 2.0 / 4, 1.0 - 3.0 / 12);
		glRotatef(-180, 0.0, 1.0, 0.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		Shape4.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(8 * 0.25, 5 * 0.25, 2.0 / 8 + 1.0 - 3.0 / 6);
		glRotatef(ANG, 0.0, 0.0, 1.0);
		glTranslatef(-8 * 0.25, -5 * 0.25, 0.0);
		glTranslatef(0.25 * 16, 0.18 * 5, 0.0);
		cylinder.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(8 * 0.25, 5 * 0.25, 0.0);
		glRotatef(ANG, 0.0, 0.0, 1.0);
		glTranslatef(-8 * 0.25, -5 * 0.25, 0.0);
		glTranslatef(15.0 / 64, 2.0 / 4 + 3.0 / 5 + 1.0 / 7, 2.0 / 8 + 1.0 - 3.0 / 6);
		glRotatef(-10, 0.0, 0.0, 1.0);
		glRotatef(-90, 1.0, 0.0, 0.0);
		Shape1.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(22 * 0.25, 16 * 0.25, 2.0 / 8 + 1.0 - 3.0 / 6);
		glRotatef(ANG1 + 10.0, 0.0, 0.0, 1.0);
		glTranslatef(-22 * 0.25, -16 * 0.25, 0.0);
		glTranslatef(17 * 0.25 + 0.06, 9 * 0.25 - 0.05, 0.0);
		cylinder.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(22 * 0.25, 16 * 0.25, 0.0);
		glRotatef(ANG1, 0.0, 0.0, 1.0);
		glTranslatef(-22 * 0.25, -16 * 0.25, 0.0);
		glTranslatef(5.5 / 2, 5.0 - 1.25 / 1.7, 3.0 / 12 * 2);
		glTranslatef(1.25 + 15.0 / 64 + 8 * 2.3 / 5 - 1.0 / 20, 2 * (1.25 / 4 + 2.0 / 4), 0.0);
		glRotatef(50, 0.0, 0.0, 1.0);
		glRotatef(180, 0.0, 0.0, 1.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		Shape2.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(8 * 0.25, 5 * 0.25, 0.0);
		glRotatef(ANG, 0.0, 0.0, 1.0);
		glTranslatef(-8 * 0.25, -5 * 0.25, 0.0);
		glTranslatef(16 * 0.25, 5 * 0.18, 0.0);
		glRotatef(ANG3, 0.0, 0.0, 1.0);
		glTranslatef(-16 * 0.25, -5 * 0.18, 0.0);
		glTranslatef(1.25 / 4 + 15.0 / 64 + 8 * 2.3 / 5 - 2.2 / 8, 1.25 / 4 + 2.0 / 4 + 1.0 / 12, 3.0 / 12 * 3);
		glRotatef(-25, 0.0, 0.0, 1.0);
		glRotatef(90, 0.0, 0.0, 1.0);
		glRotatef(90, 1.0, 0.0, 0.0);
		Shape5.DrawWireframe();
		glPopMatrix();*/
		glPushMatrix();
		//canh_quat.setupMaterial(ambient, diffuse_orange, specular, shininess);
		//glTranslatef(0, 0, 6 * 0.2);
		canh_quat.DrawWireframe();
		glPopMatrix();

		glPushMatrix();
		/*thanh_lien_ket.setupMaterial(ambient, diffuse_orange, specular, shininess);
		glTranslatef(0, 0, 6 * 0.2);*/
		thanh_lien_ket.DrawWireframe();
		glPopMatrix();

		glPopMatrix();

		glEnable(GL_LIGHTING);
	}

}

void drawLucGiac(float x, float y, float z, float R, float alpha)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glColor4f(0.3, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(-60 * PI / 180), y, z + R * sin(-60 * PI / 180));
	glVertex3f(x + R * cos(0), y, z + R * sin(0));
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(77.0 / 255.0, 166.0 / 255.0, 210.0 / 255.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(60 * PI / 180), y, z + R * sin(60 * PI / 180));
	glVertex3f(x + R * cos(120 * PI / 180), y, z + R * sin(120 * PI / 180));
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(1.0, 1.0, 1.0, alpha);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + R * cos(180 * PI / 180), y, z + R * sin(180 * PI / 180));
	glVertex3f(x + R * cos(240 * PI / 180), y, z + R * sin(240 * PI / 180));
	glVertex3f(x + R * cos(300 * PI / 180), y, z + R * sin(300 * PI / 180));
	glVertex3f(x, y, z);
	glEnd();
}

int main(int argc, char* argv[])
{
	cout << "1,2: Xoay can dao" << endl;
	cout << "W, w: Chuyen doi qua lai giua che do khung day va to mau" << endl;
	cout << "V, v: Chuyen doi qua lai giua hai che do nhin khac nhau" << endl;
	cout << "+   : Tang khoang cach camera" << endl;
	cout << "-   : Giam khoang cach camera" << endl;
	cout << "up arrow  : Tang chieu cao camera" << endl;
	cout << "down arrow: Giam chieu cao camera" << endl;
	cout << "<-         : Quay camera theo chieu kim dong ho" << endl;
	cout << "->         : Quay camera nguoc chieu kim dong ho";


	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Le Kha - 1810976"); // open the screen window

	create();
	myInit();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(key);
	glutKeyboardFunc(movement);
	glutMainLoop();
	return 0;
}