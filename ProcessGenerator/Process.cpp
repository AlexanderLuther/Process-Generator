#include "Process.h"

Process::Process(int id){
    this->id = id;
}

void Process::setId(int id){
    this->id = id;
}

int Process::getId(){
    return id;
}

int Process::getPID(){
    return PID;
}

void Process::setPID(int PID){
    this->PID = PID;
}

Process::~Process(){

}