# Sem09-MolecularBiology

## Course Overview
In this course, we explored the fundamentals of **molecular biology** and the intersection of **software development** with biological data. Topics included:
- Sequence alignment algorithms (e.g., Needleman-Wunsch).
- RNA structure prediction using dynamic programming.
- Hidden Markov Models (HMM) for sequence analysis.
- Graph-based approaches for sequencing problems.
  
This repository contains implementations of key algorithms and tools we developed as part of our assignments.

---

## Repository Structure

### 1. **ARN prediction**
- **File**: `ARN_prediction.py`
- **Description**: Implements the **Nussinov algorithm** for predicting RNA secondary structures. It uses dynamic programming to calculate base pair probabilities and traceback for RNA folding.
- **Features**:
  - Calculates the matrix for paired base energies.
  - Generates a traceback to predict base pairings.
  - Outputs a formatted visualization of the RNA structure.

---

### 2. **HMM (Hidden Markov Models)**
- **File**: `HmmV3.cpp`
- **Description**: This code implements a **Hidden Markov Model (HMM)** for analyzing sequence alignments with insertions, deletions, and emissions.
- **Features**:
  - Reads input sequences from a file.
  - Calculates **emission probabilities** (probability of a symbol in a state).
  - Eliminates columns using a **heuristic threshold**.
  - Calculates **transition probabilities** for matches (M), insertions (I), and deletions (D).
  - Outputs HMM parameters in a readable format.

**Input File**:  
An `Input.txt` file with aligned sequences.

---

### 3. **Needleman-WunschV2**
- **File**: `NW_V2.cpp`
- **Description**: Implements the **Needleman-Wunsch algorithm** for global sequence alignment.
- **Features**:
  - Aligns two DNA sequences with match/mismatch scores and gap penalties.
  - Generates multiple alignments by tracking optimal paths.
  - Outputs the aligned sequences and the total alignment score.

**Input Sequences**:
- Preloaded examples include sequences for **bacteria**, **SARS-CoV**, and **Influenza**.

---

### 4. **Secuenciamiento (Sequencing)**
- **Files**: 
  - `secuenciamiento.cpp`
  - `Graph_visual.py`
- **Description**: A graph-based approach for sequence assembly using substring overlaps.
- **Features**:
  - Constructs a graph where nodes represent sequences, and edges represent **overlap values**.
  - Uses a **greedy algorithm** to align sequences based on maximum overlap.
  - Generates a consensus sequence.
  - Outputs the graph adjacency matrix to `out.txt`.

**Graph Visualization**:  
- `Graph_visual.py` reads the adjacency matrix from `out.txt` and visualizes the graph using **NetworkX**.

---

## Running the Code

### 1. **Python Scripts**
Ensure you have Python installed. Run the scripts with:
```bash
python3 ARN_prediction.py
python3 Graph_visual.py
```

### 2. **C++ Programs**
To compile and run the C++ files:
```bash
g++ -o HMM HmmV3.cpp
./HMM

g++ -o NW NW_V2.cpp
./NW

g++ -o sequencing secuenciamiento.cpp
./sequencing
```

**Input File**: Place your sequences in `Input.txt` if required.

---

## Sample Outputs
1. **ARN Prediction**:  
   RNA folding matrix and secondary structure traceback.
2. **HMM**:  
   Transition and emission probabilities for sequence alignments.
3. **Needleman-Wunsch**:  
   Aligned sequences with the optimal alignment score.
4. **Sequencing**:  
   - Consensus sequence from multiple sequence alignments.
   - Visualization of the overlap graph.
