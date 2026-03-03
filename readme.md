# Snake CLI (C + ncurses)

A classic Snake game implemented in C using the ncurses library for real-time terminal rendering and input handling. 

This version introduces a unique twist: every piece of food consumed leaves behind a permanent block on the board. Colliding with one of these blocks results in game over, increasing the difficulty over time and adding a strategic layer beyond traditional Snake mechanics.

(add in screenshots/gifs)

---

## Controls

| Key | Action    |
|-----|-----------|
| ↑   | Move Up   |
| ↓   | Move Down |
| ←   | Move Left |
| →   | Move Right|

Note: the snake cannot reverse direction.

---

## Game Objects

| Symbol | Description |
|--------|-------------|
| `@` | Snake head (player-controlled) |
| `0` | Snake body segments |
| `$` | Food (increases length and spawns a block) |
| `X` | Permanent obstacle block |
| `+` `-` `|` | Board boundary walls |

---

## How to Run

### 1. Install ncurses

macOS (Homebrew)
`brew install ncurses`

Ubuntu / Debian
`sudo apt install libncurses-dev`

### 2. Build
`gcc main.c -lncurses`

### 3. Run
`./a.out`