//todo: setTimeout and send location in every 1sec

var nanoKONTROL = require('korg-nano-kontrol');
var serialport = require("serialport");
var SerialPort = serialport.SerialPort
var port = new SerialPort("/dev/tty.usbmodem1411", {
  baudrate: 115200,
  parser: serialport.parsers.readline('\n')
}
);

var step = 20;

port.on('open', function () {
  console.log("serial port open");
});

port.on('data', function (data) {
  console.log('Received: ' + data);
});

var COMMAND = {
  TURN : 1, 
  TILT : 2, 
  TURN_TILT : 3, 
};

function turn(){

}

function tilt(){

}

function turn_and_tilt(){

}

function sendDestination(printer){
  dest1 = printer.dest1;
  dest2 = printer.dest2;
  dest3 = printer.dest3;
  dest4 = printer.dest4;
  dest5 = printer.dest5;
  dest6 = printer.dest6;
  sentence = "{\"dest1\":\""+dest1+"\",\"dest2\":\""+dest2+"\",\"dest3\":\""+dest3+"\",\"dest4\":\""+dest4+"\",\"dest5\":\""+dest5+"\",\"dest6\":\""+dest6+"\"}\n"
  port.write(sentence, function(err,bytesWritten){
    if(err){
      return console.log('Error: ',err.message);
    }
  });
}

function sendJog(jog_command){
  sentence = "{\"jog\":\""+jog_command+"\"}\n"
  port.write(sentence, function(err,bytesWritten){
    if(err){
      return console.log('Error: ',err.message);
    }
  });
}

function Printer(){
  this.dist1 = '';
  this.dist2 = '';
  this.dist3 = '';
  this.dist4 = '';
  this.dist5 = '';
  this.dist6 = '';
}

nanoKONTROL.connect()
.then(function(device){
  console.log('connected! ' + device.name);

  var printer = new Printer();  

  // register specific slider/knob/button event
  device.on('button:m:1', function(value){
    if(value){
      console.log("TURN");
      turn();
      console.log("TURN ended");
    }
  });
  device.on('button:m:2', function(value){
    if(value){
      console.log("TILT");
      tilt();
      console.log("TILT ended");
    }
  });
  device.on('button:m:3', function(value){
    if(value){
      console.log("TURN WITH TILT");
      turn_and_tilt();
      console.log("TURN WITH TILT ended");
    }
  });

  device.on('button:stop', function(value){
    console.log("button:stop >>> "+value);
    if(value === false){
      console.log('exit!!');
      device.close();
    }
  });


})
.catch(function(err){
  console.error(err);
});

