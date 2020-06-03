#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include "CgBase/CgBaseTriangleMesh.h"
#include <glm/glm.hpp>
#include <vector>

class CgBaseEvent;
class CgBaseRenderer;
class CgCube;
class CgPolyline;

class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();

    void handleEvent(CgBaseEvent *e);
    void setRenderer(CgBaseRenderer *r);
    void renderObjects();

    std::vector<CgPolyline *> *buildFaceNormals();

private:
    CgBaseRenderer *m_renderer;

    CgCube *m_cube;
    CgBaseTriangleMesh *m_curr_obj;

    std::vector<CgPolyline *> *m_lines;
    glm::vec3 m_rgb;

    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;
};

#endif // CGSCENECONTROL_H
