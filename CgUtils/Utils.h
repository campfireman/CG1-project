#include <vector>
#include "CgBase/CgBaseTriangleMesh.h"
#include "CgSceneGraph/CgPolyline.h"

class Utils
{
public:
    static void createNormals(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &triangle_indices, std::vector<glm::vec3> &face_normals, std::vector<glm::vec3> &vertex_normals);
    static std::vector<glm::vec3> laneRiesenfeld(std::vector<glm::vec3> line, unsigned int iterations, unsigned int n);
};