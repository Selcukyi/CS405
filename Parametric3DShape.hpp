#ifndef PARAMETRIC3DSHAPE_HPP
#define PARAMETRIC3DSHAPE_HPP

#include "glm.hpp"
#include "gtc/constants.hpp"
#include "gtx/rotate_vector.hpp"
#include "gtx/transform.hpp"
#include "common.hpp"
#include "gtc/type_ptr.hpp"
#include "ParametricLine.hpp";

#include "Model3D.hpp"
#include <vector>
using namespace std;

class Parametric3DShape
{
public:
    static Model3D generate(glm::vec2(*parametricLine)(float),
        unsigned vertical,
        unsigned rotation);

private:
    static glm::vec3 rotated(float t, float r, glm::vec2(*parametricLine)(float));
    static unsigned int VHtoIndex(int v, int h, int max_v, int max_h);

    static vector<glm::vec3> fillPositions(glm::vec2(*parametricLine)(float), unsigned vertical, unsigned rotation);
    static vector<glm::vec3> fillNormals(glm::vec2(*parametricLine)(float), unsigned vertical, unsigned rotation);
    static vector<unsigned int> fillIndices(glm::vec2(*parametricLine)(float), unsigned vertical, unsigned rotation);
    static glm::vec3 parametricSurface(glm::vec2(*parametricLine)(float), float t, float r);

};

Model3D Parametric3DShape::generate(glm::vec2(*parametricLine)(float),
    unsigned vertical,
    unsigned rotation)
{
    vector<glm::vec3> positions = fillPositions(parametricLine, vertical, rotation);
    vector<glm::vec3> normals = fillNormals(parametricLine, vertical, rotation);
    vector<unsigned int> indices = fillIndices(parametricLine, vertical, rotation);

    return Model3D(positions, normals, indices);
}

glm::vec3 Parametric3DShape::rotated(float t, float r, glm::vec2(*parametricLine)(float))
{
    glm::vec3 point = glm::vec3((*parametricLine)(t), 0);

    return glm::rotateY(point, r * glm::two_pi<float>());
}

unsigned int Parametric3DShape::VHtoIndex(int v, int h, int max_v, int max_h)
{
    return (h % max_h) * max_v + v;
}

vector<glm::vec3> Parametric3DShape::fillPositions(glm::vec2(*parametricLine)(float), unsigned vertical, unsigned rotation)
{
    vector<glm::vec3> positions;

    // fill positions
    for (int h = 0; h < rotation; h++)
    {
        for (int v = 0; v < vertical; v++)
        {
            float t = (float)v / (vertical - 1);
            float r = (float)h / rotation;
            positions.push_back(rotated(t, r, parametricLine));
        }
    }

    return positions;
}

vector<unsigned int> Parametric3DShape::fillIndices(glm::vec2(*parametricLine)(float), unsigned vertical, unsigned rotation)
{
    vector<unsigned int> indices;

    for (int r = 0; r < rotation; r++)
    {
        for (int v = 0; v < vertical - 1; v++)
        {
            indices.push_back(VHtoIndex(v, r, vertical, rotation));
            indices.push_back(VHtoIndex(v + 1, r, vertical, rotation));
            indices.push_back(VHtoIndex(v, r + 1, vertical, rotation));

            indices.push_back(VHtoIndex(v, r + 1, vertical, rotation));
            indices.push_back(VHtoIndex(v + 1, r, vertical, rotation));
            indices.push_back(VHtoIndex(v + 1, r + 1, vertical, rotation));
        }
    }

    return indices;
}

vector<glm::vec3> Parametric3DShape::fillNormals(glm::vec2(*parametricLine)(float), unsigned vertical, unsigned rotation)
{
    vector<glm::vec3> normals;

    for (int r = 0; r < rotation; ++r)
    {
        for (int v = 0; v < vertical; ++v)
        {
            float nv = v / float(vertical - 1);
            float nr = r / float(rotation);
            float epsilonv = 1 / float(vertical - 1);
            float epsilonr = 1 / float(rotation);

            auto to_next_v = parametricSurface(parametricLine, nv + epsilonv, nr);
            auto from_prev_v = parametricSurface(parametricLine, nv, nr) - parametricSurface(parametricLine, nv - epsilonv, nr);
            auto tangent_v = (to_next_v + from_prev_v) / 2.0f;

            auto to_next_r = parametricSurface(parametricLine, nv, nr + epsilonr) - parametricSurface(parametricLine, nv, nr);
            auto from_prev_r = parametricSurface(parametricLine, nv, nr) - parametricSurface(parametricLine, nv, nr - epsilonr);
            auto tangent_r = (to_next_r + from_prev_r) / 2.0f;

            auto normal = glm::normalize(glm::cross(tangent_r, tangent_v));
            normals.push_back(normal);
        }
    }

    return normals;
}

glm::vec3 Parametric3DShape::parametricSurface(glm::vec2(*parametricLine)(float), float t, float r)
{
    glm::vec3 p = glm::vec3(parametricLine(t), 0.0f);
    return glm::rotateY(p, r * glm::two_pi<float>());
};

#endif