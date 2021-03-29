#ifndef PROCESS_H
#define PROCESS_H
#include <stdlib.h>
#include <string>

class Process{

    private:
        int id; 
        int PID;

    public:
        Process(int id);
        int getId();
        void setId(int id);
        int getPID();
        void setPID(int PID);
        ~Process();
};

#endif //PROCESS_H
