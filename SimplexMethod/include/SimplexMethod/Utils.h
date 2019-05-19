#ifndef UTILS_H
#define UTILS_H
/*============================================================================*/
#include <SimplexMethod/SimplexTableElement.h>
/*============================================================================*/
#include <mpir.h>
#include <mpirxx.h>
/*============================================================================*/
#include <vector>
/*============================================================================*/
struct Point
{
  mpq_class x, y;
};
/*============================================================================*/
mpq_class Dot(
  const Point& p1,
  const Point& p2);
bool IsBasis(
  const Point& point);
/*============================================================================*/
std::vector<mpq_class>& CreateElementDataFromPoints(
  std::vector<mpq_class>& data,
  const Point& p1,
  const Point& p2);
SimplexTableElement* CreateInequalityElement(
  const Point& p1,
  const Point& p2);
SimplexTableElement* CreateObjectiveElement(
  const Point& p1,
  const Point& p2);
std::vector<SimplexTableElement*>& CreateSimplexTableDataFromPoints(
  std::vector<SimplexTableElement*>& data,
  const std::vector<Point>& points);
/*============================================================================*/
mpq_class GetTotalPart(
  const mpq_class& impropFraction);
mpq_class GetProperFraction(
  const mpq_class& impropFraction);
/*============================================================================*/
#endif // UTILS_H