#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "mysolver.h"

using namespace std;
using namespace Eigen;

int main(void){
// - スライダー間距離D[mm]        : 56+(12/2)*2=68mm
// - ロッド長さlc[mm]                  : 262+(8/2)*2=268mm
// - スライダー設置半径rb[mm]    : sqrt(269.7^2-200.5^2)=180.38248
// - テーブル半径re[mm]               :90mm
// - テーブル初期高さPz[mm]       :438.17mm
  float re = 90;
  float D = 68;
  float lc = 268;
  float rb = 180.38;
  float Pz = 438.17;

  float phi = M_PI/24; //% rotation around X axis
  float theta = M_PI/12; //% rotation around Y axis
  float psi = M_PI/16; //% rotation around Z axis

  float xd = 50;
  float yd = 50;
  float zd = Pz;

  MatrixXf C(1,6);
  C << computeSliderControl(re,rb,lc,D,Pz,xd,yd,zd,phi,theta,psi);
  cout << "*** C:  " << endl << C << endl;

}
