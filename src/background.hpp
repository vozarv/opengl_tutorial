#pragma once

#include "obj_loader.hpp"
#include "shader.hpp"
#include "transform.hpp"
#include "player.hpp"
#include "stb_image.h"
#include <GL/glew.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "mesh.hpp"



class Background {

public:
  Background();
  void Draw(Shader& shader, Player& player);

protected:
private:
  unsigned int textureID;
  //unsigned int skyboxVAO, skyboxVBO;
};
