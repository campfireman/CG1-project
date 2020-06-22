#include "CgMouseEvent.h"
#include <iostream>
CgMouseEvent::CgMouseEvent(Cg::EventType type, glm::vec2 localPos, Cg::MouseButtons button)
{
    m_type = type;
    m_localPos = localPos;
    m_button = button;
}
CgMouseEvent::CgMouseEvent(Cg::EventType type, glm::vec2 localPos, glm::vec2 windowPos, glm::vec2 screenPos, glm::vec2 windowSize, Cg::MouseButtons button)
{
    m_type = type;
    m_localPos = localPos;
    m_button = button;
    m_windowSize = windowSize;
    m_windowPos = windowPos;
    m_screenPos = screenPos;
}

CgMouseEvent::~CgMouseEvent()
{
}
CgBaseEvent *CgMouseEvent::clone()
{
    return new CgMouseEvent(m_type, m_localPos, m_windowPos, m_screenPos, m_windowSize, m_button);
}

Cg::EventType CgMouseEvent::getType()
{
    return m_type;
}
Cg::MouseButtons CgMouseEvent::button() const
{
    return m_button;
}

int CgMouseEvent::x() const
{
    return m_localPos.x;
}
int CgMouseEvent::y() const
{
    return m_localPos.y;
}

glm::vec2 CgMouseEvent::getScreenPos() const
{
    return m_screenPos;
}

int CgMouseEvent::getWindowPosX() const
{
    return m_windowPos.x;
}
int CgMouseEvent::getWindowPosY() const
{
    return m_windowPos.y;
}
int CgMouseEvent::getWindowSizeX() const
{
    return m_windowSize.x;
}
int CgMouseEvent::getWindowSizeY() const
{
    return m_windowSize.y;
}

std::ostream &operator<<(std::ostream &os, const CgMouseEvent &e)
{
    os << "Mouse-Event of Type: " << e.m_type << ", LocalPos:(" << e.m_localPos.x << "," << e.m_localPos.y << "), Button: " << e.m_button;
    return os;
}
