#ifndef SHAREDMEMORYDRIVER_H
#define SHAREDMEMORYDRIVER_H
#define SHARE_MEMORY_OBJECT_SIZE 200
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "Command.h"

using namespace std;

class SharedMemoryDriver{

    private:
        Command* command;
        int fileDescriptor;
        struct stat sharedMemoryObject;
        string statement;

    public:
        SharedMemoryDriver();
        void create(string name);
        void write(string name, Command* buffer);
        Command* read(string name);
        void remove(string name);
};

#endif // SHAREDMEMORYDRIVER_H
