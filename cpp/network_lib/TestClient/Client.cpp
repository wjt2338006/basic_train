//
// Created by RagPanda on 2016/4/6.
//
#include <iostream>
#include <string>
#include <stdio.h>
#include "../Socket.h"
using namespace std;
void clntTCP();
void clntUDP();
void homework2016415_udpTest();
int main()
{

    clntTCP();
    //clntUDP();
    //homework2016415_udpTest();

}
void clntTCP()
{
    cout << "input ip" << endl;
    string ip("");
    cin >> ip ;

    cout << "input port"<<endl;
    string port("");
    cin >> port ;

    try
    {
        Socket::init();
        Socket client(Socket::IPV4,Socket::TCP);
        client.connect(ip.c_str(),port.c_str());
        while(1)
        {
            string data("");
            cout << "input data (enter q exit)" << endl;
            cin >> data ;
            if(data == string("q")){ break;}
            int len = data.size();

            string sendStr;
            sendStr = std::to_string(len);
            sendStr+="\n";
            sendStr+=data;

            client.write(sendStr);
            cout << "send data:"<< sendStr <<end;
            cout << "recv data" << endl;
            cout << client.read(100) <<endl;
        }
    }
    catch (exception & e){
        cerr<<e.what()<<endl;
    }
}
void clntUDP()
{
    Socket::init();
    string s("13310520313");
    Socket clnt(Socket::IPV4,Socket::UDP);


    /*
      //有连接的UDP
    clnt.connect("127.0.0.1","12345");
    clnt.write(s);
     */


    ///*无连接的
    //clnt.bind("127.0.0.2","12348");//可选
    auto r = clnt.sendTo(s,"127.0.0.1","12345");
    cout <<r <<endl;
    //*/
}
void homework2016415_udpTest()
{
    Socket::init();
    Socket clnt(Socket::IPV4,Socket::UDP);
    clnt.connect("127.0.0.1","12345");

    unsigned  int i = 0;
    unsigned  int max = 100;
    string s("");
    for(int  i=0;i<10000; i++)
    {
        s+="x";
    }
    while(i++ < max)
    {

        clnt.write(s);
    }
    cout << "fine  " << endl;

}
