#ifndef BRIVALUE_H
#define BRIVALUE_H

#include <iostream>
#include <string>
#include <boost/rational.hpp>

using namespace std;

class BRIValue {

  private:
    boost::rational<int> _value;
    bool _inf;
    bool _possitive;

  public:
    BRIValue() : _inf(false) {}
    BRIValue(int n) : _value(n), _inf(false) {}
    BRIValue(int n, int d) : _value(n,d), _inf(false) {}

    static BRIValue infinity() noexcept {
      BRIValue f;
      f._inf=true;
      f._possitive=true;
      return f;
    }

    static BRIValue minusInfinity() noexcept {
      BRIValue f;
      f._inf=true;
      f._possitive=false;
      return f;
    }

    BRIValue& operator=(const BRIValue& o) noexcept { 
      this->_value = o._value;
      this->_inf = o._inf;
      this->_possitive = o._possitive;
      return *this;
    }


    /* Aritmetical operators */

    BRIValue& operator+=(const BRIValue& o) noexcept {
      this->_value += o._value;
      if (o._inf) {
        this->_inf = o._inf;
        this->_possitive = o._possitive; // + * {+/-} = {+/-}
      };
      return *this;
    }

    BRIValue& operator-=(const BRIValue& o) noexcept { 
      this->_value -= o._value;
      if (!this->_inf && o._inf) {
        this->_inf = o._inf;
        this->_possitive = !o._possitive; // - * {+/-} = {-/+}
      } else if (o._inf && (this->_possitive == o._possitive)) { //-inf-(-inf) = -inf+inf = 0 = inf-inf
        this->_inf = false;
        this->_value = boost::rational<int>(0);
      }
      return *this;
    }

    BRIValue& operator/=(const BRIValue& o) noexcept {
      if (!this->inf) {
        if (o._inf) {
          this->_value = boost::rational<int>(0);
        } else {
          this->_value /= o._value;
        }
      }
      return *this;
    }

    BRIValue& operator*=(const BRIValue& o) noexcept {
      if (!this->inf && o._inf) {
        this->_inf = o._inf;
        this->_possitive = o._possitive;
      } else if (o._inf && (this->_possitive == o._possitive)) { // (+ * + = -) and (- * - = +)
        this->_possitive = !this->_possitive;
      } else {
        this->_value *= o._value;
      }
      return *this;
    }

    BRIValue& operator--() noexcept {
      this->_value -= boost::rational<int>(1);
      return *this;
    }

    BRIValue& operator++() noexcept {
      this->_value += boost::rational<int>(1);
      return *this;
    }

    string naturalDisplay() {
      if (this->_inf) {
        if (this->_possitive)
          return "inf";
        else
          return "-inf";
      }
      
      return to_string(_value.numerator()) + "/" + to_string(_value.denominator());  
    }
};

inline BRIValue operator+(const BRIValue lhs, const BRIValue& rhs) noexcept {
  BRIValue res = lhs;
  res += rhs;
  return res;
}

inline BRIValue operator-(const BRIValue lhs, const BRIValue& rhs) noexcept {
  BRIValue res = lhs;
  res -= rhs;
  return res;
}

inline BRIValue operator/(const BRIValue lhs, const BRIValue& rhs) noexcept {
  BRIValue res = lhs;
  res /= rhs; 
  return res;
}

inline bool operator==(const BRIValue& lhs, const BRIValue& rhs) noexcept {

  if (lhs._inf && rhs._inf) return (lhs._possitive == rhs._possitive);
  else if (lhs._inf || rhs._inf) return false;
  return (lhs._value == rhs._value);
}

inline bool operator!=(const BRIValue& lhs, const BRIValue& rhs) noexcept {
  return !operator==(lhs,rhs);
}

inline bool operator<(const BRIValue& lhs, const BRIValue& rhs) noexcept {
  if (lhs._inf && lhs._possitive) return false;
  else if (lhs._inf && !lhs._possitive) return !(rhs._inf && !rhs._possitive);
  else if (rhs._inf && rhs._possitive) return true;
  else if (rhs._inf) return false;
  return (lhs._value < rhs._value);
}

inline bool operator>(const BRIValue& lhs, const BRIValue& rhs) noexcept {
  return  operator< (rhs,lhs);
}

inline bool operator<=(const BRIValue& lhs, const BRIValue& rhs) noexcept {
  return !operator> (lhs,rhs);
}

inline bool operator>=(const BRIValue& lhs, const BRIValue& rhs) noexcept {
  return !operator< (lhs,rhs);
}

inline std::ostream& operator<<(std::ostream& os, const BRIValue& t) noexcept {
    
  if (t._inf) {
    if (t._possitive)
      os << "inf";
    else
      os << "-inf";
  } else {
    os << t._value;
  } 
  return os;
}

inline std::istream& operator>>std::istream& is, BRIValue& rhs) noexcept {
  string a;
  int n,d;
  is >> a;
  if (a == "inf") rhs = BRIValue::infinity();
  else if (a == "-inf") = BRIValue::minusInfinity();
  else {
    n = std::stoi(a.substr(0, a.find_last_of("/")));
    d = std::stoi(a.substr(a.find_last_of("/")+1));
    rhs = BRIValue(n,d);
  }
  return is;
}


  //TODO: Chack this specialization
  // Specialize numeric_limits
namespace std {
  template<>
  class numeric_limits<BRIValue>{
  public:
    static constexpr bool is_specialized = true;
    static BRIValue min() noexcept { return BRIValue(-1,1) * BRIValue{numeric_limits<int>::max(), numeric_limits<int>::min()}; }
    static BRIValue max() noexcept { return BRIValue{numeric_limits<int>::max(), numeric_limits<int>::min()}; }
    static BRIValue lowest() noexcept { return BRIValue(-1,1) * BRIValue{numeric_limits<int>::max(), numeric_limits<int>::min()}; }

    static constexpr bool is_signed = true;
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = true;
    static BRIValue epsilon() noexcept { return BRIValue{1,1} - BRIValue{numeric_limits<int>::max(), numeric_limits<int>::max() - 1}; }
    static BRIValue round_error() noexcept { return BRIValue(0); }

    static constexpr int  min_exponent = numeric_limits<int>::min(); // trash_value
    static constexpr int  min_exponent10 = min_exponent/radix; // trash_value
    static constexpr int  max_exponent = numeric_limits<int>::max(); // trash_value
    static constexpr int  max_exponent10 = max_exponent/radix; // trash_value

    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_indeterminate;
    static constexpr bool has_denorm_loss = false;
    static BRIValue infinity() noexcept { return BRIValue::infinity(); }

    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = false;
    static constexpr bool is_modulo = false;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
  };
}

#endif // BRIVALUE_H