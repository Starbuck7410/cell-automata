# Game of Life From Scratch!

## Functionality

This project is a custom implementation of Conway's Game of Life, built with modularity and customizability in mind and using C and the X11 library for graphics. Unlike typical implementations that use high-level game engines, this project talks directly to an X server to draw pixels manually. 

The simulation features a wrapping "toroidal" grid, meaning cells that go off the edge of the screen reappear on the opposite side. 

### Usage

The simulation starts in a "paused" state, allowing you to draw your initial configuration.\
The controls are as follows:
* Left Click: Toggle a cell between alive (white) and dead (black).
* Spacebar: Toggle the simulation between running and paused.
* 'q' or 'Esc': Exit the application.

## Build instructions

To build and run the project, ensure you have the X11 development headers installed. The included `makefile` handles the compilation and execution:

**To compile the project:**
```bash
make
```

**To run the simulation:**
```bash
make run
```

## Simulation Logic

The core of the simulation is driven by two function pointers: `rule_life` and `rule_death`. This allows for easy modification of the cellular automata rules without rewriting the engine.

### Current Rule Set (Standard Conway's Game of Life)
* **Birth**: A dead cell becomes alive if it has exactly 3 neighbors.
* **Survival**: A living cell stays alive if it has 2 or 3 neighbors.
* **Death**: Otherwise, the cell dies from underpopulation or overpopulation.

The state update is performed using a bitwise approach based on a life and death mask to prevent "tearing" or partial updates during a single iteration.

## Code Architecture

The project is split into a modular frontend (Canvas) and backend (Automata).

* `canvas.c/.h`: Handles all X11 communication, window creation, and the scaling of "cells" into screen pixels. 
* `automata.c/.h`: Contains the grid logic, neighbor counting with wrapping coordinates, and the iteration engine.
* `main.c`: The glue code. It handles the event loop, user input (mouse clicks for drawing), and the main simulation toggle.
