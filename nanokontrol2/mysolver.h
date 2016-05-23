#ifndef _MYSOLVER_H
#define _MYSOLVER_H

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;

MatrixXf computeSliderControl(float re,float rb,float lc,float D,float Pz,float xd, float yd, float zd,float phi,float theta,float psi); 

#endif