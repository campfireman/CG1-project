#include "./CgButtonPressedEvent.h"

Cg::EventType CgButtonPressedEvent::getType()
{
    return this->m_type;
}

Cg::ButtonType CgButtonPressedEvent::getButton()
{
    return this->m_button;
}

CgBaseEvent *CgButtonPressedEvent::clone()
{
    return new CgButtonPressedEvent(m_type, m_button);
}

std::ostream &operator<<(std::ostream &os, const CgButtonPressedEvent &e)
{
    os << "CgButtonPressedEvent: " << std::endl;
    return os;
}