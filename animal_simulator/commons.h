#pragma once

struct RGBAColor 
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
};

void setRGBAColor(struct RGBAColor * color, unsigned char r, unsigned char g, unsigned char b, unsigned char a);