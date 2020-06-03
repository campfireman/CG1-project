#include "CgCube.h"
#include "CgBase/CgEnums.h"
#include "CgUtils/ObjLoader.h"

CgCube::CgCube(int id) : m_id(id), m_type(Cg::TriangleMesh)
{
    m_vertices.push_back(glm::vec3(0.5, 0.5, 0.5));    // 0
    m_vertices.push_back(glm::vec3(-0.5, 0.5, 0.5));   // 1
    m_vertices.push_back(glm::vec3(-0.5, 0.5, -0.5));  // 2
    m_vertices.push_back(glm::vec3(0.5, 0.5, -0.5));   // 3
    m_vertices.push_back(glm::vec3(0.5, -0.5, 0.5));   // 4
    m_vertices.push_back(glm::vec3(-0.5, -0.5, 0.5));  // 5
    m_vertices.push_back(glm::vec3(-0.5, -0.5, -0.5)); // 6
    m_vertices.push_back(glm::vec3(0.5, -0.5, -0.5));  // 7
    // oben
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(2);

    // unten
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(4);

    // links
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(1);

    // rechts
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(7);

    // hinten
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(0);

    // vorne
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(3);

    for (int i = 0; i < m_triangle_indices.size(); i += 3)
    {
        auto p_0 = m_vertices[m_triangle_indices[i]];
        auto p_1 = m_vertices[m_triangle_indices[i + 1]];
        auto p_2 = m_vertices[m_triangle_indices[i + 2]];

        auto centroid = (p_0 + p_1 + p_2) * glm::vec3(1.0 / 3, 1.0 / 3, 1.0 / 3);
        auto normal = glm::normalize(glm::cross(p_1 - p_0, p_2 - p_0));
        m_face_normals.push_back(normal);
        // m_vertex_normals.push_back(normal);
        // m_vertex_normals.push_back(normal);
        // m_vertex_normals.push_back(normal);
        // m_triangle_normals.push_back(new CgPolyline(m_id + 100 + i, std::vector<glm::vec3>{centroid, centroid + normal}, glm::vec3(255.0, 80.0, 30.0), 1));
    }
}

CgCube::~CgCube()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_triangle_normals.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

void CgCube::init(std::vector<glm::vec3> arg_verts, std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices = arg_verts;
    m_vertex_normals = arg_normals;
    m_triangle_indices = arg_triangle_indices;
}

void CgCube::init(std::string filename)
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

const std::vector<glm::vec3> &CgCube::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3> &CgCube::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3> &CgCube::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2> &CgCube::getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int> &CgCube::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<CgPolyline *> &CgCube::getTriangleNormals() const
{
    return m_triangle_normals;
}

const std::vector<glm::vec3> &CgCube::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3> &CgCube::getFaceColors() const
{
    return m_face_colors;
}
