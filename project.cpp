#include <iostream>
#include <string>
#include <fstream> 
#include <filesystem>
#include <stdlib.h>
#include "project.hpp"
using namespace std;


void repository::addDLL(doublyNode* toInsert){
    if(DLLhead == NULL && DLLtail == NULL){ //no commit has happened yet
        toInsert->commitNumber = 0;
        toInsert->head = NULL;
        toInsert->previous = NULL;
        toInsert->next = NULL;
        DLLhead = toInsert;
        DLLtail = toInsert;

    }
    else{ //adds DLLnode to tail of DLL 

        DLLtail->next = toInsert;
        DLLtail->next->previous = toInsert;
        toInsert->commitNumber = DLLtail->commitNumber++;
        DLLtail = toInsert;
        DLLtail->next = NULL; //when next == NULL it is the end of the LL

    }

}

repository::repository(){ //constructor to set everything to NULL
    DLLhead->commitNumber = 0;
    DLLhead->head = NULL;
    DLLhead->previous = NULL;
    DLLhead->next = NULL;
    DLLhead = NULL;

    DLLtail->commitNumber = 0;
    DLLtail->head = NULL;
    DLLtail->previous = NULL;
    DLLtail->next = NULL;
    DLLtail = NULL;
}




void repository::addFile(string name) // namespace name
{

    string line;
    string fileType;
    singlyNode* temp  = DLLtail->head; //gets temp to head of SLL
     while(temp!=NULL){
        if(temp->fileName == name){
            cout << "file already added. Use commit to save file changes" << endl;
            return;
        }
        temp = temp->next;
        
    }

        if(temp == NULL){ //inserts if SLL is empty
            temp = new singlyNode;
            temp->fileName = name;
            temp->fileVersion = name + "_0"; //gets name of file version from name using substrings
            temp->next = NULL;
            DLLhead->head = temp;
            string copyToGit = "cp " + name + " ./.minigit/" + temp->fileVersion;
            //system(copyToGit.c_str()); //copies file into minigit directory
        }

        else{ // inserts at the end of SLL
            singlyNode* prev;

            while (temp !=NULL){//gets temp to end of list with prev pointer
                prev = temp;
                temp = temp->next;
            }
            singlyNode* endOflist = new singlyNode;
            temp = endOflist;
            temp->fileName = name;
            temp->fileVersion = name + "_0"; 


            temp->next = NULL;
            prev->next = temp; //puts temp into end of SLL
        }

}

void repository::deleteFile(string name){

    singlyNode* curr = DLLtail -> head;
    singlyNode* prev = DLLtail -> head;
    bool found = false;
    while(curr != NULL){
            if(curr->fileName == name && curr->fileName == DLLhead->head->fileName){
                //deleteVect.push_back(file)
                DLLhead->head = DLLhead->head->next;
                delete curr;
                found = true;
            }
        
            else{
                if(curr->fileName == name){
                    prev->next = curr->next;
                    delete curr;
                    found = true;
                }

            }
        prev = curr;
        curr = curr -> next;
    }
    if(found == false){
        cout << "Filename does not exist." << endl;
        return;
    }

}


void repository::commit(){
    if(DLLtail->head ==NULL){
        cout << "try adding files before commiting" << endl;
        return;
    }
        string filetoAdd;
        string miniGitFile;//file in minigit directory
        string commitFile; //file you are commiting
        ifstream file;
        int versionNumber;
        string copyLine;
        singlyNode* temp = DLLtail->head; //set crawler Node to head of SLL
        bool doesexist = false;
        while(temp!=NULL){
            string tmp = "./.minigit/" + temp->fileVersion;
            file.open(tmp.c_str());
            if(file.fail()){//add files to .minigit if its not in there already
                cout << "fails" << endl;
                copyLine = "cp " + temp->fileName + " ./.minigit/" + temp->fileVersion;
                system(copyLine.c_str()); //copies file into minigit directory 

            }
            else{
                

                file.open(tmp.c_str()); //collect both files to compare 
                while(file){
                    getline(file,miniGitFile);
                }
                file.close();
                file.open(temp->fileName);
                while(file){
                    getline(file,commitFile); 
                }
                file.close();
                if(commitFile == miniGitFile){ //if the files are the same do not do anyhting
                    //not finding equal files
                    cout << "equal files" << endl;
                    continue;
                }
                else{
                    temp->numOfSim++; //  increments number of similar files 
                    temp->fileVersion = temp->fileName + "_" + to_string(temp->numOfSim); //updates SLL node fileVersion
                    cout << temp->fileVersion  << endl;
                    copyLine = "cp " + temp->fileName + " ./.minigit/" + temp->fileVersion;
                    system(copyLine.c_str()); //copies file into minigit directory

                        //add converted file into .minigit with incremented version number
                        //increment file's verion number in SLLnode


                }
                doublyNode* addNode = new doublyNode;
                //creates new DLL node, establishes connection with tail and updates tail using add
                addNode = DLLtail;
                addNode->commitNumber = DLLtail->commitNumber++;
                addDLL(addNode);
                //create new DLLnode
                //add DLLnode into DLL (new DLL = oldDLL->next)
                //set new DLL->head = old DLLhead

            }
            
            temp = temp->next;
            // need to check if file exists, if so change bool to true and break
            // also if it exists, need to compare version in minigit w/ new version
        
        }

        
}



