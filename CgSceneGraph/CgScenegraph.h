#ifndef CG_SCENEGRAPH_H
#define CG_SCENEGRAPH_H

#include "CgScenegraphNode.h"
#include "CgBase/CgBaseRenderer.h"
#include <stack>
#include <tuple>

class CgScenegraph
{
public:
    CgScenegraph(CgScenegraphNode *root_node);
    void render(CgBaseRenderer *renderer, glm::mat4 base);

    CgScenegraphNode *getRootNode() const;
    void setRootNode(CgScenegraphNode *root_node);

    void deleteNode(CgScenegraphNode *&node);

private:
    CgScenegraphNode *m_root_node;
    std::stack<std::tuple<CgScenegraphNode *, glm::mat4>> m_stack;
};
#endif