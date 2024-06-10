## Installation
```bash
sudo apt-get update && sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude make
```
## Compiling

```bash
make
```

## Deploying to Arduino Uno

To upload the binary to your Arduino Uno, check on which port
your Arduino is connected.
Then you can upload the program with:

```bash
make deploy
```

## License

MIT License
