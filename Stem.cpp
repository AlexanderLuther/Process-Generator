#include "Stem.h"

/**
 * Metodo que crea un proceso Tallo.
 */
void Stem::createStem(Command* command){
    this->createSharedMemorySpace(to_string(this->getId()));
    this->semaphore = sem_open(to_string(this->getId()).c_str(), O_CREAT | O_EXCL, 0644, 1);
    int tempPID;
    tempPID = fork();
    switch(tempPID){
        //Error
        case -1:
            sharedMemoryDriver->remove(to_string(this->getId()).c_str());
            sem_unlink (to_string(this->getId()).c_str());
            sem_close(semaphore); 
            throw (string)"Error creando un nuevo proceso para la planta con id=" + to_string(this->getId()); 
        break;
        //Proceso Tallo
        case 0: 
            execute(); 
        break;
        //Proceso Consola
        default:
            this->setPID(tempPID);
            this->write(to_string(this->getId()), command);
            pthread_create(&thread, NULL, thread_run, NULL);
        break;
    }
}

/**
 * Hilo para esperar a que el proceso hijo  termine y que este sea removido del planificador
 * para evitar que se convierta en un proceso zombie
 */
void* Stem::thread_run(void* data){ 
    wait(NULL); 
    pthread_exit(data);
}

/*
 * Metodo que modifica un proceso Tallo
 */ 
void Stem::modifyStem(Command* command){
    this->write(to_string(this->getId()), command);
}

/**
 * Metodo que llama a la creacion de un nuevo espacio de memoria compartida.
 */
void Stem::createSharedMemorySpace(string name){
    try{
        sharedMemoryDriver->create(name);
    } catch(int error){
        switch(error){
            case 0: throw (string)"Error de Creacion: No se pudo crear un objeto de memoria compartida para la planta con id=" + to_string(this->getId());
            case 1: throw (string)"Error de Creacion: No se pudo asignar un tamaño al objeto de memoria compartida para la planta con id=" + to_string(this->getId());
        }
    }
}

/**
 * Metodo que llama a la escritura dentro de un espacio de memoria compartida
 */
void Stem::write(string name, Command* command){
    try{
        //Entrada Seccion Critica
        sem_wait(semaphore);
        sharedMemoryDriver->write(name, command);
        sem_post(semaphore);
        //Salida Seccion Critica
    } catch(int error){
        switch(error){
            case 0: throw (string)"Error de Escritura: No se pudo leer el objeto de memoria compartida para la planta con id=" + to_string(this->getId());
            case 1: throw (string)"Error de Escritura: No se pudo mapear el objeto de memoria compartida para la planta con id=" + to_string(this->getId());
        }
    }
}

/**
 * Metodo que llama a la lectura dentro de un espacio de memoria compartida
 */
Command* Stem::read(string name){
    try{
        Command* tempCommand;
        //Entrada Seccion Critica
        sem_wait(semaphore);
        tempCommand = sharedMemoryDriver->read(name);
        sem_post(semaphore);
        //Salida Seccion Critica
        return tempCommand;
    } catch(int error){
        switch(error){
            case 0: throw (string)"Error de Lectura: No se pudo leer el objeto de memoria compartida para la planta con id=" + to_string(this->getId());
            case 1: throw (string)"Error de Lectura: No se pudo hacer fstat sobre el objeto de memoria compartida para la planta con id=" + to_string(this->getId());
            case 2: throw (string)"Error de Lectura: No se pudo mapear el objeto de memoria compartida para la planta con id=" + to_string(this->getId());
        }
    }
    return nullptr;
}

/**
 * Bucle de ejecucion del Tallo 
*/
void Stem::execute(){
    while(true){    
        sharedCommand = this->read(to_string(this->getId()));
        
        //Verificar si se termina el proceso Tallo
        if(sharedCommand->getCommandType() == CREATE_TREE_BRANCH && sharedCommand->getBranchesAmount() == 0){
            sem_unlink (to_string(this->getId()).c_str());
            sem_close(semaphore); 
            this->sharedMemoryDriver->remove(to_string(this->getId()));
            exit(0);
        }
        
        //Crear Ramas
        if(this->currentBranchesAmount < sharedCommand->getBranchesAmount()){
            for(int i=0; i<(sharedCommand->getBranchesAmount()-this->currentBranchesAmount); i++){
                Branch* branch = new Branch(this->currentBranchesAmount+1);
                branch->setParentId(this->getId());
                branch->createBranch(this->semaphore);
                this->currentBranchesAmount++;
            }
        //Eliminar Ramas
        } else if(this->currentBranchesAmount > sharedCommand->getBranchesAmount()){
            this->currentBranchesAmount = sharedCommand->getBranchesAmount();
        } 
        sleep(1);
    }
}
