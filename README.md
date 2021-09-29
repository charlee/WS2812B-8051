Control WS2812B with 8051
========================================



This is an example of controlling a WS2812B LED strip with a single [STC89C52RC](http://www.stcmicro.com/datasheet/STC89C51RC-en.pdf) MCU.
Although STC89C52RC is an MCU produced over 10 years ago and it is not recommended to be used in products,
it is still one of the MCUs with lowest cost in the market, and is a great choice for hobby projects.

This project shows an example of using STC89C52RC to drive a WS2812B LED strip.

**Prerequisites**

According to the [WS2812B datasheet](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf),
sending bit 0 or 1 to a WS2812B requires sending signals in about 400ns.
A classic 8051 MCU will not work since its machine cycle equals to 12 clock cycles,
so when using a 12MHz crystal, one cycle is exactly 1us, much greater than the required 400ns.

Fortunately ST89C52RC supports a so-called "6T" mode (or "double-speed") where each machine cycle takes only 6 clock cycles.
This could reduce the time of a machine cycle down to 250ns when using a 24MHz crystal.

Therefore the prerequisites are:

- A 8051 MCU that supports 6T mode
- Using a 24MHz crystal


**Development**

This project is originally developed under Windows.

Install [SDCC](http://sdcc.sourceforge.net/)

Install `make`:

    > chocolatey.exe install make

To generate the HEX file, simply run `make` under the `src` directory.