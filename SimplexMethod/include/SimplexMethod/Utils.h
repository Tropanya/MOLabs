#ifndef UTILS_H
#define UTILS_H
/*============================================================================*/
#include <SimplexMethod/SimplexTableRow.h>
/*============================================================================*/
struct Point
{
  Element x, y;
};
/*============================================================================*/
Element Dot(
  const Point& p1,
  const Point& p2);
bool IsBasis(
  const Point& point);
/*============================================================================*/
std::vector<Element>& CreateElementDataFromPoints(
  std::vector<Element>& data,
  const Point& p1,
  const Point& p2);
SimplexTableRow* CreateInequalityElement(
  const Point& p1,
  const Point& p2);
SimplexTableRow* CreateObjectiveElement(
  const Point& p1,
  const Point& p2);
std::vector<SimplexTableRow*>& CreateSimplexTableDataFromPoints(
  std::vector<SimplexTableRow*>& data,
  const std::vector<Point>& points);
/*============================================================================*/
Element GetTotalPart(
  const Element& impropFraction);
Element GetProperFraction(
  const Element& impropFraction);
/*============================================================================*/
#endif // UTILS_H