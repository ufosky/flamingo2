
#include "FL/Components/PositionComp.h"

#include <iostream>

PositionComp::PositionComp() : Component(FL_COMPTYPE_POSITION) {
    pos << 0, 0, 0;
    size << 0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;
}

PositionComp::PositionComp(Eigen::Vector3f *p) : Component(FL_COMPTYPE_POSITION) {
    pos = *p;
    size << 0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;
}

PositionComp::PositionComp(Eigen::Vector3f *p, Eigen::Matrix<float,3,4> *s) : Component(FL_COMPTYPE_POSITION) {
    pos = *p;
    size = *s;
}

PositionComp::PositionComp(float x, float y) : Component(FL_COMPTYPE_POSITION) {
    pos << x, y, 0;
    size << 0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;
}

PositionComp::PositionComp(float x, float y, float w, float h) : Component(FL_COMPTYPE_POSITION) {
    pos << x, y, 0;
    size << -w / 2, w / 2,  w / 2, -w / 2,
            -h / 2, -h / 2, h / 2, h / 2,
            0,      0,      0,     0;
}

PositionComp::PositionComp(SDL_Rect *r) : Component(FL_COMPTYPE_POSITION) {
    pos << r->x + r->w / 2, r->y - r->h / 2, 0;
    size << -r->w / 2, r->w / 2,  r->w / 2, -r->w / 2,
            -r->h / 2, -r->h / 2, r->h / 2, r->h / 2,
            0,         0,         0,        0;
}

PositionComp::~PositionComp() {

}

