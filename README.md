Mastermind
==========

How to play can be found here: http://en.wikipedia.org/wiki/Mastermind_%28board_game%29

mastermind.c
==========
The peg colors are White, Green, Red, Purple, Orange, and Blue. First think of a four color combination such as RWOG for Red White Orange Green. The computer will try to guess color combinations and the human player will respond with numbers of red and white pegs. If the computer takes more than 10 turns to guess then the human player wins, otherwise the computer wins.


mastermindstats.c
==========
Running this will randomly generate color combinations and automatically play a certain number of games, recording how many moves the computer takes to win. The percentages for each number of turns is then outputted when the program completes.
