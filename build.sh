#!/bin/bash
RELEASE=true
clear
[ -e main.exec ] && rm main.exec
[ -e main.o ] && rm main.o
[ -e glad.o ] && rm glad.o
[ -e Engine.o ] && rm Engine.o
[ -e Graphics.o ] && rm Graphics.o
[ -e Shader.o ] && rm Shader.o
[ -e Texture.o ] && rm Texture.o
[ -e Camera.o ] && rm Camera.o
[ -e stb_image.o ] && rm stb_image.o
echo "--- Building... ---"
g++ -std=c++11 -c main.cpp glad.c Engine/Camera.cpp Engine/Engine.cpp Engine/Graphics.cpp Engine/Shader.cpp stb_image.cpp Engine/Texture.cpp
g++ main.o glad.o Camera.o Engine.o Graphics.o Shader.o stb_image.o Texture.o -o main.exec -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
test -x main.exec
if [ "$?" -eq 1 ]
then
    echo "--- Build Failed ---"
else
    # clear
    echo "--- Build Complete ---"
    if $RELEASE
    then
        rm -r dist/res
        cp -r res dist/res
        g++ main.o glad.o Camera.o Engine.o Graphics.o Shader.o stb_image.o Texture.o -o dist/main.exec -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
        echo "Release build located in ./dist"
    fi
    [ -e main.o ] && rm main.o
    [ -e glad.o ] && rm glad.o
    [ -e Engine.o ] && rm Engine.o
    [ -e Graphics.o ] && rm Graphics.o
    [ -e Shader.o ] && rm Shader.o
    [ -e stb_image.o ] && rm stb_image.o
    [ -e Texture.o ] && rm Texture.o
    [ -e Camera.o ] && rm Camera.o

    echo "--- Running Program ---"
    mangohud --dlsym ./main.exec
    echo "--- Program Killed ---"

    [ -e main.exec ] && rm main.exec
    
fi
