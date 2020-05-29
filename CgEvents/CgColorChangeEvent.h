#ifndef CGCOLORCHANGEEVENT_H
#define CGCOLORCHANGEEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>

class CgColorChangeEvent : public CgBaseEvent
{

public:
    CgColorChangeEvent(Cg::EventType type, Cg::Color color, int value) : m_type(type), m_color(color), m_value(value){};
    ~CgColorChangeEvent(){};

    //inherited
    Cg::EventType getType();
    Cg::Color getColor();
    int getValue();
    CgBaseEvent *clone();

    friend std::ostream &operator<<(std::ostream &os, const CgColorChangeEvent &e);

private:
    Cg::EventType m_type;
    Cg::Color m_color;
    int m_value;
};
#endif // CGTRACKBALLEVENT_H
