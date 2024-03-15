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
| watch-toggle | toggle gpio pin at a set period        |
| watch-read | read gpio pin at a set period        |

## Quality of life features

A few quality of life features expected in a Linux terminal are implemented here such as using the arrow keys to scroll up and down the command history and ctrl+backspace to delete the whole word

## Demo

In the following demo, we have an arduino uno with D12 and D8 shorted together. We configure these pins accordingly and watch
as the values are updated in real time. We also use the watch command to allow D8 to periodically toggle while we manually check the pin value on D12. The entire command line is run onboard the microcontroller and is accessed through the screen command. 

![](https://github.com/rafguevara14/embedded-command-line/blob/main/gifs/example.gif)
