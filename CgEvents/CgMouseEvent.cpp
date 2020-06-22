#include "CgMouseEvent.h"

CgMouseEvent::CgMouseEvent(Cg::EventType type, glm::vec2 localPos, Cg::MouseButtons button)
{
    m_type = type;
    m_localPos = localPos;
    m_button = button;
}
CgMouseEvent::CgMouseEvent(Cg::EventType type, glm::vec2 localPos, glm::vec2 windowPos, glm::vec2 screenPos, glm::vec2 windowSize, Cg::MouseButtons button) : CgMouseEvent(type, localPos, button)
{
    m_windowSize = windowSize;
    m_windowPos = windowPos;
    m_screenPos = screenPos;
}

CgMouseEvent::~CgMouseEvent()
{
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

glm::vec2 CgMouseEvent::getWindowPos() const
{
    return m_windowPos;
}
glm::vec2 CgMouseEvent::getWindowSize() const
{
    return m_windowSize;
}
CgBaseEvent *CgMouseEvent::clone()
{
    return new CgMouseEvent(m_type, m_localPos, m_button);
}

std::ostream &operator<<(std::ostream &os, const CgMouseEvent &e)
{
    os << "Mouse-Event of Type: " << e.m_type << ", LocalPos:(" << e.m_localPos.x << "," << e.m_localPos.y << "), Button: " << e.m_button;
    return os;
}
