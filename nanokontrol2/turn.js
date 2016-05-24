//turn.js 
//compute inverse kinematics

module.exports = function(port){
	var ref = require('ref');
	var ffi = require('ffi');

	var ArrayType = require('ref-array');
	var float = ref.types.float;
	var FloatArray = ArrayType(float);
	var result = new FloatArray(6);

	var MySolver = ffi.Library('./mysolver', {
		'solveInverseMechanism': ['void', [FloatArray,'float','float','float','float','float','float','float','float','float','float','float']]
	});

	var constant = require('./constant');
	const re = constant().re;
	const D =  constant().D;
	const lc = constant().lc;
	const rb = constant().rb;
	const Pz = constant().Pz;

    // P = [0.1-i_time/200,0.2+i_time/200,Pz]; % Position Vector of the end effector
    // phi = pi/12*(i_time/10); % rotation around X axis
    // theta = pi/12*(i_time/10); % rotation around Y axis
    // psi = pi/16*(i_time/10); % rotation around Z axis

	for(var i=0;i<360;i=i+10){
		doSetTimeout(i);
	}

	function doSetTimeout(i){
		// setTimeout(function() { calculationAndSend(i); }, i*50);
		setTimeout(function() { calculationAndSend(i); }, i*10);
	}

	function calculationAndSend(i){
		var phi = 0; 
		var theta = 0; 
		var psi = 0; 
		var xd = 100*Math.cos(i/180*Math.PI);
		var yd = 100*Math.sin(i/180*Math.PI);
		var zd = Pz;

		MySolver.solveInverseMechanism(result,re,rb,lc,D,Pz,xd,yd,zd,phi,theta,psi);
		dest1 = result[0];
		dest2 = result[1];
		dest3 = result[2];
		dest4 = result[3];
		dest5 = result[4];
		dest6 = result[5];
		sentence = "{\"dest1\":\""+dest1+"\",\"dest2\":\""+dest2+"\",\"dest3\":\""+dest3+"\",\"dest4\":\""+dest4+"\",\"dest5\":\""+dest5+"\",\"dest6\":\""+dest6+"\"}\n"
		console.log(i);
		console.log(sentence);
		port.write(sentence, function(err,bytesWritten){
			if(err){
				return console.log('Error: ',err.message);
			}
		});
	}
}