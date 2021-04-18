#include <iostream>
#include <string>
#include <fstream> 
#include <filesystem>
#include <stdlib.h>
#include "project.hpp"
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
}




void repository::addFile(string name) // namespace name
{
    string line;
    string fileType;
    singlyNode* temp  = DLLhead->head; //gets temp to head of SLL

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

    singlyNode* curr = DLLhead -> head;
    singlyNode* prev = DLLhead -> head;
    bool found = false;
    while(curr != NULL){
            if(curr->fileName == name && curr->fileName == DLLhead->head->fileName){
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


void repository::commit(doublyNode* currNode){
        string fileNname = "";
        string miniGitFile;//file in minigit directory
        string commitFile; //file you are commiting
        ifstream file;
        string fullFile;
        string copyLine;
        singlyNode* temp = currNode->head;
        system("cd .minigit");
        bool doesexist = false;
        while(temp!=NULL){
            file.open(temp->fileVersion);
            if(file.fail()){
                copyLine = "cp " + temp->fileName + " ./.minigit/" + temp->fileVersion;
                system(copyLine.c_str()); //copies file into minigit directory
            }
            else{

                file.open(temp->fileVersion); //collect both files to compare 
                while(file){
                getline(file,miniGitFile);
                }
                file.close();
                system("cd ..");
                file.open(temp->fileVersion);
                while(file){
                getline(file,commitFile);
                }
                file.close();
                if(commitFile == miniGitFile){ //if the files are the same do not do anyhting
                    continue;
                }
                else{
                        //add converted file into .minigit with incremented version number
                        //increment file's verion number in SLLnode


                }
                //create new DLLnode
                //add DLLnode into DLL (new DLL = oldDLL->next)
                //set new DLL->head = old DLLhead
                



            }
            

                    
    
            
            temp = temp->next;
            // need to check if file exists, if so change bool to true and break
            // also if it exists, need to compare version in minigit w/ new version
        
        }
        if(doesexist == true){
            // need to check to see if there are differences
        }



}



