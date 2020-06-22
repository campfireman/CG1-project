#include "CgPolyline.h"
#include "CgScenegraph.h"

class CgRay : public CgPolyline
{
public:
    CgRay(unsigned int id, glm::vec3 start, glm::vec3 dir);

    std::vector<glm::vec3> collisions(CgScenegraph *graph);

private:
    glm::vec3 m_start;
    glm::vec3 m_dir;
};