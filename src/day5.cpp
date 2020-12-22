#include <math.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

void findAirplaneSeat(string, int, int, int&);
void addTicket(int[], const int);

int main(int argc, char* argv[]) {
    ifstream file;
    // file.open("testing5.txt");
    file.open("binarySeating.txt");

    // STL priority_queue functions as max_heap with default parameters
    priority_queue<int> pq;

    string line;
    while (getline(file, line) && !file.eof()) {
        int row = 0, col = 0;
        // Get the row
        findAirplaneSeat(line.substr(0, line.length() - 3), 0, 127, row);
        // Get the col
        findAirplaneSeat(line.substr(line.length() - 3), 0, 7, col);

        int seatID = row * 8 + col;
        pq.push(seatID);
        // cout << "Row: " << row << "; Col: " << col << "; ID: " << seatID <<
        // endl;
    }

    cout << "Part 1 > " << pq.top() << endl;
    file.close();
    return 0;
}

void findAirplaneSeat(string ticket, int beg, int end, int& seat) {
    if (!ticket.length()) {
        return;
    } else {
        char binPos = ticket[0];
        if (binPos == 'F' || binPos == 'L') {
            seat = floor((beg + end) / 2.0);
            end = seat;
        } else if (binPos == 'B' || binPos == 'R') {
            seat = ceil((beg + end) / 2.0);
            beg = seat;
        } else {
            cout << "Something went wrong?" << endl;
            // Invalid seat pos
        }
    }
    findAirplaneSeat(ticket.substr(1), beg, end, seat);
}
