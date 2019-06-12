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

  Fraction _paramValue;
  Fraction _computedValue;

  bool _isCompute;
public:
  explicit Element(
    const Fraction& free = 0,
    const Fraction& coefficient = 0);

  void Compute(
    const Fraction& paramVal);

  Element& operator+=(
    const Element& other);
  Element& operator-=(
    const Element& other);
  Element& operator*=(
    const Element& other);
  Element& operator/=(
    const Element& other);

  friend Element operator-(
    const Element& other);

  friend Element operator+(
    const Element& lft,
    const Element& rht);
  friend Element operator-(
    const Element& lft,
    const Element& rht);
  friend Element operator*(
    const Element& lft,
    const Element& rht);
  friend Element operator/(
    const Element& lft,
    const Element& rht);

  friend bool operator<(
    const Element& lft,
    const Element& rht);
  friend bool operator<=(
    const Element& lft,
    const Element& rht);
  friend bool operator>(
    const Element& lft,
    const Element& rht);
  friend bool operator>=(
    const Element& lft,
    const Element& rht);

  friend bool operator==(
    const Element& lft,
    const Element& rht);
  friend bool operator!=(
    const Element& lft,
    const Element& rht);

  friend Element abs(
    const Element& other);

  inline const Fraction& GetFree() const { return _free; }
  inline const Fraction& GetCoefficient() const { return _coefficient; }
  inline const Fraction& GetParamValue() const { return _paramValue; }
  inline const Fraction& GetComputedValue() const { return _computedValue; }

  friend std::ostream& operator<<(
    std::ostream& stream,
    const Element& element);
};
/*============================================================================*/
#endif // ELEMENT_H