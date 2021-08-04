# Watchy

The source code for my [Watchy](https://watchy.sqfmi.com/).

The config file (`src/config.h`) is encrypted with [`git-secret`](https://git-secret.io/). Copy `src/config.h.sample` to `src/config.h` and make your own.

## Features

### Watch Faces

- [BigTime](./src/BigTime/README.md) - as the title says
- [Prose](./src/Prose/README.md) - the time in words
- [Cowsay](./src/Cowsay/Cowsay.md) - ``echo `date` + "\n" + `fortune` | cowsay`` (roughly)

### Buttons

- Top-Right: `vibrateTime` so you can tell the time in the dark. Vibrates for 100ms for every hour and then 200ms for every quarter-hour. Early is probably better than late so minutes are rounded up to the nearest quarter-hour.
- Bottom-Right: switch between watch faces
- Top-Left: [displays weather in Singapore](./src/Weather/README.md)

### Others

- Static sleep screen between 12am-6am (customisable) to conserve power. Interruptable on button press.
- Periodically NTP time synchronisation

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

It is probably wise to design a watchface in Paint.NET / Photoshop first before writing the display code because of the long feedback loop. There's no hot reloading 😢. The screen is 200px x 200px and the DPI is 141.

- [Fonts](https://rop.nl/truetype2gfx/)
- [Images](https://javl.github.io/image2cpp/)

The docs for the display library can be found [here](https://learn.adafruit.com/adafruit-gfx-graphics-library/overview).

- `Watchy_Custom` is a big class containing each watchface as a separate method (or methods), as well as other methods providing other functionality

Estimate your actual battery capacity using [G6EJD/LiPo_Battery_Capacity_Estimator](https://github.com/G6EJD/LiPo_Battery_Capacity_Estimator)

Note that the Watchy class uses the [`Arduino_Json.h` library](https://arduinojson.org/) which is not the same as the [`ArduinoJson.h` library](https://arduinojson.org/).

## Other Watchy Projects

- [Watchy-Screen](https://github.com/charles-haynes/Watchy-Screen/tree/master/src) - a more sophisticated implementation of multiple screens
