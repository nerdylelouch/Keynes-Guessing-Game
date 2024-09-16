// Nash Equilibrium condition would be if all players chose the same number.

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm> 

using namespace std;

// Function to calculate y based on players' guesses
double calculate_y(const vector<int>& guesses) {
    double sum = 0;
    for (int guess : guesses) {
        sum += guess;
    }
    double avg = sum / guesses.size();
    return 0.8 * avg;
}

// Function to find the players closest to y
vector<int> find_closest(const vector<int>& guesses, double y) {
    vector<int> closest_players;
    double closest_distance = numeric_limits<double>::infinity();
    
    for (size_t i = 0; i < guesses.size(); ++i) {
        double distance = fabs(guesses[i] - y);
        if (distance < closest_distance) {
            closest_distance = distance;
            closest_players = {static_cast<int>(i)};  
        } else if (distance == closest_distance) {
            closest_players.push_back(static_cast<int>(i));  
        }
    }
    
    return closest_players;
}

int main() {
    int num_players;
    while (true) {
        cout << "Enter the number of players: ";
        cin >> num_players;
        if (cin.fail() || num_players < 2) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            cout << "Invalid input. At least 2 players are required to play the game. Please enter a valid number." << endl;
        } else {
            break;
        }
    }

    int end_counter_value;
    while (true) {
        cout << "Enter the counter value at which the game ends for a player: ";
        cin >> end_counter_value;
        if (cin.fail() || end_counter_value >= 0) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            cout << "Invalid input. Counter value should be less than 0. Please enter a valid value." << endl;
        } else {
            break;
        }
    }

    vector<string> player_names(num_players);
    for (int i = 0; i < num_players; ++i) {
        cout << "Enter the name of Player " << (i + 1) << ": ";
        cin >> player_names[i];
    }

    vector<int> counters(num_players, 0);
    vector<bool> active_players(num_players, true);
    bool game_over = false;

    while (!game_over) {
        vector<int> guesses(num_players, -1);
        vector<int> active_guesses;
        
        // Take input from the players
        for (int i = 0; i < num_players; ++i) {
            if (active_players[i]) {  
                while (true) {
                    cout << player_names[i] << ", enter your guess (0-100): ";
                    cin >> guesses[i];
                    if (cin.fail() || guesses[i] < 0 || guesses[i] > 100) {
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                        cout << "Invalid input. Guess must be between 0 and 100. Please enter a valid guess." << endl;
                    } else {
                        break;
                    }
                }
                active_guesses.push_back(guesses[i]);
            }
        }

        // Calculate y 
        if (active_guesses.empty()) {
            cout << "No active players left. The game ends." << endl;
            break;
        }
        
        double y = calculate_y(active_guesses);
        cout << "Calculated y = " << y << endl;

        // Find the players closest to y 
        vector<int> valid_guesses;
        for (int i = 0; i < num_players; ++i) {
            if (active_players[i]) {
                valid_guesses.push_back(guesses[i]);
            }
        }
        
        vector<int> closest_players = find_closest(valid_guesses, y);
        vector<int> closest_indices;
        for (int i = 0; i < num_players; ++i) {
            if (active_players[i]) {
                auto it = find(closest_players.begin(), closest_players.end(), guesses[i]);
                if (it != closest_players.end()) {
                    closest_indices.push_back(i);
                }
            }
        }

        cout << "Player(s) ";
        for (size_t i = 0; i < closest_indices.size(); ++i) {
            cout << player_names[closest_indices[i]];
            if (i < closest_indices.size() - 1) {
                cout << " and ";
            }
        }
        cout << " are closest to y." << endl;

        // Decrement 1 point from players who are not closest to y
        vector<int> eliminated_players;
        for (int i = 0; i < num_players; ++i) {
            if (active_players[i] && find(closest_indices.begin(), closest_indices.end(), i) == closest_indices.end()) {
                counters[i] -= 1;
                if (counters[i] <= end_counter_value) {
                    cout << player_names[i] << " is eliminated." << endl;
                    eliminated_players.push_back(i);
                }
            }
        }

        // Remove eliminated players from active players
        for (int player : eliminated_players) {
            active_players[player] = false;
        }

        // Print player counters
        cout << "Player counters:" << endl;
        for (int i = 0; i < num_players; ++i) {
            if (active_players[i]) {
                cout << player_names[i] << ": " << counters[i] << endl;
            }
        }

        // Check if only one player remains
        int active_count = count(active_players.begin(), active_players.end(), true);
        if (active_count == 1) {
            for (int i = 0; i < num_players; ++i) {
                if (active_players[i]) {
                    cout << player_names[i] << " wins the game!" << endl;
                    game_over = true;
                    break;
                }
            }
        }
    }

    return 0;
}

