#include <iostream>
#include <string>
#include <ctype.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;


class Operator : public CPPUNIT_NS::TestFixture
{
 CPPUNIT_TEST_SUITE( Operator );
 CPPUNIT_TEST( getusername_UT );
 CPPUNIT_TEST(getpassword_UT);
 CPPUNIT_TEST(getbrandname_UT);
 CPPUNIT_TEST(getGPRS_UT);
 CPPUNIT_TEST(getmnc_UT);
 CPPUNIT_TEST(setusername_UT);
 CPPUNIT_TEST(setbrandname_UT);
CPPUNIT_TEST(setpassword_UT);
 CPPUNIT_TEST(validusername_UT);
CPPUNIT_TEST(validpassword_UT);
CPPUNIT_TEST(validbrandname_UT);
 CPPUNIT_TEST(testoperatorclass);
 CPPUNIT_TEST_SUITE_END();
protected:
std::string username;
std::string password;
std::string brandname;
int regis;
int GPRS;
int mnc;

public:
Operator() { 
username  = "hirijashree";
brandname="Airtel";
password="cap";
GPRS=5;
regis=23;
mnc=40500;
																					}

void setUp();
bool setusername(std::string n) { 
																					if(n != ""){	
																					username= n;
return true;
																					}
														
																					else{
																					return false;
																					}
																					}						

bool setpassword(std::string n) {

	if(n != ""){

		password= n;
		return true;
		                                                                                                                                                                        }

	                                                                                                                                                                        else{

																							return false;

																						}

}


bool setbrandname(std::string n) { 

if(n != ""){
brandname= n;
return true;
	}
else{
return false;
		}
		}






void setregister(int i) { regis = i; }
int getregister() { return regis; }
std::string getusername() { return username; }
bool validusername(string n)
																										{
																					for(int i=0;i<n.size();i++)
																					if(isdigit(n.at(i)))
																																											{
																																										return false;
																																												}
																					return true;
																																						}
			

std::string getpassword() { return password; }
bool validpassword(string n)
	                                                                                                                                                                                                                {

																					for(int i=0;i<n.size();i++)
																					if(isdigit(n.at(i)))


																											     {
																					                                                                                                                                                                                                                                                                                                                                                return false;
																																																																										                                                                                                                                                                                                                                                                                                                                                                }
																					                                                                                                                                                                        return true;

																																																	                                                                                                                                        }

void setmnc(int i) { mnc = i; }
int getmnc() { return mnc; }
void setGPRS(int i) { GPRS = i; }
int getGPRS() { return GPRS; }
std::string getbrandname() { return brandname; }
bool validbrandname(string n)
{
for(int i=0;i<n.size();i++)
if(isdigit(n.at(i)))
																					{																					return false;
																					}
return true;
}









void display()
																							{																			cout<<"USERNAME "<<username<<endl;
																					cout<<"PASSWORD IS"<<password<<endl;
																					cout<<"REGISTER NUMBER"<<regis<<endl;
					
cout<<"GPRS VALUE"<<GPRS<<endl;
cout<<"BRANDNAME"<<brandname<<endl;
cout<<"MNC"<<mnc<<endl;
																															}																					protected:																													
																					void getusername_UT();
																					void getpassword_UT();
																					void getregister_UT();																			void validusername_UT();
void validpassword_UT();
																					void getbrandname_UT();
void setusername_UT();
void setpassword_UT();
void setbrandname_UT();
void getGPRS_UT();
void getmnc_UT();
void validbrandname_UT();
void testoperatorclass();
};
