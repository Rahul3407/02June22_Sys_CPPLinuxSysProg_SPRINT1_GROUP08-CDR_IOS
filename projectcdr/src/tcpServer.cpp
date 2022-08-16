#include <myHeader.h>
#include <server.h>
#include <client.h>

#define MAX_SIZE 1024      //Buffer size
#define BACK_LOG 10        //Backlog size
#define ARR_SIZE 10        //Character array size

//setters and getters
string Operator:: getName(){
        return b_name;
}
void Operator::setInc(long c){
        incom_call=c;
}
void Operator::setOuc(long c){
        out_call=c;
}
void Operator::setDown(long d){
    d_download=d;
}
void Operator::setUp(long u){
    d_upload=u;
}
void Operator::setIn(long i){
    in_msg=i;
}
void Operator::setOut(long o){
    out_msg=o;
}
long Operator::getInc(){
    return incom_call;
}
long Operator::getOuc(){
    return out_call;
}
long Operator::getDown(){
    return d_download;
}
long Operator::getUp(){
    return d_upload;
}
long Operator::getIn(){
    return in_msg;
}
long Operator::getOut(){
    return out_msg;
}
long Operator::getId(){
    return t_operators;
}

long j=0;
string c,col[ARR_SIZE];
map<long,Operator> out;     //STL container Map
void process_chunk(string l)
{
        stringstream X(l);      //Tokenization
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

        if(out.count(l1))
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
                 Operator o(l1,col[1],l2,t1,l3,l4,l5,l6);
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
                 out[l1]=o;
                     }
             else{
                 Operator o(l1,col[1],t1,t1,t1,t1,t1,t2);
                 out[l1]=o;
                 }

                 }
}

int main()
{
        ostringstream a;
        int sockfd, ret, newSockfd ;    //File descriptor

    struct sockaddr_in sAddr, newAddr;

    socklen_t addr_size;

        char buff[MAX_SIZE];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("socket() error");
        exit(1);
        }
        cout<<"[+]Server socket is created.\n";

                // Populating Own address structure to bind it to the Socket
        memset(&sAddr,'\0',sizeof(sAddr));

        sAddr.sin_family = AF_INET;
        sAddr.sin_port = htons(PORT);
        sAddr.sin_addr.s_addr = inet_addr("127.0.0.1");    // IP Address

        ret = bind(sockfd,(struct sockaddr*)&sAddr,sizeof(sAddr));

        if(ret < 0)
        {
                perror("bind() error");
            exit(1);
        }

        cout<<"[+]Bind to the port: "<<4056<<endl;

        if(listen(sockfd, BACK_LOG) == 0)
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
                        bzero(buff, sizeof(buff));
                        read(newSockfd, buff,MAX_SIZE );     //Receives buff as "data.cdr" or country code from 173 line of client based on conditions
                                                cout<<buff<<endl;
                                                if(strcmp(buff,"")==0){
                                                        cout<<"Disconnected"<<endl;
                                break;
                                }
                        if(strcmp(buff,"data.cdr") != 0)
                        {
                                long f=stol(buff);
                                                        if(!out.count(f)){
                                                                char buff3[]="Not";
                                                                write(newSockfd, buff3, strlen(buff3));    //Sending buff3 content to buff in line 175 of client
                                                        }
                                                        else{
                                                                a << "Operator Brand: " << out[f].getName() << " ("<<out[f].getId()<< ")\n\tIncoming voice call durations: "<< out[f].getInc() <<"\n\tOutgoing voice call durations: "<< out[f].getOuc()<<"\n\tIncoming SMS messages: "<< out[f].getIn()<<"\n\tOutgoing SMS messages: "<<out[f].getOut()<<"\n\tMB downloaded: "<< out[f].getDown()    <<" | MB uploaded: "<< out[f].getUp()<<endl;
                                                                string output=a.str();
                                                                char buff4[MAX_SIZE];
                                                                strcpy(buff4,output.c_str());
                                                                write(newSockfd, buff4, strlen(buff4));  //The data in buff4 sending to buff in line 184 of client
                                                        }
                                                        break;
                        }
                        else
                        {
                            cout<<"File from Client"<<buff<<endl;
                            ifstream file(buff);
                            string l;
                            if(!file)
                                {
                                        cout<<"Unable to open"<<endl;
                                                                        char buff2[]="Unable to find cdr file";
                                                                        write(newSockfd, buff2, strlen(buff2));
                                }
                            else
                                {
                                    cout <<"Proccessing Data"<<endl;
                                    while(getline(file,l)){
                                        process_chunk(l);
                                    }
                                                                        cout <<"Processed Data"<<endl;
                                }
                                ofstream outfile;
                                outfile.open("out.txt");
                                                         map<long,Operator>::iterator itr;
                                                         for(itr=out.begin();itr!=out.end();++itr){
                                        outfile<< "Operator Brand: " <<  (itr->second).getName() << " ("<<itr->first<< ")\n\tIncoming voice call durations: "<< (itr->second).getInc() <<"\n\tOutgoing voice call durations: "<< (itr->second).getOuc()<<"\n\tIncoming SMS messages: "<< (itr->second).getIn()<<"\n\tOutgoing SMS messages: "<<(itr->second).getOut()<<"\n\tMB downloaded: "<< (itr->second).getDown()<<" | MB uploaded: "<< (itr->second).getUp()<<endl;
                        }
                                outfile.close();
                                char buff1[]="Processed the cdr file and created out.txt file";
                                write(newSockfd, buff1, strlen(buff1));      //Sending content of buff1 to line 165 of client
                                bzero(buff, sizeof(buff));
                                bzero(buff1, sizeof(buff1));
                                                                break;
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

    return EXIT_SUCCESS;
}
