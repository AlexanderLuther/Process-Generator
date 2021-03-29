#include "MainFrame.h"
#include "ui_mainframe.h"

MainFrame::MainFrame(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainFrame){
    ui->setupUi(this);
}

/**
 * Funcion que obtiene y llama a la ejecucion de comandos.
 * Valida que commandArea no este vacio y que no contenga  solamente espacios.
 * Si se cumple lo anterior, obtiene los datos en commandArea y elimina  todos
 * los espacions que el QString  contenga. Obtiene  una instancia  de la clase
 * Command y asigna su valor al objeto command. Llama a la ejecucion del comando
 * escribe el comando utilizado en historyArea y limpia el  texto ingresado en
 * commandArea. Si se produce una excepcion esta es  capturada y se muestra un
 * mensaje de error en historyArea.
 * @brief MainFrame::on_executeButton_clicked
 */
void MainFrame::on_executeButton_clicked(){
    try{
        if(!ui->commandArea->text().isEmpty() || ui->commandArea->text().replace(" ","").size() != 0){
            command = commandDriver->getCommand(ui->commandArea->text().replace(" ","").toStdString());
            commandDriver->executeCommand(command, stems);
            ui->historyArea->append(QString::fromStdString(command->getCommand()));
        }
    } catch(QString msg){
        ui->historyArea->append(msg);
    }
    ui->commandArea->clear();
}

MainFrame::~MainFrame(){
    delete ui;
}

void MainFrame::on_actionCargar_Archivo_triggered(){
    vector<string>* data = new vector<string>();
    string path = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("Text Files (*.txt)")).toStdString();
    filesDriver->readFile(data, path);
    for(int i=0; i<data->size(); i++){
        try{
            command = commandDriver->getCommand(data->at(i));
            commandDriver->executeCommand(command, stems);
            ui->historyArea->append(QString::fromStdString(command->getCommand()));
        } catch(string exception){
            ui->historyArea->append(QString::fromStdString(exception));
        }
    }
}
