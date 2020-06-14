#include "CgScenegraphNode.h"
#include "CgBase/CgBaseRenderer.h"
#include <stack>

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
    std::stack<glm::mat4> m_stack;

    void pushMatrix();
    void popMatrix();
    void applyTransformation(glm::mat4 transformation);
    void render_rec(CgBaseRenderer *renderer, CgScenegraphNode *node);
};