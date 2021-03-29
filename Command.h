#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include "CommandType.h"

using namespace std;

class Command{

    private:
        CommandType type;
        int id;
        int branchesAmount;
        int leavesAmount;
        string command;

    public:
        Command(CommandType type, int id);
        Command(CommandType type, int id, int branchesAmount);
        Command(CommandType type, int id, int branchesAmount, int leavesAmount);
        void setCommandType(CommandType type);
        CommandType getCommandType();
        void setId(int id);
        int getId();
        void setBranchesAmount(int branches);
        int getBranchesAmount();
        void setLeavesAmount(int leaves);
        int getLeavesAmount();
        string getCommand();
        ~Command();
};

#endif // COMMAND_H

