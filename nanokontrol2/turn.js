//turn.js 
//compute inverse kinematics
var ref = require('ref');
var ffi = require('ffi');

var ArrayType = require('ref-array');
var int = ref.types.int;
var float = ref.types.float;
var double = ref.types.double;
var IntArray = ArrayType(int);
var FloatArray = ArrayType(float);
var ArrayArray = ArrayType(IntArray);

//declare constant
var re = 90;
var D = 68;
var lc = 268;
var rb = 180.38;
var Pz = 438.17;

var phi = Math.PI/24; //% rotation around X axis
var theta = Math.PI/12; //% rotation around Y axis
var psi = Math.PI/16; //% rotation around Z axis

var xd = 50;
var yd = 50;
var zd = Pz;

var MySolver = ffi.Library('./mysolver', {
  // 'hello': [ 'void', [] ]
  'solveInverseMechanism': [FloatArray, ['float','float','float','float','float','float','float','float','float','float','float']]
  // "computeSliderControl": [ 'pointer', ['float','float','float','float','float','float','float','float','float','float','float'] ]
  // "computeLinkPos": ['pointer', ['pointer', 'pointer', 'pointer', 'pointer', 'pointer']],
  // "computeActuation" : ['pointer',['pointer', 'float']]
});

// MySolver.hello();
// MySolver.computeSliderControl(re,rb,lc,D,Pz,xd,yd,zd,phi,theta,psi);
var C = MySolver.solveInverseMechanism(re,rb,lc,D,Pz,xd,yd,zd,phi,theta,psi);
console.log(C);

