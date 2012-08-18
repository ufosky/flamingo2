 
#ifndef POSITIONCOMP_H_
#define POSITIONCOMP_H_ 

class PositionComp;

#include "FL/Entity/Component.h"
#include "FL/Components/FLComponents.h"

#include "eigen3/Eigen/Dense"
#include "SDL.h"


class PositionComp : public Component {
	public:
		PositionComp();
		PositionComp(Eigen::Vector3f *pos);
		PositionComp(float x, float y);
		PositionComp(float x, float y, float width, float height);
        PositionComp(SDL_Rect *r);
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

        const Eigen::Vector3f *GetPoint(int corner);
        float GetCornerX(int corner);
        float GetCornerY(int corner);

    private:
        float _x, _y, _w, _h;
        
        Eigen::Vector3f _pos;
        Eigen::Matrix<float,3,4> _dim;

        void _Reset();

        virtual char *Columns();
        virtual char *DumpRow();
};

#endif

