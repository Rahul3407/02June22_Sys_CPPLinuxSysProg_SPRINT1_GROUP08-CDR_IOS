#include <myHeader.h>

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

	    string getName();
        void setInc(long);
        void setOuc(long);
        void setDown(long);
        void setUp(long);
        void setIn(long);
        void setOut(long );
        long getInc();
        long getOuc();
        long getDown();
        long getUp();
        long getIn();
        long getOut();
        long getId();

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
