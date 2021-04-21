#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include "project.hpp"
using namespace std;




int main(){
    int option;
    vector<string> deleteVect;
    string choice;
    repository master;
    doublyNode* currNode = new doublyNode;
    master.addDLL(currNode);
    
    bool check = false;
    while(choice != "init"){
        cout << "     Welcome to MiniGit" << endl;
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
                cout << "1. Add file" << endl;
                cout << "2. Delete file" << endl;
                cout << "3. Commit changes" << endl;
                cout << "4. View previous commits (checkout)" << endl;
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
                        cin >> filename;
                        master.deleteFile(filename);
                        break;
                    }
                    case 3:{
                        master.commit();
                        break;
                    }
                    case 4:{

                    }
                    case 5:{
                        cout << "Quiting will delete your repository. Are you sure you want to procceed?  Type '1234321' to confirm deletion." << endl;
                        cin >> option;
                        if(option == 1234321){
                            cout << "Thank you for using MiniGit" << endl;
                            system("rm -r .minigit");
                            return 0;

                        }
                        else{
                            cout << "Repository not deleted." << endl;
                            break;
                        }
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


