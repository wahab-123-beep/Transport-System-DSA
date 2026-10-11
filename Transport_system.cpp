#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <climits>
#include <set>
#include <iomanip>

using namespace std;


struct User {
    string id;
    string name;
    string phone;

    string serialize() const { return id + "," + name + "," + phone; }
};

struct Edge {
    int destination;
    int weight;
};

struct RideRequest {
    string passengerName;
    int priority; // 5: Premium, 1: Standard

    bool operator<(const RideRequest& other) const {
        return priority < other.priority; // Max-Heap logic
    }
};

class UserDatabase {
private:
    static const int TABLE_SIZE = 10;
    list<User> table[TABLE_SIZE];
    const string fileName = "users_db.txt";

    int hashFunction(string id) {
        int sum = 0;
        for (char c : id) sum += c;
        return sum % TABLE_SIZE;
    }

public:
    void insertUser(User u, bool save = true) {
        int index = hashFunction(u.id);
        table[index].push_back(u);
        if (save) saveToFile();
    }

    User* searchUser(string id) {
        int index = hashFunction(id);
        for (auto& u : table[index]) {
            if (u.id == id) return &u;
        }
        return nullptr;
    }

    void saveToFile() {
        ofstream outFile(fileName);
        for (int i = 0; i < TABLE_SIZE; i++)
            for (auto& u : table[i]) outFile << u.serialize() << endl;
        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile(fileName);
        if (!inFile) return;
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, name, phone;
            getline(ss, id, ','); getline(ss, name, ','); getline(ss, phone, ',');
            if (!id.empty()) insertUser({ id, name, phone }, false);
        }
        inFile.close();
    }
};

class CityMap {
private:
    int numCities;
    vector<list<Edge>> adjList;

public:
    CityMap(int cities) : numCities(cities) { adjList.resize(cities); }

    void addRoute(int u, int v, int w) {
        adjList[u].push_back({ v, w });
        adjList[v].push_back({ u, w });
    }

    void findShortestPath(int start, int end) {
        vector<int> dist(numCities, INT_MAX);
        vector<int> parent(numCities, -1);
        set<pair<int, int>> pq;

        dist[start] = 0;
        pq.insert({ 0, start });

        while (!pq.empty()) {
            int u = pq.begin()->second;
            pq.erase(pq.begin());
            if (u == end) break;

            for (auto& edge : adjList[u]) {
                if (dist[u] + edge.weight < dist[edge.destination]) {
                    pq.erase({ dist[edge.destination], edge.destination });
                    dist[edge.destination] = dist[u] + edge.weight;
                    parent[edge.destination] = u;
                    pq.insert({ dist[edge.destination], edge.destination });
                }
            }
        }

        if (dist[end] == INT_MAX) cout << "No route found!\n";
        else {
            cout << "Shortest Distance: " << dist[end] << " km\nPath: ";
            printPath(parent, end);
            cout << endl;
        }
    }

    void printPath(vector<int>& parent, int j) {
        if (parent[j] == -1) { cout << j; return; }
        printPath(parent, parent[j]);
        cout << " -> " << j;
    }

    void display() {
        for (int i = 0; i < numCities; i++) {
            cout << "City " << i << ": ";
            for (auto& e : adjList[i]) cout << "-> " << e.destination << "(" << e.weight << "km) ";
            cout << endl;
        }
    }
};


class TransportSystem {
private:
    UserDatabase userDB;
    CityMap map;
    priority_queue<RideRequest> rideQueue;
    stack<string> history;

public:
    TransportSystem() : map(6) {
        userDB.loadFromFile();

        map.addRoute(0, 1, 4); map.addRoute(0, 2, 2);
        map.addRoute(1, 2, 1); map.addRoute(1, 3, 5);
        map.addRoute(2, 3, 8); map.addRoute(2, 4, 10);
        map.addRoute(3, 4, 2); map.addRoute(3, 5, 6);
    }

    void menu() {
        int choice;
        do {
            cout << "\n--- TRANSPORT SYSTEM MENU ---\n";
            cout << "1. Register User (Hash Table)\n";
            cout << "2. View Map & Routes (Graph)\n";
            cout << "3. Request Ride (Priority Queue)\n";
            cout << "4. Dispatch Next Ride (Heap)\n";
            cout << "5. Find Shortest Path (Dijkstra)\n";
            cout << "6. View Recent Dispatch History (Stack)\n";
            cout << "0. Exit\nChoice: "; cin >> choice;

            switch (choice) {
            case 1: {
                User u;
                cout << "ID: "; cin >> u.id;
                cout << "Name: "; cin.ignore(); getline(cin, u.name);
                cout << "Phone: "; cin >> u.phone;
                userDB.insertUser(u);
                break;
            }
            case 2: map.display(); break;
            case 3: {
                string id; int p;
                cout << "Enter User ID: "; cin >> id;
                User* u = userDB.searchUser(id);
                if (u) {
                    cout << "Priority (1:Std, 5:Prem): "; cin >> p;
                    rideQueue.push({ u->name, p });
                    cout << "Ride Queued!\n";
                }
                else cout << "User Not Found!\n";
                break;
            }
            case 4: {
                if (!rideQueue.empty()) {
                    RideRequest r = rideQueue.top();
                    cout << "Dispatching: " << r.passengerName << " (Prio: " << r.priority << ")\n";
                    history.push(r.passengerName);
                    rideQueue.pop();
                }
                else cout << "No rides in queue.\n";
                break;
            }
            case 5: {
                int s, e;
                cout << "Start City (0-5): "; cin >> s;
                cout << "End City (0-5): "; cin >> e;
                map.findShortestPath(s, e);
                break;
            }
            case 6: {
                cout << "Last Dispatched: " << (history.empty() ? "None" : history.top()) << endl;
                break;
            }
            }
        } while (choice != 0);
    }
};

int main() {
    TransportSystem ts;
    ts.menu();
    return 0;
}