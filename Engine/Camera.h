#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
    float FOV;
    float speed;

    glm::vec3 pos;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw, pitch;
    float sensitivity;

    void move(glm::vec3 vel, float deltaTime);

public:
    Camera(float FOV,float yaw, float pitch, glm::vec3 pos, float speed = 2.0f, float sensitivity = 0.1f);
    ~Camera();

    glm::mat4 getViewMatrix();
    void updateCameraDirection();

    void setYaw(float yaw);
    void setPitch(float pitch);
    void setPosition(glm::vec3 pos);

    void moveRight(float deltaTime);
    void moveLeft(float deltaTime);
    void moveUp(float deltaTime);
    void moveDown(float deltaTime);
    void moveForward(float deltaTime);
    void moveBack(float deltaTime);
    void walkForward(float deltaTime);
    void walkBackward(float deltaTime);

    float getYaw();
    float getPitch();
    glm::vec3 getPosition();
    float getSpeed();
    float getSensitivity();
};
