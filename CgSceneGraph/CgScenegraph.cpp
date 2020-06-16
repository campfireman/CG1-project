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

void CgScenegraph::render(CgBaseRenderer *renderer, glm::mat4 base)
{
    m_stack.push(std::make_tuple(m_root_node, base * m_root_node->getCurrentTransformation()));
    while (!m_stack.empty())
    {
        auto entry = m_stack.top();
        auto node = std::get<0>(entry);
        auto transformation = std::get<1>(entry);
        node->render(renderer, transformation);
        m_stack.pop();

        for (auto &child : node->getChildren())
        {
            m_stack.push(std::make_tuple(child, transformation * child->getCurrentTransformation()));
        }
    }
}