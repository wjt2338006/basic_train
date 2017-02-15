
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <string>
#include "Socket.h"
//using namespace std;
void servTCP();
void servUDP();
void homework2016415_udpTest();
int main()
{
    servTCP();
    //servUDP();
    //homework2016415_udpTest();
}

void servTCP()
{
    Socket::init();
    Socket serv(Socket::IPV4,Socket::TCP);
    serv.bind("0.0.0.0","12345");
    serv.listen(10);
    while(true)
    {
      try
      {
        Socket c = serv.accept();
        while(true)
        {
            int preReadNum = 10;
            string preRead = c.read(preReadNum);
            auto num = preRead.find("\n");
            int infoLen = std::stoi(preRead.substr(0,num));
            int restRead = infoLen - (preReadNum-num-1);
            string alreadyReadStr = preRead.substr(num+1,preRead.length());


            string s = c.read(restRead);
            s = alreadyReadStr +s;
            cout <<"trueinfo data:" <<s <<endl;
            c.write(s);
        }

      }
      catch(...)
      {
        std::cerr << "servTCP error" << std::endl;
      }

    }
    //return 0;
}
void servThreadTCP()
{
  Socket::init();
  Socket serv(Socket::IPV4,Socket::TCP);
  serv.bind("0.0.0.0","12345");
  serv.listen(10);
  while(true)
  {

    Socket c = serv.accept();
      //mingw-32需更新 c++11不可用 vs可用
     /* std::thread sonThread([std::move(c)]
    {
      try
      {
        while(true)
        {
          string s = c.read(100);
          cout << s <<endl;
          c.write(s);
        }
      }
      catch(...)
      {
        std::cerr << "servThreadTCP error" << std::endl;
      }


    });
    sonThread.detach();*/
  }
}
void servUDP()
{
    Socket::init();
    Socket serv(Socket::IPV4,Socket::UDP);
    serv.bind("127.0.0.1","12345");

    /*Socket clnt(Socket::IPV4,Socket::UDP);
    clnt.bind("127.0.0.2","45678");*/

    string s = serv.recvFrom(100);
    cout << s << endl;
}
void homework2016415_udpTest()
{
    Socket::init();
    Socket serv(Socket::IPV4,Socket::UDP);
    serv.bind("127.0.0.1","12345");

    int expireTime = 5000;
    int recvBuff =32*1024;
    setsockopt(serv.getOriginSocket(),SOL_SOCKET,SO_RCVBUF,(char*)&recvBuff,sizeof(recvBuff));
    setsockopt(serv.getOriginSocket(),SOL_SOCKET,SO_RCVTIMEO,(char*)&expireTime,sizeof(expireTime));

    unsigned  int i = 0;
    unsigned  int max = 100;
    unsigned  int losePacket = 0;
    while(i++<max)
    {

        string s = serv.read(100000);
        if(s.size() == 0)
        {

            cout<<"no "<<i<<" "<<"lost!"<<endl;

            break;
        }
        cout<<"no "<<i<<" "<<endl;
    }
    i-=1;
    cout << "total:" << max << endl;
    cout << "recv:" << i<< endl;
    cout << "lost:" ;
    float r = (float) 1-((float)i/(float)max);
    cout<<r<<endl;
    return ;

}
