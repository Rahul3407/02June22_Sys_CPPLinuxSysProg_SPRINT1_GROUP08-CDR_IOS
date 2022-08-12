#pragma once
#include <myHeader.h>
#define PORT 4056

int process_cdr();

class User{
	public:
    	User() {}
        User(int a,string u,string g,string p){
        	age=a;
            username=u;
            gender=g;
            password=p;
        }
        string getPass();
        string getUser();
	private:
    	int age;
        string username;
        string gender;
        string password;
};
