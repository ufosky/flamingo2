
#include "FL/Components/PositionComp.h"

#include <iostream>

PositionComp::PositionComp() {
	_SetType();
    pos << 0, 0, 0;
    size << 0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;
}

PositionComp::PositionComp(Eigen::Vector3f *p) {
	_SetType();
    pos = *p;
    size << 0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;
}

PositionComp::PositionComp(Eigen::Vector3f *p, Eigen::Matrix<float,3,4> *s) {
	_SetType();
    pos = *p;
    size = *s;

}

PositionComp::PositionComp(float x, float y) {
	_SetType();
    pos << x, y, 0;
    size << 0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0;
}

PositionComp::PositionComp(float x, float y, float w, float h) {
	_SetType();
    pos << x, y, 0;
    size << -w / 2, w / 2,  w / 2, -w / 2,
            -h / 2, -h / 2, h / 2, h / 2,
            0,      0,      0,     0;
}

PositionComp::PositionComp(SDL_Rect *r) {
    _SetType();
    pos << r->x + r->w / 2, r->y - r->h / 2, 0;
    size << -r->w / 2, r->w / 2,  r->w / 2, -r->w / 2,
            -r->h / 2, -r->h / 2, r->h / 2, r->h / 2,
            0,         0,         0,        0;
}

PositionComp::~PositionComp() {

}

void PositionComp::Init() {

}

void PositionComp::Process() {

}

void PositionComp::Cleanup() {

}

