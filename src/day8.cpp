#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

vector<string> splitStr(string str, string delim);

class Instruction {
   private:
    string operation;
    int argument;
    bool visited;

   public:
    Instruction();
    Instruction(string op, int arg) : operation(op), argument(arg), visited(false) { }

    void setOperation(string op) { this->operation = op; }
    void setArg(int arg) { this->argument = arg; }
    void setVisited() { this->visited = true; }

    string getOp() { return this->operation; }
    int getArg() { return this->argument; }
    bool getVisited() { return this->visited; }
};

class Computer {
   private:
    vector<Instruction> bootCode;
    int accumulator;
    int ptr;

   public:
    Computer() : accumulator(0), ptr(0) {}
    Computer(vector<Instruction> bootCode) : bootCode(bootCode), accumulator(0), ptr(0) {}

    void setBootCode(vector<Instruction> bc) { bootCode = bc; }

    void run() {
        while (ptr < bootCode.size()) {
            cout << "Before > accumulator: " << accumulator << "; ptr: " << ptr << endl;
            step();
            cout << "After > accumulator: " << accumulator << "; ptr: " << ptr << endl;
            cout << endl;
        }
    }

    void step() {
        Instruction& currIns = bootCode[ptr];

        cout << currIns.getOp() << " " << currIns.getArg() << endl;

        if (currIns.getVisited()) {
            cout << "Already visited: ";
            cout << accumulator << endl;
            // Used to exit out once we've found the first repeated instruction
            ptr = bootCode.size() + 1;
            return;
        } else {
            currIns.setVisited();
        }

        string op = currIns.getOp();
        if (!op.compare("acc")) {
            acc(currIns.getArg());
            ptr++;
        } else if (!op.compare("jmp")) {
            jmp(currIns.getArg());
        } else {
            // NOP or invalid
            ptr++;
        }
    }

    void acc(int inc) { accumulator += inc; }

    void jmp(int idx) { ptr = ptr + idx; }
};

int main(int argc, char* argv[]) {
    ifstream file;
    // file.open("testing8.txt");
    file.open("console.txt");

    vector<Instruction> bootCode;
    string line;
    while (getline(file, line) && !file.eof()) {
        auto opArg = splitStr(line, " ");

        Instruction nextInstruction(opArg[0], std::stoi(opArg[1]));
        bootCode.push_back(nextInstruction);
    }

    Computer gameBoy(bootCode);
    gameBoy.run();

    file.close();
    return 0;
}

vector<string> splitStr(string str, string delim) {
    vector<string> ret;
    int idx = str.find(delim);
    while (idx > 0) {
        string split = str.substr(0, idx);
        ret.push_back(split);
        str = str.substr(idx + delim.length());
        idx = str.find(delim);
    }
    ret.push_back(str);
    return ret;
}
