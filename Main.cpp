#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Functions.h"





int main()
{
	draw_two_triangle();
	draw_all_2d_transformations();
	draw_3d_triangle();
	draw_3d_triangle_mouse();
	project();
	return 0; 
}