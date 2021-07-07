# Watchy

The source code for my [Watchy](https://watchy.sqfmi.com/).

The config file (`src/config.h`) is encrypted with [`git-secret`](https://git-secret.io/). Copy `src/config.h.sample` to `src/config.h` and make your own.

## Features

### Buttons

- Top-Right: `vibrateTime` so you can tell the time in the dark. Vibrates for 100ms for every hour and then 200ms for every quarter-hour, rounded up.

### Others

- Static sleep screen between 12am-6am (customisable) to conserve power. Interruptible on button press.

## Setup

### Arduino IDE

1. Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to Additional Board Manager URLs
2. Install `esp32` in the Board Manager
3. Install `Watchy` in the Library Manager
4. Set board to `ESP32 Dev Module`
5. Set Partition Scheme to `Minimal SPIFFS`

### VSCode

#### Arduino for VSCode

[Get the extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino).

Follow the steps for Arduino above and set `arduino.path` to the folder containing your Arduino binary, possibly `/usr/local/bin`.

#### PlatformIO

TODO

## Development

It is probably wise to design a watchface in Paint.NET / Photoshop first before writing the display code because of the long feedback loop. There's no hot reloading 😢.

- [Fonts](https://rop.nl/truetype2gfx/)
- [Images](https://javl.github.io/image2cpp/)
