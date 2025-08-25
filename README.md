# Quadratic equation solver

Written during MIPT'25 summer school.

## Overview

This program is intended to solve quadratic equations with all possible caution.

To solve your equation, you need to enter it's coefficients (IEEE754 double precision).

## Build & run

### Linux

Make sure you have `make` and `g++` installed. Run in your console:

```bash
make
```

then

```bash
make run
```

## Test

Tests are placed in `test/input.txt` file. Every single test is written different line
and formatted as followed:

|case             |format                     |
|-----------------|---------------------------|
| no roots:       |`<c1> <c2> <c3> nan  nan`  |
| 1 root:         |`<c1> <c2> <c3> <r1> nan`  |
| 2 roots:        |`<c1> <c2> <c3> <r1> <r2>` |
| infinite roots: |`<c1> <c2> <c3> inf  <any>`|
| linear:         |`<c1> <c2> <c3> nan  nan`  |

Where `c1`, `c2`, `c3` are coefficients, `r1` and `r2` are intended roots of equation
$c_1x^2 + c_2x + c_3 = 0$.

### Running tests

#### Linux

In root repository directory, run in your console:

```bash
make test
```

## Documentaion

To generate documentaion for this project, make shure you have `doxygen` installed.

### Linux

To generate docs, run this in root repository directory in your console:

```bash
doxygen
```

Then open `html/index.html` in your browser.
