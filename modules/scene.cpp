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

Scene::Scene() {
    this->depth = 5;
    this->outputName = "test.png";
}

void Scene::setOutputName(std::string name) {
    this->outputName = name;
}

void Scene::setDepth(int rayDepth) {
    this->depth = rayDepth;
}

void Scene::setViewport(int width, int height) {
    this->width = width;
    this->height = height;
}

void Scene::setCamera(Vector eye, Vector lookAt, Vector up, float fovy) {
    this->camera.setCamera(eye, lookAt, up, this->width, this->height, fovy);
}

void Scene::addObject(GeometricPrimitive obj) {
    this->tracer.addObject(obj);
}

void Scene::render() {
    Sampler sampler(this->width, this->height);
    Film film(this->width, this->height);
    Sample sample;
    Ray ray;
    Vector color;

    while(sampler.getSample(&sample)) {
        this->camera.generateRay(sample, &ray);
        this->tracer.trace(ray, &color);
        film.commit(sample, color);
    }
    film.writeImage(this->outputName);
    film.cleanUp();
}
