#include "texture.hpp"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string &fileName) {
  int width, height, numComponents;
  unsigned char *imageData =
      stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  if (imageData == NULL) {
    std::cerr << "Texture loading failed for texture: " << fileName
              << std::endl;
  }

  // Solid textures
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // Alpha textures - prevent border overlapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);

  // For specular maps, the 3rd parameter should be GL_RGBA
  glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, imageData);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(imageData);
}

Texture::~Texture() { glDeleteTextures(1, &m_texture); }

void Texture::Bind(unsigned int unit) {
  assert(unit >= 0 && unit <= 31);
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, m_texture);
}