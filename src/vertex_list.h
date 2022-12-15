#pragma once
#include "mesh.hpp"

    //TODO új fájl, amiben az alap csúcsok, és a hozzájuk tartozó meshek létre vannak hozva.  
    //A mesh objektumokat egy vektorban el kell tárolni, és a Draw funkciót egy for ciklusban meghívni
    //TODO általánosítás textúrára

Vertex triangle[] = {   Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(-0.5,-0.5), glm::vec3(0.0, 0.0, -1.0)),
                        Vertex(glm::vec3(0,0.5,0), glm::vec2(0,0.5), glm::vec3(0.0, 0.0, -1.0)),
                        Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.5,-0.5), glm::vec3(0.0, 0.0, -1.0))};

Vertex triangle_n[] = {   Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(-0.5,-0.5), glm::vec3(0.0, 0.0, 1.0)),
                        Vertex(glm::vec3(0,0.5,0), glm::vec2(0,0.5), glm::vec3(0.0, 0.0, 1.0)),
                        Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(0.5,-0.5), glm::vec3(0.0, 0.0, 1.0))};

unsigned int triangle_indices[] = { 0, 1, 2};