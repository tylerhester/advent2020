#include <string>

using std::string;

enum opcode {
    nop = 0,
    acc = 1,
    jmp = 2
};

class Instruction {
   private:
    opcode opc;
    int argument;
    bool visited;

   public:
    Instruction();
    Instruction(opcode op, int arg);

    void setOp(opcode op);
    void setArg(int arg);
    void setVisited();

    opcode getOp();
    int getArg();
    bool getVisited();
};
