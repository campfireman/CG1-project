#ifndef CGPOLYLINE_H
#define CGPOLYLINE_H

#include <vector>
#include <glm/glm.hpp>
#include "../CgBase/CgBasePolyline.h"
#include "../CgBase/CgEnums.h"
class CgPolyline : public CgBasePolyline
{
public:
    CgPolyline(unsigned int id, std::vector<glm::vec3> vertices, glm::vec3 color, unsigned int line_width) : m_id(id), m_vertices(vertices), m_color(color), m_line_width(line_width){};
    Cg::ObjectType getType() const;
    unsigned int getID() const;
    const std::vector<glm::vec3> &getVertices() const;
    glm::vec3 getColor() const;
    unsigned int getLineWidth() const;

private:
    std::vector<glm::vec3> m_vertices;
    glm::vec3 m_color;
    unsigned int m_line_width;
    const unsigned int m_id;
};

inline unsigned int CgPolyline::getID() const { return m_id; }
inline Cg::ObjectType CgPolyline::getType() const { return Cg::Polyline; }
#endif