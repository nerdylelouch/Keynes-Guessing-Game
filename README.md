# Keynes-Guessing-Game
A C++ implementation of a multiplayer guessing game inspired by game theory concepts and the Netflix series "Alice in Borderland".

## Game Overview
This game is a strategic multiplayer contest where players must guess numbers while considering the choices of others. The game incorporates elements of game theory, including concepts similar to the Nash Equilibrium and level-k thinking.

## Game Rules
- Players simultaneously guess a number between 0 and 100.
- The target number (y) is calculated as 80% of the average of all guesses.
- Players whose guesses are furthest from the target lose a point.
- Players are eliminated when their score reaches a predetermined negative value.
- The last player remaining wins the game.

## Game Theory Concepts
### Nash Equilibrium
In this game, a Nash Equilibrium would occur if all players chose the same number, as no player could unilaterally improve their position by changing their strategy. However, the game's dynamics often prevent this equilibrium from being reached.
### Level-k Thinking
The game encourages level-k thinking, where players must anticipate the strategies of others:
- Level-0: Naive random guessing
- Level-1: Guessing 80% of the expected average if others guess randomly
- Level-2: Guessing based on the assumption that others are using level-1 thinking
and so on...

## Future Enhancements
Implement a graphical user interface
Add network multiplayer support
Introduce variations of the game with different calculation methods for the target number

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.
