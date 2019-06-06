#include "SimplexMethod/Element.h"
/*============================================================================*/
#include <cassert>
#include <iostream>
/*============================================================================*/
Element::Element(
  const Fraction& free,
  const Fraction& coefficient):
  _free(free),
  _coefficient(coefficient),
  _isCompute(false)
{
  if (Fraction(0) == _coefficient)
  {
    _isCompute = true;
    _computedValue = _free;
  }
}
/*============================================================================*/
void Element::Compute(const Fraction& parameter)
{
  _computedValue = _free + (_coefficient * parameter);
}
/*============================================================================*/
Element& Element::operator+=(const Element& other)
{
  this->_free += other._free;
  this->_coefficient += other._coefficient;

  return (*this);
}
/*============================================================================*/
Element& Element::operator-=(const Element& other)
{
  this->_free -= other._free;
  this->_coefficient -= other._coefficient;

  return (*this);
}
/*============================================================================*/
Element& Element::operator*=(const Element& other)
{
  if (!(this->_isCompute || other._isCompute))
    assert(false);

  this->_free *= other._free;

  return (*this);
}
/*============================================================================*/
Element& Element::operator/=(const Element& other)
{
  if (!(this->_isCompute || other._isCompute))
    assert(false);

  assert(Fraction(0) != other._free);

  this->_free /= other._free;

  return (*this);
}
/*============================================================================*/
Element& Element::operator+=(const Fraction& other)
{
  this->_free += other;

  return (*this);
}
/*============================================================================*/
Element& Element::operator-=(const Fraction& other)
{
  this->_free -= other;

  return (*this);
}
/*============================================================================*/
Element& Element::operator*=(const Fraction& other)
{
  this->_free *= other;
  this->_coefficient *= other;

  return (*this);
}
/*============================================================================*/
Element& Element::operator/=(const Fraction& other)
{
  assert(Fraction(0) != other);

  this->_free /= other;
  this->_coefficient /= other;

  return (*this);
}
/*============================================================================*/
Element operator-(const Element& other)
{
  return Element(
    -other._free,
    -other._coefficient);
}
/*============================================================================*/
Element operator+(const Element& lft, const Element& rht)
{
  return Element(
    lft._free + rht._free,
    lft._coefficient + rht._coefficient);
}
/*============================================================================*/
Element operator-(const Element& lft, const Element& rht)
{
  return Element(
    lft._free - rht._free,
    lft._coefficient - rht._coefficient);
}
/*============================================================================*/
Element operator*(const Element& lft, const Element& rht)
{
  if (!(lft._isCompute || rht._isCompute))
    assert(false);

  return Element(
    lft._free * rht._free);
}
/*============================================================================*/
Element operator/(const Element& lft, const Element& rht)
{
  if (!(lft._isCompute || rht._isCompute))
    assert(false);

  assert(Fraction(0) != rht._free);

  return Element(
    lft._free / rht._free);
}
/*============================================================================*/
Element operator+(const Element& lft, const Fraction& rht)
{
  return Element(
    lft._free + rht,
    lft._coefficient);
}
/*============================================================================*/
Element operator-(const Element& lft, const Fraction& rht)
{
  return Element(
    lft._free - rht,
    lft._coefficient);
}
/*============================================================================*/
Element operator*(const Element& lft, const Fraction& rht)
{
  return Element(
    lft._free * rht,
    lft._coefficient * rht);
}
/*============================================================================*/
Element operator/(const Element& lft, const Fraction& rht)
{
  assert(Fraction(0) != rht);

  return Element(
    lft._free / rht,
    lft._coefficient / rht);
}
/*============================================================================*/
Element operator+(const Fraction& lft, const Element& rht)
{
  return Element(
    lft + rht._free,
    rht._coefficient);
}
/*============================================================================*/
Element operator-(const Fraction& lft, const Element& rht)
{
  return Element(
    lft - rht._free,
    rht._coefficient);
}
/*============================================================================*/
Element operator*(const Fraction& lft, const Element& rht)
{
  return Element(
    lft * rht._free,
    lft * rht._coefficient);
}
/*============================================================================*/
Element operator/(const Fraction& lft, const Element& rht)
{
  if (!rht._isCompute)
    assert(false);

  assert(Fraction(0) != rht._free);

  return Element(
    lft / rht._free);
}
/*============================================================================*/
bool operator<(const Element& lft, const Element& rht)
{
  if (!(lft._isCompute || rht._isCompute))
    assert(false);

  return lft._computedValue < rht._computedValue;
}
/*============================================================================*/
bool operator<=(const Element& lft, const Element& rht)
{
  if (!(lft._isCompute || rht._isCompute))
    assert(false);

  return lft._computedValue <= rht._computedValue;
}
/*============================================================================*/
bool operator>(const Element& lft, const Element& rht)
{
  return !(lft <= rht);
}
/*============================================================================*/
bool operator>=(const Element& lft, const Element& rht)
{
  return !(lft < rht);
}
/*============================================================================*/
bool operator==(const Element& lft, const Element& rht)
{
  return (lft._free == rht._free) && (lft._coefficient == rht._coefficient);
}
/*============================================================================*/
bool operator!=(const Element& lft, const Element& rht)
{
  return !(lft == rht);
}
/*============================================================================*/
Element abs(const Element& other)
{
  if (other._isCompute)
    return Element(abs(other._free));
  else
    assert(false);
}
/*============================================================================*/
std::ostream& operator<<(
  std::ostream& stream,
  const Element& element)
{
  if (Fraction(0) != element._coefficient)
    stream << "(" << element._free << "+(" << element._coefficient << "t))";
  else
    stream << element._free;

  return stream;
}
/*============================================================================*/