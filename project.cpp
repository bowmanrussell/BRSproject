#include <iostream>
#include <string>
#include <filesystem>
#include <stdlib.h>
#include "project.hpp"
using namespace std;


repository::repository(){ //constructor
    CurrDLL->commitNumber = 0;
    CurrDLL->head = NULL;
    CurrDLL->previous = NULL;
    CurrDLL->next = NULL;
}




void repository::addFile(string name){
    string line;
    string fileType;
    singlyNode* temp  = CurrDLL->head; //gets temp to head of SLL

        if(temp == NULL){ //inserts if SLL is empty
            temp = new singlyNode;
            line = name.substr(0, (name.length()-4));
            fileType = name.substr(name.length()-4,4);
            temp->fileName = name;
            temp->fileVersion = line + "_00" + fileType; //gets name of file version from name using substrings
            temp->next = NULL;
            CurrDLL->head = temp;
            string copyToGit = "cp " + name + " ./.minigit/" + temp->fileVersion;
            cout << copyToGit << endl;
            system(copyToGit.c_str()); //copies file into minigit directory

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
            line = name.substr(0, (name.length()-3));
            fileType = name.substr(-3,3);
            temp->fileName = name;
            temp->fileVersion = line + "_00." + fileType;

            temp->next = NULL;
            prev->next = temp; //puts temp into end of SLL
        }

}

void repository::deleteFile(string name){
    //create two pointers
    singlyNode* A = CurrDLL -> head;
    singlyNode* B = CurrDLL -> head;
    //create a variable to check if name is found
    bool found = false;
    //use while loop to go through LinkedList
    while(A -> next != NULL){
        //if its found set found to true and break out loop
        if(A -> fileName == name){
            found = true;
            break;
        }
        A = A -> next;
    }
    //if it was not found 
    if(found == false){
        cout << "Filename does not exist." << endl;
        return;
    }
    //set A to head again
    A = CurrDLL -> head;
    //check if that's where the filename is found first
    if(A -> fileName == name){
        CurrDLL -> head = A -> next;
        delete A;
        return;
    }
    //if it was not found at head loop through linked list
    while(A != NULL){
        //if A next is the name
        if(A -> next -> fileName == name){
            //set b equal to the node after A
            B = A -> next -> next;
            //delete the node that the file name was found at
            delete A -> next;
            //set a next to b
            A -> next = B;
            //return out
            return;
        }
        A = A -> next;
    }

}
