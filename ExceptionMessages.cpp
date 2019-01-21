#include "ExceptionMessages.h"

const char* ExceptionMessage::PIXEL_INVALID_X_INTERVAL_MSSG = "Class Pixel - function Pixel() - Pixel with xbegin larger or equal to xend";
const char* ExceptionMessage::PIXEL_INVALID_Y_INTERVAL_MSSG = "Class Pixel - function Pixel() - Pixel with ybegin larger or equal to yend";
const char* ExceptionMessage::PIXEL_NOT_SQUARE_MSSG = "Class Pixel - function Pixel() - Pixel not square";
const char* ExceptionMessage::PIXEL_NULL_COLOR_PTR_MSSG = "Class Pixel - Function Pixel() - Null pointer for color";
			
const char* ExceptionMessage::GRID_INVALID_WIDTH_MSSG = "Class Grid - function Grid() - Null or Negative width (w)";
const char* ExceptionMessage::GRID_INVALID_HEIGHT_MSSG = "Class Grid - function Grid() - Null or Negative height (h)";
const char* ExceptionMessage::GRID_INVALID_PIXEL_SIZE_MSSG = "Class Grid - function Grid() - Null or Negative pixel size (pixelsize)";
const char* ExceptionMessage::GRID_NULL_COLOR_PTR_MSSG = "Class Grid - Function Grid() - Null pointer for default color(defaultcolor)";
			
const char* ExceptionMessage::TRIANGLE_NULL_VERTEX_A_MSSG = "Class Triangle- Function Triangle() - Null vertex a";
const char* ExceptionMessage::TRIANGLE_NULL_VERTEX_B_MSSG = "Class Triangle- Function Triangle() - Null vertex b";
const char* ExceptionMessage::TRIANGLE_NULL_VERTEX_C_MSSG = "Class Triangle- Function Triangle() - Null vertex c";
const char* ExceptionMessage::TRIANGLE_REPEATED_VERTEX_MSSG = "Class Triangle - Function Triangle() - Triangle with two or more identic vertices";
		
const char* ExceptionMessage::MESH_INVALID_FILENAME_MSSG = "Class Mesh - Function Mesh() - Empty string for file name (meshfilename)";
const char* ExceptionMessage::MESH_MISSING_CORRUPTED_FILE_MSSG = "Class Mesh - Fucntion Mesh() - File missing or corrupted - ";
const char* ExceptionMessage::MESH_FILE_HEADER_ERROR_MSSG = "Class Mesh - Fucntion Mesh() - File with incomplete header";
const char* ExceptionMessage::MESH_FILE_INCORRECT_NUMBER_LINES_MSSG = "Class Mesh - Fucntion Mesh() - File with incorrect number of lines";
	
const char* ExceptionMessage::IMAGEMAKER_INVALID_TPP_NUM_MSSG = "Class ImageMaker - Function ImageMaker() - Null or Negative value for Triangles per Pixel (trianglesperpixel)";
const char* ExceptionMessage::IMAGEMAKER_NULL_MESH_POINTER_MSSG = "Class ImageMaker - Function ImageMaker() - Null pointer for mesh";
const char* ExceptionMessage::IMAGEMAKER_NULL_COLOR_POINTER_MSSG = "Class ImageMaker - Function ImageMaker() - Null pointer for default color(defaultcolor)";
const char* ExceptionMessage::IMAGEMAKER_NULL_P1_POINTER_MSSG = "Class ImageMaker - Function sameSide() - Null pointer for p1";
const char* ExceptionMessage::IMAGEMAKER_NULL_P2_POINTER_MSSG = "Class ImageMaker - Function sameSide() - Null pointer for p2";
const char* ExceptionMessage::IMAGEMAKER_NULL_A_POINTER_MSSG = "Class ImageMaker - Function sameSide() - Null pointer for a";
const char* ExceptionMessage::IMAGEMAKER_NULL_B_POINTER_MSSG = "Class ImageMaker - Function sameSide() - Null pointer for b";
const char* ExceptionMessage::IMAGEMAKER_IDENTICAL_P1_P2_MSSG = "Class ImageMaker - Function sameSide() - Identical pointers for p1 and p2";
const char* ExceptionMessage::IMAGEMAKER_IDENTICAL_A_B_MSSG = "Class ImageMaker - Function sameSide() - Identical pointers for a and b";
const char* ExceptionMessage::IMAGEMAKER_NULL_P_POINTER_MSSG = "Class ImageMaker - Function pointInTriangle() - Null pointer for p";
const char* ExceptionMessage::IMAGEMAKER_NULL_T_POINTER_MSSG = "Class ImageMaker - Function pointInTriangle() - Null pointer for triangle (t)";
