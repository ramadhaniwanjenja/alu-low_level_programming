# Graph Traversal using DFS & BFS

This project demonstrates **graph traversal algorithms** — **Depth-First Search (DFS)** and **Breadth-First Search (BFS)** — implemented in **C**.


## 🏗 How the Program Works
1. The user enters:
   - The **number of vertices** in the graph
   - The **number of edges** in the graph
   - Each **edge** as a pair of vertices (example: `1 2` means connection between node 1 and 2)

2. The program builds an **adjacency list** to represent the graph

3. The user chooses a **starting vertex** for traversal

4. The program runs both **DFS** and **BFS** from the chosen starting vertex

5. It prints the traversal order for both algorithms

---

## ⌨️ Example Input and Output

### Input Format
```
Enter number of vertices: 12
Enter number of edges: 11
Enter edges:
1 2
1 3
1 4
2 5
3 6
4 7
5 8
6 9
7 10
8 11
9 12
Enter starting vertex: 1
```

### Expected Output
```
DFS Traversal starting at 1: 1 2 5 8 11 3 6 9 12 4 7 10
BFS Traversal starting at 1: 1 2 3 4 5 6 7 8 9 10 11 12
```

### Graph Visualization
```
        1
      / | \
     2  3  4
     |  |  |
     5  6  7
     |  |  |
     8  9  10
     |  |
    11  12
```

---

## ⚙️ Algorithm Details

### DFS (Depth-First Search)
- **Strategy:** Go deep before going wide
- **Data Structure:** Stack (or recursion)
- **Memory Usage:** O(V) for the call stack
- **Path:** Follows one branch completely before trying others

### BFS (Breadth-First Search)  
- **Strategy:** Explore all neighbors before going deeper
- **Data Structure:** Queue
- **Memory Usage:** O(V) for the queue
- **Path:** Level-by-level exploration

## 📊 Time & Space Complexity
For a graph with `V` vertices and `E` edges:

| Algorithm | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| **DFS**   | O(V + E)       | O(V)             |
| **BFS**   | O(V + E)       | O(V)             |

Both algorithms visit each vertex and edge exactly once.

---

## 🔧 Implementation Features
- **Adjacency List Representation:** Memory efficient for sparse graphs
- **Undirected Graph:** Edges work in both directions
- **Dynamic Memory Allocation:** Handles graphs of any size
- **Visited Array:** Prevents infinite loops and duplicate visits

---

## 📚 Real-World Applications

### DFS is used in:
- Cycle detection in graphs
- Topological sorting
- Finding strongly connected components
- Maze solving and puzzle games
- Dependency resolution

### BFS is used in:
- Shortest path in unweighted graphs
- Web crawlers (exploring websites level by level)
- Social networking (friends of friends)
- GPS navigation systems
- Garbage collection algorithms

---

## ✅ How to Compile and Run

### Prerequisites
- GCC compiler
- Basic C development environment

### Steps
1. **Clone/Download** the repository
2. **Compile** the code:
   ```bash
   gcc graph.c -o graph
   ```
3. **Run** the program:
   ```bash
   ./graph
   ```
4. **Follow the prompts** to enter your graph data
