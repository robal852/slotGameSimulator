Welcome to the Slot Game Simulator repository!

This project is a simulator of the slot machine game based on https://wazdan.com/games/hot-slot-777-crown
The game is 5-reel slot machine with
- 3 rows of symbols.
- 20 winning lines
- 7 regular symbols
- SCATTER symbol, which does not need to align in a winning line from left to right (only the number of SCATTER symbols in a given winning line matters)

Usage:
To run the simulator, you can use the following command line arguments:
  ./slotGameSimulator -gamesCount 100000 -startCredit 5000000 -creditOutFile output.txt

This command will:
- Perform 100,000 game simulations with an initial credit of 5,000,000
- Save the credit state changes to a file named 'output.txt' (each line of the file represents a credit state)
- Display a summary report on the standard console

Additionally, you can use the -symbols option to check the payout for a specific combination. For example:
  ./slotGameSimulator -symbols 0,1,2,3,4,5,5,5,5,5,6,6,6,6,6

Generating Plot:
There's a script available for generating a plot from the data saved by the program. To use the script:
  python drawAPlot.py <file_path>


Requirements:
The simulator is written in C++17 and utilizes Google Test
The plotting script is written in Python and requires matplotlib library.
