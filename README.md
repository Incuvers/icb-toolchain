# ICB Toolchain Demo

Modified: 2022-09

Demo of using CMake to create a toolchain for building and flashing firmware for the Incuvers Control Board. I have supplied a sample program which blinks the `SCK` LED (PORTB1) at 2Hz. It also uses an ISR tied to the interrupt vector for completed usart reception to echo characters back to a serial console.

## Setup
You will need `avr-libc` and the `avr` code generation tooling. On MacOSX you can use `homebrew` to install these dependancies:
```bash
brew tap osx-cross/avr
brew install avr-gcc
```
Your code generation tools root should be under `/usr/local/bin` try running `avr-gcc --version` in the terminal to ensure it is found.

## Configuration
You will need to define the serial device for the control board. Furthermore the following programs need to be found in the `CGT_ROOT` path:
- avr-gcc
- avr-objcopy
- avrdude
- avr-g++
- avr-strip

Once this is confirmed update the cmake definitions in the `CMakeLists.txt`:
```cmake
set(SERIAL_PORT "/dev/tty.usbserial-A10JTC54")
set(CGT_ROOT "/usr/local/bin")
```

Run the cmake project configuration:
```bash
mkdir build
cd build
cmake ..
```

## Compilation
Compile the firmware to `.elf` format and then object copy to `.hex`:
```bash
make -j4
```

## Flashing
Flash the `.hex` binary to the control board:
```bash
make flash
```

The SCK should blink at 2Hz:
[!img](docs/icb.png)

## Fuse Configuration
I've added a fuse directive to setup the chips fuses according to the ATMEL2560:
```bash
make fuses
```

## Demo
Open a serial console to the control board by targetting the usb device in `/dev` and run at `115200` baud:
```bash
$ screen /dev/yourusbdevice 115200
...
type some random stuff in the console and ensure characters echo back.
```

> To exit screen: `ctrl+a` to enter command mode, then press `k` for kill and then press `y` to confirm kill

## Further Reading
[ATMEL 2560 Datasheet](https://ww1.microchip.com/downloads/en/devicedoc/atmel-2549-8-bit-avr-microcontroller-atmega640-1280-1281-2560-2561_datasheet.pdf) to get started baremetal programming.