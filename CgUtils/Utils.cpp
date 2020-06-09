#include "Utils.h"
#include <iostream>
#include <numeric>
#include <glm/gtx/string_cast.hpp>

void Utils::createNormals(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &triangle_indices, std::vector<glm::vec3> &face_normals, std::vector<glm::vec3> &vertex_normals)
{
    // vertex_normals.clear();
    // face_normals.clear();
    std::vector<std::vector<glm::vec3>> vertex_normals_raw{};
    vertex_normals_raw.resize(vertices.size());
    for (int i = 0; i < triangle_indices.size(); i += 3)
    {
        auto p_0 = vertices[triangle_indices[i]];
        auto p_1 = vertices[triangle_indices[i + 1]];
        auto p_2 = vertices[triangle_indices[i + 2]];

        auto normal = glm::normalize(glm::cross(p_1 - p_0, p_2 - p_0));
        face_normals.push_back(normal);

        vertex_normals_raw[triangle_indices[i]].push_back(normal);
        vertex_normals_raw[triangle_indices[i + 1]].push_back(normal);
        vertex_normals_raw[triangle_indices[i + 2]].push_back(normal);
    }

    for (std::vector<glm::vec3> &normals : vertex_normals_raw)
    {
        auto sum_of_elems = glm::vec3(0.0, 0.0, 0.0);
        for (auto &p : normals)
        {
            sum_of_elems += p;
        }
        auto vertex_normal = glm::normalize(sum_of_elems / (float)normals.size());
        vertex_normals.push_back(vertex_normal);
    }
}

std::vector<glm::vec3> Utils::laneRiesenfeld(std::vector<glm::vec3> line, unsigned int iterations, unsigned int n)
{
    for (int i = 0; i < iterations; i++)
    {
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
