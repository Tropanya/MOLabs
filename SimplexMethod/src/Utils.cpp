#include "SimplexMethod/Utils.h"
/*============================================================================*/
#include <SimplexMethod/InequalityElement.h>
#include <SimplexMethod/ObjectiveElement.h>
/*============================================================================*/
mpq_class Dot(
  const Point& p1,
  const Point& p2)
{
  return (p1.x * p2.x) + (p1.y * p2.y);
}
/*============================================================================*/
bool IsBasis(
  const Point& point)
{
  if ((Dot(point, { mpq_class(1), mpq_class(0) }) == 0) ||
    (Dot(point, { mpq_class(0), mpq_class(1) }) == 0))
    return true;

  return false;
}
/*============================================================================*/
std::vector<mpq_class>& CreateElementDataFromPoints(
  std::vector<mpq_class>& data,
  const Point& p1,
  const Point& p2)
{
  data.emplace_back(p1.y - p2.y);
  data.emplace_back(p2.x - p1.x);
  data.emplace_back(-(p1.x * p2.y - p2.x * p1.y));

  return data;
}
/*============================================================================*/
SimplexTableElement* CreateInequalityElement(
  const Point& p1,
  const Point& p2)
{
  std::vector<mpq_class> data;
  data = CreateElementDataFromPoints(data, p1, p2);

  if (!IsBasis({ data[0], data[1] }))
    return new InequalityElement(data, InequalitySignType::LE);
  else
    return nullptr;
}
/*============================================================================*/
SimplexTableElement* CreateObjectiveElement(
  const Point& p1,
  const Point& p2)
{
  std::vector<mpq_class> data;
  data = CreateElementDataFromPoints(data, p1, p2);

  return new ObjectiveElement(data, ObjectiveElementType::MAX);
}
/*============================================================================*/
std::vector<SimplexTableElement*>& CreateSimplexTableDataFromPoints(
  std::vector<SimplexTableElement*>& data,
  const std::vector<Point>& points)
{
  SimplexTableElement* result;

  for (unsigned int i = 1; i < points.size(); ++i)
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
}/*============================================================================*/
mpq_class GetTotalPart(
  const mpq_class& improperFraction)
{
  return improperFraction.get_num() / improperFraction.get_den();
}
/*============================================================================*/
mpq_class GetProperFraction(
  const mpq_class& improperFraction)
{
  return improperFraction -
    (improperFraction.get_num() / improperFraction.get_den());
}
/*============================================================================*/