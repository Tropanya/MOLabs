#include "SimplexMethod/Element.h"
/*============================================================================*/
#include <cassert>
/*============================================================================*/
Element::Element(
  const mpq_class& free,
  const mpq_class& coefficient):
  _free(free),
  _coefficient(coefficient)
{  }
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
Element& Element::operator+=(const mpq_class& other)
{
  this->_free += other;

  return (*this);
}
/*============================================================================*/
Element& Element::operator-=(const mpq_class& other)
{
  this->_free -= other;

  return (*this);
}
/*============================================================================*/
Element& Element::operator*=(const mpq_class& other)
{
  this->_free *= other;
  this->_coefficient *= other;

  return (*this);
}
/*============================================================================*/
Element& Element::operator/=(const mpq_class& other)
{
  assert(mpq_class(0) != other);

  this->_free /= other;
  this->_coefficient /= other;

  return (*this);
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
Element operator+(const Element& lft, const mpq_class& rht)
{
  return Element(
    lft._free + rht,
    lft._coefficient);
}
/*============================================================================*/
Element operator-(const Element& lft, const mpq_class& rht)
{
  return Element(
    lft._free - rht,
    lft._coefficient);
}
/*============================================================================*/
Element operator*(const Element& lft, const mpq_class& rht)
{
  return Element(
    lft._free * rht,
    lft._coefficient * rht);
}
/*============================================================================*/
Element operator/(const Element& lft, const mpq_class& rht)
{
  assert(mpq_class(0) != rht);

  return Element(
    lft._free / rht,
    lft._coefficient / rht);
}
/*============================================================================*/
Element operator+(const mpq_class& lft, const Element& rht)
{
  return Element(
    lft + rht._free,
    rht._coefficient);
}
/*============================================================================*/
Element operator-(const mpq_class& lft, const Element& rht)
{
  return Element(
    lft - rht._free,
    rht._coefficient);
}
/*============================================================================*/
Element operator*(const mpq_class& lft, const Element& rht)
{
  return Element(
    lft * rht._free,
    lft * rht._coefficient);
}
/*============================================================================*/
std::ostream& operator<<(
  std::ostream& stream,
  const Element& elemnt)
{
  if (mpq_class(0) != elemnt._coefficient)
    stream << "(" << elemnt._free << "+(" << elemnt._coefficient << "t))";
  else
    stream << elemnt._free;

  return stream;
}
/*============================================================================*/