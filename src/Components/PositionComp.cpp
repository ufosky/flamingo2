
#include "FL/Components/PositionComp.h"
#include <sqlite3.h>

PositionComp::PositionComp() : Component(FL_COMPTYPE_POSITION) {
    _x = 0;
    _y = 0;
    _w = 0;
    _h = 0;
    _Reset();
}

PositionComp::PositionComp(Eigen::Vector3f *p) : Component(FL_COMPTYPE_POSITION) {
    _x = (*p)(0);
    _y = (*p)(1);
    _w = 0;
    _h = 0;
    _Reset();
}

PositionComp::PositionComp(float x, float y) : Component(FL_COMPTYPE_POSITION) {
    _x = x;
    _y = y;
    _w = 0;
    _h = 0;
    _Reset();
}

PositionComp::PositionComp(float x, float y, float w, float h) : Component(FL_COMPTYPE_POSITION) {
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    _Reset();
}

PositionComp::PositionComp(SDL_Rect *r) : Component(FL_COMPTYPE_POSITION) {
    _x = r->x;
    _y = r->y;
    _w = r->w;
    _h = r->h;
    _Reset();
}

PositionComp::~PositionComp() {

}

void PositionComp::_Reset() {
    _pos << _x, _y, 0;
    _dim << -_w / 2, _w / 2,  _w / 2, -_w / 2,
            -_h / 2, -_h / 2, _h / 2, _h / 2,
            0,       0,       0,      0;
}

float PositionComp::GetX() {
    return _x;
}

void PositionComp::SetX(float x) {
    _x = x;
    _Reset();
}


float PositionComp::GetY() {
    return _y;
}

void PositionComp::SetY(float y) {
    _y = y;
    _Reset();
}


float PositionComp::GetWidth() {
    return _w;
}

void PositionComp::SetWidth(float w) {
    _w = w;
    _Reset();
}


float PositionComp::GetHeight() {
    return _h;
}

void PositionComp::SetHeight(float h) {
    _h = h;
    _Reset();
}


void PositionComp::SetPos(float x, float y) {
    _x = x;
    _y = y;
    _Reset();
}

void PositionComp::SetDim(float w, float h) {
    _w = w;
    _h = h;
    _Reset();
}

const Eigen::Vector3f *PositionComp::GetPoint(int corner) {

    if (corner <= 3) {
        return new Eigen::Vector3f(_dim.col(corner));
    }
    return NULL;
}

float PositionComp::GetCornerX(int corner) {

    return _dim(0, corner);
}

float PositionComp::GetCornerY(int corner) {

    return _dim(1, corner);
}

char *PositionComp::Columns() {
    return (char *)", x real, y real, w real, h real";
}

char *PositionComp::DumpRow() {
    return sqlite3_mprintf(", %f, %f, %f, %f", _x, _y, _w, _h);
}

