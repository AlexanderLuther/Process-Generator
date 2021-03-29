#include "Command.h"

Command::Command(CommandType type, int id){
    this->type=type;
    this->id=id;
    this->branchesAmount=0;
    this->leavesAmount=0;
}

Command::Command(CommandType type, int id, int branchesAmount){
    this->type=type;
    this->id=id;
    this->branchesAmount=branchesAmount;
    this->leavesAmount=0;
}

Command::Command(CommandType type, int id, int branchesAmount, int leavesAmount){
    this->type=type;
    this->id=id;
    this->branchesAmount=branchesAmount;
    this->leavesAmount=leavesAmount;
}

void Command::setCommandType(CommandType type){
    this->type=type;
}

CommandType Command::getCommandType(){
    return type;
}

void Command::setId(int id){
    this->id=id;
}

int Command::getId(){
    return id;
}

void Command::setBranchesAmount(int branchesAmount){
    this->branchesAmount=branchesAmount;
}

int Command::getBranchesAmount(){
    return branchesAmount;
}

void Command::setLeavesAmount(int leavesAmount){
    this->leavesAmount=leavesAmount;
}

int Command::getLeavesAmount(){
    return leavesAmount;
}

string Command::getCommand(){
    switch(type){
        case CREATE_TREE:
            return "(P," + to_string(id) + ")";
        case CREATE_TREE_BRANCH:
            return "(P," + to_string(id) + "," + to_string(branchesAmount) + ")";
        case CREATE_TREE_BRANCH_LEAF:
            return "(P," + to_string(id) + "," + to_string(branchesAmount) + "," + to_string(leavesAmount) + ")";
        case PRINT:
            return "(I," + to_string(id) + ")";
        case SHOW:
            return "(M," + to_string(id) + ")";
    }
    return "";
}

Command::~Command(){
}
