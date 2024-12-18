#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Definición de la estructura del estado
struct State {
    map<char, int> emissions;
    map<string, int> transitions;
    int total_emissions = 0;
    int total_transitions = 0;
};

// Función para calcular las probabilidades
void calculateProbabilities(map<string, State>& states) {
    for (auto& kv : states) {
        State& state = kv.second;
        cout << "Estado: " << kv.first << endl;
        cout << "Probabilidades de emision:" << endl;
        for (auto& kv : state.emissions) {
            cout << kv.first << ": " << (double)kv.second / state.total_emissions << endl;
        }
        cout << "Probabilidades de transicion:" << endl;
        for (auto& kv : state.transitions) {
            cout << kv.first << ": " << (double)kv.second / state.total_transitions << endl;
        }
    }
}

int main() {
    // Secuencias de ejemplo
    vector<string> sequences = {
        "VGA--HAGEY",
        "V----NVDEV",
        "VEA--DVAGH",
        "VKG------D",
        "VYS--TYETS",
        "FNA--NIPKH",
        "IAGADNGAGY"
    };

    // Crear los estados
    map<string, State> states;
    for (string& sequence : sequences) {
        string prevState = "";
        for (char c : sequence) {
            string state = string(1, c);
            if (prevState != "") {
                states[prevState].transitions[state]++;
                states[prevState].total_transitions++;
            }
            states[state].emissions[c]++;
            states[state].total_emissions++;
            prevState = state;
        }
    }

    // Calcular las probabilidades
    calculateProbabilities(states);

    return 0;
}
