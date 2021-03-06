#include "Cube.h"

Cube::Cube(float x, float y, float z, float rotb, float rotc, float rotd, float theta, float size, Quaternion rotation, std::string tex, std::string shader, std::string obj)
	: _x(x), _y(y), _z(z), _rotB(rotb), _rotC(rotc), _rotD(rotd), _theta(theta), _size(size), rotation(rotation)
{
	_shader = LoadShaders((shader + ".v").c_str(),(shader+".f").c_str());
	if (tex != "")
		_texture = LoadTexture(tex.c_str());
	else
		_texture = 0;
	modelviewMat = (GLfloat*) calloc(16,sizeof(GLfloat));
	modelviewMat[0] = modelviewMat[5] = modelviewMat[10] = modelviewMat[15] = 1;

	if (obj != "")
	{
		loadOBJ(obj.c_str(), out_vertices, out_uvs, out_normals);
		std::cout << "size : " << out_vertices.size();
	}
}

Cube::~Cube()
{
	free(modelviewMat);
}

void Cube::solidColoredCube()
{

	GLfloat coord[8][3] =
	{
		{-_size,-_size,-_size},
		{_size,-_size,-_size },
		{_size, _size, -_size},
		{-_size,_size,-_size},
		{-_size,-_size,_size},
		{_size,-_size,_size},
		{_size,_size,_size},
		{-_size,_size,_size}
	};

	GLfloat color[6][3] =
	{
		{1.0,0.0,0.0},
		{0.0,1.0,0.0},
		{0.0,0.0,1.0},
		{0.0,1.0,1.0},
		{1.0,1.0,0.0},
		{1.0,0.0,1.0},
	};

	GLubyte num[6][4] =
	{ {0,1,2,3},
	{1,5,6,2},
	{4,5,6,7},
	{0,4,7,3},
	{0,1,5,4},
	{2,6,7,3}
	};

	glUseProgram(_shader);

	glEnable(GL_TEXTURE_2D);
	if (_texture != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);
	}

	float modelview[16];
	float proj[16];
	glGetFloatv(GL_PROJECTION_MATRIX, proj);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

	glUniformMatrix4fv(glGetUniformLocation(_shader, "projection"), 1, GL_FALSE, proj);
	glUniformMatrix4fv(glGetUniformLocation(_shader, "modelview"), 1, GL_FALSE, modelview);
	int texcoord_index = glGetAttribLocation(_shader, "in_coord");
	if (out_vertices.size() == 0)
	{
		for (int x = 0; x != 6; x++)
		{
			//glColor3f(color[x][0], color[x][1], color[x][2]);

				glBegin(GL_QUADS);
				glVertex3fv(coord[num[x][0]]);
				glVertexAttrib2f(texcoord_index, 0, 0);
				glVertex3fv(coord[num[x][1]]);
				glVertexAttrib2f(texcoord_index, 0, 1);
				glVertex3fv(coord[num[x][2]]);
				glVertexAttrib2f(texcoord_index, 1, 1);
				glVertex3fv(coord[num[x][3]]);
				glVertexAttrib2f(texcoord_index, 1, 0);
				glEnd();

		}
	}
	else
	{
		for (int i = 0; i < out_vertices.size(); i += 3)
		{
			glBegin(GL_TRIANGLES);
			glVertexAttrib2f(texcoord_index, out_uvs[i]._x, out_uvs[i]._y);
			glVertex3f(out_vertices[i]._x,out_vertices[i]._y, out_vertices[i]._z);
			glVertexAttrib2f(texcoord_index, out_uvs[i + 1]._x, out_uvs[i + 1]._y);
			glVertex3f(out_vertices[i+1]._x, out_vertices[i+1]._y, out_vertices[i+1]._z);
			glVertexAttrib2f(texcoord_index, out_uvs[i + 2]._x, out_uvs[i + 2]._y);
			glVertex3f(out_vertices[i+2]._x, out_vertices[i+2]._y, out_vertices[i+2]._z);
			glEnd();
		}

	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}
GLuint Cube::LoadTexture(const char* filename)
{
	GLuint texture;
	
	unsigned char* bitmapData;
	BMP::INFOHEADER infoheader;

	bitmapData = BMP::LoadBitmapFile(filename, &infoheader);

	if (bitmapData != NULL) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, infoheader.width, infoheader.height, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
		glGenerateMipmap(GL_TEXTURE_2D);
		free(bitmapData);
		return texture;
	}
	else {
		return 0;
	}
	
}
void Cube::draw(int repere)
{
	glPushMatrix();

	glMultMatrixf(modelviewMat);

	glPushMatrix();

	glTranslatef(_x,_y,_z);
	if (out_vertices.size() != 0) {
		glScalef(_size, _size, _size);
	}

	this->solidColoredCube();

	

	glDisable(GL_TEXTURE_2D);

	if(repere == 1){
	//HELPER
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(2, 0, 0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 2);
	glEnd();
	}
	glPopMatrix();

	glPopMatrix();

}

void Cube::rotate( Quaternion q)
{
	GLfloat* matrix = q.quaternion2Matrix();
	glPushMatrix();
	glLoadMatrixf(modelviewMat);
	glMultMatrixf(matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMat);
	glPopMatrix();



}


GLfloat Cube::rotb() const
{
	return _rotB;
}

GLfloat Cube::rotc() const
{
	return _rotC;
}
GLfloat Cube::rotd() const
{
	return _rotD;
}
GLfloat Cube::thetha() const
{
	return _theta;
}