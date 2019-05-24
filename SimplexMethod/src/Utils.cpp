#include "SimplexMethod/Utils.h"
/*============================================================================*/
#include <SimplexMethod/InequalityRow.h>
#include <SimplexMethod/TargetRow.h>
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
SimplexTableRow* CreateInequalityElement(
  const Point& p1,
  const Point& p2)
{
  std::vector<mpq_class> data;
  data = CreateElementDataFromPoints(data, p1, p2);

  if (!IsBasis({ data[0], data[1] }))
    return new InequalityRow(data, InequalitySignType::LE);
  else
    return nullptr;
}
/*============================================================================*/
SimplexTableRow* CreateObjectiveElement(
  const Point& p1,
  const Point& p2)
{
  std::vector<mpq_class> data;
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
mpq_class GetTotalPart(
  const mpq_class& impropFraction)
{
  return impropFraction.get_num() / impropFraction.get_den();
}
/*============================================================================*/
mpq_class GetProperFraction(
  const mpq_class& impropFraction)
{
  mpq_class tmpImpropFraction =
    impropFraction - (impropFraction.get_num() / impropFraction.get_den());

  if (tmpImpropFraction < mpq_class(0))
  {
    if (1 == tmpImpropFraction.get_den())
      return mpq_class(0);
    else
      return impropFraction - (tmpImpropFraction - mpq_class(1));
  }
  else
    return tmpImpropFraction;
}
/*============================================================================*/