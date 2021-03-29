#ifndef PROCESS_H
#define PROCESS_H
#include <stdlib.h>
#include <string>

class Process{

    private:
        int id; 

    public:
        Process(int id);
        int getId();
        void setId(int id);
        void kill(int pid);
        ~Process();
};

#endif //PROCESS_H
