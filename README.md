# Keynes-Guessing-Game

A C++ implementation of a multiplayer guessing game inspired by game theory concepts and the Netflix series "Alice in Borderland". The game has been enhanced with a Streamlit-based graphical user interface (UI) for an interactive experience.

## Game Overview

This game is a strategic multiplayer contest where players must guess numbers while considering the choices of others. The game incorporates elements of game theory, including concepts similar to the Nash Equilibrium and level-k thinking.

With the addition of the Streamlit UI (`app.py`), players can now engage in the game interactively on the web.

# Game Rules

1. **Initial Scores**: All players start with a score of 0.
2. **Guessing**: Each player simultaneously guesses a number between 0 and 100.
3. **Target Calculation**: The target number (`y`) is calculated as 80% of the average of all guesses.
4. **Losing a Round**: The players whose guesses are furthest from the target lose 1 point.
5. **Elimination**: Players are eliminated when their score reaches the predetermined elimination threshold (e.g., -5).
6. **Victory**: The last player remaining is the winner.


## Game Theory Concepts

### Nash Equilibrium
In this game, a Nash Equilibrium would occur if all players chose the same number, as no player could unilaterally improve their position by changing their strategy. However, the game's dynamics often prevent this equilibrium from being reached.

### Level-k Thinking
The game encourages level-k thinking, where players must anticipate the strategies of others:
- **Level-0**: Naive random guessing.
- **Level-1**: Guessing 80% of the expected average if others guess randomly.
- **Level-2**: Guessing based on the assumption that others are using level-1 thinking, and so on...

## Streamlit UI (`app.py`)

The game now features a Streamlit-based UI for an interactive web experience. With the UI, players can:
- Input their names and guesses.
- View the calculated target number (`y`).
- See which player is closest to `y` and which players are eliminated.
- Track player scores and the game’s progress.

To run the game with the Streamlit UI:
1. Install Streamlit: `pip install streamlit`
2. Run the Streamlit app: `streamlit run app.py`

## Future Enhancements
- Add network multiplayer support.
- Introduce a leaderboard system.

## Troubleshooting
- If you encounter issues with the Streamlit UI not updating correctly, try clearing cache or use the "Rerun" button in Streamlit.

## Contributing
Contributions are welcome! Feel free to fork the repository and submit a pull request. If you encounter any bugs or have feature suggestions, please open an issue.
