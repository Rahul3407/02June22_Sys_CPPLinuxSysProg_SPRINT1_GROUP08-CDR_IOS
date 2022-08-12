#include <myHeader.h>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <map>
#include <thread>
#include <cstdlib>
class Operator
{
         public:
                Operator(){}    //Default Costructor
                Operator(long o,string b,long c1,long c2,long dow,long up,long in,long out)    //Parameterized Constructor
                {
                        t_operators=o;
                        b_name=b;
                        incom_call=c1;
                        out_call=c2;
                        d_download=dow;
                        d_upload=up;
                        in_msg=in;
                        out_msg=out;
                }

        //setters and getters
                string getName(){
                return b_name;
                }
                void setInc(long c){
                incom_call=c;
                }
                void setOuc(long c){
                        out_call=c;
                }
                void setDown(long d){
                d_download=d;
                }
                void setUp(long u){
                d_upload=u;
                }
                void setIn(long i){
                in_msg=i;
                }
                void setOut(long o){
                out_msg=o;
                }
                long getInc(){
                return incom_call;
                }
                long getOuc(){
                return out_call;
                }
                long getDown(){
                return d_download;
                }
                long getUp(){
                return d_upload;
                }
                long getIn(){
                return in_msg;
                }
                long getOut(){
                return out_msg;
                }
                long getId(){
                return t_operators;
                }

        private:
                long t_operators;
        string b_name;
        long incom_call;
        long out_call;
        long d_download;
        long d_upload;
        long in_msg;
        long out_msg;
};
long j=0;
string c,col[10];
map<long,Operator> out;
void process_chunk(string l)
{
        stringstream X(l);
        while(getline(X,c,'|')){
                col[j++]=c;
        }
        j=0;
        long l1=stol(col[2]);
        long l2=stol(col[4]);
        long l3=stol(col[5]);
        long l4=stol(col[6]);
        long l5=0;
        long l6=0;
        long t1=0;
        long t2=1;

//Logic of code

        if(out[l1].getId()!=0)
        {
                if(col[3]=="MTC")
                        out[l1].setInc(out[l1].getInc()+l2);
                else if(col[3]=="MOC")
                    out[l1].setOuc(out[l1].getOuc()+l2);
                else if(col[3]=="GPRS")
                {
                        out[l1].setDown(out[l1].getDown()+l3);
                        out[l1].setUp(out[l1].getUp()+l4);
                }
                else if(col[3]=="SMS-MT")
                        out[l1].setIn(out[l1].getIn()+1);
                else
                        out[l1].setOut(out[l1].getOut()+1);
        }
        else{

                if(col[3]=="MTC"){
                        Operator o(l1,col[1],t1,l2,l3,l4,l5,l6);
                        out[l1]=o;
                        }
                else if(col[3]=="MOC"){
                        Operator o(l1,col[1],t1,l2,l3,l4,l5,l6);
                        out[l1]=o;
                        }
                else if(col[3]=="GPRS"){
                        Operator o(l1,col[1],t1,t1,l3,l4,l5,l6);
                        out[l1]=o;
                        }
                else if(col[3]=="SMS-MT"){
                        Operator o(l1,col[1],t1,t1,t1,t1,t2,t1);
                        out[l1];
                        }
                else{
                        Operator o(l1,col[1],t1,t1,t1,t1,t1,t2);
                        out[l1];
                        }

        }
}

int main()
{

        int sockfd, ret ;

        struct sockaddr_in sAddr, newAddr;

        socklen_t addr_size, newSockfd;

        char buff[1024];
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0)
        {
                perror("socket() error");
                exit(1);
        }

        cout<<"[+]Server socket is created.\n";

        memset(&sAddr,'\0',sizeof(sAddr));

        sAddr.sin_family = AF_INET;
        sAddr.sin_port = htons(4056);
        sAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        ret = bind(sockfd,(struct sockaddr*)&sAddr,sizeof(sAddr));

        if(ret < 0)
        {
                perror("bind() error");
                exit(1);
        }

        cout<<"[+]Bind to the port: "<<4056<<endl;


        if(listen(sockfd,10) == 0)
                cout<<"[+]Listening....."<<endl;
        else
                cout<<"[-]Error in binding"<<endl;
        while(1){
                memset(&buff,'\0',sizeof(buff));
                newSockfd = accept(sockfd,(struct sockaddr*) &newAddr, &addr_size);
                if(newSockfd < 0)
                {
                        perror("accept() error");
                        exit(1);
                }
                if(fork() == 0){

                        while(1){
                                //recv(newSockfd, buff, 1024,0);
                                read(newSockfd, buff, 1024);
                                if(strcmp(buff,":Bye") == 0 || strcmp(buff,"")==0)
                                {
                                        bzero(buff, sizeof(buff));
                                        cout<<"Disconnected Client"<<endl;
                                        break;
                                }
                                else
                                {
                                    cout<<"size"<<sizeof(buff)<<endl;
                                        cout<<"Client Message: "<<buff<<endl;
                                        ifstream file(buff);
                                        string l;
                                        if(!file)
                                        {
                                        cout<<"Unable to open"<<endl;
                                        }
                                        else
                                        {
                                                cout <<"Proccessing Data"<<endl;
                                                while(getline(file,l)){
                                        process_chunk(l);
                                }
                                }
                                ofstream outfile;
                                outfile.open("out.txt");
                map<long,Operator>::iterator itr;
                                for(itr=out.begin();itr!=out.end();++itr){
                                        outfile<< "Operator Brand: " <<  (itr->second).getName() << " ("<<itr->first<< ")\n\tIncoming voice call durations: "<< (itr->second).getInc() <<"\n\tOutgoing voice call durations: "<< (itr->second).getOuc()<<"\n\tIncoming SMS messages: "<< (itr->second).getIn()<<"\n\tOutgoing SMS messages: "<<(itr->second).getOut()<<"\n\tMB downloaded: "<< (itr->second).getDown()<<" | MB uploaded: "<< (itr->second).getUp()<<endl;
                        }
                                outfile.close();
                                char buff1[]="Processed the cdr file and created out.txt file";
                                write(newSockfd, buff1, strlen(buff1));
                                bzero(buff, sizeof(buff));
                                bzero(buff1, sizeof(buff1));
                                }
                        }
                }
                else
                {
                        close(sockfd);
                        //close(newSockfd);
                        wait(0);
                }

        }

        close(newSockfd);

        return 0;
}
