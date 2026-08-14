# STM32F103 PWM LED Demo

A small STM32F103 learning project that demonstrates how to generate a PWM signal with a general-purpose timer. The firmware drives the onboard LED connected to `PB5` and continuously changes the PWM compare value to create a breathing-light effect.

## Features

- Generates PWM with `TIM3 Channel 2`
- Uses the partial TIM3 remap to route `TIM3_CH2` to `PB5`
- Produces an approximately `100 kHz` PWM signal
- Continuously varies the compare value from `0` to `700`
- Includes basic LED, key, delay, timer, and USART drivers
- Built with the STM32F10x Standard Peripheral Library

## Hardware

This project targets an ALIENTEK WarShip STM32 development board with an `STM32F103ZE` microcontroller.

| Function | Peripheral | Pin |
| --- | --- | --- |
| PWM output / LED0 | `TIM3_CH2` | `PB5` |
| LED1 | GPIO | `PE5` |
| USART1 TX | `USART1_TX` | `PA9` |
| USART1 RX | `USART1_RX` | `PA10` |

Only the PWM output on `PB5` is required for the main demo. If you use a different STM32F103 board, connect an LED with a suitable current-limiting resistor to `PB5`, or update the GPIO and timer remap configuration for your hardware.

## PWM Configuration

The timer is initialized in [`USER/main.c`](USER/main.c):

```c
TIM3_PWM_Init(719, 0);
```

With a `72 MHz` TIM3 clock, the PWM frequency is:

```text
PWM frequency = 72 MHz / ((719 + 1) * (0 + 1)) = 100 kHz
```

TIM3 operates in PWM mode 2. The duty cycle is updated through the channel 2 compare register:

```c
TIM_SetCompare2(TIM3, led0pwmval);
```

The compare value repeatedly rises from `0` to `700` and then falls back to `0`, changing the LED brightness.

## Getting Started

### Requirements

- An STM32F103ZE development board
- A compatible programmer/debugger, such as ST-LINK or J-Link
- Keil MDK-ARM with STM32F1 device support

### Build and Flash

1. Clone this repository:

   ```bash
   git clone <repository-url>
   cd pwm_learning
   ```

2. Open [`USER/PWM.uvproj`](USER/PWM.uvproj) in Keil uVision. Newer Keil versions may prompt you to convert the project format.

3. Select and configure your programmer in **Options for Target > Debug**.

4. Build the `Target 1` target.

5. Flash the firmware to the board and reset it.

The LED connected to `PB5` should continuously fade between low and high brightness.

## Project Structure

```text
.
|-- CORE/                 CMSIS core support and startup files
|-- HARDWARE/
|   |-- KEY/              Push-button driver
|   |-- LED/              LED GPIO driver
|   `-- TIMER/            TIM3 interrupt and PWM configuration
|-- STM32F10x_FWLib/      STM32F10x Standard Peripheral Library
|-- SYSTEM/
|   |-- delay/            SysTick-based delay functions
|   |-- sys/              System and GPIO bit-band helpers
|   `-- usart/            USART1 driver
|-- USER/                 Application entry point and Keil project
`-- README.md
```

## Key Files

- [`USER/main.c`](USER/main.c): application entry point and PWM duty-cycle update loop
- [`HARDWARE/TIMER/timer.c`](HARDWARE/TIMER/timer.c): TIM3 PWM and interrupt initialization
- [`HARDWARE/LED/led.c`](HARDWARE/LED/led.c): onboard LED GPIO initialization

## Notes

- The firmware assumes a `72 MHz` system/timer clock.
- The duty-cycle update loop has no delay, so its fade rate depends on execution speed. Add a short `delay_ms()` call in the loop if you want a slower transition.
- Some original source comments use a legacy Chinese character encoding and may not display correctly in UTF-8 editors. This does not affect compilation.

## Acknowledgements

The low-level board support code is based on ALIENTEK STM32 educational examples. Refer to the copyright notices in the source files for their original attribution and usage terms.
