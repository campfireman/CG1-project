#include "./CgSORChangedEvent.h"

Cg::EventType CgSORChangedEvent::getType()
{
    return this->m_type;
}

Cg::SOROptionType CgSORChangedEvent::getOption()
{
    return this->m_option;
}

int CgSORChangedEvent::getValue()
{
    return this->m_value;
}

CgBaseEvent *CgSORChangedEvent::clone()
{
    return new CgSORChangedEvent(m_type, m_option, m_value);
}

std::ostream &operator<<(std::ostream &os, const CgSORChangedEvent &e)
{
    os << "CgSORChangedEvent: " << std::endl;
    return os;
}