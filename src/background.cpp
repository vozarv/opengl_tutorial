#include "background.hpp"

std::vector<std::string> faces = {
    "./res/textures/skybox/right.jpg", "./res/textures/skybox/left.jpg",
    "./res/textures/skybox/top.jpg",   "./res/textures/skybox/bottom.jpg",
    "./res/textures/skybox/front.jpg", "./res/textures/skybox/back.jpg"};

//TODO source folder as input
Background::Background() {


  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  int width, height, nrChannels;
  for (unsigned int i = 0; i < faces.size(); i++) {
    unsigned char *data =
        stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height,
                   0, GL_RGB, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    } else {
      std::cout << "Cubemap tex failed to load at path: " << faces[i]
                << std::endl;
      stbi_image_free(data);
    }
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void Background::Draw(Shader& shader, Player& player) {

    Mesh mesh("./res/objects/cube.obj");
    glDepthMask(GL_FALSE);
    shader.Bind();
    shader.Update(player);
    mesh.Draw(0);
    glDepthMask(GL_TRUE);
}