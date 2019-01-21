/**
Classe Triangle, que representa um triangulo no espa�o tridimensional.
Os v�rtices do triangulo s�o objetos da classe Vertex
*/

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Vertex.h"

class Triangle
{
public:
	/**
	*o primeiro vertice do tri�ngulo
	*/
	Vertex * a;
	
	/**
	*o segundo vertice do tri�ngulo
	*/
	Vertex * b;
	
	/**
	*o terceiro vertice do tri�ngulo
	*/
	Vertex * c;
	
	/**
	*M�todo construtor da classe Triangle

	*Vertex* a, Vertex* b, Vertex* c s�o os tres vertices que definem um triangulo
	*/
	Triangle(Vertex* a, Vertex* b, Vertex* c);
	
	/**
	*Cor do triangulo (RGBA)
	*/
	Vec4b* color();

	/**
	*area do triangulo projetado em 2D (ignorando a componente Z)
	*/
	float area2d();
};

#endif