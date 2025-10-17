# IoT Systems Programming Project
## Data Structures and Algorithms in C


This repository contains implementations of five fundamental data structures and algorithms applied to real-world IoT and embedded systems scenarios.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Questions Implemented](#questions-implemented)
- [System Requirements](#system-requirements)
- [Quick Start](#quick-start)
- [Detailed Usage](#detailed-usage)
- [Project Structure](#project-structure)
- [Author](#author)

---

## 🎯 Overview

This project demonstrates practical implementations of:
- **Doubly Linked Lists** for sensor data logging
- **Binary Search Trees** for access control systems
- **Graph Algorithms** for device communication mapping
- **Dijkstra's Algorithm** for emergency route optimization
- **Huffman Coding** for lossless file compression

All implementations are optimized for embedded systems with limited memory and real-time constraints.

---

## 📝 Questions Implemented

### Question 1: IoT Gateway Log System
**Data Structure:** Doubly Linked List  
**Features:**
- Real-time sensor data logging with bidirectional navigation
- Thread-safe live streaming mode
- Circular buffer with 20-log maximum capacity
- Commands: `n` (next), `p` (previous), `y` (live mode), `z` (pause), `c` (clear), `s` (save)

**File:** `q1_iot_gateway.c`

---

### Question 2: Smart Access Control System
**Data Structure:** Binary Search Tree  
**Features:**
- Case-sensitive name verification
- Levenshtein distance for typo detection
- Automatic suggestion for similar names (≤3 character difference)
- Security logging for unrecognized entries

**File:** `q2_access_control.c`  
**Required:** `authorized_names.txt`

---

### Question 3: Device Communication Mapper
**Data Structure:** Directed Graph (Adjacency List + Matrix)  
**Features:**
- Visualize IoT device communication patterns
- Query incoming and outgoing connections
- Display adjacency matrix
- Dynamic addition of devices and connections

**File:** `q3_device_mapper.c`

---

### Question 4: Emergency Route Optimizer
**Algorithm:** Dijkstra's Shortest Path  
**Features:**
- Finds optimal route to emergency sites
- Bidirectional road network with travel times
- Displays complete path and total travel time
- Supports multiple dispatch locations

**File:** `q4_route_optimizer.c`

---

### Question 5: Medical File Compression Tool
**Algorithm:** Huffman Coding  
**Features:**
- Lossless compression for text files
- Automatic compression ratio calculation
- Integrity verification (byte-by-byte comparison)
- Generates compressed and decompressed files

**File:** `q5_huffman_compression.c`

---

## 💻 System Requirements

- **Compiler:** GCC 7.5.0 or higher
- **OS:** Linux, macOS, or Windows (with WSL2)
- **Libraries:** 
  - `pthread` (for Q1)
  - Standard C library

---

## 🚀 Quick Start

### Clone the Repository
```bash
git clone [YOUR-REPO-URL]
cd iot-systems-project
```

### Compile All Programs
```bash
# Question 1 - IoT Gateway
gcc -o q1 q1_iot_gateway.c -lpthread -Wall

# Question 2 - Access Control
gcc -o q2 q2_access_control.c -Wall

# Question 3 - Device Mapper
gcc -o q3 q3_device_mapper.c -Wall

# Question 4 - Route Optimizer
gcc -o q4 q4_route_optimizer.c -Wall

# Question 5 - Huffman Compression
gcc -o q5 q5_huffman_compression.c -Wall
```

### Run Programs
```bash
./q1  # IoT Gateway
./q2  # Access Control
./q3  # Device Mapper
./q4  # Route Optimizer
./q5  # Huffman Compression
```

---

## 📖 Detailed Usage

### Question 1: IoT Gateway Log System

```bash
./q1
```

**Commands:**
- `n` - Navigate to next (newer) log
- `p` - Navigate to previous (older) log
- `y` - Start live streaming mode
- `z` - Pause live streaming
- `c` - Clear all logs
- `s` - Save and exit

**Example Session:**
```
=== IoT Gateway Log System ===
[Log #1] Temperature | Value: 25.50 | Time: 2025-10-17 14:30:15

Enter command: y
[LIVE] New log added: Humidity = 62.30

Enter command: n
[Log #2] Humidity | Value: 60.20 | Time: 2025-10-17 14:30:17
```

---

### Question 2: Smart Access Control System

**Setup:**
Create `authorized_names.txt`:
```
Alice
Bob
Charlie
Diana
```

```bash
./q2
```

**Example:**
```
Enter name: Alice
✓ ACCESS GRANTED
Welcome, Alice!

Enter name: Alise
✗ ACCESS DENIED
Did you mean: Alice? (Similarity score: 1)

Enter name: Unknown123
✗ ACCESS DENIED
Name not recognized. Logging for review.
```

---

### Question 3: Device Communication Mapper

```bash
./q3
```

**Menu Options:**
1. Query device connections
2. Display adjacency matrix
3. Add new connection
4. Exit

**Example Query:**
```
Enter device ID: D004

=== Device: D004 ===
Outgoing connections (sends data to):
  -> D005
  -> D006

Incoming connections (receives data from):
  <- D002
```

---

### Question 4: Emergency Route Optimizer

```bash
./q4
```

**Example:**
```
Enter starting location: Dispatch Center

=== Route Optimization Result ===
Optimal Path:
Dispatch Center -> Sector A -> Sector B -> Junction C -> Sector E -> Emergency Site

Total Travel Time: 33 minutes
```

---

### Question 5: Medical File Compression

**Setup:**
Create a sample text file `patient_record.txt`:
```
Patient Name: John Doe
Diagnosis: Hypertension
Medication: Lisinopril 10mg
Notes: Regular checkup scheduled...
```

```bash
./q5
```

**Example Output:**
```
Enter patient record filename: patient_record.txt

=== Compression Results ===
Original file size: 2048 bytes
Compressed size: 1124 bytes
Compression ratio: 45.12%

=== Decompression Complete ===
Output: decompressed.txt

✓ SUCCESS: Decompressed file matches original exactly!
```

---

## 📁 Project Structure

```
iot-systems-project/
├── q1_iot_gateway.c          # Question 1: Doubly Linked List
├── q2_access_control.c        # Question 2: Binary Search Tree
├── q3_device_mapper.c         # Question 3: Graph Implementation
├── q4_route_optimizer.c       # Question 4: Dijkstra's Algorithm
├── q5_huffman_compression.c   # Question 5: Huffman Coding
├── authorized_names.txt       # Input for Q2
├── patient_record.txt         # Sample input for Q5
├── README.md                  # This file
└── REPORT.md                  # Detailed project report
```

---



## 📊 Performance Characteristics

| Question | Data Structure | Time Complexity | Space Complexity |
|----------|----------------|-----------------|------------------|
| Q1 | Doubly Linked List | O(1) insert/delete | O(n) |
| Q2 | Binary Search Tree | O(log n) search | O(n) |
| Q3 | Graph (Adj List) | O(1) edge add | O(V + E) |
| Q4 | Dijkstra | O(V²) | O(V) |
| Q5 | Huffman Coding | O(n log n) | O(n) |

---



## 🌟 Key Features

- ✅ **Memory Efficient:** Optimized for embedded systems
- ✅ **Thread-Safe:** Concurrent operations with mutex locks (Q1)
- ✅ **Real-Time:** Designed for time-critical applications
- ✅ **Robust:** Comprehensive error handling
- ✅ **Production-Ready:** Clean, maintainable code

---

## 📚 Learning Outcomes

This project demonstrates:
1. **Data Structure Selection:** Choosing appropriate structures for specific problems
2. **Algorithm Implementation:** Practical coding of classic algorithms
3. **Concurrency:** Thread-safe programming with pthreads
4. **Memory Management:** Efficient allocation/deallocation in C
5. **Error Handling:** Robust input validation and edge case handling
6. **Real-World Application:** IoT and embedded systems context

---



## 👤 Author

**[Ramadhani  Shafii Wanjenja]**
- Course: [Low-Level Programming]
- Email: [r.wanjenja@alustudent.com]

---
