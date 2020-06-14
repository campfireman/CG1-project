#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include "CgBase/CgBaseTriangleMesh.h"
#include "CgScenegraph.h"
#include "CgAppearance.h"
#include "CgScenegraphNode.h"

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

    void resetCurNode();

    void buildFaceNormals();
    void buildVertexNormals();
    void rebuildNormals();

    static unsigned int idCounter;

private:
    CgBaseRenderer *m_renderer;

    CgBaseTriangleMesh *m_curr_obj;
    CgLoadedObj *m_loaded_obj;
    CgCube *m_cube;
    CgSolidOfRevolution *m_solid_of_revolution;

    CgScenegraph *m_cur_scenegraph;
    CgScenegraph *m_object_scenegraph;
    CgScenegraph *m_chess_scenegraph;
    CgScenegraphNode *m_cube_node;
    CgScenegraphNode *m_solid_of_revolution_node;
    CgScenegraphNode *m_loaded_obj_node;
    CgScenegraphNode *m_cur_node;

    CgScenegraphNode *m_face_normals;
    CgScenegraphNode *m_vertex_normals;
    glm::vec4 m_cur_color;

    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;
};

#endif // CGSCENECONTROL_H
