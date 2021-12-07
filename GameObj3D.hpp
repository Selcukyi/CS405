#ifndef GAMEOBJ3D_HPP
#define GAMEOBJ3D_HPP

#include "Model3D.hpp"
#include <gtx/quaternion.hpp>

struct TransformInfo
{
public:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation; // degrees

    glm::mat4 getTransformMatrix()
    {
        return
            glm::translate(glm::mat4(1.0f), this->position)
            * glm::toMat4(glm::quat(rotation))
            * glm::scale(glm::mat4(1.0f), this->scale);
    }
};

class GameObj3D
{
public:
    GameObj3D(Model3D& model);

    void draw();
    void load(Model3D* model);

    void translate(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotate(float x, float y, float z); // degrees

    glm::vec3 position();
    glm::vec3 scale();
    glm::vec3 rotation();
    glm::mat4 getTransform();

private:
    Model3D* model3d = nullptr;
    TransformInfo transformInfo;
};

GameObj3D::GameObj3D(Model3D& model)
{
    this->transformInfo.position = glm::vec3(0);
    this->transformInfo.scale = glm::vec3(1);
    this->transformInfo.rotation = glm::vec3(0);

    this->model3d = &model;
}

void GameObj3D::draw()
{
    this->model3d->bind();
    glDrawElements(GL_TRIANGLES, model3d->getIndicesCount(), GL_UNSIGNED_INT, NULL);
}

void GameObj3D::load(Model3D* model)
{
    delete (this->model3d);
    this->model3d = model3d;
};

void GameObj3D::translate(float x, float y, float z)
{
    this->transformInfo.position = glm::vec3(x, y, z);
}

void GameObj3D::scale(float x, float y, float z)
{
    this->transformInfo.scale = glm::vec3(x, y, z);
}

void GameObj3D::rotate(float x, float y, float z)
{
    this->transformInfo.rotation = glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z));
}

glm::vec3 GameObj3D::position()
{
    return this->transformInfo.position;
}

glm::vec3 GameObj3D::scale()
{
    return this->transformInfo.scale;
}

glm::vec3 GameObj3D::rotation()
{
    return this->transformInfo.rotation;
}

glm::mat4 GameObj3D::getTransform() {
    return this->transformInfo.getTransformMatrix();
}

#endif