#include "Shader.h"

unsigned int Shader::compileShader(GLenum shaderType, const char *shaderSrc)
{
    unsigned int shader;
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);

    //Error Check
    int shaderSuccess;
    char error[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderSuccess);

    if(!shaderSuccess){
        glGetShaderInfoLog(shader, 512, NULL, error);
        std::cout << "Shader Compilation Failed: \n" << error << std::endl;
        return -1;
    }


    return shader;
}

unsigned int Shader::linkProgram()
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, this->vertexShaderID);
    glAttachShader(shaderProgram, this->fragmentShaderID);
    glLinkProgram(shaderProgram);

    //Error Check
    int shaderSuccess;
    char error[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderSuccess);

    if(!shaderSuccess){
        glGetProgramInfoLog(shaderProgram, 512, NULL, error);
        std::cout << "Program Link Failed: \n" << error << std::endl;
        return -1;
    }

    return shaderProgram;
}

std::string Shader::retrieveShaderSource(const char* path)
{
    std::string code;
    std::ifstream shaderFile;

    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try{
        shaderFile.open(path);
        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        code = shaderStream.str();
    }
    catch(std::ifstream::failure err){
        std::cout << "Could not read shader file: `" << path << "`" << std::endl;
    }

    return code;
}

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    //------ Vertex Shader Compilation----
    this->vertexShaderID = compileShader(GL_VERTEX_SHADER, retrieveShaderSource(vertexPath).c_str());
    //------ Fragment Shader Compilation----
    this->fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, retrieveShaderSource(fragmentPath).c_str());

    //--- Create Shader Program
    this->programID = linkProgram();
}

Shader::~Shader()
{
}

void Shader::useProgram()
{
    glUseProgram(this->programID);
}

int Shader::setUniformFloat4(const char *name, float x, float y, float z, float w)
{
    int location = glGetUniformLocation(this->programID, name);
    glUniform4f(location, x, y, z, w);

    return location;
}

int Shader::setUniformFloat3(const char *name, float x, float y, float z)
{
    int location = glGetUniformLocation(this->programID, name);
    glUniform3f(location, x, y, z);

    return location;
}

int Shader::setUniformFloat2(const char *name, float x, float y)
{
    int location = glGetUniformLocation(this->programID, name);
    glUniform2f(location, x, y);

    return location;
}

int Shader::setUniformFloat1(const char *name, float x)
{
    int location = glGetUniformLocation(this->programID, name);
    glUniform1f(location, x);

    return location;
}

int Shader::setUnformInt1(const char *name, int x)
{
    int location = glGetUniformLocation(this->programID, name);
    glUniform1i(location, x);

    return location;
}

int Shader::setUnformInt2(const char *name, int x, int y)
{
    int location = glGetUniformLocation(this->programID, name);
    glUniform2i(location, x, y);

    return location;
}

int Shader::setUnformInt3(const char *name, int x, int y, int z)
{
    int location = glGetUniformLocation(this->programID, name);
    glUniform3i(location, x, y, z);

    return location;
}

int Shader::setUnformInt4(const char *name, int x, int y, int z, int w)
{
    int location = glGetUniformLocation(this->programID, name);
    glUniform4i(location, x, y, z, w);

    return location;
}

int Shader::setUnformMat4(const char *name, glm::mat4 matrix)
{
    int location = glGetUniformLocation(this->programID, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

    return location;
}
