#include "commons.h"

void setRGBAColor(struct RGBAColor * color, unsigned char r, unsigned char g, unsigned char b, unsigned char a) 
{
	color->R = r;
	color->G = g;
	color->B = b;
	color->A = a;
};