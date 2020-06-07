#include "CgLoadedObj.h"
#include "CgBase/CgEnums.h"
#include "CgUtils/ObjLoader.h"
#include "CgUtils/Utils.h"

CgLoadedObj::CgLoadedObj(int id) : m_id(id), m_type(Cg::TriangleMesh)
{
}

CgLoadedObj::~CgLoadedObj()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

void CgLoadedObj::init(std::vector<glm::vec3> arg_verts, std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices = arg_verts;
    m_vertex_normals = arg_normals;
    m_triangle_indices = arg_triangle_indices;
    Utils::createNormals(m_vertices, m_triangle_indices, m_face_normals, m_vertex_normals);
}

void CgLoadedObj::init(std::string filename)
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

const std::vector<glm::vec3> &CgLoadedObj::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3> &CgLoadedObj::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3> &CgLoadedObj::getVertexColors() const
{
    return m_vertex_colors;
}

const std::vector<glm::vec2> &CgLoadedObj::getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int> &CgLoadedObj::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3> &CgLoadedObj::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3> &CgLoadedObj::getFaceColors() const
{
    return m_face_colors;
}
