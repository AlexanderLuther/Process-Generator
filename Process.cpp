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

void Process::kill(int pid){
    std::string statement = "kill -9" + pid;
    system(statement.c_str());
}

Process::~Process(){

}