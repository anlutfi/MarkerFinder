/*Implementação dos métodos da classe Vertex
*/

#include "Vertex.h"

/*Método construtor:
float x, float y, float z são as coordenadas x,y,z da posição do vértice

uchar r, uchar g, uchar b, uchar a são as componentes r, g, b, a da cor do vértice
*/
Vertex::Vertex(float x, float y, float z, uchar r, uchar g, uchar b, uchar a)
{
	this->position = new Vec3f(x, y, z);
	this->color = new Vec4b(r, g, b, a);
}

/*Projeção bidimensional do ponto, ou seja, suas coordenadas (X,Y).
*/
Vec2f* Vertex::bidim (void)
{
	return new Vec2f((float)this->position->val[X], (float)this->position->val[Y]);
}