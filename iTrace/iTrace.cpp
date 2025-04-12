#include "pin.h"
#include <iostream>
#include <string>
#include <fstream>

std::string opCode_;
std::ofstream myFilePtr;

//-------KNOB-------//
KNOB<std::string> knobForOutput(KNOB_MODE_WRITEONCE, "pintool", "o", "itrace.out", "Enter a name for the output file");
// KNOB<string> KnobForOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "outfile.out", "Output file name");
//-----get Instr -------//
VOID getInstr(){
    myFilePtr << opCode_ << std::endl;
}


//----Instrument Function ---------/
VOID Instruction(INS ins, VOID *V){
    opCode_ = OPCODE_StringShort(INS_Opcode(ins));
    INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(getInstr), IARG_END);
}

//-------Usage ---------//
INT32 Usage(){
    std::cout << "This tool Reports the machine code equivalent for instructions";
    std::cout << KNOB_BASE::StringKnobSummary();
    return -1;
}

//----Instrument Finsish ------//
VOID Finish(INT32 val, VOID* VAL){
    myFilePtr.close();
}

//INS_Disassemble()

int main(int argc, char *argv[]){

    if(PIN_Init(argc, argv)) {return Usage();}

    myFilePtr.open(knobForOutput.Value(), std::ios::out );
    
    INS_AddInstrumentFunction(Instruction, 0);
    
    PIN_AddFiniFunction(Finish, 0);
    
    PIN_StartProgram();
    
    return 0;

}