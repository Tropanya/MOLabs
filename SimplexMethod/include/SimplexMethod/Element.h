#ifndef ELEMENT_H
#define ELEMENT_H
/*============================================================================*/
#include <mpir.h>
#include <mpirxx.h>
/*============================================================================*/
class Element
{
private:
  mpq_class _free;
  mpq_class _coefficient;
public:
  Element(
    const mpq_class& free = 0,
    const mpq_class& coefficient = 0);

  Element& operator+=(const Element& other);
  Element& operator-=(const Element& other);

  Element& operator+=(const mpq_class& other);
  Element& operator-=(const mpq_class& other);
  Element& operator*=(const mpq_class& other);
  Element& operator/=(const mpq_class& other);

  friend Element operator+(const Element& lft, const Element& rht);
  friend Element operator-(const Element& lft, const Element& rht);

  friend Element operator+(const Element& lft, const mpq_class& rht);
  friend Element operator-(const Element& lft, const mpq_class& rht);
  friend Element operator*(const Element& lft, const mpq_class& rht);
  friend Element operator/(const Element& lft, const mpq_class& rht);

  friend Element operator+(const mpq_class& lft, const Element& rht);
  friend Element operator-(const mpq_class& lft, const Element& rht);
  friend Element operator*(const mpq_class& lft, const Element& rht);

  friend std::ostream& operator<<(
    std::ostream& stream,
    const Element& elemnt);
};
/*============================================================================*/
#endif // ELEMENT_H