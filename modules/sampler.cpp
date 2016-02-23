/**************************************************
 *                                                *
 * Definition of the Sampler class                *
 *                                                *
 * Produces samples for the ray generation method *
 *                                                *
 **************************************************/

#include "../headers/core.hpp"
#include "../headers/rendering.hpp"

Sampler::Sampler(int width, int height) {
    this->screenSize = Vector(width, height, 0);
    this->currentPixel = Vector(0, 0, 0);
}

// yields the current sample position (single sample per pixel)
bool Sampler::getSample(Sample* smp) {
    smp->x = this->currentPixel.x + 0.5;
    smp->y = this->currentPixel.y + 0.5;
    if(smp->x > this->screenSize.x) {
        // sample left the screen, go to next line
        this->currentPixel.x = 0;
        this->currentPixel.y += 1;
        smp->x = 0.5;
        smp->y = this->currentPixel.y + 0.5;
        if(smp->y > this->screenSize.y)
            // the screen is over, returns false
            return false;
    }
    this->currentPixel.x++;
    return true;
}
