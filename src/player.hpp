#pragma once

#include "camera.hpp"

class Player {

    public:
        Player(glm::vec3 pos, float fov, float aspect, float zNear, float zFar);
        void setLight() { m_spotlight_switch = true; }
        void resetLight() { m_spotlight_switch = false; }
        bool getSwitch() const { return m_spotlight_switch; }
  
        //TODO getter-setter
        Camera m_camera;


    protected:
    private:
        bool m_spotlight_switch;
};
