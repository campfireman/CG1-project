#include "CgScenegraphNode.h"
#include <algorithm>
#include <iostream>

CgScenegraphNode::CgScenegraphNode()
{
}

CgScenegraphNode::CgScenegraphNode(std::vector<CgBaseRenderableObject *> objects, glm::mat4 current_transformation, CgAppearance appearance, CgScenegraphNode *parent)
{
    m_objects = objects;
    m_current_transformation = current_transformation;
    m_appearance = appearance;
    m_parent = parent;
    m_children = std::vector<CgScenegraphNode *>{};
}
CgScenegraphNode::CgScenegraphNode(std::vector<CgBaseRenderableObject *> objects, glm::mat4 current_transformation, CgAppearance appearance, CgScenegraphNode *parent, std::vector<CgScenegraphNode *> children) : CgScenegraphNode(objects, current_transformation, appearance, parent)
{
    m_children = children;
}

std::vector<CgBaseRenderableObject *> &CgScenegraphNode::getObjects()
{
    return m_objects;
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
}
void CgScenegraphNode::removeChild(CgScenegraphNode *child)
{
    m_children.erase(std::find(m_children.begin(), m_children.end(), child));
}
void CgScenegraphNode::render(CgBaseRenderer *renderer, glm::mat4 &transformation)
{
    renderer->setUniformValue("modelviewMatrix", transformation);

    renderer->setUniformValue("mycolor", m_appearance.getBaseColor());

    renderer->setUniformValue("matDiffuseColor", m_appearance.getMatDiffuseColor());
    renderer->setUniformValue("lightDiffuseColor", m_appearance.getBaseColor());

    renderer->setUniformValue("matAmbientColor", m_appearance.getMatAmbientColor());
    renderer->setUniformValue("lightAmbientColor", m_appearance.getBaseColor());

    renderer->setUniformValue("matSpecularColor", m_appearance.getMatSpecularColor());
    renderer->setUniformValue("lightSpecularColor", m_appearance.getBaseColor());

    for (CgBaseRenderableObject *&object : m_objects)
    {
        std::cout << "render obj" << std::endl;
        renderer->render(object);
    }
}