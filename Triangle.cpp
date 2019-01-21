/*Implementação dos métodos da classe Triangle
*/

#include "ExceptionMessages.h"
#include "Triangle.h"

/*Método construtor
	Vertex* a, Vertex* b, Vertex* c são os tres vertices que definem um triangulo
*/
Triangle::Triangle(Vertex* a, Vertex* b, Vertex* c)
{
	/*assertivas para garantir consistencia do triangulo
	*/
	if(a == NULL)
	{
		throw ExceptionMessage::TRIANGLE_NULL_VERTEX_A_MSSG;
	}
	if(b == NULL)
	{
		throw ExceptionMessage::TRIANGLE_NULL_VERTEX_B_MSSG;
	}
	if(c == NULL)
	{
		throw ExceptionMessage::TRIANGLE_NULL_VERTEX_C_MSSG;
	}
	/*assertiva para garantir que os vertices recebidos são diferentes
	obs.: testar a colinearidade dos pontos não é possivel dado que as coordenadas
	dos vertices são em ponto flutuante e, por falta de precisão, o teste falharia
	em casos corretos
	*/
	if(a==b || a==c || b==c)
	{
		throw ExceptionMessage::TRIANGLE_REPEATED_VERTEX_MSSG;
	}

	
	this->a = a;
	this->b = b;
	this->c = c;
}

/*Cor do triangulo (RGBA)
*/
Vec4b* Triangle::color()
{
	//calcular a média das cores de cada vértice, ou seja, a cor do baricentro
	uchar r = (this->a->color->val[R] + this->b->color->val[R] + this->c->color->val[R]) / 3;
	uchar g = (this->a->color->val[G] + this->b->color->val[G] + this->c->color->val[G]) / 3;
	uchar b = (this->a->color->val[B] + this->b->color->val[B] + this->c->color->val[B]) / 3;
	uchar a = (this->a->color->val[A] + this->b->color->val[A] + this->c->color->val[A]) / 3;

	return new Vec4b(r, g, b, a);
}

/*area do triangulo projetado em 2D (ignorando a componente Z)
*/
float Triangle::area2d()
{
	//projetar cada um dos vértices em 2D
	Vec2f* a2d = this->a->bidim();
	Vec2f* b2d = this->b->bidim();
	Vec2f* c2d = this->c->bidim();

	//calcular e retornar a área do triangulo projetado
	return abs(   (  ( a2d->val[X] * (b2d->val[Y] - c2d->val[Y]) ) +
			         ( b2d->val[X] * (c2d->val[Y] - a2d->val[Y]) ) +
					 ( c2d->val[X] * (a2d->val[Y] - b2d->val[Y]) )  )/2   );
}