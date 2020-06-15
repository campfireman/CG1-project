#include "CgNodeCursor.h"

CgAppearance CgNodeCursor::m_selected_appearance(
    glm::vec4(178 / 255.0, 34 / 255.0, 34 / 255.0, 1.0),
    glm::vec4(178 / 255.0, 34 / 255.0, 34 / 255.0, 1.0),
    glm::vec4(178 / 255.0, 34 / 255.0, 34 / 255.0, 1.0),
    glm::vec4(178 / 255.0, 34 / 255.0, 34 / 255.0, 1.0),
    1);
CgNodeCursor::CgNodeCursor(CgScenegraph *scenegraph) : m_scenegraph(scenegraph)
{
    this->setCurNode(m_scenegraph->getRootNode());
}

void CgNodeCursor::setCurNode(CgScenegraphNode *node)
{
    m_cur_node = node;
    m_prev_appearance = m_cur_node->getAppearance();
    m_cur_node->setAppearance(m_selected_appearance);
}