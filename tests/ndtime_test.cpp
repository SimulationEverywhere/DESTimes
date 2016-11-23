/**
 * Copyright (C) 2016  Laouen Mayal Louan Belloli
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "../NDTime.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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
    NDTime c("-inf");
    NDTime d("-infinity");
    NDTime e("infinity");

    BOOST_CHECK_EQUAL(a,b);
    BOOST_CHECK_EQUAL(a,e);
    BOOST_CHECK_EQUAL(b,e);
    BOOST_CHECK_EQUAL(c,d);
  }

  BOOST_AUTO_TEST_CASE( constructors_test ) {
    
    std::vector<NDTime> times;

    NDTime a(10);
    NDTime b(9,60);
    NDTime c(9,59,60);
    NDTime d(9,59,59,1000);
    NDTime e(9,59,59,999,1000);
    NDTime f(9,59,59,999,999,1000);
    NDTime g(9,59,59,999,999,999,1000);
    NDTime h(9,59,59,999,999,999,999,1000);
    NDTime i(11,-59,-59,-999,-999,-999,-999,-1000);
    NDTime j(11,-59,-59,-999,-999,-999,-1000);
    NDTime k(11,-59,-59,-999,-999,-1000);
    NDTime l(11,-59,-59,-999,-1000);
    NDTime m(11,-59,-59,-1000);
    NDTime n(11,-59,-60);
    NDTime o(11,-60);

    times.push_back(a);
    times.push_back(b);
    times.push_back(c);
    times.push_back(d);
    times.push_back(e);
    times.push_back(f);
    times.push_back(g);
    times.push_back(h);
    times.push_back(i);
    times.push_back(j);
    times.push_back(k);
    times.push_back(l);
    times.push_back(m);
    times.push_back(n);
    times.push_back(o);

    for (int i = 0; i < times.size(); ++i) {
      for(int j = i+1; j < times.size(); ++j) {
        BOOST_CHECK_EQUAL(times[i],times[j]);
      }
    }
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
  
  BOOST_AUTO_TEST_CASE( less ) {

    NDTime minusInf("-inf");
    NDTime inf("inf");
    NDTime a(10);
    NDTime b(0);
    NDTime c(-10,55);
    NDTime d(-10);
    NDTime e(-10,-55);

    BOOST_CHECK(minusInf < inf);
    BOOST_CHECK(minusInf < a);
    BOOST_CHECK(minusInf < b);
    BOOST_CHECK(minusInf < c);
    BOOST_CHECK(minusInf < d);
    BOOST_CHECK(minusInf < e);
    
    BOOST_CHECK(b < a);
    BOOST_CHECK(c < a);
    BOOST_CHECK(d < a);
    BOOST_CHECK(e < a);
    BOOST_CHECK(c < b);
    BOOST_CHECK(d < b);
    BOOST_CHECK(e < b);
    BOOST_CHECK(d < c);
    BOOST_CHECK(e < c);
    BOOST_CHECK(e < d);

    BOOST_CHECK(a < inf);
    BOOST_CHECK(b < inf);
    BOOST_CHECK(c < inf);
    BOOST_CHECK(d < inf);
    BOOST_CHECK(e < inf);

    BOOST_CHECK(!(minusInf < minusInf));
    BOOST_CHECK(!(inf < inf));
    BOOST_CHECK(!(a < a));
    BOOST_CHECK(!(b < b));
    BOOST_CHECK(!(c < c));
    BOOST_CHECK(!(d < d));
    BOOST_CHECK(!(e < e));
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( deepView )
  
  BOOST_AUTO_TEST_CASE( deep_view_off ) {
    
    NDTime a(10,5,10,105,10,105,10,10);
    NDTime b(10,5,10,105,10,105,10);
    NDTime c(10,5,10,105,10,105);
    NDTime d(10,5,10,105,10);
    NDTime e(10,5,10,105);
    NDTime f(10,5,10);
    NDTime g(10,5);
    NDTime h(10);
    std::string expected1 = "10:05:10:105";
    std::string expected2 = "10:05:10:000";
    std::string expected3 = "10:05:00:000";
    std::string expected4 = "10:00:00:000";
    
    std::stringstream out;
    out << a; BOOST_CHECK_EQUAL(out.str(),expected1); out.str(""); out.clear();
    out << b; BOOST_CHECK_EQUAL(out.str(),expected1); out.str(""); out.clear();
    out << c; BOOST_CHECK_EQUAL(out.str(),expected1); out.str(""); out.clear();
    out << d; BOOST_CHECK_EQUAL(out.str(),expected1); out.str(""); out.clear();
    out << e; BOOST_CHECK_EQUAL(out.str(),expected1); out.str(""); out.clear();
    out << f; BOOST_CHECK_EQUAL(out.str(),expected2); out.str(""); out.clear();
    out << g; BOOST_CHECK_EQUAL(out.str(),expected3); out.str(""); out.clear();
    out << h; BOOST_CHECK_EQUAL(out.str(),expected4); out.str(""); out.clear();
  }
  
  BOOST_AUTO_TEST_CASE( deep_view_on ) {

    NDTime a(10,5,10,105,10,105,10,10);
    NDTime b(10,5,10,105,10,105,10);
    NDTime c(10,5,10,105,10,105);
    NDTime d(10,5,10,105,10);
    NDTime e(10,5,10,105);
    NDTime f(10,5,10);
    NDTime g(10,5);
    NDTime h(10);
    std::string expected_a = "10:05:10:105:010:105:010:010";
    std::string expected_b = "10:05:10:105:010:105:010:000";
    std::string expected_c = "10:05:10:105:010:105:000:000";
    std::string expected_d = "10:05:10:105:010:000:000:000";
    std::string expected_e = "10:05:10:105:000:000:000:000";
    std::string expected_f = "10:05:10:000:000:000:000:000";
    std::string expected_g = "10:05:00:000:000:000:000:000";
    std::string expected_h = "10:00:00:000:000:000:000:000";

    NDTime::startDeepView();
    
    std::stringstream out;
    out << a; BOOST_CHECK_EQUAL(out.str(),expected_a); out.str(""); out.clear();
    out << b; BOOST_CHECK_EQUAL(out.str(),expected_b); out.str(""); out.clear();
    out << c; BOOST_CHECK_EQUAL(out.str(),expected_c); out.str(""); out.clear();
    out << d; BOOST_CHECK_EQUAL(out.str(),expected_d); out.str(""); out.clear();
    out << e; BOOST_CHECK_EQUAL(out.str(),expected_e); out.str(""); out.clear();
    out << f; BOOST_CHECK_EQUAL(out.str(),expected_f); out.str(""); out.clear();
    out << g; BOOST_CHECK_EQUAL(out.str(),expected_g); out.str(""); out.clear();
    out << h; BOOST_CHECK_EQUAL(out.str(),expected_h); out.str(""); out.clear();
  }


  BOOST_AUTO_TEST_CASE( deep_view_toggle ) {
    NDTime a(10,5,10,105,10,105,10,10);
    NDTime b(10,5,10,105,10,105,10);
    NDTime c(10,5,10,105,10,105);
    NDTime d(10,5,10,105,10);
    NDTime e(10,5,10,105);
    NDTime f(10,5,10);
    NDTime g(10,5);
    NDTime h(10);

    std::string dv_expected_a = "10:05:10:105:010:105:010:010";
    std::string dv_expected_b = "10:05:10:105:010:105:010:000";
    std::string dv_expected_c = "10:05:10:105:010:105:000:000";
    std::string dv_expected_d = "10:05:10:105:010:000:000:000";
    std::string dv_expected_e = "10:05:10:105:000:000:000:000";
    std::string dv_expected_f = "10:05:10:000:000:000:000:000";
    std::string dv_expected_g = "10:05:00:000:000:000:000:000";
    std::string dv_expected_h = "10:00:00:000:000:000:000:000";
    std::string sv_expected_a = "10:05:10:105";
    std::string sv_expected_b = "10:05:10:105";
    std::string sv_expected_c = "10:05:10:105";
    std::string sv_expected_d = "10:05:10:105";
    std::string sv_expected_e = "10:05:10:105";
    std::string sv_expected_f = "10:05:10:000";
    std::string sv_expected_g = "10:05:00:000";
    std::string sv_expected_h = "10:00:00:000";

    std::stringstream out;
    NDTime::startDeepView();
    out << a; BOOST_CHECK_EQUAL(out.str(),dv_expected_a); out.str(""); out.clear();
    NDTime::stopDeepView();
    out << a; BOOST_CHECK_EQUAL(out.str(),sv_expected_a); out.str(""); out.clear();

    NDTime::startDeepView();
    out << b; BOOST_CHECK_EQUAL(out.str(),dv_expected_b); out.str(""); out.clear();
    NDTime::stopDeepView();
    out << b; BOOST_CHECK_EQUAL(out.str(),sv_expected_b); out.str(""); out.clear();

    NDTime::startDeepView();
    out << c; BOOST_CHECK_EQUAL(out.str(),dv_expected_c); out.str(""); out.clear();
    NDTime::stopDeepView();
    out << c; BOOST_CHECK_EQUAL(out.str(),sv_expected_c); out.str(""); out.clear();

    NDTime::startDeepView();
    out << d; BOOST_CHECK_EQUAL(out.str(),dv_expected_d); out.str(""); out.clear();
    NDTime::stopDeepView();
    out << d; BOOST_CHECK_EQUAL(out.str(),sv_expected_d); out.str(""); out.clear();

    NDTime::startDeepView();
    out << e; BOOST_CHECK_EQUAL(out.str(),dv_expected_e); out.str(""); out.clear();
    NDTime::stopDeepView();
    out << e; BOOST_CHECK_EQUAL(out.str(),sv_expected_e); out.str(""); out.clear();

    NDTime::startDeepView();
    out << f; BOOST_CHECK_EQUAL(out.str(),dv_expected_f); out.str(""); out.clear();
    NDTime::stopDeepView();
    out << f; BOOST_CHECK_EQUAL(out.str(),sv_expected_f); out.str(""); out.clear();

    NDTime::startDeepView();
    out << g; BOOST_CHECK_EQUAL(out.str(),dv_expected_g); out.str(""); out.clear();
    NDTime::stopDeepView();
    out << g; BOOST_CHECK_EQUAL(out.str(),sv_expected_g); out.str(""); out.clear();

    NDTime::startDeepView();
    out << h; BOOST_CHECK_EQUAL(out.str(),dv_expected_h); out.str(""); out.clear();
    NDTime::stopDeepView();
    out << h; BOOST_CHECK_EQUAL(out.str(),sv_expected_h); out.str(""); out.clear();
  }

BOOST_AUTO_TEST_SUITE_END()
