
#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL/SDL.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>

class Screen {

    Eigen::Affine3f t;

    public:
        Screen();
        Screen(SDL_Rect *local);
        Screen(SDL_Rect *local, Eigen::Matrix<float,4,3> *bound);
        ~Screen();
        
        SDL_Rect local_rect;
        Eigen::Matrix<float,4,3> bound_rect;

        void LoadIdentity();
        void Draw();
        void Transform(Eigen::Affine3f transform);
};

#endif
