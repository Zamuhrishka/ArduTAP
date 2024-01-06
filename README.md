# ArduTAP: Simple Library for Working with JTAG TAP

ArduTAP is an Arduino library designed to facilitate communication with devices using the JTAG protocol. It provides an intuitive and straightforward interface for interfacing with JTAG Test Access Ports (TAPs).

## Features

- Simple and easy-to-use API for interacting with JTAG devices.
- Supports basic JTAG operations such as reading from and writing to instruction and data registers.
- Allows setting up and controlling the JTAG communication speed and other parameters.


## Install

- Clone this repository into Arduino/Libraries or use the built-in Arduino IDE Library manager to install a copy of this library.

- Include in your sketch

```c
#include "TAP.hpp"
```

### Install Using PlatformIO

Install ArduTAP using the platformio library manager in your editor, or using the PlatformIO Core CLI, or by adding it to your platformio.ini as shown below:

```shell
[env]
lib_deps =
    ArduTAP
[env]
lib_deps =
    https://github.com/Zamuhrishka/ArduTAP.git
```

## Usage

- Create object

```c
TAP tap = TAP(TMS, TDI, TDO, TCK, RST);
```

- Call neccessory methods

```c
tap.read(IDCODE, (uint8_t *)&id);
```

Also see [examples](./examples/).

## Contributing

Bug reports and/or pull requests are welcome.

## Disclaimer

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

## License

Permission is granted to anyone to use this software for any purpose, including commercial applications.
