#include "glm.hpp"
#include "gtc/constants.hpp"
#include "gtx/rotate_vector.hpp"
#include "gtx/transform.hpp"
#include "common.hpp"
#include "gtc/type_ptr.hpp"

namespace ParametricLine
{
    glm::vec2 halfCircle(float t)
    {
        // [0, 1]
        t -= 0.5;
        // [-0.5, 0.5]
        t *= glm::pi<float>();
        // [-PI/2, PI/2]

        return glm::vec2(cos(t), sin(t));
    }

    glm::vec2 circle(float t)
    {
        // [0, 1]
        t -= 0.5;
        // [-0.5, 0.5]
        t *= glm::two_pi<float>();
        // [-PI, PI]

        auto c = glm::vec2(0.7, 0);
        float r = 0.3;
        return glm::vec2(cos(t), sin(t)) * r + c;
    };

    glm::vec2 spikes(float t)
    {
        // [0, 1]
        t -= 0.5;
        // [-0.5, 0.5]
        t *= glm::two_pi<float>();
        // [-PI, PI]

        auto c = glm::vec2(0.7, 0);
        float r = 0.3;
        float a = 2 + 4 * 2;
        return (glm::vec2(cos(t) + sin(a * t) / a, sin(t) + cos(a * t) / a)) * r + c;
    };
}
