#include "SimplexMethod/Utils.h"
/*============================================================================*/
#include <SimplexMethod/InequalityRow.h>
#include <SimplexMethod/TargetRow.h>
/*============================================================================*/
Element Dot(
  const Point& p1,
  const Point& p2)
{
  return (p1.x * p2.x) + (p1.y * p2.y);
}
/*============================================================================*/
/*bool IsBasis(
  const Point& point)
{
  if ((Dot(point, { Element(1), Element(0) }) == 0) ||
      (Dot(point, { Element(0), Element(1) }) == 0))
    return true;

  return false;
}*/
/*============================================================================*/
std::vector<Element>& CreateElementDataFromPoints(
  std::vector<Element>& data,
  const Point& p1,
  const Point& p2)
{
  data.emplace_back(p1.y - p2.y);
  data.emplace_back(p2.x - p1.x);
  data.emplace_back(-(p1.x * p2.y - p2.x * p1.y));

  return data;
}
/*============================================================================*/
SimplexTableRow* CreateInequalityElement(
  const Point& p1,
  const Point& p2)
{
  std::vector<Element> data;
  data = CreateElementDataFromPoints(data, p1, p2);

  return new InequalityRow(data, InequalitySignType::LE);

  //if (!IsBasis({ data[0], data[1] }))
  //  return new InequalityRow(data, InequalitySignType::LE);
  //else
  //  return nullptr;
}
/*============================================================================*/
SimplexTableRow* CreateObjectiveElement(
  const Point& p1,
  const Point& p2)
{
  std::vector<Element> data;
  data = CreateElementDataFromPoints(data, p1, p2);

  return new TargetRow(data, TargetType::MAX);
}
/*============================================================================*/
std::vector<SimplexTableRow*>& CreateSimplexTableDataFromPoints(
  std::vector<SimplexTableRow*>& data,
  const std::vector<Point>& points)
{
  SimplexTableRow* result;

  for (std::size_t i = 1; i < points.size(); ++i)
  {
    if (points.size() - 2 == i)
      result = CreateInequalityElement(points[i - 1], points[0]);
    else if (i > points.size() - 2)
      result = CreateObjectiveElement(points[i - 1], points[i]);
    else
      result = CreateInequalityElement(points[i - 1], points[i]);

    if (result)
      data.emplace_back(result);
  }

  return data;
}
/*============================================================================*/
Fraction GetTotalPart(
  const Fraction& impropFraction)
{
  return impropFraction.get_num() /
           impropFraction.get_den();
}
/*============================================================================*/
Fraction GetProperFraction(
  const Fraction& impropFraction)
{
  Fraction tmpImpropFraction =
    impropFraction - (impropFraction.get_num() /
                        impropFraction.get_den());

  if (tmpImpropFraction < Fraction(0))
  {
    if (1 == tmpImpropFraction.get_den())
      return Fraction(0);
    else
      return impropFraction - (tmpImpropFraction - Fraction(1));
  }
  else
    return tmpImpropFraction;
}
/*============================================================================*/