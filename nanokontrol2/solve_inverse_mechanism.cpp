#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <cmath>

using namespace Eigen;
using namespace std;
MatrixXf computeLinkPos(MatrixXf L, MatrixXf P, Matrix3f R, MatrixXf s, MatrixXf pb);
MatrixXf computeActuation(MatrixXf L, float lc);

MatrixXf computeSliderControl(float re,float rb,float lc,float D,float Pz,float xd, float yd, float zd,float phi,float theta,float psi) {
  // void computeSliderControl(float re,float rb,float lc,float D,float Pz,float xd, float yd, float zd,float phi,float theta,float psi) {
  // - スライダー間距離D[mm]        : 56+(12/2)*2=68mm
  // - ロッド長さlc[mm]                  : 262+(8/2)*2=268mm
  // - スライダー設置半径rb[mm]    : sqrt(269.7^2-200.5^2)=180.38248
  // - テーブル半径re[mm]               :90mm
  // - テーブル初期高さPz[mm]       :438.17mm
  // float re = 90;
  // float Pz = 438.17;
  // float D = 68;
  // float lc = 268;
  // float rb = 180.38;

  float th = asin(D/(2*rb)); //% theta1: angle (linear actuator)
  float th2 = asin(D/(2*re)); //% theta2: angle (end effector)

  MatrixXf pb(6,3);
  pb << 
    rb*cos(th),rb*sin(th),0,
    rb*cos(-th),rb*sin(-th),0,
    rb*cos(2*M_PI/3+th),rb*sin(2*M_PI/3+th),0,
    rb*cos(2*M_PI/3-th),rb*sin(2*M_PI/3-th),0,
    rb*cos(4*M_PI/3+th),rb*sin(4*M_PI/3+th),0,
    rb*cos(4*M_PI/3-th),rb*sin(4*M_PI/3-th),0;

  MatrixXf s_local(6,3);
  s_local << 
    re*cos(th2),re*sin(th2),0,
    re*cos(-th2),re*sin(-th2),0,
    re*cos(2*M_PI/3+th2),re*sin(2*M_PI/3+th2),0,
    re*cos(2*M_PI/3-th2),re*sin(2*M_PI/3-th2),0,
    re*cos(4*M_PI/3+th2),re*sin(4*M_PI/3+th2),0,
    re*cos(4*M_PI/3-th2),re*sin(4*M_PI/3-th2),0;

  MatrixXf sliders(6,3);
  sliders <<
    rb*cos(th),rb*sin(th),Pz,
    rb*cos(-th),rb*sin(-th),Pz,
    rb*cos(2*M_PI/3+th),rb*sin(2*M_PI/3+th),Pz,
    rb*cos(2*M_PI/3-th),rb*sin(2*M_PI/3-th),Pz,
    rb*cos(4*M_PI/3+th),rb*sin(4*M_PI/3+th),Pz,
    rb*cos(4*M_PI/3-th),rb*sin(4*M_PI/3-th),Pz;

  // float phi = M_PI/24; //% rotation around X axis
  // float theta = M_PI/12; //% rotation around Y axis
  // float psi = M_PI/16; //% rotation around Z axis

  Matrix3f R;
  R << 
    cos(phi)*cos(theta),cos(phi)*sin(theta)*sin(psi)-sin(phi)*cos(psi),cos(phi)*sin(theta)*cos(psi)+sin(phi)*sin(psi),
    sin(phi)*cos(theta),sin(phi)*sin(theta)*sin(psi)+cos(phi)*cos(psi),sin(phi)*sin(theta)*cos(psi)-cos(phi)*sin(psi),
    -sin(theta),cos(theta)*sin(psi),cos(theta)*cos(psi);

  Vector3f a;
  a << 0,0,1;

  MatrixXf s(6,3);
  s = s_local*R;//6x3 x 3x3 => 6x3

  MatrixXf P(1,3);
  P << xd,yd,zd; //% Position Vector of the end effector
  // P << 50,50,height; //% Position Vector of the end effector

  // cout << "*** re: " << endl << s << endl;
  // cout << "*** rb: " << endl << rb << endl;
  // cout << "*** pb:  " << endl << pb << endl;
  // cout << "*** R:  " << endl<< R << endl;

  MatrixXf L(6,3);
  L << computeLinkPos(L, P, R, s, pb); 
  // cout << "*** L:  " << endl << L << endl;

  MatrixXf C(1,6);
  C << computeActuation(L,lc);
  // cout << "*** C:  " << endl << C << endl;

  return C;
}  

// %% compute position vector of rod end of end effector
MatrixXf computeLinkPos(MatrixXf L, MatrixXf P, Matrix3f R, MatrixXf s, MatrixXf pb){
  // L = P + R*s - pb;
  for(int i=0;i<6;i++){
    L.block(i,0,1,3) << P + (s.block(i,0,1,3))*R - pb.block(i,0,1,3);
  }
  return L;
}

MatrixXf computeActuation(MatrixXf L, float lc){
  MatrixXf C(1,6); 
  for (int i=0;i<6;i++){
    float lxi = L(i,0);
    float lyi = L(i,1);
    float lzi = L(i,2);
    C.block(0,i,1,1) << lzi - sqrt(lc*lc-lxi*lxi-lyi*lyi);
  }
  return C;
}


extern "C" {

  void hello(){
    cout << "hello" << endl; 
  }

}
