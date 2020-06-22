#include "CgNodeCursor.h"

CgAppearance CgNodeCursor::m_selected_appearance(
    glm::vec4(178 / 255.0, 34 / 255.0, 34 / 255.0, 1.0),
    glm::vec4(178 / 255.0, 34 / 255.0, 34 / 255.0, 1.0),
    glm::vec4(178 / 255.0, 34 / 255.0, 34 / 255.0, 1.0),
    glm::vec4(178 / 255.0, 34 / 255.0, 34 / 255.0, 1.0),
    1);
CgNodeCursor::CgNodeCursor(CgScenegraph *scenegraph)
{
    m_scenegraph = scenegraph;
}

CgNodeCursor::CgNodeCursor(CgScenegraph *scenegraph, std::vector<CgBaseRenderableObject *> *local_coordinates) : m_scenegraph(scenegraph),
                                                                                                                 m_cur_node(NULL), m_local_coordinates(local_coordinates), m_local_coordinates_node(NULL)
{
    this->next();
}

void CgNodeCursor::setCurNode(CgScenegraphNode *node)
{
    if (m_cur_node != NULL)
    {
        m_cur_node->setAppearance(m_prev_appearance);
    }
    if (m_local_coordinates_node != NULL)
    {
        m_scenegraph->deleteNode(m_local_coordinates_node);
    }
    m_cur_node = node;
    m_prev_appearance = m_cur_node->getAppearance();
    m_cur_node->setAppearance(m_selected_appearance);
}

void CgNodeCursor::setPrevAppearance(CgAppearance appearance)
{
    m_prev_appearance = appearance;
}
CgScenegraphNode *CgNodeCursor::getCurNode() const
{
    return m_cur_node;
}

void CgNodeCursor::next()
{
    if (m_stack.empty())
    {
        m_stack.push(m_scenegraph->getRootNode());
    }
    auto node = m_stack.top();
    this->setCurNode(node);
    m_stack.pop();
    for (auto &child : node->getChildren())
    {
        m_stack.push(child);
    }
    m_local_coordinates_node = new CgScenegraphNode(*m_local_coordinates, node->getUniqueTransformation(), m_selected_appearance, node);
    m_local_coordinates_node->is_selectable = false;
    node->addChild(m_local_coordinates_node);
    if (!node->is_selectable)
    {
        this->next();
    }
}

bool CgNodeCursor::hasNext() const
{
    return !m_stack.empty();
}