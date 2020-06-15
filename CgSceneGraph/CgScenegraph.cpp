#include "CgScenegraph.h"
#include <iostream>
CgScenegraph::CgScenegraph(CgScenegraphNode *root_node)
{
    m_root_node = root_node;
}

CgScenegraphNode *CgScenegraph::getRootNode() const
{
    return m_root_node;
}
void CgScenegraph::deleteNode(CgScenegraphNode *&node)
{
    node->getParent()->removeChild(node);
    delete node;
    node = NULL;
}
void CgScenegraph::setRootNode(CgScenegraphNode *root_node)
{
    m_root_node = root_node;
}

void CgScenegraph::pushMatrix()
{
    m_stack.push(m_stack.top());
}

void CgScenegraph::popMatrix()
{
    m_stack.pop();
}

void CgScenegraph::applyTransformation(glm::mat4 transformation)
{
    m_stack.top() *= transformation;
}

void CgScenegraph::render(CgBaseRenderer *renderer, glm::mat4 base)
{
    m_stack.push(base);

    render_rec(renderer, m_root_node);
}

void CgScenegraph::render_rec(CgBaseRenderer *renderer, CgScenegraphNode *node)
{
    this->pushMatrix();
    this->applyTransformation(node->getCurrentTransformation());
    node->render(renderer, m_stack.top());
    for (auto &child : node->getChildren())
    {
        render_rec(renderer, child);
    }
    this->popMatrix();
}