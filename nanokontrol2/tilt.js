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
	const zi = constant().zi;
	const R_MOVE = constant().R_MOVE;

	//Compute initial height: Pz
	const alpha = Math.asin(D/(2*re));
	const beta = Math.asin(D/(2*rb));
	const m = 2*re*Math.cos(Math.PI/3-alpha);
	const n = 2*rb*Math.cos(Math.PI/3-beta);
	const h = lc*Math.sqrt(1-Math.pow((m-n)/(2*lc),2));
	const Pz = h + zi;


	for(var i=0;i<361;i=i+60){
		doSetTimeout(i);
	}

	function doSetTimeout(i){
		// setTimeout(function() { calculationAndSend(i); }, i*50);
		setTimeout(function() { calculationAndSend(i); }, i*15);
	}

	function calculationAndSend(i){
       	const pi_over_32 = Math.PI / 32.0;
		var phi = pi_over_32*Math.sin(i/(180.0)*Math.PI); 
		var theta = pi_over_32*Math.sin(i/(180.0)*Math.PI - 2/3*Math.PI); 
		var psi = pi_over_32*Math.sin(i/(180.0)*Math.PI - 4/3*Math.PI); 
		var xd = 0;
		var yd = 0;
		var zd = Pz;

		MySolver.solveInverseMechanism(result,re,rb,lc,D,Pz,xd,yd,zd,phi,theta,psi);
		dest1 = result[0];
		dest2 = result[1];
		dest3 = result[2];
		dest4 = result[3];
		dest5 = result[4];
		dest6 = result[5];
		sentence = "{\"auto\":\""+"command"+"\",\"dest1\":\""+dest1+"\",\"dest2\":\""+dest2+"\",\"dest3\":\""+dest3+"\",\"dest4\":\""+dest4+"\",\"dest5\":\""+dest5+"\",\"dest6\":\""+dest6+"\"}\n"
		console.log(i);
		console.log(sentence);
		port.write(sentence, function(err,bytesWritten){
			if(err){
				return console.log('Error: ',err.message);
			}
		});
	}

}
