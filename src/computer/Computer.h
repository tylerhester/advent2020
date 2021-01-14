#include <vector>
#include <string>
#include "Instruction.h"

using std::string;
using std::vector;

enum state {
    stopped = 0,
    running = 1,
    standby = 2,
    booting = 3,
    errored = 4
};

class Computer {
   private:
    vector<Instruction> bootCode;
    state status;
    int accumulator;
    int ptr;

   public:
    Computer();
    Computer(vector<Instruction> bootCode);

    void setBootCode(vector<Instruction> bc);
    int getAccumulator();
    int getStatus();
    void run();
    void step();
    void restart();
    
    void acc(int inc);
    void jmp(int idx);
};
