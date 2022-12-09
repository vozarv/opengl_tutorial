#pragma once

#include <stdio.h>
#include <string>
#include <GL/glew.h>

class Texture
{
    public:

        Texture(const std::string& fileName);

        void Bind(unsigned int unit);

        ~Texture();
        
    protected:
    private:

    GLuint m_texture;
};