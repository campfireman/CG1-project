#include "CgSceneControl.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgEvents/CgLoadObjFileEvent.h"
#include "CgEvents/CgTrackballEvent.h"
#include "CgEvents/CgColorChangeEvent.h"
#include "CgEvents/CgButtonPressedEvent.h"
#include "CgEvents/CgCheckboxChangedEvent.h"
#include "CgBase/CgBaseRenderer.h"
#include "CgExampleTriangle.h"
#include "CgCube.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "CgUtils/ObjLoader.h"
#include <string>
#include <Qt>

CgSceneControl::CgSceneControl() : m_rgb(glm::vec3(0.0, 1.0, 0.0))
{
    m_current_transformation = glm::mat4(1.);
    m_lookAt_matrix = glm::lookAt(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    m_proj_matrix = glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    m_trackball_rotation = glm::mat4(1.);

    // objects
    m_cube = new CgCube(42);
    m_curr_obj = NULL;
    m_lines = NULL;
}

CgSceneControl::~CgSceneControl()
{
    if (m_cube != NULL)
        delete m_cube;
    if (m_lines != NULL)
        delete m_lines;
}

void CgSceneControl::setRenderer(CgBaseRenderer *r)
{
    m_renderer = r;
    m_renderer->setSceneControl(this);
    m_renderer->setUniformValue("mycolor", glm::vec4(0.0, 1.0, 0.0, 1.0));

    m_renderer->init(m_cube);
}

void CgSceneControl::renderObjects()
{
    // Materialeigenschaften setzen
    // sollte ja eigentlich pro Objekt unterschiedlich sein können, naja bekommen sie schon hin....

    m_renderer->setUniformValue("matDiffuseColor", glm::vec4(0.35, 0.31, 0.09, 1.0));
    m_renderer->setUniformValue("lightDiffuseColor", glm::vec4(1.0, 1.0, 1.0, 1.0));

    m_renderer->setUniformValue("matAmbientColor", glm::vec4(0.25, 0.22, 0.06, 1.0));
    m_renderer->setUniformValue("lightAmbientColor", glm::vec4(1.0, 1.0, 1.0, 1.0));

    m_renderer->setUniformValue("matSpecularColor", glm::vec4(0.8, 0.72, 0.21, 1.0));
    m_renderer->setUniformValue("lightSpecularColor", glm::vec4(1.0, 1.0, 1.0, 1.0));

    glm::mat4 mv_matrix = m_lookAt_matrix * m_trackball_rotation * m_current_transformation;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));

    m_renderer->setUniformValue("projMatrix", m_proj_matrix);
    m_renderer->setUniformValue("modelviewMatrix", mv_matrix);
    m_renderer->setUniformValue("normalMatrix", normal_matrix);

    if (m_curr_obj != NULL)
        m_renderer->render(m_curr_obj);
    if (m_lines != NULL)
    {
        for (auto &line : *m_lines)
        {
            std::cout << "h111" << std::endl;
            m_renderer->render(line);
        }
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

    if (e->getType() & Cg::LoadObjFileEvent)
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

        m_cube->init(pos, norm, indx);
        m_renderer->init(m_cube);
        m_renderer->redraw();
    }

    // custom handlers
    if (e->getType() & Cg::CgButtonPressedEvent)
    {
        CgButtonPressedEvent *ev = (CgButtonPressedEvent *)e;
        Cg::ButtonType button = ev->getButton();
        if (button == Cg::Draw)
        {
            m_curr_obj = m_cube;
            m_renderer->redraw();
        }
    }
    std::cout << e->getType() << std::endl;
    if (e->getType() & Cg::CgCheckboxChangedEvent)
    {
        CgCheckboxChangedEvent *ev = (CgCheckboxChangedEvent *)e;
        Cg::CheckboxType checkbox = ev->getCheckbox();
        int state = ev->getState();
        if (checkbox == Cg::FaceNormals)
        {
            m_lines = buildFaceNormals();
            if (m_lines == NULL)
            {
                return;
            }
            if (state == Qt::Checked)
            {
                std::cout << "hello" << std::endl;
                for (auto &line : *m_lines)
                {
                    std::cout << line << std::endl;
                    m_renderer->init(line);
                }
                m_renderer->redraw();
            }
            else if (state == Qt::Unchecked)
            {
                if (m_lines != NULL)
                {
                    delete m_lines;
                    m_lines = NULL;
                    m_renderer->redraw();
                }
            }
        }
    }
    if (e->getType() & Cg::CgColorChangeEvent)
    {
        CgColorChangeEvent *ev = (CgColorChangeEvent *)e;
        std::cout << ev->getColor() << std::endl;
        m_rgb[ev->getColor()] = ev->getValue() / 255.0;
        std::cout << m_rgb[0] << std::endl;
        std::cout << m_rgb[1] << std::endl;
        std::cout << m_rgb[2] << std::endl;
        m_renderer->setUniformValue("mycolor", glm::vec4(m_rgb[0], m_rgb[1], m_rgb[2], 1.0));
        m_renderer->redraw();
    }
    // an der Stelle an der ein Event abgearbeitet ist wird es auch gelöscht.
    delete e;
}

std::vector<CgPolyline *> *CgSceneControl::buildFaceNormals()
{
    if (this->m_curr_obj != NULL)
    {
        std::vector<CgPolyline *> *triangle_normals = new std::vector<CgPolyline *>{};
        auto normals = m_curr_obj->getFaceNormals();
        auto triangle_indices = m_curr_obj->getTriangleIndices();
        auto vertices = m_curr_obj->getVertices();

        for (int i = 0; i < triangle_indices.size(); i += 3)
        {
            auto p_0 = vertices[triangle_indices[i]];
            auto p_1 = vertices[triangle_indices[i + 1]];
            auto p_2 = vertices[triangle_indices[i + 2]];

            auto centroid = (p_0 + p_1 + p_2) * glm::vec3(1.0 / 3, 1.0 / 3, 1.0 / 3);
            auto normal = normals[i / 3];
            triangle_normals->push_back(new CgPolyline(100 + i, std::vector<glm::vec3>{centroid, centroid + normal}, glm::vec3(255.0, 80.0, 30.0), 1));
        }
        return triangle_normals;
    }
    return NULL;
}
