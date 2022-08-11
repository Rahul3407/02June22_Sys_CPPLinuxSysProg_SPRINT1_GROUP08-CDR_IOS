#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h> /* for definition of errno */
#include <stdarg.h> /* ISO C variable aruments */
#include <cstring>
#define port 4005

using namespace std;

// struct sockaddr_in server_addr, client_addr;
// char server_msg[2000], client_msg[2000];

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

void ReadFromFile(char *fileName, char *buff)
{
        fstream fs;
        fs.open(fileName,ios::in);
        if(!fs)
        {
                strcpy(buff,fileName);
                strcat(buff," : file not found");
                return;
        }

        fs.seekg(0,fs.end);
        int length = fs.tellg();
        fs.seekg(0, fs.beg);

        char *tempbuff = new char[length+1];
        fs.read(tempbuff,length);
        strcpy(buff, tempbuff);
        fs.close();
        delete []tempbuff;
}


// void serverConn(int &sockfd)
// {
//      //create socket

//      sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

//      if(sockfd<0)
//      {
//              perror("socket() error");
//              exit(1);
//      }
//      cout<<"Server Started"<<endl;

//      server_addr.sin_family = AF_INET;
//      server_addr.sin_port = htons(port);
//      server_addr.sin_addr.s_addr = inet_addr("10.0.2.15");

//      if(bind(sockfd,(struct sockaddr *) &server_addr, sizeof(server_addr))<0)
//      {
//              perror("bind() error");
//              exit(1);
//      }

//      cout<<"Server done with binding"<<endl;

//      cout<<"Server is now open to listening for clients"<<endl;
// }


// void clientConn(int &sockfd)
// {
//      sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

//      if(sockfd<0)
//      {
//              perror("socket() error");
//              exit(1);
//      }
//      cout<<"Client Started"<<endl;

//      server_addr.sin_family = AF_INET;
//      server_addr.sin_port = htons(port);
//      server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");