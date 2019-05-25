#ifndef UTILS_H
#define UTILS_H
/*============================================================================*/
#include <SimplexMethod/SimplexTableRow.h>
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
mpq_class GetTotalPart(
  const mpq_class& impropFraction);
mpq_class GetProperFraction(
  const mpq_class& impropFraction);
/*============================================================================*/
#endif // UTILS_H