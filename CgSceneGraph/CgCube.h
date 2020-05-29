#ifndef CgCube_H
#define CgCube_H

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "CgBase/CgBaseTriangleMesh.h"
#include "CgPolyline.h"

class CgCube : public CgBaseTriangleMesh
{

public:
    CgCube(int id);

    ~CgCube();

    //inherited from CgBaseRenderableObject
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    void init(std::vector<glm::vec3> arg_verts, std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices);
    void init(std::string filename);

    //inherited from CgBaseTriangleMesh
    const std::vector<glm::vec3> &getVertices() const;
    const std::vector<glm::vec3> &getVertexNormals() const;
    const std::vector<glm::vec3> &getVertexColors() const;
    const std::vector<glm::vec2> &getVertexTexCoords() const;

    const std::vector<unsigned int> &getTriangleIndices() const;
    const std::vector<CgPolyline *> &getTriangleNormals() const;

    const std::vector<glm::vec3> &getFaceNormals() const;
    const std::vector<glm::vec3> &getFaceColors() const;

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;

    std::vector<unsigned int> m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;

    std::vector<CgPolyline *> m_triangle_normals;

    const Cg::ObjectType m_type;
    const unsigned int m_id;
};

inline Cg::ObjectType CgCube::getType() const { return m_type; }
inline unsigned int CgCube::getID() const { return m_id; }

#endif // CgCube_H
