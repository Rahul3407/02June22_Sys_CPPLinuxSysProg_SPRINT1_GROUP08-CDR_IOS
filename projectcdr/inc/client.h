#pragma once
#include <myHeader.h>
#define PORT 4056      //Port to be open

int process_cdr();

class User{
        public:
        User() {}   //Default Costructor
        User(int a,string u,string g,string p)      //Parameterized Constructor
                {
            age=a;
            username=u;
            gender=g;
            password=p;
        }
                //Function prototypes
        string getPass();
        string getUser();

                //Declaring variables
        private:
        int age;
        string username;
        string gender;
        string password;
};
