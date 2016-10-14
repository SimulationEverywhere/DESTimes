#include "../NDTime.hpp"
#include <iostream>
#include <string>

#define BOOST_TEST_MODULE britime
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE( ndtime_constructors )

  
  BOOST_AUTO_TEST_CASE( positive_time_constructions ) {
    
    NDTime a("10:51:0:0");
    NDTime b(10,50,60,0);
    NDTime c(0,50,60,36000000);
    NDTime d("0:50:60:36000000");
    NDTime e(5,52,-60,5*60*60*1000-500,500*1000,0,0,0);
    NDTime f(10,50,0,30*1000,30*1000*1000,0,0,0);
    NDTime g(10,52,-60,0);

    BOOST_CHECK_EQUAL(a,b);
    BOOST_CHECK_EQUAL(a,c);
    BOOST_CHECK_EQUAL(a,d);
    BOOST_CHECK_EQUAL(a,e);
    BOOST_CHECK_EQUAL(a,f);
    BOOST_CHECK_EQUAL(a,g);
    BOOST_CHECK_EQUAL(b,c);
    BOOST_CHECK_EQUAL(b,d);
    BOOST_CHECK_EQUAL(b,e);
    BOOST_CHECK_EQUAL(b,f);
    BOOST_CHECK_EQUAL(b,g);
    BOOST_CHECK_EQUAL(c,d); 
    BOOST_CHECK_EQUAL(c,e); 
    BOOST_CHECK_EQUAL(c,f); 
    BOOST_CHECK_EQUAL(c,g); 
    BOOST_CHECK_EQUAL(d,e); 
    BOOST_CHECK_EQUAL(d,f); 
    BOOST_CHECK_EQUAL(d,g); 
    BOOST_CHECK_EQUAL(e,f); 
    BOOST_CHECK_EQUAL(e,g); 
    BOOST_CHECK_EQUAL(f,g); 
  }

  BOOST_AUTO_TEST_CASE( negative_time_constructions ) {
    NDTime a("-10:-51:0:0");
    NDTime b(-10,-50,-60,0);
    NDTime c(0,-50,-60,-36000000);
    NDTime d("0:-50:-60:-36000000");
    NDTime e(-5,-50,-60,-5*60*60*1000-500,500*1000,0,0,0);
    NDTime f(-10,-51,60,-30*1000,-30*1000*1000,0,0,0);
    NDTime g(-10,-52,60,0);
  
    BOOST_CHECK_EQUAL(a,b);
    BOOST_CHECK_EQUAL(a,c);
    BOOST_CHECK_EQUAL(a,d);
    BOOST_CHECK_EQUAL(a,e);
    BOOST_CHECK_EQUAL(a,f);
    BOOST_CHECK_EQUAL(a,g);
    BOOST_CHECK_EQUAL(b,c);
    BOOST_CHECK_EQUAL(b,d);
    BOOST_CHECK_EQUAL(b,e);
    BOOST_CHECK_EQUAL(b,f);
    BOOST_CHECK_EQUAL(b,g);
    BOOST_CHECK_EQUAL(c,d); 
    BOOST_CHECK_EQUAL(c,e); 
    BOOST_CHECK_EQUAL(c,f); 
    BOOST_CHECK_EQUAL(c,g); 
    BOOST_CHECK_EQUAL(d,e); 
    BOOST_CHECK_EQUAL(d,f); 
    BOOST_CHECK_EQUAL(d,g); 
    BOOST_CHECK_EQUAL(e,f); 
    BOOST_CHECK_EQUAL(e,g); 
    BOOST_CHECK_EQUAL(f,g);
  }

  BOOST_AUTO_TEST_CASE( infinity_time_constructions ) {
    NDTime a("inf");
    NDTime b = std::numeric_limits<NDTime>::infinity();

    BOOST_CHECK_EQUAL(a,b);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( ndtime_aritmetic_operations )

  BOOST_AUTO_TEST_CASE( aditions ) {
    NDTime a(0,0,3,100);
    NDTime b(0,50,3,0);
    NDTime c(0,50,6,100);

    NDTime d(0,-50,6,-100);
    NDTime e(0,-50,9,0);

    NDTime f(10,0,0,0);
    NDTime g(-10,0,0,0);


    NDTime h("inf");
    NDTime i("-inf");
  
    // Testing to add a very small time to a very large time
    NDTime j(0,0,0,0,0,0,0,1);
    NDTime k(10,0,0,0,0,0,0,1);

    BOOST_CHECK_EQUAL(a+b,c);
    BOOST_CHECK_EQUAL(a+(b+c),(a+b)+c);
    BOOST_CHECK_EQUAL(a+b+c,a+c+b);
    BOOST_CHECK_EQUAL(a+d,e);
    BOOST_CHECK_EQUAL(a,c-b);
    BOOST_CHECK_EQUAL(f+g,NDTime());
    BOOST_CHECK_EQUAL(a+NDTime(),a);
    BOOST_CHECK_EQUAL(a+h,NDTime("inf"));
    BOOST_CHECK_EQUAL(a+i,NDTime("-inf"));
    BOOST_CHECK_EQUAL(i+i,NDTime("-inf"));
    BOOST_CHECK_EQUAL(h+h,NDTime("inf"));
    BOOST_CHECK_EQUAL(h+i,NDTime());
    BOOST_CHECK_EQUAL(i+h,NDTime());
    BOOST_CHECK_EQUAL(f+j,k);
  }

  BOOST_AUTO_TEST_CASE ( substractions ) {
    NDTime a(0,0,3,100);
    NDTime b(0,50,3,0);
    NDTime c(0,-50,0,100);

    NDTime d(0,-50,6,-910);
    NDTime e(0,50,-2,10);

    NDTime f(10,0,0,0);
    NDTime g(10,0,0,0);

    NDTime h("inf");
    NDTime i("-inf");
  
    // Testing to add a very small time to a very large time
    NDTime j(0,0,0,0,0,0,0,1);
    NDTime k(10,0,0,0,0,0,0,-1);

    BOOST_CHECK_EQUAL(a-b,c);
    BOOST_CHECK_EQUAL(a-(b+c),b-(a-c));
    BOOST_CHECK_EQUAL(a-(b+c),NDTime());
    BOOST_CHECK_EQUAL(b-(a-c),NDTime());
    BOOST_CHECK_EQUAL((a-b)-c,a-b-c);
    BOOST_CHECK_EQUAL((a-b)-c,a-(b+c));
    BOOST_CHECK_EQUAL(a-(b-c),a-b+c);
    BOOST_CHECK_EQUAL(a-b-c,a-c-b);
    BOOST_CHECK_EQUAL(a-d,e);
    BOOST_CHECK_EQUAL(a,c+b);
    BOOST_CHECK_EQUAL(f-g,NDTime());
    BOOST_CHECK_EQUAL(f-f,NDTime());
    BOOST_CHECK_EQUAL(a-NDTime(),a);
    BOOST_CHECK_EQUAL(a-h,NDTime("-inf"));
    BOOST_CHECK_EQUAL(a-i,NDTime("inf"));
    BOOST_CHECK_EQUAL(i-i,NDTime());
    BOOST_CHECK_EQUAL(h-h,NDTime());
    BOOST_CHECK_EQUAL(h-i,NDTime("inf"));
    BOOST_CHECK_EQUAL(i-h,NDTime("-inf"));
    BOOST_CHECK_EQUAL(f-j,k);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( comparators )
  
  BOOST_AUTO_TEST_CASE( all ) {
    
  }

BOOST_AUTO_TEST_SUITE_END()
