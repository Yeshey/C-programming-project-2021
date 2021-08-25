# C-programming-project-2021
Done in the context of the programming module in my university

## Game Rules
*Jogo do semáforo*
Objective is to complete a line(, column or diagonal) with the same colour, player to complete wins.
Players can play pieces in any tile without a Stone or Red piece, on an empty tile, a **G**reen piece will be placed, another piece on the same tile will result in **Y**ellow, final colour is **R**ed.
Other plays are *c* or *l* to add a line or a column, this type of play is allowed twice per player per game.
And **S**tones, one allowed per player
For details on how to play press 4 when prompted for help in game.

## Running:
**Windows:** run main64.exe file *(executable created with [this](https://stackoverflow.com/questions/38786014/how-to-compile-executable-for-windows-with-gcc-with-linux-subsystem) guide)*
**Unix:** requires compiling

## Compiling:
In a **Unix** system, `cd` into the main folder and run `make all`

In a **Windows** system with gcc installed, `cd` into the main folder and run:
```
gcc src/*.c -o dist/main.exe
./dist/main.exe
```
