#ifndef CgSolidOfRevolution_H
#define CgSolidOfRevolution_H
#define PI 3.14159265

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "CgBase/CgBaseTriangleMesh.h"
#include "CgPolyline.h"

class CgSolidOfRevolution : public CgBaseTriangleMesh
{

public:
    CgSolidOfRevolution(unsigned int id, CgPolyline *contour_plot, int lateral_steps, unsigned int iterations, unsigned int n);

    ~CgSolidOfRevolution();

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

    const std::vector<glm::vec3> &getFaceNormals() const;
    const std::vector<glm::vec3> &getFaceColors() const;

    void setLateralSteps(int value);
    int getLateralSteps() const;

    unsigned int getIterations() const;
    unsigned int getN() const;

    void setContourPlot(CgPolyline *contour_plot);
    CgPolyline *getContourPlot() const;

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;

    std::vector<unsigned int> m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;

    CgPolyline *m_contour_plot;
    int m_lateral_steps;
    unsigned int m_iterations;
    unsigned int m_n;

    const Cg::ObjectType m_type;
    const unsigned int m_id;
};

inline Cg::ObjectType CgSolidOfRevolution::getType() const { return m_type; }
inline unsigned int CgSolidOfRevolution::getID() const { return m_id; }

#endif // CgSolidOfRevolution_H
