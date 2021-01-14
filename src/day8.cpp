#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "computer/Computer.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

vector<string> splitStr(string str, string delim);

int main(int argc, char* argv[]) {
    ifstream file;
    // file.open("testing8.txt");
    file.open("console.txt");

    vector<Instruction> bootCode;
    string line;
    while (getline(file, line) && !file.eof()) {
        auto opArg = splitStr(line, " ");
        
        opcode op;
        if(!opArg[0].compare("nop")) {
           op = nop;
        } else if(!opArg[0].compare("acc")) {
           op = acc; 
        } else if(!opArg[0].compare("jmp")) {
            op = jmp;
        }

        Instruction nextInstruction(op, std::stoi(opArg[1]));
        bootCode.push_back(nextInstruction);
    }

    // Go through the 'memory' or the bootCode and swap a single nop for a jmp and vice versa
    // Run the computer and see if it reaches the end
    // If it does print out the value of the accumulator

    Computer gameBoy(bootCode);
    // Part 1
    gameBoy.run();
    cout << "Part 1: " << gameBoy.getAccumulator() << endl;

    cout << "Part 2: " << endl;
    vector<vector<Instruction>> possibleSolutions;
    vector<Instruction> tempSolution = bootCode;
    for (int i = 0; i < tempSolution.size(); i++) {
        opcode op = tempSolution[i].getOp();
        switch (op) {
            case nop: {
                tempSolution[i].setOp(jmp);
                possibleSolutions.push_back(tempSolution);
                tempSolution[i].setOp(nop);
                break;
            }
            case jmp: {
                tempSolution[i].setOp(nop);
                possibleSolutions.push_back(tempSolution);
                tempSolution[i].setOp(jmp);
                break;
            }
            case acc: {
                break;
            }
        }
    }

    cout << "Testing Solutions..." << endl;
    for (auto sol : possibleSolutions) {
        Computer tmp(sol);
        tmp.run();
        if (tmp.getStatus() == stopped) {
            cout << "Solution > " << tmp.getAccumulator() << endl;
        }
    }

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
