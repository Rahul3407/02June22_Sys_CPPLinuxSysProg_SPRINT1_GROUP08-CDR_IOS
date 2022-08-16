#include <myHeader.h>
#include <client.h>

#define ARR_SIZE 10
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 1024

string User::getPass(){
        return password;
}
string User::getUser(){
        return username;
}

map<string,User> users;

int registers(){
        string u,p;
        string g;
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
        return TRUE;
}

int login(){
        string u,p;
        cout<<"enter username"<<endl;
        cin >>u;
        cout <<"enter password"<<endl;
        cin >>p;
        if(users[u].getPass()!=p){
        return FALSE;
        }
        return TRUE;
}
int pro=0;
int main()
{
        ifstream f("user.txt");
    string li;
    if(!f){
        cout<<"Unable to open file"<<endl;
    }
    else{
        string tm1,ta1[ARR_SIZE];
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
                                if(log==0){
                cout <<"Enter your choice \n1.Register\n2.login"<<endl;
                cin >>c;
                switch(c){
                        case 1:r=registers();
                            if(r!=TRUE)
                            cout <<"Unable to register"<<endl;
                        else
                            cout <<"Registered successfully"<<endl;
                        break;


                    case 2:r1=login();
                        if(r1!=TRUE)
                                cout <<"Unable to login"<<endl;
                        else{
                            cout <<"Login successfully"<<endl;
                            log=1;
                            }
                        break;
                                        default:
                                                cout<<"Invalid Choice"<<endl;
                                                }
                                 }
                                 else{
                                         cout <<"Enter your choice \n1.Process CDR\n2.Search\n3.Logout"<<endl;
                                         cin>>c;
                                         switch(c){
                                                        case 1:process_cdr();
                                                                        pro=1;
                                                                        break;
                                                        case 2:if(pro==0){
                                                                        process_cdr();
                                                                        pro=1;
                                                                        process_cdr();
                                                                        break;
                                                                        }
                                                                        else{
                                                                                process_cdr();
                                                                                break;
                                                                        }
                                                        case 3:cout<<"Logged out:"<<endl;
                                                                        log=0;
                                                                        break;
                                                        default:
                                                                        cout<<"Invalid Choice"<<endl;
                                         }
                                 }
                 }
        }
}

int process_cdr(){
        int sockfd, ret;

    struct sockaddr_in sAddr;

    char buff[MAX_SIZE];

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

                //CDR Processing

                if(pro==0){
        if(ret < 0)
        {
                perror("connect() error");
            exit(1);
        }
            char buff1[]="data.cdr";
            write(sockfd, buff1, strlen(buff1));   //Sends buff1 as "data.cdr" to line 167 of server
                bzero(buff, sizeof(buff));
                if(read(sockfd, buff,MAX_SIZE ) < 0)
                {
                        perror("read() error");
                    exit(1);
                }
                else
                    cout<<"Server: \t"<<buff<<endl;   //Receives content as "Processed the cdr file and created out.txt file" from line 216 of server
                }

                //Searching for country code
                else{
                        char buff2[ARR_SIZE];
                        cout<<"Enter country code to search"<<endl;
                         cin>>buff2;
                         write(sockfd, buff2, strlen(buff2));    //Sending country code to line 167 of server if condition of line 150 fails in this client file
                         bzero(buff, sizeof(buff));
                         if(read(sockfd, buff, MAX_SIZE) < 0)    //Here buff="Not" if condition of line 173 fails in server
                         {
                                perror("read() error");
                                exit(1);
                         }
                         else{
                                if(strcmp(buff,"Not")==0)
                                        cout <<"Not Able to find a Match"<<endl;
                                else
                                        cout<<buff<<endl;
                         }
                }

        return EXIT_SUCCESS;

}