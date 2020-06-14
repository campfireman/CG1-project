#ifndef CG_SCENEGRAPH_NODE
#define CG_SCENEGRAPH_NODE

#include <vector>
#include "CgBase/CgBaseRenderableObject.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgAppearance.h"

class CgScenegraphNode
{
public:
    CgScenegraphNode();
    CgScenegraphNode(std::vector<CgBaseRenderableObject *> objects, glm::mat4 current_transformation, CgAppearance appearance, CgScenegraphNode *parent, std::vector<CgScenegraphNode *> children);
    CgScenegraphNode(std::vector<CgBaseRenderableObject *> objects, glm::mat4 current_transformation, CgAppearance appearance, CgScenegraphNode *parent);

    std::vector<CgBaseRenderableObject *> &getObjects();
    void addObject(CgBaseRenderableObject *object);
    void setObjects(std::vector<CgBaseRenderableObject *> objects);

    glm::mat4 getCurrentTransformation() const;
    void setCurrentTransformation(glm::mat4 transformation);

    CgAppearance getAppearance() const;
    void setAppearance(CgAppearance appearance);
    void setColor(glm::vec4 color);

    CgScenegraphNode *getParent() const;
    void setParent(CgScenegraphNode *parent);

    std::vector<CgScenegraphNode *> getChildren() const;
    void setChildren(std::vector<CgScenegraphNode *> children);
    void addChild(CgScenegraphNode *child);
    void removeChild(CgScenegraphNode *child);

    void render(CgBaseRenderer *renderer, glm::mat4 &transformation);

private:
    std::vector<CgBaseRenderableObject *> m_objects;
    glm::mat4 m_current_transformation;

    CgAppearance m_appearance;

    CgScenegraphNode *m_parent;
    std::vector<CgScenegraphNode *> m_children;
};
#endif