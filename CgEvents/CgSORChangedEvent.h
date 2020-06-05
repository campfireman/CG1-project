#ifndef CGSORChangedEvent_H
#define CGSORChangedEvent_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>

class CgSORChangedEvent : public CgBaseEvent
{

public:
    CgSORChangedEvent(Cg::EventType type, Cg::SOROptionType option, int value) : m_type(type), m_option(option), m_value(value){};
    ~CgSORChangedEvent(){};

    //inherited
    Cg::EventType getType();
    Cg::SOROptionType getOption();
    int getValue();
    CgBaseEvent *clone();

    friend std::ostream &operator<<(std::ostream &os, const CgSORChangedEvent &e);

private:
    Cg::EventType m_type;
    Cg::SOROptionType m_option;
    int m_value;
};
#endif // CGTRACKBALLEVENT_H
