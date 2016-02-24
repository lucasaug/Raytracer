/***************************************************
 *                                                 *
 * Definition of the Film class                    *
 *                                                 *
 * Writes to the image and keeps track of pixels   *
 *                                                 *
 ***************************************************/

#include <cmath>

#include "../include/FreeImage.h"

#include "../headers/core.hpp"
#include "../headers/mesh.hpp"
#include "../headers/rendering.hpp"

Film::Film(int width, int height) {
    this->width  = width;
    this->height = height;
    this->pixels = new BYTE[width * height * 3];
}

void Film::commit(Sample& sample, Vector& color) {
    int position = ((floor(sample.y) * this->width) + floor(sample.x));
    this->pixels[(3*position) + 0] = color.z;
    this->pixels[(3*position) + 1] = color.y;
    this->pixels[(3*position) + 2] = color.x;
}
void Film::writeImage(std::string name) {
    FreeImage_Initialise();
    FIBITMAP *img = FreeImage_ConvertFromRawBits(this->pixels, this->width, this->height, this->width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
    FreeImage_Save(FIF_PNG, img, name.c_str(), 0);
    FreeImage_DeInitialise();
}
void Film::cleanUp() {
    delete[] this->pixels;
}
