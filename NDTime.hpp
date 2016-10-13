#ifndef NDTIME_H
#define NDTIME_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <boost/algorithm/string.hpp>

class NDTime {
private:
  bool _inf;
  bool _possitive;
  int _hours; // 3600 seconds
  int _minutes; // 60 seconds
  int _seconds; // 10^0 seconds
  int _milliseconds; 	 // 10^3 seconds
  int _microseconds; // 10^6 seconds
  int _nanoseconds; // 10^9 seconds
  int _picoseconds; // 10^12 seconds
  int _femtoseconds; // 10^15 seconds

  void add_hours(int a) {
    this->_hours += a;
  }

  void add_minutes(int a) {
    this->_minutes += a;

    while (this->_minutes >= 60) {
      this->add_hours(1);
      this->_minutes -= 60;
    }

    while (this->_minutes <= -60) {
      this->add_hours(-1);
      this->_minutes += 60;
    }
  }

  void add_seconds(int a) {
    this->_seconds += a;

    while (this->_seconds >= 60) {
      this->add_minutes(1);
      this->_seconds -= 60;
    }

    while (this->_seconds <= -60) {
      this->add_minutes(-1);
      this->_seconds += 60;
    }
  }

  void add_milliseconds(int a) {
    this->_milliseconds += a;

    while (this->_milliseconds >= 1000) {
      this->add_seconds(1);
      this->_milliseconds -= 1000;
    }

    while (this->_milliseconds <= -1000) {
      this->add_seconds(-1);
      this->_milliseconds += 1000;
    }
  }

  void add_microseconds(int a) {
    this->_microseconds += a;

    while (this->_microseconds >= 1000) {
      this->add_milliseconds(1);
      this->_microseconds -= 1000;
    }

    while (this->_microseconds <= -1000) {
      this->add_milliseconds(-1);
      this->_microseconds += 1000;
    }
  }

  void add_nanoseconds(int a) {
    this->_nanoseconds += a;

    while (this->_nanoseconds >= 1000) {
      this->add_microseconds(1);
      this->_nanoseconds -= 1000;
    }

    while (this->_nanoseconds <= -1000) {
      this->add_microseconds(-1);
      this->_nanoseconds += 1000;
    }
  }

  void add_picoseconds(int a) {
    this->_picoseconds += a;

    while (this->_picoseconds >= 1000) {
      this->add_nanoseconds(1);
      this->_picoseconds -= 1000;
    }

    while (this->_picoseconds <= -1000) {
      this->add_nanoseconds(-1);
      this->_picoseconds += 1000;
    }
  }

  void add_femtoseconds(int a) {
    this->_femtoseconds += a;

    while (this->_femtoseconds >= 1000) {
      this->add_picoseconds(1);
      this->_femtoseconds -= 1000;
    }

    while (this->_femtoseconds <= -1000) {
      this->add_picoseconds(-1);
      this->_femtoseconds += 1000;
    }
  }

public:

  static bool _deep_precision;

  /******************************************/
  /************** CONSTRUCTORS **************/
  /******************************************/
  NDTime() { // default constructor
    this->_inf = false;
    this->_possitive = false;

    this->resetToZero();
  };

  NDTime(const NDTime& o) { // copy constructor
    _inf = o._inf;
    _possitive = o._possitive;
    _hours = o._hours;
    _minutes = o._minutes;
    _seconds = o._seconds;
    _milliseconds = o._milliseconds;
    _microseconds = o._microseconds;
    _nanoseconds = o._nanoseconds;
    _picoseconds = o._picoseconds;
    _femtoseconds = o._femtoseconds;
  };

  NDTime(int o_h, int o_m, int o_s, int o_ms) { // basic contructor
    this->_inf = false;
    this->_possitive = false;
    
    this->resetToZero();
    
    this->add_hours(o_h);
    this->add_minutes(o_m);
    this->add_seconds(o_s);
    this->add_milliseconds(o_ms);
  };

  NDTime(int o_h, int o_m, int o_s, int o_ms, int o_mcs, int o_ns, int o_ps, int o_fs) { // advanced constructor
    this->_inf = false;
    this->_possitive = false;

    this->resetToZero();
    
    this->add_hours(o_h);
    this->add_minutes(o_m);
    this->add_seconds(o_s);
    this->add_milliseconds(o_ms);
    this->add_microseconds(o_mcs);
    this->add_nanoseconds(o_ns);
    this->add_picoseconds(o_ps);
    this->add_femtoseconds(o_fs);
  };

  // valid options are "inf" and hh:mm:ss:mmss:nnss:...:ffss it is not necesary to specify all the units.
  NDTime(const std::string a) { 
    int v, i;
    std::vector<std::string> strs;
    
    this->_inf = false;
    this->_possitive = false;

    this->resetToZero();
    
    if (a == "inf") {
      this->_inf = true;
      this->_possitive = true;
    } else if (a == "-inf") {
      this->_inf = true;
      this->_possitive = false;
    } else {
      boost::split(strs,a,boost::is_any_of(":"));
      for(i=0; i<strs.size(); ++i) {
        v = std::stoi(strs[i]);
        switch(i) {
          case 0: this->add_hours(v) ; break;
          case 1: this->add_minutes(v) ; break;
          case 2: this->add_seconds(v) ; break;
          case 3: this->add_milliseconds(v) ; break;
          case 4: this->add_microseconds(v) ; break;
          case 5: this->add_nanoseconds(v) ; break;
          case 6: this->add_picoseconds(v) ; break;
          case 8: this->add_femtoseconds(v) ; break;
        }
      }
    }
  };

  static void startDeepView() {
    NDTime::_deep_precision = true;
  }

  static void stopDeepView() {
    NDTime::_deep_precision = false;
  }

  static NDTime infinity() noexcept {
    return NDTime("inf");
  }

  static NDTime minus_infinity() noexcept {
    return NDTime("-inf");
  }

  void resetToZero() {
    this->_inf = false;
    this->_possitive = false;
    this->_hours = 0;
    this->_minutes = 0;
    this->_seconds = 0;
    this->_milliseconds = 0;
    this->_microseconds = 0;
    this->_nanoseconds = 0;
    this->_picoseconds = 0;
    this->_femtoseconds = 0;
  }

  NDTime& operator+=(const NDTime& o) noexcept {
    if (this->_inf && o._inf) {
      if (this->_possitive != o._possitive) {
        this->resetToZero();
        this->_inf = false;
      }
    
    } else if (o._inf) {
      this->_inf = true;
      this->_possitive = o._possitive;
    
    } else {
      this->add_hours(o._hours);
      this->add_minutes(o._minutes);
      this->add_seconds(o._seconds);
      this->add_milliseconds(o._milliseconds);
      this->add_microseconds(o._microseconds);
      this->add_nanoseconds(o._nanoseconds);
      this->add_picoseconds(o._picoseconds);
      this->add_femtoseconds(o._femtoseconds);      
    }

    return *this;
  }

  NDTime& operator-=(const NDTime& o) noexcept {
    if (this->_inf && o._inf) {
      if (this->_possitive == o._possitive) {
        this->resetToZero();
        this->_inf = false;
      }
    
    } else if (o._inf) {
      this->_inf = true;
      this->_possitive = !o._possitive;
    
    } else {
      this->add_hours(-o._hours);
      this->add_minutes(-o._minutes);
      this->add_seconds(-o._seconds);
      this->add_milliseconds(-o._milliseconds);
      this->add_microseconds(-o._microseconds);
      this->add_nanoseconds(-o._nanoseconds);
      this->add_picoseconds(-o._picoseconds);
      this->add_femtoseconds(-o._femtoseconds);
    }

    return *this;
  }

  friend NDTime operator+(const NDTime& lhs, const NDTime& rhs);
  friend NDTime operator-(const NDTime& lhs, const NDTime& rhs);
  friend bool operator==(const NDTime& lhs, const NDTime& rhs);
  friend bool operator!=(const NDTime& lhs, const NDTime& rhs);
  friend bool operator<(const NDTime& lhs, const NDTime& rhs);
  friend bool operator>(const NDTime& lhs, const NDTime& rhs);
  friend bool operator<=(const NDTime& lhs, const NDTime& rhs);
  friend bool operator>=(const NDTime& lhs, const NDTime& rhs);
  friend std::ostream& operator<<(std::ostream& os, NDTime t);
  friend std::istream& operator>>(std::istream& is, NDTime t);
};

bool NDTime::_deep_precision = false;

NDTime operator+(const NDTime& lhs, const NDTime& rhs) {
  NDTime res = lhs;
  res += rhs;
  return res;
}

NDTime operator-(const NDTime& lhs, const NDTime& rhs) {
  NDTime res = lhs;
  res -= rhs;
  return res;
}

bool operator==(const NDTime& lhs, const NDTime& rhs) {
  if (lhs._inf && rhs._inf) return true;
  else if (lhs._inf || rhs._inf) return false;
  else {
    bool res = true;
    res = res && (lhs._hours == rhs._hours);
    res = res && (lhs._minutes == rhs._minutes);
    res = res && (lhs._seconds == rhs._seconds);
    res = res && (lhs._milliseconds == rhs._milliseconds);
    res = res && (lhs._microseconds == rhs._microseconds);
    res = res && (lhs._nanoseconds == rhs._nanoseconds);
    res = res && (lhs._femtoseconds == rhs._femtoseconds);
    return res;
  }
}

bool operator!=(const NDTime& lhs, const NDTime& rhs) {
  return !(lhs == rhs);
}

bool operator<(const NDTime& lhs, const NDTime& rhs) {
  if (lhs._inf && rhs._inf) return false;
  else if (rhs._inf) return true;
  else if (lhs._hours != rhs._hours) return lhs._hours < rhs._hours;
  else if (lhs._minutes != rhs._minutes) return lhs._minutes < rhs._minutes;
  else if (lhs._seconds != rhs._seconds) return lhs._seconds < rhs._seconds;
  else if (lhs._milliseconds != rhs._milliseconds) return lhs._milliseconds < rhs._milliseconds;
  else if (lhs._microseconds != rhs._microseconds) return lhs._microseconds < rhs._microseconds;
  else if (lhs._nanoseconds != rhs._nanoseconds) return lhs._nanoseconds < rhs._nanoseconds;
  else if (lhs._femtoseconds != rhs._femtoseconds) return lhs._femtoseconds < rhs._femtoseconds;
}

bool operator>(const NDTime& lhs, const NDTime& rhs) {
  if (lhs._inf && rhs._inf) return false;
  else if (lhs._inf) return true;
  else if (lhs._hours != rhs._hours) return lhs._hours > rhs._hours;
  else if (lhs._minutes != rhs._minutes) return lhs._minutes > rhs._minutes;
  else if (lhs._seconds != rhs._seconds) return lhs._seconds > rhs._seconds;
  else if (lhs._milliseconds != rhs._milliseconds) return lhs._milliseconds > rhs._milliseconds;
  else if (lhs._microseconds != rhs._microseconds) return lhs._microseconds > rhs._microseconds;
  else if (lhs._nanoseconds != rhs._nanoseconds) return lhs._nanoseconds > rhs._nanoseconds;
  else if (lhs._femtoseconds != rhs._femtoseconds) return lhs._femtoseconds > rhs._femtoseconds;
}

bool operator<=(const NDTime& lhs, const NDTime& rhs) {
  return !(lhs > rhs);
}

bool operator>=(const NDTime& lhs, const NDTime& rhs) {
  return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, NDTime t) {

  if (t._inf) {
    if (t._possitive) {
      os << "inf";
    } else {
      os << "-inf";
    }
  } else {
    os << t._hours << ":";
    os << t._minutes << ":";
    os << t._seconds << ":";
    os << t._milliseconds;
    if (t._deep_precision) {
      os << ":";
      os << t._microseconds << ":";
      os << t._nanoseconds << ":";
      os << t._femtoseconds;
    }
  }
  return os;
}

std::istream& operator>>(std::istream& is, NDTime t) {
  std::string a;
  is >> a;
  t = NDTime(a);
  return is;
}

// specialize numeric_limits
namespace std {
  template<>
  class numeric_limits<NDTime>{
  public:
    static constexpr bool is_specialized = true;
    static NDTime min() noexcept { return NDTime(numeric_limits<int>::min(),-59,-59,-999,-999,-999,-999,-999); }
    static NDTime max() noexcept { return NDTime(numeric_limits<int>::max(),59,59,999,999,999,999,999); }
    static NDTime lowest() noexcept { return NDTime(numeric_limits<int>::min(),-59,-59,-999,-999,-999,-999,-999); }

    static constexpr int  digits = numeric_limits<int>::digits;
    static constexpr int  digits10 = numeric_limits<int>::digits10;
    static constexpr bool is_signed = true;
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = true;
    static constexpr int radix = 2; // trash_value

    static constexpr int  min_exponent = numeric_limits<int>::min(); // trash_value
    static constexpr int  min_exponent10 = min_exponent/radix; // trash_value
    static constexpr int  max_exponent = numeric_limits<int>::max(); // trash_value
    static constexpr int  max_exponent10 = max_exponent/radix; // trash_value

    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_indeterminate;
    static constexpr bool has_denorm_loss = false;
    static NDTime infinity() noexcept { return NDTime::infinity(); }

    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = false;
    static constexpr bool is_modulo = false;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
  };
}

#endif