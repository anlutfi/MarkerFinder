/**
Classe Triangle, que representa um triangulo no espaço tridimensional.
Os vértices do triangulo são objetos da classe Vertex
*/

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Vertex.h"

class Triangle
{
public:
	/**
	*o primeiro vertice do triângulo
	*/
	Vertex * a;
	
	/**
	*o segundo vertice do triângulo
	*/
	Vertex * b;
	
	/**
	*o terceiro vertice do triângulo
	*/
	Vertex * c;
	
	/**
	*Método construtor da classe Triangle

	*Vertex* a, Vertex* b, Vertex* c são os tres vertices que definem um triangulo
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