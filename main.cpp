#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Engine/Engine.h"
#include "Engine/Shader.h"
#include "Engine/Texture.hpp"
#include "Engine/Camera.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

GLsizei width = 2560;
GLsizei height = 1440;

#define WIREFRAME false
#define FLY false

float mixLevel = 0.2f;

float rotation = 0.0f;
float speed = 10.0f;
double lastTime = 0.0;

float fov = 45.0f;

float floorLevel = -1.0f;
float playerHeight = 1.0f;

glm::vec3 offset = {0.0f,0.0f, 1.0f};
float movementSpeed = 2.0f;

Camera camera = Camera(
    45.0f,                      // FOV
    -90.0f,                     // Starting yaw
    0.0f,                       // Starting pitch
    glm::vec3{0.0f, 0.0f, 3.0f},// Starting Position
    2.0f,                       // Starting Speed (default 2.0f)
    0.1f                        // Starting Sens (default 0.1f)
);

bool firstMouse = true;
float lastX = width/2, lastY = height/2;


unsigned int createTriangleVertexArray(float vertices[], int vertexSize, unsigned int indices[], int indexSize);

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0, width, height);
}

void processInput(GLFWwindow *window, double deltaTime){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if(glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        if(FLY) camera.moveForward(deltaTime);
        else camera.walkForward(deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        if(FLY) camera.moveBack(deltaTime);
        else camera.walkBackward(deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera.moveRight(deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera.moveLeft(deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        camera.moveUp(deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        camera.moveDown(deltaTime);

        glm::vec3 cameraPos = camera.getPosition();
        if(cameraPos.y < floorLevel + playerHeight){
            camera.setPosition(glm::vec3{cameraPos.x, floorLevel + playerHeight, cameraPos.z});
        }
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main(){

    en::Color clearColor;
    clearColor.r = 0.2f;
    clearColor.g = 0.3f;
    clearColor.b = 0.3f;

    float floorVertices[] = {
        100.5f, 100.5f, 0.0f, 0.0f, 0.0f, // top right
        100.5f, -100.5f, 0.0f, 100.0f, 0.0f, // bottom right
        -100.5f, -100.5f, 0.0f, 100.0f, 100.0f, // bottom left
        -100.5f, 100.5f, 0.0f, 0.0f, 100.0f  // top left
    };

    float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,

     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,

     0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3(1.5f, -2.2f, -2.5f),
        glm::vec3(3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(5.7f, 3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f, 2.0f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3(7.3f, 1.0f, -1.5f)
    };

    unsigned int indices[] = { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    glfwInit();

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //FullScreen
    GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL Tutorial", monitor, NULL);
    //Windowed
    // GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL Tutorial", NULL, NULL);
    
    if(window == NULL){
        std::cout << "could not create window!" << std::endl; 
        return -1;
    }

    if(window == NULL){
        std::cout << "Failed to create GLFW Window :(" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval( 0 );
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glViewport(0,0, width, height);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    //---------- GL Code -----------------

    glEnable(GL_DEPTH_TEST);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f),glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
    // glm::mat4 projMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);



    Shader shader = Shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

    if(WIREFRAME) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //--- Texture
    Texture texture1 = Texture("res/container.jpg", GL_RGB, GL_REPEAT, GL_LINEAR);
    Texture texture2 = Texture("res/awesomeface.png", GL_RGBA, GL_REPEAT, GL_LINEAR);
    Texture grassTexture = Texture("res/grass.jpg", GL_RGB, GL_REPEAT, GL_LINEAR);
    Texture redTexture = Texture("res/red.png", GL_RGBA, GL_REPEAT, GL_LINEAR);

    unsigned int VAO1 = createTriangleVertexArray(vertices, sizeof(vertices), indices, sizeof(indices));
    unsigned int floorVAO = createTriangleVertexArray(floorVertices, sizeof(floorVertices), indices, sizeof(indices));
    
    shader.useProgram(); // don’t forget to activate the shader first!
    shader.setUnformInt1("texture1", 0);
    shader.setUnformInt1("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        double deltaTime = (currentTime - lastTime);
        lastTime = currentTime;

        processInput(window, deltaTime);

        rotation += speed * deltaTime;

        glm::mat4 view = camera.getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        redTexture.bind();
        glActiveTexture(GL_TEXTURE1);
        texture2.bind();

        shader.useProgram();
        shader.setUnformMat4("model", model);
        shader.setUnformMat4("view", view);
        shader.setUnformMat4("projection", projection);
        glBindVertexArray(VAO1);
        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle + rotation),
            glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setUnformMat4("model", model);
            // glEnable(GL_CULL_FACE); 
            // glCullFace(GL_BACK);  
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glActiveTexture(GL_TEXTURE0);
        grassTexture.bind();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3{0.0f, -1.0f, 0.0f});
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3{1.0f, 0.0f, 0.0f});
        shader.setUnformMat4("model", model);
        glBindVertexArray(floorVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

unsigned int createTriangleVertexArray(float vertices[], int vertexSize, unsigned int indices[], int indexSize)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    return VAO;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed: y ranges bottom to top
    lastX = xpos;
    lastY = ypos;

    xoffset *= camera.getSensitivity();
    yoffset *= camera.getSensitivity();

    camera.setYaw(camera.getYaw() + xoffset);
    camera.setPitch(camera.getPitch() + yoffset);

    camera.updateCameraDirection();
}
