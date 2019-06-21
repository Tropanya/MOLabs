#ifndef UTILS_H
#define UTILS_H
/*============================================================================*/
#include <SimplexMethod/InequalityRow.h>
#include <SimplexMethod/TargetRow.h>
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
  std::vector<Element>& data);
/*============================================================================*/
std::vector<Element>& CreateElementDataFromPoints(
  std::vector<Element>& data,
  const Point& p1,
  const Point& p2);
SimplexTableRow* CreateInequalityElement(
  const Point& p1,
  const Point& p2,
  const Point& pointInSOFS);
SimplexTableRow* CreateObjectiveElement(
  const Point& p1,
  const Point& p2,
  TargetType::TargetType type);
std::vector<SimplexTableRow*>& CreateSimplexTableDataFromPoints(
  std::vector<SimplexTableRow*>& result,
  const std::vector<Point>& restrPoints,
  const Point& pointInSOFS);
std::vector<SimplexTableRow*>& CreateSimplexTableDataFromPoints(
  std::vector<SimplexTableRow*>& result,
  const std::vector<Point>& restrPoints,
  const Point& pointInSOFS,
  const Point& F1,
  const Point& F2,
  TargetType::TargetType type);
/*============================================================================*/
Fraction GetTotalPart(
  const Fraction& impropFraction);
Fraction GetProperFraction(
  const Fraction& impropFraction);
/*============================================================================*/
#endif // UTILS_H