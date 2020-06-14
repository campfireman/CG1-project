#include "CgSolidOfRevolution.h"
#include "CgBase/CgEnums.h"
#include "CgUtils/ObjLoader.h"
#include "CgUtils/Utils.h"
#include <math.h>
#include <iostream>

CgSolidOfRevolution::CgSolidOfRevolution(unsigned int id, CgPolyline *contour_plot, int lateral_steps, unsigned int iterations, unsigned int n) : m_id(id), m_type(Cg::TriangleMesh), m_contour_plot(contour_plot), m_lateral_steps(lateral_steps), m_iterations(iterations), m_n(n)
{
    double step_size = 2 * M_PI / (double)m_lateral_steps;
    std::vector<glm::vec3> contour = Utils::laneRiesenfeld(m_contour_plot->getVertices(), m_iterations, m_n);

    // close body
    auto first_point = contour[0];
    auto last_point = contour[contour.size() - 1];
    if (first_point[0] != 0)
    {
        contour.insert(contour.begin(), glm::vec3(0.0, first_point[1], 0.0));
    }
    if (last_point[0] != 0)
    {
        contour.push_back(glm::vec3(0.0, last_point[1], 0.0));
    }
    m_vertices.insert(m_vertices.end(), contour.begin(), contour.end());
    // rotate body
    double phi = 0.0;
    for (int i = 1; i < m_lateral_steps; ++i)
    {
        phi = i * step_size;
        for (int j = 0; j < contour.size(); j++)
        {
            double p = glm::length(glm::vec3(0.0, contour[j][1], 0.0) - contour[j]);
            glm::vec3 new_point = glm::vec3{p * cos(phi), contour[j][1], p * sin(phi)};
            m_vertices.push_back(new_point);
            if (j > 0)
            {
                m_triangle_indices.push_back((i - 1) * contour.size() + j);
                m_triangle_indices.push_back(i * contour.size() + j - 1);
                m_triangle_indices.push_back((i - 1) * contour.size() + j - 1);
                m_triangle_indices.push_back((i - 1) * contour.size() + j);
                m_triangle_indices.push_back(i * contour.size() + j);
                m_triangle_indices.push_back(i * contour.size() + j - 1);
            }
        }
    }
    // connect last points to first points
    for (int j = 0; j < contour.size(); j++)
    {
        if (j > 0)
        {
            m_triangle_indices.push_back(m_vertices.size() - contour.size() + j);
            m_triangle_indices.push_back(j - 1);
            m_triangle_indices.push_back(m_vertices.size() - contour.size() - 1 + j);
            m_triangle_indices.push_back(m_vertices.size() - contour.size() + j);
            m_triangle_indices.push_back(j);
            m_triangle_indices.push_back(j - 1);
        }
    }
    Utils::createNormals(m_vertices, m_triangle_indices, m_face_normals, m_vertex_normals);
}

CgSolidOfRevolution::~CgSolidOfRevolution()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

void CgSolidOfRevolution::setLateralSteps(int value)
{
    this->m_lateral_steps = value;
}

int CgSolidOfRevolution::getLateralSteps() const
{
    return this->m_lateral_steps;
}

unsigned int CgSolidOfRevolution::getIterations() const
{
    return this->m_iterations;
}

unsigned int CgSolidOfRevolution::getN() const
{
    return this->m_n;
}
void CgSolidOfRevolution::setContourPlot(CgPolyline *contour_plot)
{
    this->m_contour_plot = contour_plot;
}

CgPolyline *CgSolidOfRevolution::getContourPlot() const
{
    return this->m_contour_plot;
}

void CgSolidOfRevolution::init(std::vector<glm::vec3> arg_verts, std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices = arg_verts;
    m_vertex_normals = arg_normals;
    m_triangle_indices = arg_triangle_indices;
}

void CgSolidOfRevolution::init(std::string filename)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();

    ObjLoader loader;
    loader.load(filename);

    loader.getPositionData(m_vertices);
    loader.getNormalData(m_vertex_normals);
    loader.getFaceIndexData(m_triangle_indices);
}

const std::vector<glm::vec3> &CgSolidOfRevolution::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3> &CgSolidOfRevolution::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3> &CgSolidOfRevolution::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2> &CgSolidOfRevolution::getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int> &CgSolidOfRevolution::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3> &CgSolidOfRevolution::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3> &CgSolidOfRevolution::getFaceColors() const
{
    return m_face_colors;
}
