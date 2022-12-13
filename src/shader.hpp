#pragma once

#include <string>
#include "GL/glew.h"
#include "transform.hpp"
#include "camera.hpp"

class Shader
{

    public:

        Shader(const std::string& fileName);

        void Bind();
        void Update(const Transform& transform, const Camera& camera, const float& lightIntensity);

        virtual ~ Shader();
    
    protected:
    private:

        enum
        {
            TRANSFORM_U,
            LIGHT_INTENSITY_U,
            
            NUM_UNIFORMS
        };

        static const unsigned int NUM_SHADERS = 2;

        GLuint m_program;
        GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];

};