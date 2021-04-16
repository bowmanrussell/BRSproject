#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "project.hpp"
// #include <sys/stat.h>
using namespace std;





int main(){

    string init = "";
    while(init != "init"){
    cout << "Welcome to MiniGit. Enter 'init' to make a new repository: ";
    cin >> init;
    }
    repository * master = new repository;
    
    system("mkdir .minigit");
    string command;
    int test;

    cout << "Type a git command: " << endl;

    while(true){

        cin >> command;

        if(command == "add"){
            test = 1;
        }
        if(command == "quit"){
            test = 2;
        }


        switch(test){

            case  1:{
                ifstream file; 
                bool alreadyThere = true;
                string input;
                while(alreadyThere){
                    cout << "Enter file name: " << endl;
                    cin >> input;
                    file.open(input);
                    if(file.fail() || input.length()<5||input[input.length()-4] != '.'){ //checks if a proper (.txt .csv or .cpp) is added 
                                                            //if the file opens, it already exists
                        alreadyThere = true;
                        cout << "Invalid file name" << endl;
                    }
                    else{
                        alreadyThere = false;
                    }
                }
                master->addFile(input);
                break;

            }


            case 2:{
                cout << "git quit" << endl;
                 system("rm -r ./.minigit");

                return 0;


            }

             default:{
                cout << "Fatal. Enter a valid command" << endl;
                break;
             }



        }

        cout << "Type a git command:" << endl;
    }

    system("rm -r ./.minigit");


    return 0;
}