/**
Classe ImageMaker, respons�vel por gerar um objeto da classe Grid a partir de uma malha (classe Mesh),
e por retornar a imagem png gerada por ele.
*/

#ifndef _IMAGEMAKER_H_
#define _IMAGEMAKER_H_

#include "Mesh.h"
#include "Grid.h"

class ImageMaker
{
public:
	/**
	*Malha base para gerac�o da imagem
	*/
	Mesh* mesh;

	/**
	*Grid que contem a matriz de pixels gerada a partir de mesh
	*/
	Grid* grid;

	/**
	*M�todo construtor da classe ImageMaker

	Mesh* mesh � a malha de triangulos a ser usada

	Vec4b* defaultcolor � a cor de inicializa��o dos pixels

	float trianglesperpixel � o n�mero m�dio desejado de triangulos
		da malha contidos em cada pixel de grid.
	*/
	ImageMaker(Mesh* mesh, Vec4b* defaultcolor, float trianglesperpixel);
	
	/**
	*gera e retorna a imagem png
	*/
	Mat image();
	
	/**
	*verifica se dois pontos -p1 e p2- est�o do mesmo lado da reta a b
	*/
	static bool sameSide(Vec2f* p1, Vec2f* p2, Vec2f* a, Vec2f* b);

	/**
	*verifica se um ponto p est� dentro do tri�ngulo t (em 2D)
	*/
	static bool pointInTriangle(Vec2f* p, Triangle* t);
};

#endif