# Transport System - DSA Project

## About the Project

Transport System is a console-based application developed in C++ to demonstrate the practical use of Data Structures and Algorithms (DSA). It supports user registration, route management, ride requests, priority-based ride dispatching, shortest-path calculation, and recent dispatch history.

## Features

- Register users with an ID, name, and phone number.
- Store and search user records using a hash table.
- Display the city map and connected routes.
- Add ride requests with standard or premium priority.
- Dispatch the next ride based on priority.
- Find the shortest route between two cities using Dijkstra's algorithm.
- Display the most recently dispatched passenger.
- Save registered user data in `users_db.txt`.

## Data Structures and Algorithms Used

- **Hash Table:** Stores and searches user records using a hash function and separate chaining.
- **Graph (Adjacency List):** Represents cities and routes with distances.
- **Priority Queue (Max-Heap):** Selects ride requests by priority, with higher-priority requests served first.
- **Stack:** Stores dispatch history.
- **Dijkstra's Algorithm:** Calculates the shortest distance between two cities.
- **File Handling:** Loads and saves user data in a text file.

## Technologies

- C++
- Standard C++ Library
- File handling (`ifstream` and `ofstream`)

## How to Run

1. Download or clone this repository.
2. Open `Transport_system.cpp` in a C++ IDE or editor.
3. Compile the program with a C++ compiler.

### Compile using g++

```bash
g++ Transport_system.cpp -o transport-system
```

Run on Windows:

```bash
transport-system.exe
```

Run on Linux/macOS:

```bash
./transport-system
```

## Menu Options

- `1` — Register User
- `2` — View Map & Routes
- `3` — Request Ride
- `4` — Dispatch Next Ride
- `5` — Find Shortest Path
- `6` — View Recent Dispatch History
- `0` — Exit

The map currently contains six numbered cities (`0` to `5`) and predefined routes.

## Data Storage

User details are stored in `users_db.txt` in the program's working directory. The file is created or updated when user records are saved.

## Future Improvements

- Validate user input and city indexes.
- Add more cities and configurable routes.
- Improve dispatch-history viewing.
- Add route and ride details to persistent storage.
- Add a graphical user interface.

## Author

Developed as a C++ Data Structures and Algorithms (DSA) project.
