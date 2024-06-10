## Installation

sudo apt-get update && sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude make

## Compiling

make

## Deploying to Arduino Uno

In order to upload the binary to your Arduino Uno, check on which port
your Arduino is connected. You can see the path for example in the Arduino IDE.
Replace the port with the default value in the Makefile (ARDUINO_USB).

Then you can upload the program via:

```bash
make deploy
```

## References

- https://github.com/sagarsp/arduino-blink-c

## License

MIT License
