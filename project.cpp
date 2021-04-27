#include <iostream>
#include <string>
#include <fstream> 
#include <filesystem>
#include <stdlib.h>
#include "project.hpp"
#include <copyfile.h>
using namespace std;


repository::repository(){ //constructor
    DLLhead->commitNumber = 0;
    DLLhead->head = NULL;
    DLLhead->previous = NULL;
    DLLhead->next = NULL;


    DLLtail->commitNumber = 0;
    DLLtail->head = NULL;
    DLLtail->previous = NULL;
    DLLtail->next = NULL;
    checkoutNode = DLLtail;
}
repository::~repository(){
    doublyNode* temp = DLLtail;
    doublyNode* prevDLL = DLLtail;
    singlyNode* curr;
    singlyNode* prev;
    curr = temp->head;
    prev = temp->head;
    while(temp!=NULL){
        while(curr!=NULL){
            
            prev = curr;
            curr = curr->next;
            delete prev;
        }
        prevDLL = temp;
        temp = temp->previous;  
        delete prevDLL;
    }
    temp = checkoutNode;
    delete temp;
    DLLtail = NULL;
    DLLhead = NULL;
    checkoutNode = NULL;
}

void repository::addFile(string name) // namespace name
{
    if(checkoutNode != DLLtail){
        cout << "return to most current commit to add" << endl;
        return;
    }

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

    if(checkoutNode != DLLtail){
        cout << "return to most current commit to delete" << endl;
        return false;
    }
    
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

    if(checkoutNode != DLLtail){
        cout << "return to most current commit to commit again" << endl;
        return;
    }

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
                if(commitFile == miniGitFile){ //if the files are the same do not do anyhting
                    //not finding equal files
                }
                else{
                    temp->numOfSim++; //  increments number of similar files 
                    temp->fileVersion = temp->fileName + "_" + to_string(temp->numOfSim); //updates SLL node fileVersion
                    copyLine = "cp " + temp->fileName + " ./.minigit/" + temp->fileVersion;
                    system(copyLine.c_str()); //copies file into minigit directory

                        //add converted file into .minigit with incremented version number
                        //increment file's verion number in SLLnode
                }
                miniGitFile = "";
                commitFile = "";

            }      
            temp = temp->next;
            // need to check if file exists, if so change bool to true and break
            // also if it exists, need to compare version in minigit w/ new version  
        }    
            //creates new DLL node, establishes connection with tail and updates tail using add
            if(DLLhead->next == NULL && DLLtail->previous == NULL){ 
                DLLhead = DLLtail;
                DLLtail->commitNumber = 1;
                DLLtail->previous = DLLhead;
                DLLhead->next = DLLtail;
                checkoutNode = DLLtail;

            }
            else{
                doublyNode* addNode = new doublyNode;

                addNode->head = DLLtail->head;
                addNode->previous = DLLtail;
                addNode->next = NULL;
                DLLtail->next = addNode;
                addNode->commitNumber = DLLtail->commitNumber + 1;
                DLLtail = addNode;
                checkoutNode = DLLtail;
            }
            //create new DLLnode
            //add DLLnode into DLL (new DLL = oldDLL->next)
            //set new DLL->head = old DLLhead
}

void repository::checkout(){
    bool keepGoing = true;
    string commit = "";
    int comNum;
    string copyline;
    while(keepGoing == true){

        cout << "Enter commit number: " << endl;
        cin >> commit;
        if(!isdigit(commit[0])){
            //do nothing
        }
        else{
            comNum = stoi(commit);
        }
        if(comNum > -1 && comNum <= DLLtail->commitNumber){

            keepGoing = false;
        }
        else{
            cout << "Enter valid commit number." << endl;
        }
        cout << DLLtail->commitNumber << endl;
        commit = "";
    }
    doublyNode* temp = DLLtail;
    while(temp!=NULL&&temp->commitNumber != comNum){

        temp = temp->previous;
    }
        checkoutNode = temp;
        singlyNode* headofSLL = temp->head;
        ifstream file;
    while(headofSLL != NULL){
        //find file from nodes version number
        string tmp = "./.minigit/" + headofSLL->fileVersion;
        file.open(tmp.c_str());
        copyline = "cp ./.minigit/" + headofSLL->fileVersion + " " + headofSLL->fileName;
        if(!file.fail()){
            deleteFile(headofSLL->fileName);
            system(copyline.c_str());

        }
        headofSLL = headofSLL->next;
    }
}



