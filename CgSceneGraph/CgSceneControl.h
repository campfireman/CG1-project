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
class CgSolidOfRevolution;
class CgPolyline;
class CgLoadedObj;

class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();

    void handleEvent(CgBaseEvent *e);
    void setRenderer(CgBaseRenderer *r);
    void renderObjects();

    std::vector<CgPolyline *> *buildFaceNormals();
    std::vector<CgPolyline *> *buildVertexNormals();

    static unsigned int idCounter;

private:
    CgBaseRenderer *m_renderer;

    CgCube *m_cube;
    CgSolidOfRevolution *m_solid_of_revolution;
    CgBaseTriangleMesh *m_curr_obj;
    CgLoadedObj *m_loaded_obj;

    std::vector<CgPolyline *> *m_face_normals;
    std::vector<CgPolyline *> *m_vertex_normals;
    glm::vec3 m_rgb;

    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;
};

#endif // CGSCENECONTROL_H
