#include "./CgColorChangeEvent.h"

Cg::EventType CgColorChangeEvent::getType()
{
    return this->m_type;
}

Cg::Color CgColorChangeEvent::getColor()
{
    return this->m_color;
}

int CgColorChangeEvent::getValue()
{
    return this->m_value;
}

CgBaseEvent *CgColorChangeEvent::clone()
{
    return new CgColorChangeEvent(m_type, m_color, m_value);
}

std::ostream &operator<<(std::ostream &os, const CgColorChangeEvent &e)
{
    os << "CgColorChangeEvent: " << std::endl;
    return os;
}