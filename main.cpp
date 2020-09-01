#include "tgaimage.h"
#include <cmath>
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

// Bresenham’s Line Drawing Algorithm
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{ // if the line is steep, we transpose the image
		//otherwise it would be fragmented
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1)
	{ // make it left−to−right
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	//The error variable gives us the distance to
	//the best straight line from our current (x, y) pixel.
	//Each time error is greater than one pixel,
	//we increase (or decrease) y by one,
	//and decrease the error by one as well.

	//let error = error * dx * 2
	//so error>0.5 == error > dx
	float error = 0;
	//x 每增加1 error就增加 一个斜率
	// float derror = std::abs(dy / float(dx));
	float derror = std::abs(dy) * 2;
	int y = y0;
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
			// if transposed, de−transpose
			image.set(y, x, color);
		else
			image.set(x, y, color);
		error += derror;
		if (error > dx)
		{
			y += (y1 > y0 ? 1 : -1);
			error -= dx * 2;
		}
	}
}

int main(int argc, char **argv)
{
	TGAImage image(100, 100, TGAImage::RGB);
	line(13, 20, 80, 40, image, white);
	line(20, 13, 40, 80, image, red);
	line(80, 40, 13, 20, image, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}
