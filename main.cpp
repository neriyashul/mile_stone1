
#include "ReadData.h"
#include "Var.h"

using namespace std;


int main(int argc, char** argv) {
        vector<string> v;
        unordered_map<string, Var*> vars;
     try {
           ReadData readCode;

           // if there is arg, read from file
           if (argc > 1) {
                readCode.readFromFile(argv[1]);
           // else, read from console
           } else {
                readCode.readFromConsole();
           }
           cout << "\nCya next time :)\n" << endl;

      } catch (...) {
           cout << "\nProblem with reading\n" << endl;
      }

     return 0;

}