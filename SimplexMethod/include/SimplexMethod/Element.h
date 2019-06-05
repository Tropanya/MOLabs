#ifndef ELEMENT_H
#define ELEMENT_H
/*============================================================================*/
#include <mpir.h>
#include <mpirxx.h>
/*============================================================================*/
typedef mpq_class Fraction;
/*============================================================================*/
class Element
{
private:
  Fraction _free;
  Fraction _coefficient;

  bool _hasParameter;
  bool _isCompute;
public:
  explicit Element(
    const Fraction& free = 0,
    const Fraction& coefficient = 0);

  Fraction Compute(const Fraction& parameter) const;

  Element& operator+=(const Element& other);
  Element& operator-=(const Element& other);
  Element& operator*=(const Element& other);
  Element& operator/=(const Element& other);

  Element& operator+=(const Fraction& other);
  Element& operator-=(const Fraction& other);
  Element& operator*=(const Fraction& other);
  Element& operator/=(const Fraction& other);

  friend Element operator-(const Element& other);

  friend Element operator+(const Element& lft, const Element& rht);
  friend Element operator-(const Element& lft, const Element& rht);
  friend Element operator*(const Element& lft, const Element& rht);
  friend Element operator/(const Element& lft, const Element& rht);

  friend Element operator+(const Element& lft, const Fraction& rht);
  friend Element operator-(const Element& lft, const Fraction& rht);
  friend Element operator*(const Element& lft, const Fraction& rht);
  friend Element operator/(const Element& lft, const Fraction& rht);

  friend Element operator+(const Fraction& lft, const Element& rht);
  friend Element operator-(const Fraction& lft, const Element& rht);
  friend Element operator*(const Fraction& lft, const Element& rht);
  friend Element operator/(const Fraction& lft, const Element& rht);

  friend bool operator<(const Element& lft, const Element& rht);
  friend bool operator<=(const Element& lft, const Element& rht);
  friend bool operator>(const Element& lft, const Element& rht);
  friend bool operator>=(const Element& lft, const Element& rht);

  friend bool operator==(const Element& lft, const Element& rht);
  friend bool operator!=(const Element& lft, const Element& rht);

  friend Element abs(const Element& other);

  inline const Fraction& GetFree() const { return _free; }

  friend std::ostream& operator<<(
    std::ostream& stream,
    const Element& elemnt);
};
/*============================================================================*/
#endif // ELEMENT_H