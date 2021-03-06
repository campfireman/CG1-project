#include "CgScenegraphNode.h"
#include <algorithm>
#include <iostream>
#include "CgBase/CgBaseTriangleMesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

CgScenegraphNode::CgScenegraphNode()
{
}

CgScenegraphNode::CgScenegraphNode(std::vector<CgBaseRenderableObject *> objects, CgAppearance appearance)
{
    m_objects = objects;
    m_appearance = appearance;
    m_parent = NULL;
    m_children = std::vector<CgScenegraphNode *>{};
    is_selectable = true;
    int count = 0;
    glm::vec3 sum = glm::vec3(0.0, 0.0, 0.0);
    for (auto &object : objects)
    {
        auto obj = dynamic_cast<CgBaseTriangleMesh *>(object);
        if (obj != NULL)
        {
            for (auto &vertex : obj->getVertices())
            {
                count++;
                sum += vertex;
            }
        }
    }
    m_centroid = sum / (float)count;

    m_current_transformation = glm::mat4(1.);
    m_unique_transformation = glm::mat4(1.);
}
CgScenegraphNode::CgScenegraphNode(std::vector<CgBaseRenderableObject *> objects, glm::mat4 current_transformation, CgAppearance appearance) : CgScenegraphNode(objects, appearance)
{

    m_current_transformation = current_transformation;
}
CgScenegraphNode::CgScenegraphNode(std::vector<CgBaseRenderableObject *> objects, glm::mat4 current_transformation, CgAppearance appearance, CgScenegraphNode *parent) : CgScenegraphNode(objects, current_transformation, appearance)
{
    parent = parent;
}
CgScenegraphNode::CgScenegraphNode(std::vector<CgBaseRenderableObject *> objects, glm::mat4 current_transformation, CgAppearance appearance, CgScenegraphNode *parent, std::vector<CgScenegraphNode *> children) : CgScenegraphNode(objects, current_transformation, appearance, parent)
{
    m_children = children;
}

std::vector<CgBaseRenderableObject *> &CgScenegraphNode::getObjects()
{
    return m_objects;
}

glm::vec3 CgScenegraphNode::getCentroid() const
{
    return m_centroid;
}

void CgScenegraphNode::addObject(CgBaseRenderableObject *object)
{
    m_objects.push_back(object);
}
void CgScenegraphNode::setObjects(std::vector<CgBaseRenderableObject *> objects)
{
    m_objects = objects;
}
glm::mat4 CgScenegraphNode::getCurrentTransformation() const
{
    return m_current_transformation;
}
void CgScenegraphNode::setCurrentTransformation(glm::mat4 transformation)
{
    m_current_transformation = transformation;
}

void CgScenegraphNode::transform(glm::mat4 transformation)
{
    m_current_transformation *= transformation;
}

glm::mat4 CgScenegraphNode::getUniqueTransformation() const
{
    return m_unique_transformation;
}
void CgScenegraphNode::setUniqueTransformation(glm::mat4 transformation)
{
    m_unique_transformation = transformation;
}

CgAppearance CgScenegraphNode::getAppearance() const
{
    return m_appearance;
}
void CgScenegraphNode::setAppearance(CgAppearance appearance)
{
    m_appearance = appearance;
}
void CgScenegraphNode::setColor(glm::vec4 color)
{
    m_appearance.setBaseColor(color);
}
CgScenegraphNode *CgScenegraphNode::getParent() const
{
    return m_parent;
}
void CgScenegraphNode::setParent(CgScenegraphNode *parent)
{
    m_parent = parent;
}
std::vector<CgScenegraphNode *> CgScenegraphNode::getChildren() const
{
    return m_children;
}
void CgScenegraphNode::setChildren(std::vector<CgScenegraphNode *> children)
{
    m_children = children;
}

void CgScenegraphNode::addChild(CgScenegraphNode *child)
{
    m_children.push_back(child);
    child->setParent(this);
}
void CgScenegraphNode::removeChild(CgScenegraphNode *child)
{
    m_children.erase(std::find(m_children.begin(), m_children.end(), child));
}
void CgScenegraphNode::render(CgBaseRenderer *renderer, glm::mat4 &transformation)
{
    auto mv = transformation * m_unique_transformation;
    renderer->setUniformValue("modelviewMatrix", mv);
    renderer->setUniformValue("normalMatrix", glm::transpose(glm::inverse(glm::mat3(mv))));

    renderer->setUniformValue("mycolor", m_appearance.getBaseColor());

    renderer->setUniformValue("matDiffuseColor", m_appearance.getMatDiffuseColor());

    renderer->setUniformValue("matAmbientColor", m_appearance.getMatAmbientColor());

    renderer->setUniformValue("matSpecularColor", m_appearance.getMatSpecularColor());
    renderer->setUniformValue("specShininess", m_appearance.getSpecShininess());
    renderer->setUniformValue("normalMatrix", glm::transpose(glm::inverse(glm::mat3(mv))));

    for (CgBaseRenderableObject *&object : m_objects)
    {
        renderer->render(object);
    }
}