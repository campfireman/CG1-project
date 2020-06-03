#ifndef CGCheckboxChangedEvent_H
#define CGCheckboxChangedEvent_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>

class CgCheckboxChangedEvent : public CgBaseEvent
{

public:
    CgCheckboxChangedEvent(Cg::EventType type, Cg::CheckboxType checkbox, int state) : m_type(type), m_checkbox(checkbox), m_state(state){};
    ~CgCheckboxChangedEvent(){};

    //inherited
    Cg::EventType getType();
    Cg::CheckboxType getCheckbox();
    int getState();
    CgBaseEvent *clone();

    friend std::ostream &operator<<(std::ostream &os, const CgCheckboxChangedEvent &e);

private:
    Cg::EventType m_type;
    Cg::CheckboxType m_checkbox;
    int m_state;
};
#endif // CGTRACKBALLEVENT_H
