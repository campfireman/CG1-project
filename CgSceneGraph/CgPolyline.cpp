#include "CgPolyline.h"

const std::vector<glm::vec3> &CgPolyline::getVertices() const
{
    return this->m_vertices;
}

glm::vec3 CgPolyline::getColor() const
{
    return this->m_color;
}

unsigned int CgPolyline::getLineWidth() const
{
    return this->m_line_width;
}
