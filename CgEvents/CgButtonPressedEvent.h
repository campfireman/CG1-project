#ifndef CGButtonPressedEvent_H
#define CGButtonPressedEvent_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>

class CgButtonPressedEvent : public CgBaseEvent
{

public:
    CgButtonPressedEvent(Cg::EventType type, Cg::ButtonType button) : m_type(type), m_button(button){};
    ~CgButtonPressedEvent(){};

    //inherited
    Cg::EventType getType();
    Cg::ButtonType getButton();
    CgBaseEvent *clone();

    friend std::ostream &operator<<(std::ostream &os, const CgButtonPressedEvent &e);

private:
    Cg::EventType m_type;
    Cg::ButtonType m_button;
};
#endif // CGTRACKBALLEVENT_H
