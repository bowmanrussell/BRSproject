#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "project.hpp"
// #include <sys/stat.h>
using namespace std;





int main(){
    int option;
    while(option != 5){
        cout << "=============================" << endl;
        cout << "         MAIN MENU" << endl;
        cout << endl;
        cout << "   Please choose a number" << endl;
        cout << endl;
        cout << "     Welcome to MiniGit" << endl;
        cout << endl;
        cout << "1. Add files to the current commit" << endl;
        cout << "2. Delete files from the current commit" << endl;
        cout << "3. Commit changes" << endl;
        cout << "4. View previous commits" << endl;
        cout << "5. Quit" << endl;
        cin >> option;
        if(option > 4 || option < 1){
            cout << "Invalid option, please choose a different number" << endl;
        }
        switch (option)
        {
            case 1:{
                string init = "";
                while(init != "init"){
                    cout << "Enter 'init' to make a new repository: ";
                    cin >> init;
                }
                repository * master = new repository;
                system("mkdir .minigit");
                string command;
                int test;
                bool flag = true;
                cout << "Type a git command: " << endl;
                while(flag){
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
                            flag = false;
                        }
                        default:{
                            cout << "Fatal. Enter a valid command" << endl;
                            return 0;
                        }
                    }
                    cout << "Type a git command:" << endl;
                }
                system("rm -r ./.minigit");
                return 0;
                break;
            }
            default:
                break;
            case 2:{
                string filename;
                repository* master;
                cout << "Please enter the filename you want to delete" << endl;
                getline(cin, filename);
                
            }
            case 3:{

            }
            case 4:{

            }
            case 5:{
                cout << "Thank you for using MiniGit" << endl;
                break;
                return 0;
            }
        }
    }

    
}