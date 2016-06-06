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
  float re = 45;
  float D = 68;
  float lc = 268;
  float rb = 90.2;
  float Pz = 100;
  float R_MOVE = 20;
  // float re = 90;
  // float D = 68;
  // float lc = 268;
  // float rb = 180.38;
  // float Pz = 438.17;
  // float Pz = 300;

  float phi = 0; //% rotation around X axis
  float theta = 0; //% rotation around Y axis
  float psi = 0; //% rotation around Z axis
  // float phi = M_PI/24; //% rotation around X axis
  // float theta = M_PI/12; //% rotation around Y axis
  // float psi = M_PI/16; //% rotation around Z axis

  float xd = R_MOVE;
  float yd = R_MOVE;
  float zd = Pz;


  float arrayf[6];
  solveInverseMechanism(arrayf,re,rb,lc,D,Pz,xd,yd,zd,phi,theta,psi);
  for(int i=0;i<6;i++){
     cout << arrayf[i] << endl;
  }
}
