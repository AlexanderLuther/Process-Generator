#ifndef STEM_H
#define STEM_H
#include <unistd.h>
#include <sys/types.h>      
#include <sys/shm.h>                
#include <semaphore.h>      
#include <fcntl.h> 
#include <pthread.h>
#include "Process.h"
#include "Command.h"
#include "SharedMemoryDriver.h"
#include "Branch.h"

class Stem : public Process{

    private:
        SharedMemoryDriver* sharedMemoryDriver = new SharedMemoryDriver();
        Command* sharedCommand;
        int currentBranchesAmount = 0;
        pthread_t thread; 

        //Semaforo
        sem_t *semaphore;
 
    private:
        void createSharedMemorySpace(string name);
        void write(string name, Command* Command);
        Command* read(string name);
        void execute();
        static void* thread_run(void* data);

    public:
        Stem(int id) : Process(id){};
        void createStem(Command* command);
        void modifyStem(Command* command);
        
};

#endif // STEM_H
