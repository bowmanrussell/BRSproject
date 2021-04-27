#include <iostream>
#include <string>
using namespace std;



struct singlyNode{
string fileName;
string fileVersion; // Name of file in .minigit folder 
singlyNode * next=NULL;
int numOfSim = 0;
};

struct doublyNode{
    int commitNumber;
    singlyNode * head =NULL;
    doublyNode * previous = NULL;
    doublyNode * next = NULL;
};

class repository{

    private:

    doublyNode* DLLhead = new doublyNode;
    doublyNode* DLLtail = new doublyNode;
    doublyNode* checkoutNode = new doublyNode;

    public:
        repository();
        ~repository();
        void addFile(string name);
        bool deleteFile(string name);
        void commit();
        void checkout();


};