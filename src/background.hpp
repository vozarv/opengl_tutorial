#pragma once

#include "obj_loader.hpp"
#include "shader.h"
#include "transform.hpp"
#include "player.hpp"
#include "stb_image.h"
#include <GL/glew.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "model.h"



class Background {

public:
  Background(const std::string path);
  void Draw(Shader& shader, Player& player);

  unsigned int textureID;

protected:
private:
  
  //unsigned int skyboxVAO, skyboxVBO;
};
