#ifndef CGMOUSEEVENT
#define CGMOUSEEVENT

#include "../CgBase/CgBaseEvent.h"
#include "glm/glm.hpp"
#include <iostream>

class CgMouseEvent : public CgBaseEvent
{
public:
    CgMouseEvent(Cg::EventType type, glm::vec2 localPos, Cg::MouseButtons button);
    CgMouseEvent(Cg::EventType type, glm::vec2 localPos, glm::vec2 windowPos, glm::vec2 screenPos, glm::vec2 windowSize, Cg::MouseButtons button);
    ~CgMouseEvent();

    Cg::EventType getType();
    CgBaseEvent *clone();

    Cg::MouseButtons button() const;
    int x() const;
    int y() const;

    int getWindowPosX() const;
    int getWindowPosY() const;

    glm::vec2 getScreenPos() const;
    int getWindowSizeX() const;
    int getWindowSizeY() const;

    friend std::ostream &operator<<(std::ostream &os, const CgMouseEvent &e);

private:
    Cg::EventType m_type;
    glm::vec2 m_localPos;
    glm::vec2 m_windowPos;
    glm::vec2 m_windowSize;
    glm::vec2 m_screenPos;
    Cg::MouseButtons m_button;
    Cg::KeyboardModifiers m_mod;
};

#endif // CGMOUSEEVENT
