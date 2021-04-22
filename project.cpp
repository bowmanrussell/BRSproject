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

repository::repository(){ //constructor
    DLLhead->commitNumber = 0;
    DLLhead->head = NULL;
    DLLhead->previous = NULL;
    DLLhead->next = NULL;

    DLLtail->commitNumber = 0;
    DLLtail->head = NULL;
    DLLtail->previous = NULL;
    DLLtail->next = NULL;
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
        temp = DLLtail->head;
        if(temp == NULL){ //inserts if SLL is empty
            temp = new singlyNode;
            temp->fileName = name;
            temp->fileVersion = name + "_0"; //gets name of file version from name using substrings
            temp->next = NULL;
            DLLtail->head = temp;
            string copyToGit = "cp " + name + " ./.minigit/" + temp->fileVersion;
            //system(copyToGit.c_str()); //copies file into minigit directory
        }
        else{ // inserts at the end of SLL
            singlyNode* prev;

            while (temp->next !=NULL){//gets temp to end of list with prev pointer
                prev = temp;
                temp = temp->next;
            }
            cout << temp->fileName << endl;
            singlyNode* endOflist = new singlyNode;
            endOflist->fileName = name;
            endOflist->fileVersion = name + "_0"; 


            temp->next = endOflist;
            endOflist->next = NULL; //puts temp into end of SLL
        }

}






bool repository::deleteFile(string name){
    //create two singly nodes and have them point to the head
    singlyNode* curr = DLLtail -> head;
    singlyNode* prev = DLLtail -> head;
    //create a found variable to see if its in the linked list
    bool found = false;
    if(curr == NULL){
        cout << "You need to add files before deleting" << endl;
        return false;
    }
    //have it go through the list
    while(curr != NULL){
            //if the pointer is equal to the name and its the head of the linked list
            if(curr->fileName == name && curr->fileName == DLLtail->head->fileName){
                //set the current head to the next node after head
                DLLtail->head = DLLtail->head->next;
                //delete curr
                delete curr;
                //set found to true
                cout << endl;
                cout << "deleted " << name << " successfully" << endl;
                cout << endl;
                return true;
            }
            else if(curr->fileName == name){
                //if its not the head
                prev->next = curr->next;
                delete curr;
                cout << endl;
                cout << "deleted " << name << " successfully" << endl;
                cout << endl;
                return true;
            }
        prev = curr;
        curr = curr -> next;

    }//if the file name is not found
    cout << "Filename does not exist." << endl;
    return false;
    
}


void repository::commit(){
    if(DLLtail->head ==NULL){
        cout << "try adding files before commiting" << endl;
        return;
    }
        string filetoAdd;
        string miniGitFile = "";//file in minigit directory
        string commitFile = ""; //file you are commiting
        ifstream file;
        int versionNumber;
        string copyLine;
        singlyNode* temp = DLLtail->head; //set crawler Node to head of SLL
        bool doesexist = false;
        while(temp!=NULL){
            string tmp = "./.minigit/" + temp->fileVersion;
            file.open(tmp.c_str());
            cout << tmp << endl;
            if(file.fail()){//add files to .minigit if its not in there already
                cout << "fails" << endl;
                copyLine = "cp " + temp->fileName + " ./.minigit/" + temp->fileVersion;
                system(copyLine.c_str()); //copies file into minigit directory 

            }
            else{
                file.close();
                

                file.open(tmp.c_str()); //open minigit file
                string tempString;
                while(file){
                    getline(file,tempString);
                    miniGitFile.append(tempString); //file in minigit directory
                }
                file.close();
                tempString = "";
                file.open(temp->fileName);
                while(file){
                    getline(file,tempString); 
                    commitFile.append(tempString); //file in parent directory
                }
                file.close();
                tempString = "";
                cout << commitFile << "    " << miniGitFile << endl;
                if(commitFile == miniGitFile){ //if the files are the same do not do anyhting
                    //not finding equal files
                    cout << "equal files" << endl;
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

                miniGitFile = "";
                commitFile = "";

            }      
            temp = temp->next;
            // need to check if file exists, if so change bool to true and break
            // also if it exists, need to compare version in minigit w/ new version  
        }    
}



