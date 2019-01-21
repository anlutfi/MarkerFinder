/**
Classe Vertex, que representa um vértice, um ponto no espaço tridimensional.
*/


#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "ExceptionMessages.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <assert.h>//para fins de debug

using namespace cv;
using namespace std;

/*Inicio da declaração de constantes*/
const int X = 0;
const int Y = 1;
const int Z = 2;

const int R = 0;
const int G = 1;
const int B = 2;
const int A = 3;
/*Fim da declaração de constantes*/

/**
Classe Vertex, que representa um vértice, um ponto no espaço tridimensional.
*/
class Vertex
{
public:
	/**
	posição tridimensional do ponto
	*/
	Vec3f* position;
	
	/**
	cor RBGA do ponto
	*/
	Vec4b* color;
	
	/**
	Método construtor da classe Vertex

	float x, float y, float z são as coordenadas x,y,z da posição do vértice
	uchar r, uchar g, uchar b, uchar a são as componentes r, g, b, a da cor do vértice
	*/
	Vertex(float x, float y, float z, uchar r, uchar g, uchar b, uchar a);
	
	/**
	Projeção bidimensional do ponto, ou seja, suas coordenadas (X,Y).
	*/
	Vec2f* bidim();
};

#endif