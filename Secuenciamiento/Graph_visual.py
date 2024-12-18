import io
import networkx as nx
import matplotlib.pyplot as plt


matrix=[]
# Open the text file
with open("out.txt", 'r') as file:
        for line in file:
            # Strip newlines and split the line by commas, convert each item to an integer
            row = list(map(int, line.strip().split(',')))
            matrix.append(row)

print(matrix)
G = nx.DiGraph()

print(matrix)
# Add edges based on the adjacency matrix
n = len(matrix)  # Assuming the matrix is square
for i in range(n):
    for j in range(n):  # To avoid adding edges twice
        if matrix[i][j] > 0 and j!=i:
            G.add_edge(i, j, weight=matrix[i][j])

# Draw the graph
pos = nx.shell_layout(G)  # positions for all nodes
nx.draw(G, pos, with_labels=True, node_color='lightblue', edge_color='#909090', node_size=2000, font_size=15)
plt.title("Graph from 2D Matrix")
plt.show()