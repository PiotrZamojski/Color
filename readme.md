# Scan color from txt file of CLI

## Table of Contents

- [Valid format](#Valid-format)
- [Modes](#Modes)
- [Commands](#Commands)

## Valid format

- Program applies format dec 255,255,255,255
- Program applies format hex ffffffff

## Modes

- "mix" - New color have to be average of values from given values (default mode if invalid or empty)
- "lowest" - New color have to be created from the lowest from all of colors (independently r,g,b,a)
- "highest" - New color have to be created from the highest from all of colors (independently r,g,b,a)
- "mix-saturate" - Last color have to have new saturation equal to average of other colors

## Commands

- main.exe -m mix/lowest/highest/mix-saturate values values...
- main.exe --mode mix/lowest/highest/mix-saturate values values...
- main.exe -m values values...
- main.exe -txt
- main.exe -txt mix/lowest/highest/mix-saturate