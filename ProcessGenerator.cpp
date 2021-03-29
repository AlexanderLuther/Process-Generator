#include <iostream>
#include <vector>
#include "FilesDriver.h"
#include "CommandDriver.h"
#include "Command.h"
#include "Stem.h"

void menu();
void textInputMode();
void interactiveMode();

FilesDriver* filesDriver = new FilesDriver();
CommandDriver* commandDriver = new CommandDriver(filesDriver);
vector<Stem*>* stems = new vector<Stem*>();
Command* command;

int main(){
    menu();
    return 0;
}

void menu(){
    int selectedOption;
    while(selectedOption != 3){
        cout<<"Process Generator"<<endl;
        cout<<"[1] Modo Interactivo"<<endl;
        cout<<"[2] Modo Entrada de Texto"<<endl;
        cout<<"[3] Salir"<<endl;
        cout<<"Ingrese la opcion deseada y presione enter"<<endl;
        cin>>selectedOption;
        switch(selectedOption){
            case 1: interactiveMode(); break;
            case 2: textInputMode(); break;
            case 3: exit(1); break;
            default: cout<<"La opcion ingresada no es valida\n"<<endl; break;
        }
    }
}

void textInputMode(){
    if(filesDriver->fileExist()){
        vector<string>* data = new vector<string>();
        filesDriver->readFile(data);
        for(int i=0; i<data->size(); i++){
            try{
                command = commandDriver->getCommand(data->at(i));
                commandDriver->executeCommand(command, stems);
                cout<<command->getCommand() + " ejecutado.\n"<<endl;
            } catch(string exception){
                cout<<exception<<endl;
            }
        }
    } else{
        printf("Archivo de entrada no encontrado.\n");
    }
}

void interactiveMode(){
    try{
        string data;
        cout<<"Ingrese el comando sin dejar espacios en blanco y presione enter"<<endl;
        cin>>data;
        command = commandDriver->getCommand(data);
        commandDriver->executeCommand(command, stems);
        cout<<command->getCommand() + " ejecutado.\n"<<endl;
    } catch(string exception){
        cout<<exception<<endl;
    }
}