#pragma once

#include "camera.hpp"

class Player {

    public:
        Player(glm::vec3 pos, float fov, float aspect, float zNear, float zFar);
        void toggleLight() { m_spotlight_switch = ~m_spotlight_switch; }
        bool getSwitch() const { return m_spotlight_switch; }
  
        //TODO getter-setter
        Camera m_camera;


    protected:
    private:
        bool m_spotlight_switch;
};
