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
    printer.dest1 = value;
    sendDestination(printer);
  });
  device.on('slider:2', function(value){
    console.log("slider:2 >>> "+value);
    printer.dest2 = value;
    sendDestination(printer);
  });
  device.on('slider:3', function(value){
    console.log("slider:3 >>> "+value);
    printer.dest3 = value;
    sendDestination(printer);
  });
  device.on('slider:4', function(value){
    console.log("slider:4 >>> "+value);
    printer.dest4 = value;
    sendDestination(printer);
  });
  device.on('slider:5', function(value){
    console.log("slider:5 >>> "+value);
    printer.dest5 = value;
    sendDestination(printer);
  });
  device.on('slider:6', function(value){
    console.log("slider:6 >>> "+value);
    printer.dest6 = value;
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

