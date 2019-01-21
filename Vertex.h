/**
Classe Vertex, que representa um v�rtice, um ponto no espa�o tridimensional.
*/


#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "ExceptionMessages.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <assert.h>//para fins de debug

using namespace cv;
using namespace std;

/*Inicio da declara��o de constantes*/
const int X = 0;
const int Y = 1;
const int Z = 2;

const int R = 0;
const int G = 1;
const int B = 2;
const int A = 3;
/*Fim da declara��o de constantes*/

/**
Classe Vertex, que representa um v�rtice, um ponto no espa�o tridimensional.
*/
class Vertex
{
public:
	/**
	posi��o tridimensional do ponto
	*/
	Vec3f* position;
	
	/**
	cor RBGA do ponto
	*/
	Vec4b* color;
	
	/**
	M�todo construtor da classe Vertex

	float x, float y, float z s�o as coordenadas x,y,z da posi��o do v�rtice
	uchar r, uchar g, uchar b, uchar a s�o as componentes r, g, b, a da cor do v�rtice
	*/
	Vertex(float x, float y, float z, uchar r, uchar g, uchar b, uchar a);
	
	/**
	Proje��o bidimensional do ponto, ou seja, suas coordenadas (X,Y).
	*/
	Vec2f* bidim();
};

#endif