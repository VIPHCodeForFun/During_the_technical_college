#include "Angle.h"

float Angle::getDegrees() const {
    return this->degrees;
} // getDegree(Angle* this)

/*
float getDegrees(Angle* t) {
    return t->degrees;
}
*/

void Angle::setDegrees(const float& degrees) {
    if (degrees > 360.0f)
        return;
    this->degrees = degrees;
}
