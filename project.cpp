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
repository::~repository(){ //destructs DLLs and SSLs

    doublyNode* currNode = DLLtail;
    doublyNode* tempNode;
    singlyNode* curr;
    singlyNode* temp;

    while(currNode!=NULL){
        curr = currNode->head;
        while(curr!=NULL){
            temp = curr->next;
            delete curr;
            curr = temp;

        }
        tempNode = currNode->next;
        delete currNode;
        currNode = tempNode;
    }
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
                cout << "file has been added" << endl;
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
            temp = temp->next; //increment SLL node

        }    
           
            if(DLLhead->next == NULL && DLLtail->previous == NULL){  //adds first DLL with head = tail

                DLLhead = DLLtail;
                DLLtail->commitNumber = 1;
                DLLtail->previous = DLLhead;
                DLLhead->next = DLLtail;
                checkoutNode = DLLtail;

            }
            else{
                doublyNode* addNode = new doublyNode; //ads new DLL at tail

                addNode->head = DLLtail->head;
                addNode->previous = DLLtail;
                addNode->next = NULL;
                DLLtail->next = addNode;
                addNode->commitNumber = DLLtail->commitNumber + 1;
                DLLtail = addNode;
                checkoutNode = DLLtail;
            }
}


void copy(string miniFile, string currFile){
    string line;
    //For writing text file
    //Creating ofstream & ifstream class object
    ifstream fromMini;
    fromMini.open(miniFile.c_str());
    //ofstream toMini {currFile};
 
    
    ofstream toMini(currFile, ofstream::trunc); //clearns current file
    if(toMini && fromMini){ //if they both open
 
        while(getline(fromMini,line)){ //writes .minigit file to current file
            toMini << line << endl;
        }
        
        
 
        cout << "Copy Finished" << endl;
 
    } else {
        //Something went wrong
        cout << "Couldn't copy" << endl;
    }
 
    //Closing file
    fromMini.close();
    toMini.close();
 
    return;
}

void repository::checkout(){
    bool keepGoing = true;
    string commit = "";
    int comNum = -1;
    string copyline;
    while(keepGoing == true){  

        cout << "Enter commit number: " << endl;
        cin >> commit;
        if(!isdigit(commit[0])){ //checks weather input is digit
         //do nothing
        }
        else{
            comNum = stoi(commit); //convert to int if it is a number
        }
        if(comNum > -1 && comNum <= DLLtail->commitNumber){ //check if its a valid commit number

            keepGoing = false;
        }
        else{
            cout << "Enter valid commit number." << endl; 
        }

        commit = "";
    }
        doublyNode* temp = DLLtail;
    while(temp!=NULL&&temp->commitNumber != comNum){ //finds DLL node with proper commit number

        temp = temp->previous;
    }
        checkoutNode = temp;//sets checkout node to garuntee add/delete/commit dont work
        singlyNode* headofSLL = temp->head; //sets a head of SLL node
        ifstream file;


         while(headofSLL != NULL){ //for each signly node 
            string tmp = "./.minigit/" + headofSLL->fileVersion;
            string currFile = headofSLL->fileName;
            copy(tmp, currFile);
            headofSLL = headofSLL->next;
        }



}



