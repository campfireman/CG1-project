#include "Utils.h"
#include <iostream>
void Utils::createFaceNormals(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &triangle_indices, std::vector<glm::vec3> &face_normals)
{
    for (int i = 0; i < triangle_indices.size(); i += 3)
    {
        auto p_0 = vertices[triangle_indices[i]];
        auto p_1 = vertices[triangle_indices[i + 1]];
        auto p_2 = vertices[triangle_indices[i + 2]];

        auto normal = glm::normalize(glm::cross(p_1 - p_0, p_2 - p_0));
        face_normals.push_back(normal);
    }
}

std::vector<glm::vec3> Utils::laneRiesenfeld(std::vector<glm::vec3> line, unsigned int iterations, unsigned int n)
{
    for (int i = 0; i < iterations; i++)
    {
        std::cout << i << " < " << iterations << std::endl;
        int old_size = line.size();
        line.resize(line.size() * 2);
        for (int j = 0; j < old_size; j++)
        {
            line[line.size() - 1 - j * 2] = line[old_size - 1 - j];
            line[line.size() - 2 - j * 2] = line[old_size - 1 - j];
        }
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < line.size() - 1 - j; k++)
            {
                line[k] = (line[k] + line[k + 1]) * glm::vec3(1.0 / 2, 1.0 / 2, 1.0 / 2);
            }
        }
        line.resize(line.size() - n);
    }
    return line;
}