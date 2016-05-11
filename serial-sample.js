var serialport = require("serialport");
var SerialPort = serialport.SerialPort
var port = new SerialPort("/dev/tty.usbmodem1411", {
  baudrate: 115200,
  parser: serialport.parsers.readline('\n')
  }
);

dist1 = "129"
dist2 = "22"
dist3 = "19"
dist4 = "122"
dist5 = "9"
dist6 = "2"
sentence = "{\"dist1\":\""+dist1+"\",\"dist2\":\""+dist2+"\",\"dist3\":\""+dist3+"\",\"dist4\":\""+dist4+"\",\"dist5\":\""+dist5+"\",\"dist6\":\""+dist6+"\"}"

port.on('open', function () {
  console.log("hold on. operation starts soon.");
  setInterval(sendMessage,3000);
});

port.on('data', function (data) {
  console.log('Received: ' + data);
});

function sendMessage(){
  console.log('firing it up!');
  port.write(sentence, function(err,bytesWritten){
    if(err){
      return console.log('Error: ',err.message);
    }
    console.log(bytesWritten, 'bytes written');
  });
}


