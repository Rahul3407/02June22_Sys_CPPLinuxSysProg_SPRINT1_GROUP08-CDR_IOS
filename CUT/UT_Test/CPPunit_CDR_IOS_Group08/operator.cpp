#include <cppunit/config/SourcePrefix.h>
#include <string>
#include<algorithm>

#include "operator.h"

CPPUNIT_TEST_SUITE_REGISTRATION( Operator );

void Operator::setUp()
{
		username = "hirijashree";
		regis = 23;
		brandname="Airtel";
		GPRS=5;
		mnc=40500;
		password="hi";
}

void Operator::getusername_UT() {
			std::string Name1 = "Hirija";
			std::string Name2 = getusername();
							
			CPPUNIT_ASSERT_EQUAL(Name1, Name2);
							 }
void Operator::getpassword_UT() {
	                  std::string Name1 = "Hirija";
		          std::string Name2 = getusername();
			  CPPUNIT_ASSERT_EQUAL(Name1, Name2);
										                                                         }


void Operator::getbrandname_UT() {
	                   std::string Name1 = "jio";
			   std::string Name2 = getbrandname();


			   CPPUNIT_ASSERT_EQUAL(Name1, Name2);
												                                                         }

void Operator::getregister_UT(){
			CPPUNIT_ASSERT_EQUAL(1001, getregister());
}
void Operator::getGPRS_UT(){
	                        CPPUNIT_ASSERT_EQUAL(5, getGPRS());
}
void Operator::getmnc_UT(){
	                        CPPUNIT_ASSERT_EQUAL(40500, getmnc());
}

void Operator::validusername_UT(){
			string Name1 = "Hirija";
			CPPUNIT_ASSERT_EQUAL(true, validusername(Name1));
}

void Operator::validpassword_UT(){
	                   string passwd = "hi";
		           CPPUNIT_ASSERT_EQUAL(true, validusername(passwd));
}

void Operator::validbrandname_UT(){
	                        string brand = "jio";
				 CPPUNIT_ASSERT_EQUAL(true, validbrandname(brand));
}

void Operator::setusername_UT(){
			string Name1 = "hirijashree";
					
					CPPUNIT_ASSERT_EQUAL(true, setusername(Name1));
}
void  Operator::setbrandname_UT(){
	string brand = "jio";

         CPPUNIT_ASSERT_EQUAL(true, setbrandname(brand));
}	
void Operator::setpassword_UT(){

string passwd= "Airtel";
CPPUNIT_ASSERT_EQUAL(true, setpassword(passwd));
}

void Operator::testoperatorclass()
{
		        Operator o;
			string brand ="jio";
			string Name1 = "Hirija";
			string passwd= "hi";

			//o.setUp();
			CPPUNIT_ASSERT_EQUAL(Name1, o.getusername());
			CPPUNIT_ASSERT_EQUAL(brand,o.getbrandname());
			CPPUNIT_ASSERT_EQUAL(passwd,o.getpassword());
					}
