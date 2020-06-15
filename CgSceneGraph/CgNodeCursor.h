#include "CgScenegraphNode.h"
#include "CgScenegraph.h"
#include "CgAppearance.h"
#include <glm/glm.hpp>

class CgNodeCursor
{
public:
    CgNodeCursor(CgScenegraph *scenegraph);
    void next();

    void setCurNode(CgScenegraphNode *node);
    CgScenegraphNode *getCurNode() const;
    void setScenegraph(CgScenegraph *scenegraph);

private:
    CgScenegraph *m_scenegraph;
    CgScenegraphNode *m_cur_node;
    CgAppearance m_prev_appearance;
    static CgAppearance m_selected_appearance;
};