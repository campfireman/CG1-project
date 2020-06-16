#ifndef CGTranslationChangedEvent_H
#define CGTranslationChangedEvent_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>

class CgTranslationChangedEvent : public CgBaseEvent
{

public:
    CgTranslationChangedEvent(Cg::EventType type, Cg::Axis axis, int value) : m_type(type), m_axis(axis), m_value(value){};
    ~CgTranslationChangedEvent(){};

    //inherited
    Cg::EventType getType();
    Cg::Axis getAxis();
    int getValue();
    CgBaseEvent *clone();

    friend std::ostream &operator<<(std::ostream &os, const CgTranslationChangedEvent &e);

private:
    Cg::EventType m_type;
    Cg::Axis m_axis;
    int m_value;
};
#endif // CGTRACKBALLEVENT_H
