#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "project.hpp"
// #include <sys/stat.h>
using namespace std;


bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)){
        it++;
    }
    return !s.empty() && it == s.end();
}

int main(){
    string option;
    int intoption;
    string choice;
    repository master;


    // while(option != 1){
    //     cout << "type init to start new repository" << endl;
    //     cin >> option;
        
    // }
    while(choice != "init"){
        cout << "type 'init' to start new repository" << endl;
        cout << "Type 'quit' to quit the program" << endl;
        cin >> choice;
        if(choice == "init"){
            bool run = true;
            system("mkdir .minigit");
            cout << "new repository created " << endl;
            while(run){
                cout << "=============================" << endl;
                cout << "    |Welcome to MiniGit|" << endl;
                cout << "=============================" << endl;
                cout << "         |MAIN MENU|" << endl;
                cout << "=============================" << endl;
                cout << "  |Please Select a Number|" << endl;
                cout << "=============================" << endl;
                cout << endl;
                cout << "1. Add files to the current commit" << endl;
                cout << "2. Delete files from the current commit" << endl;
                cout << "3. Commit changes" << endl;
                cout << "4. View previous commits" << endl;
                cout << "5. Quit" << endl;
                cout << endl;
                cout << "Enter Number: ";
                cin >> option;
                if(!is_number(option)){
                    cout << "error, not a number" << endl;
                }
                else{
                    intoption = stoi(option);
                }
                if(intoption > 5 || intoption < 1){ //nothing in the if statement
                //if the if statement is true it will go into default of switch statement

                }
                switch (intoption)
                {
                    case 1:{ //add
                        ifstream file; 
                        bool alreadyThere = true;
                        string input;
                        while(alreadyThere){
                            input = "";
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
                        cout << "Please enter the filename you want to delete or type 'quit' to return to menu:" << endl;
                        cin >> filename;
                        if(filename == "quit"){
                            break;
                        }
                        else{
                            master.deleteFile(filename);
                        }

                        break;

                    }
                    case 3:{
                        master.commit();
                        break;
                    }
                    case 4:{
                        master.checkout();
                        break;

                    }
                    case 5:{
                        cout << endl;
                        cout << "Thank you for using MiniGit" << endl;
                        run = false;
                        return 0;

                    }
                    default:{
                        cout << "fatal. please enter a valid command or number" << endl;
                    }
                }
            }
        }
        else if(choice == "quit"){
            cout << "Thank you for using MiniGit" << endl;
            cout << "Goodbye" << endl;
            return 0;
        }
        else{
            cout << "Please type a valid command" << endl;
        }
    }

    
}


