#include <myHeader.h>
#include <server.h>

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
                        bzero(buff, sizeof(buff));
                        read(newSockfd, buff, 1024);
                                                cout<<buff<<endl;
                                                if(strcmp(buff,"")==0){
                                                        cout<<"Disconnected"<<endl;
                                break;
                                }
                        if(strcmp(buff,"data.cdr") != 0)
                        {
                                long f=stol(buff);
                                                        if(out[f].getId()==0){
                                                                char buff3[]="Not";
                                                                write(newSockfd, buff3, strlen(buff3));
                                                        }
                                                        else{
                                                                cout<< "Operator Brand: " << out[f].getName() << " ("<<out[f].getId()<< ")\n\tIncoming voice call durations: "<< out[f].getInc() <<"\n\tOutgoing voice call durations: "<< out[f].getOuc()<<"\n\tIncoming SMS messages: "<< out[f].getIn()<<"\n\tOutgoing SMS messages: "<<out[f].getOut()<<"\n\tMB downloaded: "<< out[f].getDown()    <<" | MB uploaded: "<< out[f].getUp()<<endl;
                                                                char buff4[]="found data";
                                                                write(newSockfd, buff4, strlen(buff4));
                                                        }
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
                                write(newSockfd, buff1, strlen(buff1));
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

    return 0;

}
