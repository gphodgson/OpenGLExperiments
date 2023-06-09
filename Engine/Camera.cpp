#include "Camera.h"

Camera::Camera(float FOV, float yaw, float pitch, glm::vec3 pos, float speed, float sensitivity)
{
    this->FOV = FOV;
    this->speed = speed;
    this->sensitivity = sensitivity;
    this->setYaw(yaw);
    this->setPitch(pitch);
    this->setPosition(pos);
}

void Camera::move(glm::vec3 vel, float delaTime)
{
    this->pos += vel * (this->speed * delaTime);
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(this->pos, this->pos + this->front, this->up);
}

void Camera::setYaw(float yaw)
{
    this->yaw = yaw;
}

void Camera::setPitch(float pitch)
{
    this->pitch = pitch;

    if(this->pitch > 89.0f)
        this->pitch = 89.0f;
    if(this->pitch < -89.0f)
        this->pitch = -89.0f;
}

void Camera::setPosition(glm::vec3 pos)
{
    this->pos = pos;
}

float Camera::getYaw()
{
    return this->yaw;
}

void Camera::moveRight(float deltaTime)
{
    glm::vec3 right = glm::normalize(glm::cross(up, this->front));
    this->move(-right, deltaTime);
}

void Camera::moveLeft(float deltaTime)
{
    glm::vec3 right = glm::normalize(glm::cross(up, this->front));
    this->move(right, deltaTime);
}

void Camera::moveUp(float deltaTime)
{
    glm::vec3 right = glm::normalize(glm::cross(up, this->front));
    glm::vec3 up = glm::cross(this->front, right);
    this->move(up, deltaTime);
}

void Camera::moveDown(float deltaTime)
{
    glm::vec3 right = glm::normalize(glm::cross(up, this->front));
    glm::vec3 up = glm::cross(this->front, right);
    this->move(-up, deltaTime);
}

void Camera::moveForward(float deltaTime){
    this->move(this->front, deltaTime);
}

void Camera::moveBack(float deltaTime)
{
    this->move(-this->front, deltaTime);
}

void Camera::walkForward(float deltaTime)
{
    glm::vec3 movement(this->front.x, 0.0f, this->front.z);
    this->move(movement, deltaTime);
}

void Camera::walkBackward(float deltaTime)
{
    glm::vec3 movement(this->front.x, 0.0f, this->front.z);
    this->move(-movement, deltaTime);
}

float Camera::getSpeed()
{
    return this->speed;
}

float Camera::getPitch(){
    return this->pitch;
}

glm::vec3 Camera::getPosition(){
    return this->pos;
}

float Camera::getSensitivity(){
    return this->sensitivity;
}

void Camera::updateCameraDirection()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(direction);
}
