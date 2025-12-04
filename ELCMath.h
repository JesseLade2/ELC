#ifndef ELCMATH_H
#define ELCMATH_H

#include "ELC.h"

namespace ELC {
    float Lerp(float a, float b, float t);
    float Clamp(float value, float min, float max);
    Vec2 Normalize(Vec2 v);
}

#endif
