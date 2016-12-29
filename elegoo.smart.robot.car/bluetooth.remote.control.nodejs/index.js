var serialDeviceName = '/dev/tty.HC-06-DevB'; // ls /dev/tty.*
var SerialPort = require('serialport');
var port = new SerialPort(serialDeviceName, {
  parser: SerialPort.parsers.readline('\n')
});

console.log('Looking for devices...');

port.on('open', function() {

    console.log('Connected');

    process.stdin.on('data', function (data) {
        port.write(data);
    });

    port.on('data', function (data) {
        console.log(data.toString('utf8'));
    });

});


port.on('error', function(err) {
    console.log('Error: ', err.message);
})