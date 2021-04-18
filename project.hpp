#include <iostream>
#include <string>
using namespace std;



struct singlyNode{
string fileName;
string fileVersion; // Name of file in .minigit folder 
singlyNode * next;
};

struct doublyNode{
    int commitNumber;
    singlyNode * head;
    doublyNode * previous;
    doublyNode * next;
};

class repository{

    private:

    doublyNode* DLLhead = new doublyNode;
    doublyNode* DLLtail = new doublyNode;

    public:
        repository();
        //~repository();
        void addFile(string name);
        void deleteFile(string name);
        void commit(doublyNode* currNode);


};