#include "Leaf.h"

void Leaf::setGrandParentId(int grandParentId){
    this->grandParentId = grandParentId;
}

int Leaf::getGrandParentId(){
    return grandParentId;
}

/**
 * Metodo que crea un proceso Rama.
 */
void Leaf::createLeaf(sem_t* semaphore){
    this->semaphore = semaphore;
    switch(fork()){
        //Error
        case -1: 
            throw (string)"Error creando un nuevo proceso hoja para la planta con id=" + to_string(this->getGrandParentId()); 
        break;
        //Proceso Hoja
        case 0: 
            execute(); 
        break;
        default:
            pthread_create(&thread, NULL, thread_run, NULL);
        break;
    }
}

/**
 * Hilo para esperar a que el proceso hijo termine y que este sea removido del planificador
 * para evitar que se convierta en un proceso zombie
 */
void* Leaf::thread_run(void* data){ 
    wait(NULL); 
  pthread_exit(data);
}

/**
 * Metodo que llama a la lectura dentro de un espacio de memoria compartida
 */
Command* Leaf::read(string name){
    try{
        Command* tempCommand;
        //Entrada Seccion Critica
        sem_wait(semaphore);
        tempCommand = sharedMemoryDriver->read(name);
        sem_post(semaphore);
        //Salida Seccion Critica
        return tempCommand;
    } catch(int error){
        exit(0);
    }
    return nullptr;
}

/**
 * Bucle de ejecucion de la hoja
*/
void Leaf::execute(){
    while(true){    
        sharedCommand = this->read(to_string(this->getGrandParentId()));
        if(sharedCommand->getLeavesAmount() < this->getId()){
            exit(0);
        }
        sleep(1);
    }
}
