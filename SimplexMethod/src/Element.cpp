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
  _paramValue(0),
  _isCompute(false)
{
  if (Fraction(0) == _coefficient)
  {
    _isCompute = true;
    _computedValue = _free;
  }
}
/*============================================================================*/
void Element::Compute(
  const Fraction& paramVal)
{
  _paramValue = paramVal;
  _computedValue = _free + (_coefficient * paramVal);
  _isCompute = true;
}
/*============================================================================*/
Element& Element::operator+=(
  const Element& other)
{
  this->_free += other._free;
  this->_coefficient += other._coefficient;

  return (*this);
}
/*============================================================================*/
Element& Element::operator-=(
  const Element& other)
{
  this->_free -= other._free;
  this->_coefficient -= other._coefficient;

  return (*this);
}
/*============================================================================*/
Element& Element::operator*=(
  const Element& other)
{
  assert(this->_isCompute || other._isCompute);

  this->_free *= other._free;
  this->_coefficient = this->_free * other._coefficient +
                       this->_coefficient * other._free;

  return (*this);
}
/*============================================================================*/
Element& Element::operator/=(
  const Element& other)
{
  assert(other._isCompute);
  assert(Fraction(0) != other._free);

  this->_free /= other._free;
  this->_coefficient /= other._free;

  return (*this);
}
/*============================================================================*/
Element operator-(
  const Element& other)
{
  return Element(
    -other._free,
    -other._coefficient);
}
/*============================================================================*/
Element operator+(
  const Element& lft,
  const Element& rht)
{
  return Element(
    lft._free + rht._free,
    lft._coefficient + rht._coefficient);
}
/*============================================================================*/
Element operator-(
  const Element& lft,
  const Element& rht)
{
  return Element(
    lft._free - rht._free,
    lft._coefficient - rht._coefficient);
}
/*============================================================================*/
Element operator*(
  const Element& lft,
  const Element& rht)
{
  assert(lft._isCompute || rht._isCompute);

  return Element(
    lft._free * rht._free,
    lft._free * rht._coefficient + lft._coefficient * rht._free);
}
/*============================================================================*/
Element operator/(
  const Element& lft,
  const Element& rht)
{
  assert(rht._isCompute);
  assert(Fraction(0) != rht._free);

  return Element(
    lft._free / rht._free,
    lft._coefficient / rht._free);
}
/*============================================================================*/
bool operator<(
  const Element& lft,
  const Element& rht)
{
  assert(lft._isCompute || rht._isCompute);

  return lft._computedValue < rht._computedValue;
}
/*============================================================================*/
bool operator<=(
  const Element& lft,
  const Element& rht)
{
  assert(lft._isCompute || rht._isCompute);

  return lft._computedValue <= rht._computedValue;
}
/*============================================================================*/
bool operator>(
  const Element& lft,
  const Element& rht)
{
  return !(lft <= rht);
}
/*============================================================================*/
bool operator>=(
  const Element& lft,
  const Element& rht)
{
  return !(lft < rht);
}
/*============================================================================*/
bool operator==(
  const Element& lft,
  const Element& rht)
{
  return (lft._free == rht._free) && (lft._coefficient == rht._coefficient);
}
/*============================================================================*/
bool operator!=(
  const Element& lft,
  const Element& rht)
{
  return !(lft == rht);
}
/*============================================================================*/
Element abs(
  const Element& other)
{
  assert(other._isCompute);

  return Element(abs(other._free));
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