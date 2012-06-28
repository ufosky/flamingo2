 
#ifndef POSITIONCOMP_H_
#define POSITIONCOMP_H_ 

class PositionComp;

#include "FL/Entity/Component.h"
#include "FL/Components/FlComponents.h"

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <SDL/SDL.h>

class PositionComp : public Component {
	public:
		PositionComp();
		PositionComp(Eigen::Vector3f *pos);
		PositionComp(Eigen::Vector3f *pos, Eigen::Matrix<float,3,4> *size);
		PositionComp(float x, float y);
		PositionComp(float x, float y, float width, float height);
        PositionComp(SDL_Rect *r);
		~PositionComp();

		void Init();
		void Process();
		void Cleanup();

        Eigen::Vector3f pos;
        Eigen::Matrix<float,3,4> size;

	protected:
		void _SetType() { _type = FL_COMPTYPE_POSITION; };
};

#endif

