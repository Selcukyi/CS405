#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm.hpp>
#include <gtx/quaternion.hpp>
#include "gtc/constants.hpp"
#include "gtx/rotate_vector.hpp"
#include "gtx/transform.hpp"
#include "common.hpp"
#include "gtc/type_ptr.hpp"

class Camera
{
public:
    static glm::vec3 position;
    static glm::vec3 rotation; // (x degrees, y degrees, z degrees)

    static void moveFront(float);
    static void moveUp(float);
    static void moveRight(float);

    static glm::mat4 getViewMatrix();
    static glm::mat4 getProjMatrix();
private:
    static glm::vec3 front, up, right;
};

glm::vec3 Camera::position = glm::vec3(0, 0, 3);

glm::vec3 Camera::rotation = glm::vec3(0, 0, 0);

glm::vec3 Camera::front = glm::vec3(0, 0, -1);

glm::vec3 Camera::up = glm::vec3(0, 1, 0);

void Camera::moveFront(float num) {
    Camera::position += front * num;
    Camera::position.z = 0;
}

void Camera::moveUp(float num) {
    Camera::position += up * num;
}

void Camera::moveRight(float num) {
    Camera::position += glm::cross(front, up) * num;
}

glm::mat4 Camera::getViewMatrix()
{
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 front = glm::vec3(0, 0, -1);

    glm::vec4 u4 = glm::toMat4(glm::quat(glm::radians(rotation))) * glm::vec4(up, 1);
    glm::vec4 f4 = glm::toMat4(glm::quat(glm::radians(rotation))) * glm::vec4(front, 1);

    Camera::up = glm::vec3(u4.x, u4.y, u4.z);
    Camera::front = glm::vec3(f4.x, f4.y, f4.z);

    return glm::lookAt(position, position + Camera::front, Camera::up);
}

glm::mat4 Camera::getProjMatrix()
{
    return glm::perspective(glm::radians(45.f), 1.f, 0.1f, 1000.f);
}

#endif