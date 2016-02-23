/***********************************
 *                                 *
 * Definition of the Scene class   *
 *                                 *
 * Renders the scene               *
 *                                 *
 ***********************************/

#include "../headers/core.hpp"
#include "../headers/mesh.hpp"
#include "../headers/rendering.hpp"

void Scene::addObject(GeometricPrimitive* obj) {
    this->tracer.addObject(obj);
}

void Scene::render(Camera cam, int width, int height) {
    Sampler sampler(width, height);
    Sample sample;
    Ray ray;
    Vector color;
    Film film(width, height);

    while(sampler.getSample(&sample)) {
        cam.generateRay(sample, &ray);
        this->tracer.trace(ray, &color);
        film.commit(sample, color);
    }
    film.writeImage("test.png");
}
