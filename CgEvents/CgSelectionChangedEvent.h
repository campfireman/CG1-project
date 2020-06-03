#ifndef CGSelectionChangedEvent_H
#define CGSelectionChangedEvent_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>

class CgSelectionChangedEvent : public CgBaseEvent
{

public:
    CgSelectionChangedEvent(Cg::EventType type, Cg::SelectionType selection, int value) : m_type(type), m_selection(selection), m_value(value){};
    ~CgSelectionChangedEvent(){};

    //inherited
    Cg::EventType getType();
    Cg::SelectionType getSelection();
    int getValue();
    CgBaseEvent *clone();

    friend std::ostream &operator<<(std::ostream &os, const CgSelectionChangedEvent &e);

private:
    Cg::EventType m_type;
    Cg::SelectionType m_selection;
    int m_value;
};
#endif // CGTRACKBALLEVENT_H
