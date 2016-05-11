var serialport = require("serialport");
var SerialPort = serialport.SerialPort
var port = new SerialPort("/dev/tty.usbmodem1411", {
  baudrate: 9600,
  parser: serialport.parsers.readline('\n')
  }
);

tel = "23333320"
msg="hello world"
sentence = "{\"tel\":\""+tel+"\",\"message\":\""+msg+"\"}"

port.on('open', function () {
  setTimeout(sendMessage,5000);
});

port.on('data', function (data) {
  console.log('Receied: ' + data);
});

function sendMessage(){
  console.log('firing up.');
  port.write(sentence, function(err,bytesWritten){
    if(err){
      return console.log('Error: ',err.message);
    }
    console.log(bytesWritten, 'bytes written');
  });
}


// port.write('main screen turn on', function(err, bytesWritten) {
// port.write(sentence, function(err, bytesWritten) {
//   if (err) {
//     return console.log('Error: ', err.message);
//   }
// console.log(bytesWritten, 'bytes written');
