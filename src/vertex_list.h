#pragma once
#include "mesh.hpp"

Vertex triangle[] = {   Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(-0.5,-0.5), glm::vec3(0.0, 0.0, -1.0)),
                        Vertex(glm::vec3(0,0.5,0), glm::vec2(0,0.5), glm::vec3(0.0, 0.0, -1.0)),
                        Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.5,-0.5), glm::vec3(0.0, 0.0, -1.0))};

Vertex triangle_n[] = {   Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(-0.5,-0.5), glm::vec3(0.0, 0.0, 1.0)),
                        Vertex(glm::vec3(0,0.5,0), glm::vec2(0,0.5), glm::vec3(0.0, 0.0, 1.0)),
                        Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.5,-0.5), glm::vec3(0.0, 0.0, 1.0))};

unsigned int triangle_indices[] = { 0, 1, 2};