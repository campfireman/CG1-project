#ifndef CG_APPEARANCE
#define CG_APPEARANCE

#include <glm/glm.hpp>

class CgAppearance
{
private:
    glm::vec4 m_base_color;
    glm::vec4 m_matAmbientColor;
    glm::vec4 m_matDiffuseColor;
    glm::vec4 m_matSpecularColor;
    float m_specShininess;

public:
    CgAppearance();
    CgAppearance(glm::vec4 base_color, glm::vec4 matAmbientColor, glm::vec4 matDiffuseColor, glm::vec4 matSpecularColor, float shininess);

    glm::vec4 getBaseColor() const;
    void setBaseColor(glm::vec4 color);
    glm::vec4 getMatAmbientColor() const;
    glm::vec4 getMatDiffuseColor() const;
    glm::vec4 getMatSpecularColor() const;
    float getSpecShininess() const;
};
#endif