# PPSC

Mini project for the PPSC doctoral course of 2023-2024.
All plots are in the `results` directory, and result files are in the code subdirectories.


## Files

The project description and the answers are respectively in the `consignes.pdf` and `Rendu_V_Lannelongue.pdf` files (generated from a Notion page).


## Compiling and running

Each subdirectories contain a `makefile` with the following commands:
- `comp`: compile the code files
- `run`: run the code with example parameters
- `clear`: remove the log and compiled files

And for the `zeta0` and `mach0` directories:
- `utest`: unit test to validate that the code computes as expected
- `vtest`: verification test to measure the algorithm properties


## Aditional files

All plots are generated with the `plot_results.py` script (needing seaborn, numpy and matplotlib to run).
