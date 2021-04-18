#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "project.hpp"
// #include <sys/stat.h>
using namespace std;




int main(){
    int option;
    string choice;
    repository master;
    bool check = false;


    // while(option != 1){
    //     cout << "type init to start new repository" << endl;
    //     cin >> option;
        
    // }
    while(choice != "init"){
        cout << "type 'init' to start new repository" << endl;
        cin >> choice;
        if(choice == "init"){
            system("mkdir .minigit");
            cout << "new repository created " << endl;
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
                if(option > 5 || option < 1){
                    cout << "Invalid option, please choose a different number" << endl;
                }
                switch (option)
                {
                    case 1:{ //add
                        ifstream file; 
                        bool alreadyThere = true;
                        string input;
                        while(alreadyThere){
                            cout << "Enter file name: " << endl;
                            cin >> input;
                            file.open(input);
                            if(file.fail() || input.length()<5||input[input.length()-4] != '.'){ 
                                //checks if a proper (.txt .csv or .cpp) is added 
                                //if the file opens, it already exists
                                alreadyThere = true;
                                cout << "Invalid file name" << endl;
                            }
                            else{
                                alreadyThere = false;
                            }
                        }
                        master.addFile(input);
                        break;
                    }
        
                    case 2:{
                        string filename;
                        //repository* master;
                        cout << "Please enter the filename you want to delete" << endl;
                        getline(cin, filename);
                        master.deleteFile(filename);
                        break;
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
                    default:{
                        cout << "fatal. please enter a valid command" << endl;
                    }
                }
            }
        }
        else{
            cout << "please enter a valid option" << endl;
        }
    }

    
}


