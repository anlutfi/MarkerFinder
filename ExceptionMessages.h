/**
	declaracao de mensagens de exceção para testes
*/

#ifndef _EXCP_MSG_
#define _EXCP_MSG_

#include <stdio.h>

class ExceptionMessage
{
public:
	
	/*
	classe pixel
	*/
	static const char* PIXEL_INVALID_X_INTERVAL_MSSG;
	static const char* PIXEL_INVALID_Y_INTERVAL_MSSG;
	static const char* PIXEL_NOT_SQUARE_MSSG;
	static const char* PIXEL_NULL_COLOR_PTR_MSSG;

	/*
	classe Grid
	*/
	static const char* GRID_INVALID_WIDTH_MSSG;
	static const char* GRID_INVALID_HEIGHT_MSSG;
	static const char* GRID_INVALID_PIXEL_SIZE_MSSG;
	static const char* GRID_NULL_COLOR_PTR_MSSG;

	/*
	classe Triangle
	*/
	static const char* TRIANGLE_NULL_VERTEX_A_MSSG;
	static const char* TRIANGLE_NULL_VERTEX_B_MSSG;
	static const char* TRIANGLE_NULL_VERTEX_C_MSSG;
	static const char* TRIANGLE_REPEATED_VERTEX_MSSG;

	/*
	classe Mesh
	*/
	static const char* MESH_INVALID_FILENAME_MSSG;
	static const char* MESH_MISSING_CORRUPTED_FILE_MSSG;
	static const char* MESH_FILE_HEADER_ERROR_MSSG;
	static const char* MESH_FILE_INCORRECT_NUMBER_LINES_MSSG;

	/*
	classe ImageMaker
	*/
	static const char* IMAGEMAKER_INVALID_TPP_NUM_MSSG;
	static const char* IMAGEMAKER_NULL_MESH_POINTER_MSSG;
	static const char* IMAGEMAKER_NULL_COLOR_POINTER_MSSG;
	static const char* IMAGEMAKER_NULL_P1_POINTER_MSSG;
	static const char* IMAGEMAKER_NULL_P2_POINTER_MSSG;
	static const char* IMAGEMAKER_NULL_A_POINTER_MSSG;
	static const char* IMAGEMAKER_NULL_B_POINTER_MSSG;
	static const char* IMAGEMAKER_IDENTICAL_P1_P2_MSSG;
	static const char* IMAGEMAKER_IDENTICAL_A_B_MSSG;
	static const char* IMAGEMAKER_NULL_P_POINTER_MSSG;
	static const char* IMAGEMAKER_NULL_T_POINTER_MSSG;
	
	ExceptionMessage();

};

#endif