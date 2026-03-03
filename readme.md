# Snake CLI (C + ncurses)

A classic Snake game implemented in C using the ncurses library for real-time terminal rendering and input handling. 

(add in block feature since it's not typical in snake games)
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

## How to Run

### 1. Install ncurses

macOS (Homebrew)
```
brew install ncurses
```

Ubuntu / Debian
```
sudo apt install libncurses-dev
```

### 2. Build
```
gcc main.c -lncurses
```

### 3. Run
```
./a.out
```