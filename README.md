# Embedded Command Line

A baremetal command line used to interact with a microcontroller via UART for control of various peripherals


## Current commands

Referencing the pins on the arduino uno is as simple as referring to the silkscreen on the board ie D13 to light up an LED

| Command      | Description |
| ----------- | ----------- |
| config-in | configure gpio as input        |
| config-out | configure gpio as output                |
| read | read gpio pin        |
| toggle | toggle gpio pin        |
| set | set gpio pin        |
| reset | reset gpio pin        |

## Features

A few quality of life features expected in a Linux terminal are implemented here such as using the arrow keys to scroll up and down the command history