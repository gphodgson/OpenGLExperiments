#include "../glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
    unsigned int compileShader(GLenum shaderType, const char *shaderSrc);
    unsigned int linkProgram();
    std::string retrieveShaderSource(const char* path);
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    unsigned int programID;
    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;

    void useProgram();
    int setUniformFloat4(const char* name, float x, float y, float z, float w);
    int setUniformFloat3(const char* name, float x, float y, float z);
    int setUniformFloat2(const char* name, float x, float y);
    int setUniformFloat1(const char* name, float x);

    int setUnformInt1(const char* name, int x);
    int setUnformInt2(const char* name, int x, int y);
    int setUnformInt3(const char* name, int x, int y, int z);
    int setUnformInt4(const char* name, int x, int y, int z, int w);

    int setUnformMat4(const char* name, glm::mat4 matrix);
};
