#include <iostream>
#include <cmath>
#include <algorithm>
#include "tgaimage.h"
using namespace std;

// compile with:
// g++ rasterizer.cpp tgaimage.cpp -o out.exe

void set_color(int x, int y, TGAImage &image, TGAColor color, bool invert = false)
{
    image.set(x, y, color);
}

float line(float x0, float y0, float x1, float y1, float x, float y)
{
    return (y0 - y1) * x + (x1 - x0) * y + x0 * y1 - x1 * y0;
}


void draw_triangle_2d(TGAImage& image, float x0, float y0, float x1, float y1, float x2, float y2, TGAColor color)
{
    float x_min = min(floor(x0), min(floor(x1), floor(x2)));
    float x_max = max(ceil(x0), max(ceil(x1), ceil(x2)));

    float y_min = min(floor(y0), min(floor(y1), floor(y2)));
    float y_max = max(ceil(y0), max(ceil(y1), ceil(y2)));

    for (float y = y_min; y <= y_max; ++y) {
        for (float x = x_min; x <= x_max; ++x) {
            float alfa = line(x1, y1, x2, y2, x, y) / line(x1, y1, x2, y2, x0, y0);
            float beta = line(x2, y2, x0, y0, x, y) / line(x2, y2, x0, y0, x1, y1);
            float gama = line(x0, y0, x1, y1, x, y) / line(x0, y0, x1, y1, x2, y2);

            if (alfa > 0 && alfa < 1 && beta > 0 && beta < 1 && gama > 0 && gama < 1) {
                set_color(x, y, image, color);
            }
        }
    }
}

void draw_triangle_2d_gouraurd(TGAImage& image, float x0, float y0, TGAColor c0, float x1, float y1, TGAColor c1, float x2, float y2, TGAColor c2)
{
    float x_min = min(floor(x0), min(floor(x1), floor(x2)));
    float x_max = max(ceil(x0), max(ceil(x1), ceil(x2)));

    float y_min = min(floor(y0), min(floor(y1), floor(y2)));
    float y_max = max(ceil(y0), max(ceil(y1), ceil(y2)));

    for (float y = y_min; y <= y_max; ++y) {
        for (float x = x_min; x <= x_max; ++x) {
            float alfa = line(x1, y1, x2, y2, x, y) / line(x1, y1, x2, y2, x0, y0);
            float beta = line(x2, y2, x0, y0, x, y) / line(x2, y2, x0, y0, x1, y1);
            float gama = line(x0, y0, x1, y1, x, y) / line(x0, y0, x1, y1, x2, y2);

            if (alfa > 0 && alfa < 1 && beta > 0 && beta < 1 && gama > 0 && gama < 1) {
                set_color(x, y, image, TGAColor((alfa * c0.r + beta * c1.r + gama * c2.r), (alfa * c0.g + beta * c1.g + gama * c2.g), (alfa * c0.b + beta * c1.b + gama * c2.b), 255));
            }
        }
    }
}


void draw_triangle(TGAImage& image, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, TGAColor color) {
// homogene koord.
    x0 /= z0;
    y0 /= z0;
    x1 /= z1;
    y1 /= z1;
    x2 /= z2;
    y2 /= z2;

    x0 = (1 + x0) * 0.5 * width;
    x1 = (1 + x1) * 0.5 * width;
    x2 = (1 + x2) * 0.5 * width;

    y0 = (1 + y0) * 0.5 * height;
    y1 = (1 + y1) * 0.5 * height;
    y2 = (1 + y2) * 0.5 * height;

    float x_min = min(floor(x0), min(floor(x1), floor(x2)));
    float x_max = max(ceil(x0), max(ceil(x1), ceil(x2)));

    float y_min = min(floor(y0), min(floor(y1), floor(y2)));
    float y_max = max(ceil(y0), max(ceil(y1), ceil(y2)));

    for (float y = y_min; y <= y_max; ++y) {
        for (float x = x_min; x <= x_max; ++x) {
            float alfa = line(x1, y1, x2, y2, x, y) / line(x1, y1, x2, y2, x0, y0);
            float beta = line(x2, y2, x0, y0, x, y) / line(x2, y2, x0, y0, x1, y1);
            float gama = line(x0, y0, x1, y1, x, y) / line(x0, y0, x1, y1, x2, y2);

            if (alfa > 0 && alfa < 1 && beta > 0 && beta < 1 && gama > 0 && gama < 1) {
                set_color(x, y, image, color);
            }
        }
    }
}

// dimenzije slike
const int width  = 200;
const int height = 200;

// definirajmo boje
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0, 0, 255);
const TGAColor blue  = TGAColor(0, 0, 255, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

int main()
{
    // definiraj sliku
    TGAImage image(width, height, TGAImage::RGB);

    draw_triangle_2d(image, 70, 70, 100, 150, 220, 120, blue);
    draw_triangle_2d(image, 300, 230, 400, 270, 330, 360, red);

    // spremi sliku 
    image.flip_vertically();
    image.write_tga_file("triangles.tga");

    TGAImage image1(width, height, TGAImage::RGB);

    draw_triangle_2d_gouraurd(image1, 10, 20, blue, 150, 120, red, 200, 170, green);

    image.flip_vertically();
    image.write_tga_file("triangles1.tga");


    TGAImage image2(width, height, TGAImage::RGB);

    draw_triangle(image2, -12, -7, 60, 40, -20, 30, 50, 22, 100, red);

    image.flip_vertically();
    image.write_tga_file("triangles1.tga");
}