var nanoKONTROL = require('korg-nano-kontrol');
var serialport = require("serialport");
var SerialPort = serialport.SerialPort
var port = new SerialPort("/dev/tty.usbmodem1411", {
  baudrate: 115200,
  parser: serialport.parsers.readline('\n')
}
);

port.on('open', function () {
  console.log("serial port open");
});

port.on('data', function (data) {
  console.log('Received: ' + data);
});

function sendDestination(printer){
  dist1 = printer.dist1;
  dist2 = printer.dist2;
  dist3 = printer.dist3;
  dist4 = printer.dist4;
  dist5 = printer.dist5;
  dist6 = printer.dist6;
  sentence = "{\"dist1\":\""+dist1+"\",\"dist2\":\""+dist2+"\",\"dist3\":\""+dist3+"\",\"dist4\":\""+dist4+"\",\"dist5\":\""+dist5+"\",\"dist6\":\""+dist6+"\"}\n"
  port.write(sentence, function(err,bytesWritten){
    if(err){
      return console.log('Error: ',err.message);
    }
    // console.log(bytesWritten, 'bytes written');
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
    console.log("slider:1 >>> "+value);
    printer.dist1 = value;
    sendDestination(printer);
  });
  device.on('slider:2', function(value){
    console.log("slider:2 >>> "+value);
    printer.dist2 = value;
    sendDestination(printer);
  });
  device.on('slider:3', function(value){
    console.log("slider:3 >>> "+value);
    printer.dist3 = value;
    sendDestination(printer);
  });
  device.on('slider:4', function(value){
    console.log("slider:4 >>> "+value);
    printer.dist4 = value;
    sendDestination(printer);
  });
  device.on('slider:5', function(value){
    console.log("slider:5 >>> "+value);
    printer.dist5 = value;
    sendDestination(printer);
  });
  device.on('slider:6', function(value){
    console.log("slider:6 >>> "+value);
    printer.dist6 = value;
    sendDestination(printer);
  });
  
  // device.on('knob:1', function(value){
  //   console.log("knob:1 >>> "+value);
  // });
  //
  // device.on('button:play', function(value){
  //   console.log("button:play >>> "+value);
  // });

  device.on('button:stop', function(value){
    console.log("button:stop >>> "+value);
    if(value === false){
      console.log('exit!!');
      device.close();
    }
  });

  // catch all slider/knob/button event
  // device.on('slider:*', function(value){
  //   console.log(this.event+' => '+value);
  //
  // });

  // device.on('knob:*', function(value){
  //   console.log(this.event+' => '+value);
  // });
  //
  // device.on('button:**', function(value){
  //   console.log(this.event+' => '+value);
  // });

})
.catch(function(err){
  console.error(err);
});

