#include <fstream>
#include <sstream>
#include <string>
#include<map>
#include <myHeader.h>
#define PORT 4056
int process_cdr();
class User{
        private:
                int age;
                string username;
                string gender;
                string password;
        public:
                User() {}
                User(int a,string u,string g,string p){
                age=a;
                username=u;
                gender=g;
                password=p;
                }
                string getPass(){
                return password;
                }
                string getUser(){
                return username;
                }
        };
map<string,User> users;
int registers(){
string u,p,g;
cout <<"enter username"<<endl;
cin >>u;
cout <<"enter password"<<endl;
cin >>p;
cout <<"enter gender (M/F)"<<endl;
cin >>g;
int a;
cout <<"enter age"<<endl;
cin >>a;
ofstream f;
f.open("user.txt",ios::app);
f <<u<<" "<<a<<" "<<g<<" "<<p<<endl;
User u1(a,u,g,p);
users[u]=u1;
return 1;
}
int login(){
string u,p;
cout<<"enter username"<<endl;
cin >>u;
cout <<"enter password"<<endl;
cin >>p;
if(users[u].getPass()!=p){
        return 0;
}
return 1;
}
int main()
{
        ifstream f("user.txt");
        string li;
        if(!f){
        cout<<"Unable to open file"<<endl;
        }
        else{
        string tm1,ta1[10];
        int j=0;
        while(getline(f,li)){
                stringstream X(li);
                while(getline(X,tm1,' ')){
                        ta1[j++]=tm1;
                        }
                        j=0;
                        User u(stoi(ta1[1]),ta1[0],ta1[2],ta1[3]);
                        users[ta1[0]]=u;
        }
        int log=0;
        int c=0,r=0,r1=0;
        while(1){
                cout <<"Enter your choice \n1.Register\n2.login\n3.process cdr"<<endl;
                cin >>c;
                switch(c){
                case 1:r=registers();
                                if(r!=1)
                                        cout <<"unable to register"<<endl;
                                else
                                        cout <<"registered successfully"<<endl;
                                break;
                case 2:r1=login();
                                if(r1!=1)
                                cout <<"unable to login"<<endl;
                        else{
                                        cout <<"login successfully"<<endl;
                                        log=1;
                                }
                        break;
                case 3:if(log!=1){
                                        cout <<"login to process cdr"<<endl;
                                }
                                else{
                                        cout <<"processing cdr"<<endl;
                                        process_cdr();
                                }
                                break;

        }
        }
        }
}
int process_cdr(){
        int sockfd, ret;

        struct sockaddr_in sAddr;

        char buff[1024];

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0)
        {
                perror("socket() error");
                exit(1);
        }

        cout<<"[+]Client socket is created.\n";

        memset(&sAddr,'\0',sizeof(sAddr));

        sAddr.sin_family = AF_INET;
        sAddr.sin_port = htons(PORT);
        sAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        ret = connect(sockfd, (struct sockaddr*)&sAddr, sizeof(sAddr));

        if(ret < 0)
        {
                perror("connect() error");
                exit(1);
        }
        cout<<"[+]Connected to the Server"<<endl;
        while(1)
        {
                cout<<"Client: \t";
                cin>>buff;
                //send(sockfd, buff, strlen(buff), 0);
                write(sockfd, buff, strlen(buff));
                if(strcmp(buff, ":Bye") == 0)
                {
                        close(sockfd);
                        cout<<"Disconnected from the server"<<endl;
                        exit(0);
                }
                bzero(buff, sizeof(buff));
                //if(recv(sockfd, buff, 1024, 0) < 0)
                if(read(sockfd, buff, 1024) < 0)
                {
                        perror("read() error");
                        exit(1);
                }
                else
                        cout<<"Server: \t"<<buff<<endl;
        }
        return 0;

}