# Game of Life with Ncurses

This project is a simple implementation of Conway's Game of Life using the Ncurses library for terminal-based visualization. Users can select different initial states for the cellular automaton, and the program will visualize the evolution of the cells over time.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [License](#license)

## Features

- Different initial states to choose from:
  - Stable
  - Long-lived
  - Periodic
  - Moving
  - Train
- Terminal-based visualization using Ncurses for a colorful and interactive experience.
- Customizable simulation speed.

## Installation

To build and run this project, you need to have the `ncurses` library installed on your system. Follow the instructions below for different operating systems:

### Ubuntu/Debian

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev