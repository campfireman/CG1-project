#include "./CgTranslationChangedEvent.h"

Cg::EventType CgTranslationChangedEvent::getType()
{
    return this->m_type;
}

Cg::Axis CgTranslationChangedEvent::getAxis()
{
    return this->m_axis;
}

int CgTranslationChangedEvent::getValue()
{
    return this->m_value;
}

CgBaseEvent *CgTranslationChangedEvent::clone()
{
    return new CgTranslationChangedEvent(m_type, m_axis, m_value);
}

std::ostream &operator<<(std::ostream &os, const CgTranslationChangedEvent &e)
{
    os << "CgTranslationChangedEvent: " << std::endl;
    return os;
}