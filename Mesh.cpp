/*Implementa��o dos m�todos da classe Mesh
*/

#include "ExceptionMessages.h"
#include "Mesh.h"

/*inicio da declara��o de constantes*/
const char* END_HEADER = "end_header";
const char* ELEMENT_TAG = "element";
const char* VERTEX_TAG = "vertex";
const char* TRIANGLE_TAG = "face";
/*fim da declara��o de constantes*/

/*Metodo construtor:
string meshfile � um arquivo texto contendo os dados da malha.
Esse m�todo � responsavel por inicializar todos os v�rtices (classe Vertex)
e todos os triangulos (classe Triangle)
*/
Mesh::Mesh(string meshfilename)
{
	if(meshfilename.empty())
	{
		throw ExceptionMessage::MESH_INVALID_FILENAME_MSSG;
	}
	
	/*abrindo o arquivo com a malha
	*/
	ifstream meshfile;
	meshfile.open(meshfilename, ios::in);

	if(!meshfile.is_open())
	{
		throw ExceptionMessage::MESH_MISSING_CORRUPTED_FILE_MSSG;
	}
	
	string line; //linha atual na leitura do arquivo
	int vertexcount = 0; //quantidade total de vertices na malha
	int trianglecount = 0; //quantidade total de triangulos na malha
		
	//obtem as quantidades de v�rtices e triangulos no arquivo de entrada
	while( line != END_HEADER )
	{
		getline(meshfile, line);
			
		if( line.find(ELEMENT_TAG) != string::npos )
		{
			/*se a linha contem a descri��o de um vertice
			*/
			if( line.find(VERTEX_TAG) != string::npos )
			{
				/*vari�veis para guardar metadados presentes no arquivo
				que n�o s�o relevantes
				*/
				char *trash = NULL;
				char *dirt = NULL;
					
				sscanf(line.c_str(), "%s%s%d", &trash, &dirt, &vertexcount);					
			}
				
			/*se a linha contem a descri��o de um triangulo
			*/
			else if( line.find(TRIANGLE_TAG) != string::npos )
			{
				char *trash, *dirt;
					
				sscanf(line.c_str(), "%s%s%d", &trash, &dirt, &trianglecount);	
			}
		}
	}

	/*se o cabe�alho do arquivo n�o estiver com o formato adequado
	*/
	if(vertexcount == 0 || trianglecount == 0)
	{
		throw ExceptionMessage::MESH_FILE_HEADER_ERROR_MSSG;
	}
	
	this->vertexcount = vertexcount;
	this->trianglecount = trianglecount;
	this->vertices = new Vertex*[this->vertexcount];
	this->triangles = new Triangle*[this->trianglecount];
	

	cout << "Reading file into mesh...";
	//preenche a lista de v�rtices com os dados do arquivo
	for(int count = 0; count < this->vertexcount; count++)
	{
		/*se a quantidade de vertices informada no cabe�alho do arquivo
		n�o corresponder com a quantidade de v�rtices descritos no arquivo
		*/
		if(!getline(meshfile, line))
		{
			throw ExceptionMessage::MESH_FILE_INCORRECT_NUMBER_LINES_MSSG;
		}
		
		float x, y, z; //vari�veis auxiliares para coordenadas tridimensionais
		int r, g, b, a; //vari�veis auxiliares para componentes de cor (RGBA)
			
		/*le os dados do v�rtice atual e adiciona um novo vertice (classe Vertex)
		� lista de v�rtices do objeto
		*/
		sscanf(line.c_str(), "%f%f%f%d%d%d%d", &x, &y, &z, &r, &g, &b, &a);
		this->vertices[count] = new Vertex(x, y, z, r, g, b, a);
	}
		
	//preenche a lista de triangulos com os dados do arquivo
	for(int count = 0; count < this->trianglecount; count++)
	{
		/*se a quantidade de vertices informada no cabe�alho do arquivo
		n�o corresponder com a quantidade de v�rtices descritos no arquivo
		*/
		if(!getline(meshfile, line))
		{
			throw ExceptionMessage::MESH_FILE_INCORRECT_NUMBER_LINES_MSSG;
		}

		int a, b, c;//vari�veis auxiliares para os tres vertices que compoem o triangulo
		int trash;//varaivel auxiliar para dado irrelevante presente no arquivo de entrada
			
		/*le os dados do triangulo atual e adiciona um novo triangulo (classe Triangle)
		� lista de triangulos do objeto
		*/
		sscanf(line.c_str(), "%d%d%d%d", &trash, &a, &b, &c);
		this->triangles[count] = new Triangle(this->vertices[a], this->vertices[b], this->vertices[c]);
	}

	cout << "done - ";
		
	//fecha arquivo
	meshfile.close();
	
}

/*area total da malha projetada em 2D (ignorando a componente Z de todos os triangulos)
*/
float Mesh::area2d()
{
	float area = 0.0F;
	
	/*soma a �rea de todas as projecoes de todos os triangulos
	*/
	for(int i = 0; i < this->trianglecount; i++)
	{
		area += this->triangles[i]->area2d();
	}

	return area;
}