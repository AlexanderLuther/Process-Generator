#ifndef COMMANDDRIVER_H
#define COMMANDDRIVER_H
#define MAXIMUN_TREES_AMOUNT 10
#define MAXIMUN_BRANCHES_AMOUNT 5
#define MAXIMUN_LEAVES_AMOUNT 10
#define DELIMITER ','
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "FilesDriver.h"
#include "Stem.h"
#include "Command.h"
#include "QFileDialog"

#include <QMainWindow>
#include <iostream>

using namespace std;

class CommandDriver{

    private:
        Stem* stem;
        vector<string> dataList;
        FilesDriver* filesDriver;
        
    private:
        void splitData(string data);
        int searchById(int id, vector<Stem*>* stems);
        Stem* getStem(int id, vector<Stem*>* stems);
        bool verifyStemsAmount(vector<Stem*>* stems);
        bool verifyBranchesAmount(Command* command, int type);
        bool verifyLeavesAmount(Command* command, int type);
        void createTree(Command* command, vector<Stem*>* stems);
        void createTreeBranchLeaf(Command* command, vector<Stem*>* stems);
        void print(Command* command, vector<Stem*>* stems);
        void show(Command* command, vector<Stem*>* stems);
        void removeStem(int id, vector<Stem*>* stems);

    public:
        CommandDriver(FilesDriver* filesDriver);
        Command* getCommand(string data);
        void executeCommand(Command* command, vector<Stem*>* stems);
        ~CommandDriver();
};

#endif // COMMANDDRIVER_H
