#include "SimplexMethod/Utils.h"
/*============================================================================*/
Element Dot(
  const Point& p1,
  const Point& p2)
{
  return (p1.x * p2.x) + (p1.y * p2.y);
}
/*============================================================================*/
bool IsBasis(
  std::vector<Element>& data)
{
  if ((data[2] == Element(0)) &&
      ((Dot({ data[0], data[1] }, { Element(1), Element(0) }) == Element(0)) ||
       (Dot({ data[0], data[1] }, { Element(0), Element(1) }) == Element(0))))
    return true;
  else
    return false;
}
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
  const Point& p2,
  const Point& pointInSOFS)
{
  std::vector<Element> data;
  data = CreateElementDataFromPoints(data, p1, p2);

  InequalitySignType::InequalitySignType sign = InequalitySignType::LE;

  if ((data[0] * pointInSOFS.x + data[1] * pointInSOFS.y - data[2]) > Element(0))
    sign = InequalitySignType::GE;

  if (!IsBasis(data))
    return new InequalityRow(data, sign);
  else
    return nullptr;
}
/*============================================================================*/
SimplexTableRow* CreateObjectiveElement(
  const Point& p1,
  const Point& p2,
  TargetType::TargetType type)
{
  std::vector<Element> data;
  data = CreateElementDataFromPoints(data, p1, p2);

  return new TargetRow(data, type);
}
/*============================================================================*/
std::vector<SimplexTableRow*>& CreateSimplexTableDataFromPoints(
  std::vector<SimplexTableRow*>& result,
  const std::vector<Point>& restrPoints,
  const Point& pointInSOFS)
{
  SimplexTableRow* tmpRes;

  std::size_t pointsSize = restrPoints.size();
  for (std::size_t i = 1; i <= pointsSize; ++i)
  {
    if (i == pointsSize)
      tmpRes = CreateInequalityElement(restrPoints[pointsSize - 1],
        restrPoints[0], pointInSOFS);
    else
      tmpRes = CreateInequalityElement(restrPoints[i - 1],
        restrPoints[i], pointInSOFS);

    if (tmpRes)
      result.emplace_back(tmpRes);
  }

  return result;
}
/*============================================================================*/
std::vector<SimplexTableRow*>&CreateSimplexTableDataFromPoints(
  std::vector<SimplexTableRow*>& result,
  const std::vector<Point>& restrPoints,
  const Point& pointInSOFS,
  const Point& F1,
  const Point& F2,
  TargetType::TargetType type)
{
  SimplexTableRow* tmpRes;

  std::size_t pointsSize = restrPoints.size();
  for (std::size_t i = 1; i <= pointsSize; ++i)
  {
    if(i == pointsSize)
      tmpRes = CreateInequalityElement(restrPoints[pointsSize - 1],
                                       restrPoints[0], pointInSOFS);
    else
      tmpRes = CreateInequalityElement(restrPoints[i - 1],
                                       restrPoints[i], pointInSOFS);

    if (tmpRes)
      result.emplace_back(tmpRes);
  }

  tmpRes = CreateObjectiveElement(F1, F2, type);
  result.emplace_back(tmpRes);

  return result;
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
  if (0 == (impropFraction.get_num() % impropFraction.get_den()))
    return Fraction(0);
  else
  {
    if (impropFraction < Fraction(0))
      return impropFraction - (GetTotalPart(impropFraction) - Fraction(1));
    else
      return impropFraction - GetTotalPart(impropFraction);
  }
}
/*============================================================================*/