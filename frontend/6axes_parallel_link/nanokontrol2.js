var nanoKONTROL = require('korg-nano-kontrol');
var serialport = require("serialport");
var SerialPort = serialport.SerialPort
var port = new SerialPort("/dev/tty.usbmodem1411", {
  baudrate: 115200,
  parser: serialport.parsers.readline('\n')
}
);

var step = 20;
var initialHeight = 100;

var inverse_mechanism = require('./inverse_mechanism');
var turn = inverse_mechanism().turn;
var tilt = inverse_mechanism().tilt;

port.on('open', function () {
  console.log("serial port open");
});

port.on('data', function (data) {
  console.log('Received: ' + data);
});

var COMMAND = {
  UP1   : 1, 
  DOWN1 : 2, 
  UP2   : 3, 
  DOWN2 : 4, 
  UP3   : 5, 
  DOWN3 : 6, 
  UP4   : 7, 
  DOWN4 : 8, 
  UP5   : 9, 
  DOWN5 : 10, 
  UP6   : 11, 
  DOWN6 : 12
};


const divider = 5;
function sendManualDestination(printer){
  dest1 = initialHeight + printer.dest1/divider;
  dest2 = initialHeight + printer.dest2/divider;
  dest3 = initialHeight + printer.dest3/divider;
  dest4 = initialHeight + printer.dest4/divider;
  dest5 = initialHeight + printer.dest5/divider;
  dest6 = initialHeight + printer.dest6/divider;
  sentence = "{\"slider\":\""+"manual"+"\",\"dest1\":\""+dest1+"\",\"dest2\":\""+dest2+"\",\"dest3\":\""+dest3+"\",\"dest4\":\""+dest4+"\",\"dest5\":\""+dest5+"\",\"dest6\":\""+dest6+"\"}\n"
  port.write(sentence, function(err,bytesWritten){
    if(err){
      return console.log('Error: ',err.message);
    }
  });
}

function sendDump(){
  sentence = "{\"dump\":\""+"all"+"\"}\n"
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

function sendHoming(){
  sentence = "{\"home\":\""+"g28"+"\"}\n"
  port.write(sentence, function(err,bytesWritten){
    if(err){
      return console.log('Error: ',err.message);
    }
  });
}

function sendStandBy(){
  sentence = "{\"standby\":\""+"go"+"\"}\n"
  port.write(sentence, function(err,bytesWritten){
    if(err){
      return console.log('Error: ',err.message);
    }
  });
}

function sendToggleMode(){
  sentence = "{\"mode\":\""+"select"+"\"}\n"
  port.write(sentence, function(err,bytesWritten){
    if(err){
      return console.log('Error: ',err.message);
    }
  });
}

function sendATC(direction){
  if(direction==="CW"){
    sentence = "{\"atc\":\""+"CW"+"\"}\n"
  } else if(direction==="CCW"){
    sentence = "{\"atc\":\""+"CCW"+"\"}\n"
  }
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
  device.on('slider:1', function(value){
    printer.dest1 = value;
    if(printer.dest1 % step ==1){
      console.log("slider:1 >>> "+value);
      sendManualDestination(printer);
    }
  });
  device.on('slider:2', function(value){
    printer.dest2 = value;
    if(printer.dest2 % step ==1){
      console.log("slider:2 >>> "+value);
      sendManualDestination(printer);
    }
  });
  device.on('slider:3', function(value){
    printer.dest3 = value;
    if(printer.dest3 % step ==1){
      console.log("slider:3 >>> "+value);
      sendManualDestination(printer);
    }
  });
  device.on('slider:4', function(value){
    printer.dest4 = value;
    if(printer.dest4 % step ==1){
      console.log("slider:4 >>> "+value);
      sendManualDestination(printer);
    }
  });
  device.on('slider:5', function(value){
    printer.dest5 = value;
    if(printer.dest5 % step ==1){
      console.log("slider:5 >>> "+value);
      sendManualDestination(printer);
    }
  });
  device.on('slider:6', function(value){
    printer.dest6 = value;
    if(printer.dest6 % step ==1){
      console.log("slider:6 >>> "+value);
      sendManualDestination(printer);
    }
  });
  device.on('button:s:1', function(value){
    if(value){
      console.log("button:s:1>>> "+value);
      sendJog(COMMAND.UP1);
    }
  });
  device.on('button:r:1', function(value){
    if(value){
      console.log("button:r:1>>> "+value);
      sendJog(COMMAND.DOWN1);
    }
  });
  device.on('button:s:2', function(value){
    if(value){
      console.log("button:s:2>>> "+value);
      sendJog(COMMAND.UP2);
    }
  });
  device.on('button:r:2', function(value){
    if(value){
      console.log("button:r:2>>> "+value);
      sendJog(COMMAND.DOWN2);
    }
  });
  device.on('button:s:3', function(value){
    if(value){
      console.log("button:s:3>>> "+value);
      sendJog(COMMAND.UP3);
    }
  });
  device.on('button:r:3', function(value){
    if(value){
      console.log("button:r:3>>> "+value);
      sendJog(COMMAND.DOWN3);
    }
  });
  device.on('button:s:4', function(value){
    if(value){
      console.log("button:s:4>>> "+value);
      sendJog(COMMAND.UP4);
    }
  });
  device.on('button:r:4', function(value){
    if(value){
      console.log("button:r:4>>> "+value);
      sendJog(COMMAND.DOWN4);
    }
  });
  device.on('button:s:5', function(value){
    if(value){
      console.log("button:s:5>>> "+value);
      sendJog(COMMAND.UP5);
    }
  });
  device.on('button:r:5', function(value){
    if(value){
      console.log("button:r:5>>> "+value);
      sendJog(COMMAND.DOWN5);
    }
  });
  device.on('button:s:6', function(value){
    if(value){
      console.log("button:s:6>>> "+value);
      sendJog(COMMAND.UP6);
    }
  });
  device.on('button:r:6', function(value){
    if(value){
      console.log("button:r:6>>> "+value);
      sendJog(COMMAND.DOWN6);
    }
  });

  device.on('button:play', function(value){
    if(value){
      console.log("button:play >>> "+value);
      console.log("dumpAll()");
      sendDump();      
    }
  });

  device.on('button:rec', function(value){
    if(value){
      console.log("home axis.");
      sendHoming();      
    }
  });


  device.on('button:stop', function(value){
    console.log("button:stop >>> "+value);
    if(value === false){
      console.log('exit!!');
      device.close();
    }
  });

  //PRESET CONTROL//
  device.on('button:m:1', function(value){
    if(value){
      console.log("TURN");
      turn(port);
    }
  });
  device.on('button:m:2', function(value){
    if(value){
      console.log("TILT");
      tilt(port);
    }
  });
  device.on('button:m:3', function(value){
    if(value){
      console.log("STAND BY");
      sendStandBy();
    }
  });
  device.on('button:m:4', function(value){
    if(value){
      console.log("Toggle mode");
      sendToggleMode();
    }
  });

  device.on('button:marker:next', function(value){
    if(value){
      console.log("Rotate ATC: Clockwise");
      sendATC("CW");      
    }
  });

  device.on('button:marker:prev', function(value){
    if(value){
      console.log("Rotate ATC: Counter Clockwise");
      sendATC("CCW");      
    }
  });

})
.catch(function(err){
  console.error(err);
});

