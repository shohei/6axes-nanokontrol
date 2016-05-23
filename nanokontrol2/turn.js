//turn.js 
//compute inverse kinematics
var ref = require('ref');
var ffi = require('ffi');

var ArrayType = require('ref-array');
var float = ref.types.float;
var FloatArray = ArrayType(float);
var result = new FloatArray(6);

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
  'solveInverseMechanism': ['void', [FloatArray,'float','float','float','float','float','float','float','float','float','float','float']]
});

MySolver.solveInverseMechanism(result,re,rb,lc,D,Pz,xd,yd,zd,phi,theta,psi);
for(var i=0;i<result.length;i++){
	console.log(result[i]);
}
