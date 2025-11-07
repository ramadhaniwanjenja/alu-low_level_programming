# Low Level Programming - Week 3 Formative Assessment


## Overview

This repository contains solutions to Week 3 Formative Assessment covering:
- System-level programming and disassembly
- Assembly language programming
- C extensions with Python
- Secure file encryption using shared libraries

**Total Points:** 18/18 (18% of total grade)

---

## Prerequisites
```bash
sudo apt-get update
sudo apt-get install build-essential nasm binutils python3-dev python3-pip
pip3 install matplotlib
```

---

## Question 1: ELF Binary Disassembler

### Description
Disassembles ELF executable files using objdump and saves assembly code to text file.

### Files
- `Question_1_Disassembler.c`
- `sample.c` (test file)

### Compilation & Usage
```bash
gcc -o disassembler Question_1_Disassembler.c
gcc -o sample sample.c
./disassembler ./sample
cat sample_disassembled.txt
```

### Points: 4/4

---

## Question 2: ATM Assembly Program

### Description
x86 assembly program simulating ATM operations: Deposit, Withdraw, Check Balance, Exit.

### Files
- `Question_2_ATM.asm`

### Features
- Initial balance: $1000
- Modular functions
- Input validation
- Insufficient funds check

### Compilation & Usage
```bash
nasm -f elf32 Question_2_ATM.asm -o atm.o
ld -m elf_i386 -o Question_2_ATM atm.o
./Question_2_ATM
```

### Usage Example
```
====== ATM MENU ======
1. Deposit
2. Withdraw
3. Check Balance
4. Exit
Enter your choice: 3
Current Balance: $1000
```

### Points: 4/4

---

## Question 3: IoT Monitoring System

### Description
Simulates IoT sensors (Temperature, Humidity, Battery) with real-time graphs.

### Files
- `sensor_module.c` (C extension)
- `setup.py` (build script)
- `monitor.py` (visualization)

### Features
- Reads every 2 seconds for 30 seconds
- Real-time matplotlib graphs
- Temperature: 20-35°C
- Humidity: 40-70%
- Battery: 50-100%

### Compilation & Usage
```bash
python3 setup.py build
sudo python3 setup.py install
python3 monitor.py
```

### Points: 6/6

---

## Question 4: Diary Manager with Encryption

### Description
Command-line diary with symmetric encryption (Caesar cipher, key=4).

### Files
- `diary_lib.c` (shared library)
- `diary_main.c` (main program)

### Features
- Add encrypted entries
- View with password (default: "1234")
- Stored encrypted in memory
- Max 100 entries, 500 chars each

### Compilation & Usage
```bash
gcc -shared -fPIC -o libdiary.so diary_lib.c
gcc -o diary diary_main.c -L. -ldiary
LD_LIBRARY_PATH=. ./diary
```

### Usage Example
```
===== Diary Manager =====
1. Add Entry
2. View Entries
3. Exit
Enter choice: 1
Enter your diary entry:
Today was great!
Entry added and encrypted successfully!

Enter choice: 2
Enter password to view entries: 1234
===== Diary Entries =====
Entry 1: Today was great!
```

### Points: 4/4

---

## Troubleshooting

### Q1: objdump not found
```bash
sudo apt-get install binutils
```

### Q2: _start symbol error
Ensure `global _start` and `_start:` label exist in assembly file.

### Q3: Python.h not found
```bash
sudo apt-get install python3-dev
```

### Q3: Module not found
```bash
export PYTHONPATH=$PYTHONPATH:$(pwd)/build/lib.linux-x86_64-3.x
```

### Q4: Library not found
```bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
```



**Student:** [Ramadhani Shafii Wanjenja]  