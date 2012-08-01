
%module positioncomp
%{
#include "FL/Components/PositionComp.h"
%}

class PositionComp : public Component {
    public:
        PositionComp();
        PositionComp(float x, float y);
        PositionComp(float x, float y, float width, float height);
        ~PositionComp();

        float GetX();
        void SetX(float x);

        float GetY();
        void SetY(float y);

        float GetWidth();
        void SetWidth(float w);

        float GetHeight();
        void SetHeight(float h);

        void SetPos(float x, float y);
        void SetDim(float w, float h);

        float GetCornerX(int corner);
        float GetCornerY(int corner);
};

