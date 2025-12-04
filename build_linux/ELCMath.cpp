#include "ELCMath.h"
#include <cmath>

namespace ELC {

float Lerp(float a, float b, float t) {
    return a + (b - a) * Clamp(t, 0.0f, 1.0f);
}

float Clamp(float value, float min, float max) {
    return std::fmax(min, std::fmin(max, value));
}

Vec2 Normalize(Vec2 v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    if (len > 0) return {v.x / len, v.y / len};
    return {0, 0};
}

}
