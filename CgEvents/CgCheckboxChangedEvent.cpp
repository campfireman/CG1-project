#include "./CgCheckboxChangedEvent.h"

Cg::EventType CgCheckboxChangedEvent::getType()
{
    return this->m_type;
}

Cg::CheckboxType CgCheckboxChangedEvent::getCheckbox()
{
    return this->m_checkbox;
}

int CgCheckboxChangedEvent::getState()
{
    return this->m_state;
}

CgBaseEvent *CgCheckboxChangedEvent::clone()
{
    return new CgCheckboxChangedEvent(m_type, m_checkbox, m_state);
}

std::ostream &operator<<(std::ostream &os, const CgCheckboxChangedEvent &e)
{
    os << "CgCheckboxChangedEvent: " << std::endl;
    return os;
}