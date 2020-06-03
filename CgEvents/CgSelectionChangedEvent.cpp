#include "./CgSelectionChangedEvent.h"

Cg::EventType CgSelectionChangedEvent::getType()
{
    return this->m_type;
}

Cg::SelectionType CgSelectionChangedEvent::getSelection()
{
    return this->m_selection;
}

int CgSelectionChangedEvent::getValue()
{
    return this->m_value;
}

CgBaseEvent *CgSelectionChangedEvent::clone()
{
    return new CgSelectionChangedEvent(m_type, m_selection, m_value);
}

std::ostream &operator<<(std::ostream &os, const CgSelectionChangedEvent &e)
{
    os << "CgSelectionChangedEvent: " << std::endl;
    return os;
}