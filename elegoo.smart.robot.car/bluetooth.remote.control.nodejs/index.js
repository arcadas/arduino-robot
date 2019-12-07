var serialDeviceName = '/dev/tty.HC-06-DevB'; // ls /dev/tty.*
var SerialPort = require('serialport');
var Readline = require('@serialport/parser-readline');
var port = new SerialPort(serialDeviceName, {
  parser: new Readline({ delimiter: '\n'})
});

console.log('Looking for devices...');

port.on('open', function() {

    console.log('Connected');

    var stdin = process.stdin;
    stdin.setRawMode( true );
    stdin.resume();
    stdin.setEncoding('utf8');

    stdin.on('data', function (key) {
        // ctrl-c ( end of text )
        if ( key === '\u0003' ) {
            process.exit();
        }
        process.stdout.write( key );
        port.write(key);
    });

    port.on('data', function (data) {
        console.log(data.toString('utf8'));
    });

});


port.on('error', function(err) {
    console.log('Error: ', err.message);
})
