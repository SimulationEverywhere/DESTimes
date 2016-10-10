#include "../NDTime.hpp"
#include <iostream>
#include <string>

#define BOOST_TEST_MODULE britime
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( britime_constructors_tests )

  BOOST_AUTO_TEST_CASE( positive_time_constructions ) {
    NDTime a("10:51:0:0");
    NDTime b(10,50,60,0);
    NDTime c(0,50,60,36000000);
    NDTime d("0:50:60:36000000");
    NDTime e(5,50,60,5*60*60*1000-500,500*1000,0,0,0);
    NDTime f(10,50,0,30*1000,30*1000*1000,0,0,0);

    BOOST_CHECK_EQUAL(a,b);
    BOOST_CHECK_EQUAL(a,c);
    BOOST_CHECK_EQUAL(a,d);
    BOOST_CHECK_EQUAL(a,e);
    BOOST_CHECK_EQUAL(a,f);
    BOOST_CHECK_EQUAL(b,c);
    BOOST_CHECK_EQUAL(b,d);
    BOOST_CHECK_EQUAL(b,e);
    BOOST_CHECK_EQUAL(b,f);
    BOOST_CHECK_EQUAL(c,d); 
    BOOST_CHECK_EQUAL(c,e); 
    BOOST_CHECK_EQUAL(c,f); 
    BOOST_CHECK_EQUAL(d,e); 
    BOOST_CHECK_EQUAL(d,f); 
    BOOST_CHECK_EQUAL(e,f);	
  }

  BOOST_AUTO_TEST_CASE( negative_time_constructions ) {

  }

  BOOST_AUTO_TEST_CASE( infinity_time_constructions ) {

  }

BOOST_AUTO_TEST_SUITE_END()