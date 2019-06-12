#include "ParametricMethod/ParametricMethod.h"
/*============================================================================*/
#include <iostream>
/*============================================================================*/
std::ostream& operator<<(
  std::ostream& stream,
  const Interval& interval)
{
  stream << "Sub interval: ";

  if (Range::NEG_INF == interval.min)
    stream << "-inf";
  else
    stream << interval.min;

  stream << ", ";

  if (Range::POS_INF == interval.max)
    stream << "+inf";
  else
    stream << interval.max;

  return stream;
}
/*============================================================================*/
ParametricMethod::ParametricMethod(
  const SimplexTable& table,
  const Interval& interval):
  _table(table),
  _interval(interval)
{
  std::cout << _table << std::endl;
}
/*============================================================================*/
void ParametricMethod::Compute()
{
  Fraction leftBound = _interval.min;

  while (_interval.max != leftBound)
  {
    _table.Rebuild(Fraction(leftBound), false);

    Interval subInterval;

    bool isFirstNegative = true;
    bool onlyNagative = true;

    bool isFirstPositive = true;
    bool onlyPositive = true;

    for (std::size_t i = 0; i < _table.GetData().back().size() - 1; ++i)
    {
      Element tmp = _table.GetData().back()[i];

      if (tmp.GetCoefficient() > Fraction(0))
      {
        Fraction tmpMax = -tmp.GetFree() / tmp.GetCoefficient();

        if (isFirstPositive)
        {
          subInterval.min = tmpMax;
          isFirstPositive = false;
          onlyNagative &= false;
        }
        else
        {
          if (subInterval.min < tmpMax)
            subInterval.min = tmpMax;
        }
      }
      else if (tmp.GetCoefficient() < Fraction(0))
      {
        Fraction tmpMin = -tmp.GetFree() / tmp.GetCoefficient();

        if (isFirstNegative)
        {
          subInterval.max = tmpMin;
          isFirstNegative = false;
          onlyPositive &= false;
        }
        else
        {
          if (tmpMin < subInterval.max)
            subInterval.max = tmpMin;
        }
      }
      else
        continue;
    }

    if (onlyNagative)
      subInterval.min = Range::NEG_INF;

    if (onlyPositive)
      subInterval.max = Range::POS_INF;

    std::cout << subInterval << std::endl;
    std::cout << _table << std::endl;

    if (Range::POS_INF == subInterval.max)
      break;
    else
      leftBound = subInterval.max + Fraction(1, 1000);
  }
}
/*============================================================================*/