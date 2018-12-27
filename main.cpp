

#include "ShuntingYard.h";
#include "stdio.h"
#include "CommandExpression.h"
#include "OpenTcpServer.h"
#include "OpenTcpClientCommand.h"
#include "OpenTcpClientCommand.h"
#include "Enterc.h"
#include "Exit.h"

using namespace std;
int main(){
    string str = "2.5 + 1";
    ShuntingYard s;
    Expression* e = s.expressionFromString(str);

    vector<string> v;
    Command* a = new OpenTcpServer();
    Command*c = new Enterc();
    Command * b = new OpenTcpCommand();
    c->doCommand(v);

    /*OpenServerCommand o;
    int sockfd = o.openServer(5002);
    //int newsockfd = o.connectToClient(sockfd);
    for (int i = 0; i < 5; ++i) {
        o.writeToClient(sockfd);
    }*/

    cout << e->calculate();
    return 0;
}