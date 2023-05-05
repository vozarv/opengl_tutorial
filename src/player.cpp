#include "player.hpp"



Player::Player(glm::vec3 pos, float fov, float aspect, float zNear, float zFar) : 
    m_camera(pos, fov, aspect, zNear, zFar),
    m_spotlight_switch(false)
{
    
}