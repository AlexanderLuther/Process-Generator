#include "CommandDriver.h"

CommandDriver::CommandDriver(FilesDriver* filesDriver){
    this->filesDriver = filesDriver;
}

Command* CommandDriver::getCommand(string data){
    int parenthsisOIndex = data.find("(");
    int parenthesisCIndex = data.find(")");
    if(parenthsisOIndex == -1 || parenthesisCIndex == -1){
        throw (string)"Comando Incorrecto";
    } else{
        //Remover espacios en blanco y parentesis.
        data = data.substr(parenthsisOIndex+1, parenthesisCIndex-1);
        data.erase(remove(data.begin(), data.end(), ' '), data.end());
        //Split
        splitData(data);

        //Crear la instancia de la clase comando
        switch(dataList.at(0)[0]){
            case 'P':
                if(dataList.size() == 2)
                    return new Command(CREATE_TREE, stoi(dataList.at(1)));
                else if(dataList.size() == 3)
                    return new Command(CREATE_TREE_BRANCH, stoi(dataList.at(1)), stoi(dataList.at(2)));
                else
                    return new Command(CREATE_TREE_BRANCH_LEAF, stoi(dataList.at(1)), stoi(dataList.at(2)), stoi(dataList.at(3)));
            case 'M':
                return new Command(SHOW, stoi(dataList.at(1)));
            case 'I':
                return new Command(PRINT, stoi(dataList.at(1)));
            default:
                throw (string)"Comando Incorecto";
        }
    }
    return nullptr;
}

/**
 * Metodo que realizar un split a los datos que recibe como parametro
 * El caracter delimitador se encuentra dentro del macro DELIMITER.
 * Los datos se almacenan en el vector dataList.
 */
void CommandDriver::splitData(string data){
    dataList.clear();
    stringstream ss(data);
    string token;
    while (getline(ss, token, DELIMITER)) {
        dataList.push_back(token);
    }
}

/**
 * Metodo que ejecuta un comando.
 * @brief CommandDriver::executeCommand
 * @param command
 */
void CommandDriver::executeCommand(Command* command, vector<Stem*>* stems){
    switch(command->getCommandType()) {
        case CREATE_TREE: 
            createTree(command, stems); 
        break;
        case CREATE_TREE_BRANCH: 
            createTreeBranchLeaf(command, stems); 
        break;
        case CREATE_TREE_BRANCH_LEAF:
            createTreeBranchLeaf(command, stems);
        break;
        case PRINT:
            print(command, stems);
        break;
        case SHOW:
        break;
    }
}

/**
 * Metodo que busca un Id dentro de la lista stems.
 * Si el id de una instancia en alguna posicion de la lista es igual al id recibido como
 * parametro se  retorna  true. Si no se encuentra ninguna coincidencia se retorna false.
 * @brief CommandDriver::searchById
 * @param id
 * @param stemsId
 * @return true|false
 */
int CommandDriver::searchById(int id, vector<Stem*>* stems){
    for(int i=0; i<stems->size(); i++){
        if(stems->at(i)->getId() == id) return 1;
    }
    return 0;
}

void CommandDriver::removeStem(int id, vector<Stem*>* stems){
    for(int i=0; i<stems->size(); i++){
        if(stems->at(i)->getId() == id){
           //
            break;
        }
    }
}

/**
 * Metodo que retorna un puntero a una instancia de la clase  Stem
 * Busca dentro de la lista stems y si algun elemento coincide con
 * el parametro id entonces se retorna.
 */ 
Stem* CommandDriver::getStem(int id, vector<Stem*>* stems){
    for(int i=0; i<stems->size(); i++){
        if(stems->at(i)->getId() == id) return stems->at(i);
    }
    return nullptr;
}


/**
 * Metodo que verifica que la cantidad de tallos no exceda a la cantidad maxima.
 */
bool CommandDriver::verifyStemsAmount(vector<Stem*>* stems){
    if(stems->size() < MAXIMUN_TREES_AMOUNT)
         return true;
    else 
        throw (string)"Numero Maximo de Plantas Alcanzado.";
    return false;
}

/**
 * Metodo que verifica que la cantidad de ramas no exceda a la cantidad maxima.
 */
bool CommandDriver::verifyBranchesAmount(Command* command, int type){
    if(command->getBranchesAmount() <= MAXIMUN_BRANCHES_AMOUNT)
        return true;
    else{
        switch(type){
            case 0:
                throw (string)"Error al crear planta con Id=" + to_string(command->getId()) + ". El numero de ramas(" +to_string(command->getBranchesAmount()) + ") excede al maximo permitido(5).";
            break;
            case 1:
                throw (string)"Error al modificar planta con Id=" + to_string(command->getId()) + ". El numero de ramas(" +to_string(command->getBranchesAmount()) + ") excede al maximo permitido(5)."; 
            break;
        }
    }
    return false;
}

/**
 * Metodo que verifica que la cantidad de hojas no exceda a la cantidad maxima.
 */
bool CommandDriver::verifyLeavesAmount(Command* command, int type){
    if(command->getLeavesAmount() <= MAXIMUN_LEAVES_AMOUNT)
        return true;
    else{
        switch(type){
            case 0:
                throw (string)"Error al crear planta con Id=" + to_string(command->getId()) + ". El numero de hojas(" +to_string(command->getLeavesAmount()) + ") excede al maximo permitido(10).";
            break;
            case 1:
                throw (string)"Error al modificar planta con Id=" + to_string(command->getId()) + ". El numero de hojas(" +to_string(command->getLeavesAmount()) + ") excede al maximo permitido(10).";    
            break;
        }
    }
    return false;
}

/**
 * Metodo que crea  un nuevo  tallo sin hojas  ni ramas. Verifica  que no exista ninguna
 * planta con el id que se recibe como parametro. Si existe se recibe 1 caso contrario 0.
 * Si se recibe 1 se lanza un error, si se recibe 0 y no se ha alcanzado el numero maximo
 * de plantas se crea una nueva planta.
 * @brief CommandDriver::createTree
 * @param id
 * @param stemsId
 */
void CommandDriver::createTree(Command* command, vector<Stem*>* stems){    
    switch(this->searchById(command->getId(), stems)){
        
        //Crear Planta
        case 0:
            if(this->verifyStemsAmount(stems)){
                Stem* stem = new Stem(command->getId());
                stem->createStem(command);
                stems->push_back(stem);
            }
        break;

        //Ya existe la Planta
        case 1:
            throw (string)"Ya existe una Planta con Id=" + to_string(command->getId()) + ".";
        break;
    }
}

void CommandDriver::createTreeBranchLeaf(Command* command, vector<Stem*>* stems){
    switch(this->searchById(command->getId(), stems)){
        
        //Crear Planta
        case 0:
            if(this->verifyStemsAmount(stems)){
                if(this->verifyBranchesAmount(command, 0)){
                    if(this->verifyLeavesAmount(command, 0)){
                        Stem* stem = new Stem(command->getId());
                        stem->createStem(command);
                        stems->push_back(stem);
                    } 
                } 
            } 
        break;

        //Modificar Planta
        case 1:
            if(this->verifyBranchesAmount(command, 1)){
                if(this->verifyLeavesAmount(command, 1)){
                    stem = this->getStem(command->getId(), stems);  
                    stem->modifyStem(command);
                    if(command->getBranchesAmount() == 0){
                        this->removeStem(command->getId(), stems);
                    } 
                } 
            } 
        break;
    }
}

void CommandDriver::print(Command* command, vector<Stem*>* stems){
    switch(this->searchById(command->getId(), stems)){
        //No existe la Planta
        case 0:
            throw (string)"No existe ninguna Planta con Id=" + to_string(command->getId()) + ".";
        break;

        //Existe planta
        case 1:
            stem = this->getStem(command->getId(), stems);  
            cout<<"Pausa de 2 segundos para que todos los procesos se actualicen correctamente"<<endl;
            //sleep(2);
            filesDriver->writeFile(to_string(stem->getPID()));
        break;
    }
}

CommandDriver::~CommandDriver(){
}