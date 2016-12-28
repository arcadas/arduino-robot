# Arduino Based Hobby Robot Project

<img src="/readme/car.jpg" alt="Elegoo Smart Robot Car" width="500" />

First you need to download the documentation and base source codes from http://www.elegoo.com website for Elegoo Smart Robot Car.

## Elegoo Smart Robot Car

- Lesson 0 Assemble The Car
- Lesson 1 Make The Car Move
- Lesson 2 Bluetooth Car
- Lesson 3 Infrared Remote Control Car ([steps](/elegoo.smart.robot.car/infrared.remote.control.ino))
- Lesson 4 Obstacle Avoidance Car
- Lesson 5 Line Tracking Car

## Arduino Uno

### Bluetooth

Tutorial: [Cheap 2 Way Bluetooth Connection Between Arduino and PC](http://www.instructables.com/id/Cheap-2-Way-Bluetooth-Connection-Between-Arduino-a/?ALLSTEPS)

Sketches: [/arduino.uno/bluetooth/](/arduino.uno/bluetooth/)

Tested with HC-06 bluetooth device on OSX. Follow above instractions from tutorial and when you connected your HC-06 bluetooth device to Arduino Uno and the sketch is uploaded. Open iTerm2 app on OSX.

Check your serial devices: `ls /dev/tty.*`
```sh
 611 crw-rw-rw-  1 root  wheel   18,   0 28 Dec 11:34 /dev/tty.Bluetooth-Incoming-Port
1273 crw-rw-rw-  1 root  wheel   18,  86 28 Dec 16:27 /dev/tty.HC-06-DevB
```

Connect to Arduino over bluetooth by screen: `screen /dev/tty.HC-06-DevB 9600`.

Send data from Arduino to PC
```sh
Arduino counter: 1
Arduino counter: 2
```
Send data to Arduino from PC
```sh
Press 1 to turn Arduino pin 13 LED ON or 0 to turn it OFF
```

Screen help: http://ss64.com/osx/screen.html
- Kill screen: `CTRL+A K`
- Detach screen: `CTRL+A D`
- List screens: `screen -list`
- Reattach to screen: `screen -r tty.HC-06-DevB`

<img src="/readme/bluetooth.a.jpg" alt="Arduino with Bluetooth" width="200" />
<img src="/readme/bluetooth.b.jpg" alt="Arduino with Bluetooth" width="208" />

## Todo list

Navigation
- self-driving
- map
- position
- route plan
- move by plan

Sensors
- ultrasonic sensor

Communication
- wi-fi
- LCD

Monitoring
- noise level

Energetics
- solar power

Units
- vacuum cleaner

Hardware
- arm

## Video
https://www.youtube.com/watch?v=jUqzGy4fTZE
