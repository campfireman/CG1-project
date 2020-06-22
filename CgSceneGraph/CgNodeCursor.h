#ifndef CG_NODE_CURSOR
#define CG_NODE_CURSOR

#include "CgScenegraphNode.h"
#include "CgScenegraph.h"
#include "CgAppearance.h"
#include <glm/glm.hpp>

class CgNodeCursor
{
public:
    CgNodeCursor(CgScenegraph *scenegraph);
    CgNodeCursor(CgScenegraph *scenegraph, std::vector<CgBaseRenderableObject *> *local_coordinates);
    void next();
    bool hasNext() const;

    void setCurNode(CgScenegraphNode *node);
    CgScenegraphNode *getCurNode() const;
    void setScenegraph(CgScenegraph *scenegraph);

    void setPrevAppearance(CgAppearance app);

    void resetStack(CgScenegraphNode *cur_node);

private:
    CgScenegraph *m_scenegraph;
    CgScenegraphNode *m_cur_node;
    CgScenegraphNode *m_local_coordinates_node;
    CgAppearance m_prev_appearance;
    static CgAppearance m_selected_appearance;

    std::vector<CgBaseRenderableObject *> *m_local_coordinates;

    std::stack<CgScenegraphNode *> m_stack;
};
#endif