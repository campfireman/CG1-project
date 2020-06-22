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
#include "CgEvents/CgTranslationChangedEvent.h"
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

CgSceneControl::CgSceneControl() : m_cur_color(glm::vec4(0.0, 1.0, 0.0, 1.0)), m_cur_translation(glm::vec3(1.0, 0.0, 1.0))
{
    // scenery
    m_current_transformation = glm::mat4(1.);
    m_eye = glm::vec3(0.0, 0.0, 1.0);
    m_lookAt_matrix = glm::lookAt(m_eye, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
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
    m_ball = new CgSolidOfRevolution(
        idCounter++,
        new CgPolyline(idCounter++,
                       std::vector<glm::vec3>{glm::vec3(0.0, -1.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)}, glm::vec3(0.0, 1.0, 0.0), 1),
        20,
        3,
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
                                                    glm::vec4(0.8, 0.72, 0.21, 1.0), 5),
                                       NULL);

    m_solid_of_revolution_node = new CgScenegraphNode(
        std::vector<CgBaseRenderableObject *>{m_solid_of_revolution},
        glm::mat4(1.),
        CgAppearance(glm::vec4(0.0, 1.0, 0.0, 1.0),
                     glm::vec4(0.25, 0.22, 0.06, 1.0),
                     glm::vec4(0.35, 0.31, 0.09, 1.0),
                     glm::vec4(0.8, 0.72, 0.21, 1.0), 5),
        NULL);
    m_loaded_obj_node = new CgScenegraphNode(
        std::vector<CgBaseRenderableObject *>{m_loaded_obj},
        glm::mat4(1.),
        CgAppearance(glm::vec4(0.0, 1.0, 0.0, 1.0),
                     glm::vec4(0.25, 0.22, 0.06, 1.0),
                     glm::vec4(0.35, 0.31, 0.09, 1.0),
                     glm::vec4(0.8, 0.72, 0.21, 1.0), 5),
        NULL);
    m_local_coordinates = new std::vector<CgBaseRenderableObject *>{
        new CgPolyline(idCounter++, std::vector<glm::vec3>{glm::vec3(0.0, 0.0, 0.0), glm::vec3(5.0, 0.0, 0.0)}, glm::vec3(1.0, 1.0, 1.0), 1),
        new CgPolyline(idCounter++, std::vector<glm::vec3>{glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 5.0, 0.0)}, glm::vec3(1.0, 1.0, 1.0), 1),
        new CgPolyline(idCounter++, std::vector<glm::vec3>{glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 5.0)}, glm::vec3(1.0, 1.0, 1.0), 1)};
    buildChessScene();
    m_object_scenegraph = new CgScenegraph(m_cube_node);
    m_cur_scenegraph = m_object_scenegraph;
    m_ray = NULL;
    m_collision_marker = NULL;
    m_cursor = NULL;
    this->resetCursor();
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
    m_renderer->setUniformValue("lightColor", glm::vec4(1.0, 1.0, 1.0, 1.0));

    if (m_cube != NULL)
    {
        m_renderer->init(m_cube);
    }
    if (m_solid_of_revolution != NULL)
    {
        m_renderer->init(m_solid_of_revolution);
    }
    if (m_ball != NULL)
    {
        m_renderer->init(m_ball);
    }

    if (m_local_coordinates != NULL)
    {
        for (auto &line : *m_local_coordinates)
        {
            m_renderer->init(line);
        }
    }

    if (m_chess_scenegraph != NULL)
    {
        m_renderer->init(m_ch_cube);
        m_renderer->init(m_ch_king);
        m_renderer->init(m_ch_queen);
        m_renderer->init(m_ch_rook);
        m_renderer->init(m_ch_bishop);
        m_renderer->init(m_ch_knight);
        m_renderer->init(m_ch_pawn);
        m_renderer->init(m_ch_player);
    }
}

void CgSceneControl::renderObjects()
{
    // Materialeigenschaften setzen
    m_renderer->setUniformValue("lightpos", glm::vec4(20.0, 40.0, 20.0, 1.0));

    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation * m_current_transformation;
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
        if (ev->getType() == Cg::CgMouseButtonPress && ev->button() == Cg::RightButton)
        {
            std::cout << "Ray casted!" << std::endl;

            glm::vec4 viewport = glm::vec4(ev->getWindowPosX() - ev->x(), ev->getWindowPosY() - ev->y(), m_viewport_w, m_viewport_h);
            glm::mat4 model = m_lookAt_matrix * m_trackball_rotation * m_current_transformation;
            glm::vec3 clicked_point = glm::unProject(glm::vec3(ev->getWindowPosX(), ev->getWindowSizeY() - ev->getWindowPosY(), 0.0), model, m_proj_matrix, viewport);
            glm::vec4 transformed_eye = glm::inverse(m_current_transformation * m_trackball_rotation) * glm::vec4(m_eye.x, m_eye.y, m_eye.z, 1.0);
            glm::vec3 start = glm::vec3(transformed_eye.x, transformed_eye.y, transformed_eye.z);
            glm::vec3 dir = glm::vec3(clicked_point.x, clicked_point.y, clicked_point.z) - start;

            auto ray = new CgRay(idCounter++, start, dir);
            if (m_collision_marker != NULL)
            {
                m_cur_scenegraph->deleteNode(m_collision_marker);
            }
            if (m_cur_scenegraph != NULL)
            {
                auto collisions = ray->collisions(m_cur_scenegraph);

                if (collisions.size() > 0)
                {
                    auto smallest = glm::length(collisions[0] - start);
                    int index = 0;
                    for (int i = 1; i < collisions.size(); i++)
                    {
                        auto cur = glm::length(collisions[i] - start);
                        if (cur < smallest)
                        {
                            smallest = cur;
                            index = i;
                        }
                    }
                    std::cout << "Distance Eye <-> First Collision: " << smallest << std::endl;
                    m_collision_marker = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ball}, CgAppearance(glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), 2.0f));
                    m_collision_marker->is_selectable = false;

                    m_collision_marker->setCurrentTransformation(scale(glm::translate(glm::mat4(1.), collisions[index]), m_collision_marker->getCentroid(), glm::vec3(0.2, 0.2, 0.2)));
                    m_cur_scenegraph->getRootNode()->addChild(m_collision_marker);
                }
            }
            if (m_ray != NULL)
            {
                m_cur_scenegraph->deleteNode(m_ray);
            }
            m_ray = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{ray}, CgAppearance(glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), 2.0f));
            m_ray->is_selectable = false;
            m_renderer->init(ray);
            m_cur_scenegraph->getRootNode()->addChild(m_ray);
        }
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
        }
        if (ev->text() == "-")
        {
            glm::mat4 scalemat = glm::mat4(1.);
            scalemat = glm::scale(scalemat, glm::vec3(0.8, 0.8, 0.8));

            m_current_transformation = m_current_transformation * scalemat;
        }
        auto node = m_cursor->getCurNode();
        auto cur = node->getCurrentTransformation();
        if (ev->text() == "n")
        {
            m_cursor->next();
        }
        if (ev->text() == "q")
        {
            node->setCurrentTransformation(scale(cur, node->getCentroid(), glm::vec3(1.2, 1.2, 1.2)));
        }
        if (ev->text() == "w")
        {
            node->setCurrentTransformation(scale(cur, node->getCentroid(), glm::vec3(0.8, 0.8, 0.8)));
        }
        if (ev->text() == "t")
        {
            node->setCurrentTransformation(translate(cur, m_cur_translation));
        }
        if (ev->text() == "x")
        {
            node->setCurrentTransformation(rotate(cur, glm::vec3(1.0, 0.0, 0.0)));
        }
        if (ev->text() == "y")
        {
            node->setCurrentTransformation(rotate(cur, glm::vec3(0.0, 1.0, 0.0)));
        }
        if (ev->text() == "z")
        {
            node->setCurrentTransformation(rotate(cur, glm::vec3(0.0, 0.0, 1.0)));
        }
        m_renderer->redraw();
    }

    if (e->getType() == Cg::WindowResizeEvent)
    {
        CgWindowResizeEvent *ev = (CgWindowResizeEvent *)e;
        std::cout << *ev << std::endl;
        m_proj_matrix = glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f);
        m_viewport_w = ev->w();
        m_viewport_h = ev->h();
    }

    if (e->getType() == Cg::LoadObjFileEvent)
    {

        CgLoadObjFileEvent *ev = (CgLoadObjFileEvent *)e;

        loadObject(m_loaded_obj, ev->FileName());
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
        Cg::SelectionType type = ev->getSelection();
        std::cout << ev->getValue() << std::endl;

        if (type == Cg::Object)
        {
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
            this->resetCursor();
            m_cursor->getCurNode()->setColor(m_cur_color);
            this->rebuildNormals();
        }
        if (type == Cg::Scene)
        {
            if (object == Cg::ObjectScene)
            {
                std::cout << "objects" << std::endl;
                m_cur_scenegraph = m_object_scenegraph;
            }
            else if (object == Cg::ChessScene)
            {
                std::cout << "chess" << std::endl;
                m_cur_scenegraph = m_chess_scenegraph;
            }
            this->resetCursor();
        }
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
        auto tmp = glm::vec4(m_cur_color.x, m_cur_color.y, m_cur_color.z, 1.0);
        m_cursor->setPrevAppearance(CgAppearance(tmp, tmp, tmp, tmp, 2.0f));
    }
    if (e->getType() == Cg::CgTranslationChangedEvent)
    {
        std::cout << "Translation changed event" << std::endl;
        CgTranslationChangedEvent *ev = (CgTranslationChangedEvent *)e;
        std::cout << ev->getValue() << std::endl;
        m_cur_translation[ev->getAxis()] = ev->getValue();
    }
    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;
}

void CgSceneControl::resetCursor()
{
    if (m_cur_scenegraph != NULL)
    {
        if (m_cursor != NULL)
        {
            delete m_cursor;
            m_cursor = NULL;
        }
        m_cursor = new CgNodeCursor(m_cur_scenegraph, m_local_coordinates);
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
    if (m_cursor->getCurNode() == NULL)
    {
        return;
    }
    auto face_normals = std::vector<CgBaseRenderableObject *>{};
    for (auto &object : m_cursor->getCurNode()->getObjects())
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
    auto normals = new CgScenegraphNode(face_normals, m_cursor->getCurNode()->getUniqueTransformation(), m_cursor->getCurNode()->getAppearance(), m_cursor->getCurNode());
    m_cursor->getCurNode()->addChild(normals);
    m_face_normals = normals;
}

void CgSceneControl::buildVertexNormals()
{
    if (m_cursor->getCurNode() == NULL)
    {
        return;
    }
    auto vertex_normals = std::vector<CgBaseRenderableObject *>{};
    for (auto &object : m_cursor->getCurNode()->getObjects())
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
    auto normals = new CgScenegraphNode(vertex_normals, m_cursor->getCurNode()->getUniqueTransformation(), m_cursor->getCurNode()->getAppearance(), m_cursor->getCurNode());
    m_cursor->getCurNode()->addChild(normals);
    m_vertex_normals = normals;
}

void CgSceneControl::buildChessScene()
{
    // colors & materials
    glm::vec4 brown = glm::vec4(205 / 255.0, 133 / 255.0, 63 / 255.0, 1.0);
    glm::vec4 wood_amb = glm::vec4(205 / 255.0, 133 / 255.0, 63 / 255.0, 1.0);
    glm::vec4 wood_diff = glm::vec4(205 / 255.0, 133 / 255.0, 63 / 255.0, 1.0);
    glm::vec4 wood_spec = glm::vec4(0.0, 0.0, 0.0, 1.0);
    float wood_shininess = 1.0f;

    glm::vec4 black = glm::vec4(0.1, 0.1, 0.1, 1.0);
    glm::vec4 black_amb = glm::vec4(0.02, 0.02, 0.02, 1.0);
    glm::vec4 black_diff = glm::vec4(0.01, 0.01, 0.01, 1.0);
    glm::vec4 black_spec = glm::vec4(0.4, 0.4, 0.4, 1.0);
    float black_shininess = 10.0f;

    glm::vec4 white = glm::vec4(1.0, 1.0, 1.0, 1.0);
    glm::vec4 white_amb = glm::vec4(0.25, 0.21, 0.21, 0.9);
    glm::vec4 white_diff = glm::vec4(0.99, 0.83, 0.83, 1.0);
    glm::vec4 white_spec = glm::vec4(0.3, 0.3, 0.3, 0.9);
    float white_shininess = 11.3f;

    auto board_colors = std::vector<CgAppearance>{CgAppearance(white, white_amb, white_diff, white_spec, white_shininess), CgAppearance(black, black_amb, black_diff, black_spec, black_shininess)};
    // objects
    m_ch_cube = new CgCube(idCounter++);
    m_ch_king = new CgLoadedObj(idCounter++);
    loadObject(m_ch_king, getObjectDirectory() /= "King.obj");
    m_ch_queen = new CgLoadedObj(idCounter++);
    loadObject(m_ch_queen, getObjectDirectory() /= "Queen.obj");
    m_ch_knight = new CgLoadedObj(idCounter++);
    loadObject(m_ch_knight, getObjectDirectory() /= "Knight.obj");
    m_ch_bishop = new CgLoadedObj(idCounter++);
    loadObject(m_ch_bishop, getObjectDirectory() /= "Bishop.obj");
    m_ch_rook = new CgLoadedObj(idCounter++);
    loadObject(m_ch_rook, getObjectDirectory() /= "Rook.obj");
    m_ch_player = new CgLoadedObj(idCounter++);
    loadObject(m_ch_player, getObjectDirectory() /= "Man_sitting.obj");
    m_ch_pawn = new CgSolidOfRevolution(
        idCounter++,
        new CgPolyline(idCounter++,
                       std::vector<glm::vec3>{glm::vec3(0.3, 0.0, 0.0), glm::vec3(0.5, 0.2, 0.0), glm::vec3(0.3, 0.25, 0.0), glm::vec3(0.35, 0.35, 0.0), glm::vec3(0.15, 0.5, 0.0), glm::vec3(0.25, 0.55, 0.0), glm::vec3(0.15, 0.6, 0.0), glm::vec3(0.1, 1.0, 0.0), glm::vec3(0.13, 1.25, 0.0), glm::vec3(0.33, 1.3, 0.0), glm::vec3(0.18, 1.4, 0.0), glm::vec3(0.0, 1.5, 0.0)}, glm::vec3(0.0, 1.0, 0.0), 1),
        30,
        2,
        2);

    // graph & nodes
    CgScenegraphNode *base = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *table = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *chair = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *leg = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *leg1 = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *leg2 = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *leg3 = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *leg4 = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *player = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_player}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *box1 = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *box2 = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *box3 = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *box4 = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, CgAppearance(brown, wood_amb, wood_diff, wood_spec, wood_shininess));
    CgScenegraphNode *king = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_king}, board_colors[0]);
    CgScenegraphNode *pawn = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_pawn}, board_colors[1]);
    CgScenegraphNode *knight = new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_knight}, board_colors[1]);

    base->addChild(table);
    base->addChild(leg);
    base->addChild(player);
    player->addChild(chair);
    chair->addChild(leg1);
    leg1->addChild(leg2);
    leg1->addChild(leg3);
    leg1->addChild(leg4);
    table->addChild(box1);
    box1->addChild(box2);
    box1->addChild(box3);
    box1->addChild(box4);
    box1->addChild(king);
    box1->addChild(pawn);
    box1->addChild(knight);
    m_chess_scenegraph = new CgScenegraph(base);

    auto pieces = std::vector<CgBaseRenderableObject *>{m_ch_rook, m_ch_knight, m_ch_bishop, m_ch_king, m_ch_queen, m_ch_bishop, m_ch_knight, m_ch_rook};
    glm::mat4 base_scale = scale(glm::mat4(1.), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.5, 1.0)) * glm::translate(glm::mat4(1.), glm::vec3(0.5, 1.0, 0.5));
    glm::mat4 piece_scale = glm::translate(glm::mat4(1.), glm::vec3(0.0, 0.7, 0.0));
    for (int i = 0; i < 8; i++)
    {
        int start = i % 2;
        double z_pos = (double)(-4 + i);
        for (int j = 0; j < 8; j++)
        {
            CgBaseRenderableObject *piece = NULL;
            CgAppearance piece_color = board_colors[i < 4 ? 0 : 1];
            glm::mat4 piece_transform = piece_scale;
            if (i == 0 || i == 7)
            {
                piece = pieces[j];
            }
            if (i == 1 || i == 6)
            {
                piece = m_ch_pawn;
                piece_transform *= glm::translate(glm::mat4(1.), glm::vec3(0.5, 0.0, 0.5));
            }
            if (i == 7)
            {
                piece_transform *= glm::translate(glm::mat4(1.), glm::vec3(1.0, 0.0, 1.0)) * glm::rotate(glm::mat4(1.), (float)(PI), glm::vec3(0.0, 1.0, 0.0));
            }
            double x_pos = (double)(-4 + j);
            CgAppearance color = board_colors[(start + j) % 2];
            glm::mat4 translation = glm::translate(glm::mat4(1.), glm::vec3(x_pos, 0.0, z_pos));
            table->addChild(new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{m_ch_cube}, translation * base_scale, color));
            if (piece != NULL)
            {
                table->addChild(new CgScenegraphNode(std::vector<CgBaseRenderableObject *>{piece}, translation * piece_transform, piece_color));
            }
        }
    }

    // transformations
    base->setUniqueTransformation(scale(glm::mat4(1.), base->getCentroid(), glm::vec3(8.0, 3.0, 8.0)));

    table->setUniqueTransformation(scale(glm::mat4(1.), table->getCentroid(), glm::vec3(25.0, 1.0, 25.0)));
    table->setCurrentTransformation(translate(glm::mat4(1.), glm::vec3(0.0, 28.0, 0.0)));
    leg->setCurrentTransformation(scale(translate(glm::mat4(1.0), glm::vec3(0.0, 14.0, 0.0)), leg->getCentroid(), glm::vec3(3.0, 28.0, 3.0)));

    player->setCurrentTransformation(translate(glm::mat4(1.), glm::vec3(0.0, 0.0, -10.0)));

    chair->setUniqueTransformation(scale(glm::mat4(1.), chair->getCentroid(), glm::vec3(15.0, 2.0, 15.0)));
    chair->setCurrentTransformation(translate(glm::mat4(1.), glm::vec3(0.0, 16.0, -15.0)));
    leg1->setCurrentTransformation(scale(glm::mat4(1.), leg1->getCentroid(), glm::vec3(3.0, 16.0, 3.0)));
    leg1->setUniqueTransformation(translate(glm::mat4(1.), glm::vec3(2.0, -0.56, 2.0)));
    leg2->setUniqueTransformation(translate(glm::mat4(1.), glm::vec3(-2.0, -0.56, 2.0)));
    leg3->setUniqueTransformation(translate(glm::mat4(1.), glm::vec3(-2.0, -0.56, -2.0)));
    leg4->setUniqueTransformation(translate(glm::mat4(1.), glm::vec3(2.0, -0.56, -2.0)));

    double box_length = 4.0;
    double box_thickness = 0.3;
    double box_height = 2.5;
    box1->setCurrentTransformation(translate(rotate(glm::mat4(1.), glm::vec3(0.0, 1.0, 0.0)), glm::vec3(6.0, 1.5, 0.0)));
    box2->setCurrentTransformation(translate(glm::mat4(1.0), glm::vec3(box_length - box_thickness, 0.0, 0.0)));
    box3->setCurrentTransformation(glm::rotate(translate(glm::mat4(1.), glm::vec3((box_length / 2.0) - box_thickness / 2, 0.0, -(box_length / 2) + box_thickness / 2)), (float)-(PI / 2), glm::vec3(0.0, 1.0, 0.0)));
    box4->setCurrentTransformation(glm::rotate(translate(glm::mat4(1.), glm::vec3((box_length / 2.0) - box_thickness / 2, 0.0, (box_length / 2) - box_thickness / 2)), (float)(PI / 2), glm::vec3(0.0, 1.0, 0.0)));
    box1->setUniqueTransformation(scale(glm::mat4(1.), box1->getCentroid(), glm::vec3(box_thickness, box_height, box_length)));
    box2->setUniqueTransformation(scale(glm::mat4(1.), box2->getCentroid(), glm::vec3(box_thickness, box_height, box_length)));
    box3->setUniqueTransformation(scale(glm::mat4(1.), box3->getCentroid(), glm::vec3(box_thickness, box_height, box_length)));
    box4->setUniqueTransformation(scale(glm::mat4(1.), box4->getCentroid(), glm::vec3(box_thickness, box_height, box_length)));

    king->setCurrentTransformation(translate(glm::mat4(1.), glm::vec3(box_length / 2, -box_height / 2, 0.0)));
    pawn->setCurrentTransformation(glm::rotate(translate(glm::rotate(glm::mat4(1.), -(float)(PI / 7), glm::vec3(0.0, 1.0, 0.0)), glm::vec3(box_length / 3, -box_height / 3.5, -box_length / 3)), -(float)(PI / 2.1), glm::vec3(0.0, 0.0, 1.0)));
    knight->setCurrentTransformation(glm::rotate(translate(glm::mat4(1.), glm::vec3(box_length / 7, -box_height / 2, -box_length / 3)), (float)(PI / 9), glm::vec3(0.0, 0.0, 1.0)));
}

void CgSceneControl::loadObject(CgLoadedObj *obj, std::string filename)
{
    ObjLoader *loader = new ObjLoader();
    loader->load(filename);

    std::cout << "loading .obj: " << filename << std::endl;

    std::vector<glm::vec3> pos;
    loader->getPositionData(pos);

    std::vector<glm::vec3> norm;
    loader->getNormalData(norm);

    std::vector<unsigned int> indx;
    loader->getFaceIndexData(indx);

    obj->init(pos, norm, indx);
}

fs::path CgSceneControl::getObjectDirectory()
{
    return fs::current_path() /= "CgData";
}

glm::mat4 CgSceneControl::translate(glm::mat4 cur, glm::vec3 translation)
{
    return glm::translate(cur, translation);
}
glm::mat4 CgSceneControl::scale(glm::mat4 cur, glm::vec3 centroid, glm::vec3 factor)
{
    auto pivot = glm::vec3(centroid.x, 0.0, centroid.z);
    return glm::translate(glm::scale(glm::translate(cur, pivot), factor), -pivot);
}

glm::mat4 CgSceneControl::rotate(glm::mat4 cur, glm::vec3 axis)
{
    return glm::rotate(cur, (float)(PI / 12.0), axis);
}