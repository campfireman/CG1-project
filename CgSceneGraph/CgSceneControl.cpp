#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgBase/CgBaseRenderableObject.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgLoadObjFileEvent.h"
#include "CgEvents/CgTrackballEvent.h"
#include "CgEvents/CgColorChangeEvent.h"
#include "CgEvents/CgButtonPressedEvent.h"
#include "CgEvents/CgCheckboxChangedEvent.h"
#include "CgEvents/CgSelectionChangedEvent.h"
#include "CgEvents/CgSORChangedEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgExampleTriangle.h"
#include "CgCube.h"
#include "CgSolidOfRevolution.h"
#include "CgLoadedObj.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "CgUtils/ObjLoader.h"
#include "CgUtils/Utils.h"
#include <string>
#include <Qt>

unsigned int CgSceneControl::idCounter = 100;

CgSceneControl::CgSceneControl() : m_cur_color(glm::vec4(0.0, 1.0, 0.0, 1.0))
{
    // scenery
    m_current_transformation = glm::mat4(1.);
    m_lookAt_matrix = glm::lookAt(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    m_proj_matrix = glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    m_trackball_rotation = glm::mat4(1.);

    // objects
    m_cube = new CgCube(idCounter++);
    m_solid_of_revolution = new CgSolidOfRevolution(
        idCounter++,
        new CgPolyline(idCounter++,
                       std::vector<glm::vec3>{glm::vec3(0.0, -2.0, 0.0), glm::vec3(1.0, -1.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 2.0, 0.0), glm::vec3(3.0, 3.0, 0.0)}, glm::vec3(0.0, 1.0, 0.0), 1),
        20,
        0,
        2);
    m_loaded_obj = new CgLoadedObj(idCounter++);
    m_face_normals = NULL;
    m_vertex_normals = NULL;

    // graph
    m_cube_node = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_cube},
                                       glm::mat4(1.),
                                       CgAppearance(glm::vec4(0.0, 1.0, 0.0, 1.0),
                                                    glm::vec4(0.25, 0.22, 0.06, 1.0),
                                                    glm::vec4(0.35, 0.31, 0.09, 1.0),
                                                    glm::vec4(0.8, 0.72, 0.21, 1.0)),
                                       NULL);

    m_solid_of_revolution_node = new CgScenegraphNode(
        std::vector<CgBaseRenderableObject *>{m_solid_of_revolution},
        glm::mat4(1.),
        CgAppearance(glm::vec4(0.0, 1.0, 0.0, 1.0),
                     glm::vec4(0.25, 0.22, 0.06, 1.0),
                     glm::vec4(0.35, 0.31, 0.09, 1.0),
                     glm::vec4(0.8, 0.72, 0.21, 1.0)),
        NULL);
    m_loaded_obj_node = new CgScenegraphNode(
        std::vector<CgBaseRenderableObject *>{m_loaded_obj},
        glm::mat4(1.),
        CgAppearance(glm::vec4(0.0, 1.0, 0.0, 1.0),
                     glm::vec4(0.25, 0.22, 0.06, 1.0),
                     glm::vec4(0.35, 0.31, 0.09, 1.0),
                     glm::vec4(0.8, 0.72, 0.21, 1.0)),
        NULL);
    m_curr_obj = NULL;
    m_chess_scenegraph = NULL;
    m_object_scenegraph = new CgScenegraph(m_cube_node);
    m_cur_scenegraph = m_object_scenegraph;
    this->resetCurNode();
}

CgSceneControl::~CgSceneControl()
{
    if (m_cube != NULL)
        delete m_cube;
    if (m_face_normals != NULL)
        delete m_face_normals;
    if (m_vertex_normals != NULL)
        delete m_vertex_normals;
}

void CgSceneControl::setRenderer(CgBaseRenderer *r)
{
    m_renderer = r;
    m_renderer->setSceneControl(this);
    m_renderer->setUniformValue("mycolor", glm::vec4(0.0, 1.0, 0.0, 1.0));

    if (m_cube != NULL)
    {
        m_renderer->init(m_cube);
    }
    if (m_solid_of_revolution != NULL)
    {
        m_renderer->init(m_solid_of_revolution);
    }
}

void CgSceneControl::renderObjects()
{
    // Materialeigenschaften setzen
    m_renderer->setUniformValue("lightpos", glm::vec4(0.0, -15.0, 15.0, 1.0));

    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

    m_renderer->setUniformValue("lookAtMatrix", m_lookAt_matrix);
    m_renderer->setUniformValue("projMatrix", m_proj_matrix);
    m_renderer->setUniformValue("modelviewMatrix", mv_matrix);
    m_renderer->setUniformValue("normalMatrix", normal_matrix);

    if (m_cur_scenegraph != NULL)
    {
        m_cur_scenegraph->render(m_renderer, mv_matrix);
    }
}

void CgSceneControl::handleEvent(CgBaseEvent *e)
{
    // die Enums sind so gebaut, dass man alle Arten von MausEvents über CgEvent::CgMouseEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h

    if (e->getType() & Cg::CgMouseEvent)
    {
        CgMouseEvent *ev = (CgMouseEvent *)e;
        //std::cout << *ev << std::endl;

        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if (e->getType() & Cg::CgTrackballEvent)
    {
        CgTrackballEvent *ev = (CgTrackballEvent *)e;

        m_trackball_rotation = ev->getRotationMatrix();
        m_renderer->redraw();
    }

    // die Enums sind so gebaut, dass man alle Arten von KeyEvents über CgEvent::CgKeyEvent abprüfen kann,
    // siehe dazu die CgEvent enums im CgEnums.h
    // momentan werden nur KeyPressEvents gefangen.

    if (e->getType() & Cg::CgKeyEvent)
    {
        CgKeyEvent *ev = (CgKeyEvent *)e;
        std::cout << *ev << std::endl;

        if (ev->text() == "+")
        {
            glm::mat4 scalemat = glm::mat4(1.);
            scalemat = glm::scale(scalemat, glm::vec3(1.2, 1.2, 1.2));
            m_current_transformation = m_current_transformation * scalemat;
            m_renderer->redraw();
        }
        if (ev->text() == "-")
        {
            glm::mat4 scalemat = glm::mat4(1.);
            scalemat = glm::scale(scalemat, glm::vec3(0.8, 0.8, 0.8));

            m_current_transformation = m_current_transformation * scalemat;

            m_renderer->redraw();
        }
        // hier kommt jetzt die Abarbeitung des Events hin...
    }

    if (e->getType() & Cg::WindowResizeEvent)
    {
        CgWindowResizeEvent *ev = (CgWindowResizeEvent *)e;
        std::cout << *ev << std::endl;
        m_proj_matrix = glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
    }

    if (e->getType() == Cg::LoadObjFileEvent)
    {

        CgLoadObjFileEvent *ev = (CgLoadObjFileEvent *)e;

        ObjLoader *loader = new ObjLoader();
        loader->load(ev->FileName());

        std::cout << ev->FileName() << std::endl;

        std::vector<glm::vec3> pos;
        loader->getPositionData(pos);

        std::vector<glm::vec3> norm;
        loader->getNormalData(norm);

        std::vector<unsigned int> indx;
        loader->getFaceIndexData(indx);

        m_loaded_obj->init(pos, norm, indx);
        m_renderer->init(m_loaded_obj);
        m_renderer->redraw();
    }

    // custom handlers
    if (e->getType() == Cg::CgButtonPressedEvent)
    {
        std::cout << "Button Pressed Event" << std::endl;
        CgButtonPressedEvent *ev = (CgButtonPressedEvent *)e;
        Cg::ButtonType button = ev->getButton();
        if (button == Cg::Draw)
        {
            m_renderer->redraw();
        }
    }
    if (e->getType() == Cg::CgCheckboxChangedEvent)
    {
        std::cout << "Checkbox Changed Event" << std::endl;
        CgCheckboxChangedEvent *ev = (CgCheckboxChangedEvent *)e;
        Cg::CheckboxType checkbox = ev->getCheckbox();
        int state = ev->getState();
        if (checkbox == Cg::FaceNormals)
        {
            if (state == Qt::Checked)
            {
                buildFaceNormals();
            }
            else if (state == Qt::Unchecked)
            {
                if (m_face_normals != NULL)
                {
                    m_cur_scenegraph->deleteNode(m_face_normals);
                }
            }
        }
        if (checkbox == Cg::VertexNormals)
        {
            if (state == Qt::Checked)
            {
                buildVertexNormals();
            }
            else if (state == Qt::Unchecked)
            {
                if (m_vertex_normals != NULL)
                {
                    m_cur_scenegraph->deleteNode(m_vertex_normals);
                }
            }
        }
    }

    if (e->getType() == Cg::CgSelectionChangedEvent)
    {
        std::cout << "Selection Changed Event" << std::endl;
        CgSelectionChangedEvent *ev = (CgSelectionChangedEvent *)e;
        int object = ev->getValue();
        std::cout << ev->getValue() << std::endl;

        if (object == Cg::Cube)
        {
            m_object_scenegraph->setRootNode(m_cube_node);
        }
        else if (object == Cg::SolidOfRevolution)
        {
            m_object_scenegraph->setRootNode(m_solid_of_revolution_node);
        }
        else if (object == Cg::LoadedObj)
        {
            m_object_scenegraph->setRootNode(m_loaded_obj_node);
        }
        this->resetCurNode();
        m_cur_node->setColor(m_cur_color);
        this->rebuildNormals();
    }

    if (e->getType() == Cg::CgSORChangedEvent)
    {
        std::cout << "SOR Changed Event" << std::endl;
        CgSORChangedEvent *ev = (CgSORChangedEvent *)e;
        Cg::SOROptionType option = ev->getOption();
        int value = ev->getValue();
        std::cout << ev->getValue() << std::endl;

        CgSolidOfRevolution *old_obj = m_solid_of_revolution;
        CgSolidOfRevolution *new_obj = NULL;

        auto contour = old_obj->getContourPlot();
        auto steps = old_obj->getLateralSteps();
        auto iterations = old_obj->getIterations();
        auto n = old_obj->getN();

        if (option == Cg::LateralSteps)
        {
            steps = value;
        }
        else if (option == Cg::Iterations)
        {
            iterations = value;
        }
        else if (option == Cg::N)
        {
            n = value;
        }
        new_obj = new CgSolidOfRevolution(
            idCounter++,
            contour,
            steps,
            iterations,
            n);
        if (m_curr_obj == old_obj)
        {
            m_curr_obj = new_obj;
        }
        m_solid_of_revolution = new_obj;
        m_solid_of_revolution_node->setObjects(std::vector<CgBaseRenderableObject *>{m_solid_of_revolution});
        m_renderer->init(new_obj);
        this->rebuildNormals();
        delete old_obj;
    }
    if (e->getType() == Cg::CgColorChangeEvent)
    {
        std::cout << "Color changed event" << std::endl;
        CgColorChangeEvent *ev = (CgColorChangeEvent *)e;
        std::cout << ev->getValue() << std::endl;
        m_cur_color[ev->getColor()] = ev->getValue() / 255.0;
        m_cur_node->setColor(m_cur_color);
    }
    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;
}

void CgSceneControl::resetCurNode()
{
    if (m_cur_scenegraph != NULL)
    {
        m_cur_node = m_cur_scenegraph->getRootNode();
    }
}

void CgSceneControl::rebuildNormals()
{
    if (m_face_normals != NULL)
    {
        this->m_cur_scenegraph->deleteNode(m_face_normals);
        this->buildFaceNormals();
    }
    if (m_vertex_normals != NULL)
    {
        this->m_cur_scenegraph->deleteNode(m_vertex_normals);
        this->buildVertexNormals();
    }
}

void CgSceneControl::buildFaceNormals()
{
    if (m_cur_node == NULL)
    {
        return;
    }
    auto face_normals = std::vector<CgBaseRenderableObject *>{};
    for (auto &object : m_cur_node->getObjects())
    {
        auto obj = dynamic_cast<CgBaseTriangleMesh *>(object);
        if (obj == NULL)
        {
            continue;
        }
        auto normals = obj->getFaceNormals();
        auto vertices = obj->getVertices();
        auto triangle_indices = obj->getTriangleIndices();

        for (int i = 0; i < triangle_indices.size(); i += 3)
        {
            auto p_0 = vertices[triangle_indices[i]];
            auto p_1 = vertices[triangle_indices[i + 1]];
            auto p_2 = vertices[triangle_indices[i + 2]];

            auto centroid = (p_0 + p_1 + p_2) * glm::vec3(1.0 / 3, 1.0 / 3, 1.0 / 3);
            auto normal = normals[i / 3];
            auto line = new CgPolyline(idCounter++, std::vector<glm::vec3>{centroid, centroid + normal}, glm::vec3(255.0, 80.0, 30.0), 1);
            m_renderer->init(line);
            face_normals.push_back(line);
        }
    }
    auto normals = new CgScenegraphNode(face_normals, glm::mat4(1.), m_cur_node->getAppearance(), m_cur_node);
    m_cur_node->addChild(normals);
    m_face_normals = normals;
}

void CgSceneControl::buildVertexNormals()
{
    if (m_cur_node == NULL)
    {
        return;
    }
    auto vertex_normals = std::vector<CgBaseRenderableObject *>{};
    for (auto &object : m_cur_node->getObjects())
    {
        auto obj = dynamic_cast<CgBaseTriangleMesh *>(object);
        if (obj == NULL)
        {
            continue;
        }
        auto normals = obj->getVertexNormals();
        auto vertices = obj->getVertices();

        for (int i = 0; i < vertices.size(); i++)
        {
            glm::vec3 vertex = vertices[i];
            glm::vec3 normal = normals[i];
            auto line = new CgPolyline(idCounter++, std::vector<glm::vec3>{vertex, vertex + normal}, glm::vec3(255.0, 80.0, 30.0), 1);
            m_renderer->init(line);
            vertex_normals.push_back(line);
        }
    }
    auto normals = new CgScenegraphNode(vertex_normals, glm::mat4(1.), m_cur_node->getAppearance(), m_cur_node);
    m_cur_node->addChild(normals);
    m_vertex_normals = normals;
}