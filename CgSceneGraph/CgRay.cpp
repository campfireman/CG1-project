#include "CgRay.h"
#include "CgNodeCursor.h"
#include "CgBase/CgBaseTriangleMesh.h"
#include <cmath>
#include <iostream>
#include <tuple>

CgRay::CgRay(unsigned int id, glm::vec3 start, glm::vec3 dir) : CgPolyline(id, std::vector<glm::vec3>{start, start + 100000.0f * dir}, glm::vec3(0.0, 1.0, 0.0), 1), m_start(start), m_dir(dir)
{
}

std::vector<glm::vec3> CgRay::collisions(CgScenegraph *graph)
{
    auto result = std::vector<glm::vec3>{};
    auto stack = std::stack<std::tuple<CgScenegraphNode *, glm::mat4>>{};
    stack.push(std::make_tuple(graph->getRootNode(), glm::mat4(1.) * graph->getRootNode()->getCurrentTransformation()));
    while (!stack.empty())
    {
        auto entry = stack.top();
        auto node = std::get<0>(entry);
        auto transformation = std::get<1>(entry);
        stack.pop();

        for (auto &object : node->getObjects())
        {
            auto obj = dynamic_cast<CgBaseTriangleMesh *>(object);
            if (obj == NULL)
            {
                continue;
            }
            auto vertices = obj->getVertices();
            auto triangle_indices = obj->getTriangleIndices();
            auto obj_transformation = transformation * node->getUniqueTransformation();

            for (int i = 0; i < triangle_indices.size(); i += 3)
            {
                auto p0 = obj_transformation * glm::vec4(vertices[triangle_indices[i]], 1.0);
                auto p1 = obj_transformation * glm::vec4(vertices[triangle_indices[i + 1]], 1.0);
                auto p2 = obj_transformation * glm::vec4(vertices[triangle_indices[i + 2]], 1.0);

                auto p_0 = glm::vec3(p0.x, p0.y, p0.z);
                auto p_1 = glm::vec3(p1.x, p1.y, p1.z);
                auto p_2 = glm::vec3(p2.x, p2.y, p2.z);

                auto n = glm::normalize(glm::cross(p_1 - p_0, p_2 - p_0));
                auto d = glm::dot(n, p_0);
                auto t = (d - glm::dot(n, m_start)) / (glm::dot(n, m_dir));

                if (std::isfinite(t) && t >= 0.0f)
                {
                    auto q = m_start + t * m_dir;

                    auto v0 = p_1 - p_0;
                    auto v1 = p_2 - p_0;
                    auto v2 = q - p_0;

                    float d00 = glm::dot(v0, v0);
                    float d01 = glm::dot(v0, v1);
                    float d11 = glm::dot(v1, v1);
                    float d20 = glm::dot(v2, v0);
                    float d21 = glm::dot(v2, v1);
                    float denom = d00 * d11 - d01 * d01;
                    float v = (d11 * d20 - d01 * d21) / denom;
                    float w = (d00 * d21 - d01 * d20) / denom;
                    float u = 1.0f - v - w;
                    if (w >= 0 && w <= 1 && u >= 0 && u <= 1 && v >= 0 && v <= 1)
                    {
                        std::cout << u << std::endl;
                        std::cout << v << std::endl;
                        std::cout << w << std::endl;
                        result.push_back(q);
                        std::cout << obj->getID() << std::endl;
                    }
                }
            }
        }
        for (auto &child : node->getChildren())
        {
            stack.push(std::make_tuple(child, transformation * child->getCurrentTransformation()));
        }
    }
    return result;
}