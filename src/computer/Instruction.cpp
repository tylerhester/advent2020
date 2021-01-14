#include "Instruction.h"

Instruction::Instruction() : opc(nop), argument(0), visited(false) {}
Instruction::Instruction(opcode op, int arg) : opc(op), argument(arg), visited(false) {}

void Instruction::setOp(opcode op) { this->opc = op; }
void Instruction::setArg(int arg) { this->argument = arg; }
void Instruction::setVisited() { this->visited = true; }

opcode Instruction::getOp() { return this->opc; }
int Instruction::getArg() { return this->argument; }
bool Instruction::getVisited() { return this->visited; }

