import streamlit as st

# Function to calculate y based on players' guesses
def calculate_y(guesses):
    avg = sum(guesses) / len(guesses)
    return 0.8 * avg

# Function to find the players closest to y
def find_closest(guesses, y):
    closest_players = []
    closest_distance = float('inf')

    for i, guess in enumerate(guesses):
        distance = abs(guess - y)
        if distance < closest_distance:
            closest_distance = distance
            closest_players = [i]  # Reset list with this player
        elif distance == closest_distance:
            closest_players.append(i)  # Add this player if equally close

    return closest_players

# Initialize session state variables
if 'num_players' not in st.session_state:
    st.session_state.num_players = 0
if 'player_names' not in st.session_state:
    st.session_state.player_names = []
if 'counters' not in st.session_state:
    st.session_state.counters = []
if 'active_players' not in st.session_state:
    st.session_state.active_players = set()
if 'game_started' not in st.session_state:
    st.session_state.game_started = False
if 'end_counter_value' not in st.session_state:
    st.session_state.end_counter_value = -1  # Default value for end counter

# UI for the game
st.title("Keynes Guessing Game")

if not st.session_state.game_started:
    # Limit the number of players to a maximum of 10
    st.session_state.num_players = st.number_input("Enter the number of players:", min_value=2, max_value=10, step=1)
    st.session_state.end_counter_value = st.number_input("Enter the counter value at which the game ends for a player (negative value):", value=-1, max_value=-1, step=-1)

    if st.button("Start Game"):
        st.session_state.player_names = ["" for _ in range(st.session_state.num_players)]
        st.session_state.counters = [0 for _ in range(st.session_state.num_players)]
        st.session_state.active_players = set(range(st.session_state.num_players))
        st.session_state.game_started = True

if st.session_state.game_started:
    st.write("## Enter Player Names")
    for i in range(st.session_state.num_players):
        st.session_state.player_names[i] = st.text_input(f"Enter the name of Player {i + 1}:", value=st.session_state.player_names[i], key=f"name_{i}")

    if all(st.session_state.player_names):
        st.write("## Player Inputs")
        guesses = []
        for i in range(st.session_state.num_players):
            if i in st.session_state.active_players:
                guess = st.number_input(f"{st.session_state.player_names[i]}, enter your guess (0-100):", min_value=0, max_value=100, key=f"guess_{i}")
                guesses.append(guess)
            else:
                guesses.append(None)

        if st.button("Submit Guesses"):
            active_guesses = [g for g in guesses if g is not None]
            if not active_guesses:
                st.write("No active players left. The game ends.")
            else:
                y = calculate_y(active_guesses)
                st.write(f"Calculated y = {y}")

                valid_guesses = [(i, guess) for i, guess in enumerate(guesses) if guess is not None]
                closest_players = find_closest([g[1] for g in valid_guesses], y)
                closest_indices = [valid_guesses[i][0] for i in closest_players]
                st.write(f"Player(s) {', '.join([st.session_state.player_names[x] for x in closest_indices])} are closest to y.")

                eliminated_players = []
                for i in range(st.session_state.num_players):
                    if i in st.session_state.active_players and i not in closest_indices:
                        st.session_state.counters[i] -= 1
                        if st.session_state.counters[i] <= st.session_state.end_counter_value:
                            st.write(f"{st.session_state.player_names[i]} is eliminated.")
                            eliminated_players.append(i)

                for player in eliminated_players:
                    st.session_state.active_players.discard(player)

                st.write("### Player counters:")
                for i in range(st.session_state.num_players):
                    if i in st.session_state.active_players:
                        st.write(f"{st.session_state.player_names[i]}: {st.session_state.counters[i]}")

                if len(st.session_state.active_players) == 1:
                    winner = next(iter(st.session_state.active_players))
                    st.write(f"### {st.session_state.player_names[winner]} wins the game!")
                    st.session_state.game_started = False
