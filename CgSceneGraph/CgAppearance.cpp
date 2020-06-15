#include "CgAppearance.h"

CgAppearance::CgAppearance(){};
CgAppearance::CgAppearance(glm::vec4 base_color, glm::vec4 matAmbientColor, glm::vec4 matDiffuseColor, glm::vec4 matSpecularColor, float shininess) : m_base_color(base_color), m_matAmbientColor(matAmbientColor), m_matDiffuseColor(matDiffuseColor), m_matSpecularColor(matSpecularColor), m_specShininess(shininess){};

glm::vec4 CgAppearance::getBaseColor() const
{
    return m_base_color;
}
void CgAppearance::setBaseColor(glm::vec4 color)
{
    m_base_color = color;
}
glm::vec4 CgAppearance::getMatAmbientColor() const
{
    return m_matAmbientColor;
}
glm::vec4 CgAppearance::getMatDiffuseColor() const
{
    return m_matDiffuseColor;
}
glm::vec4 CgAppearance::getMatSpecularColor() const
{
    return m_matSpecularColor;
}

float CgAppearance::getSpecShininess() const
{
    return m_specShininess;
}