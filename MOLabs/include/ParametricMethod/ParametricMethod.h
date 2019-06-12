#ifndef PARAMETRIC_METHOD_H
#define PARAMETRIC_METHOD_H
/*============================================================================*/
#include <SimplexMethod/SimplexTable.h>
/*============================================================================*/
#include <climits>
/*============================================================================*/
namespace Range
{
  enum Range
  {
    NEG_INF = INT_MIN,
    POS_INF = INT_MAX
  };
}
/*============================================================================*/
struct Interval
{
  Fraction min;
  Fraction max;

  friend std::ostream& operator<<(
    std::ostream& stream,
    const Interval& interval);
};
/*============================================================================*/
class ParametricMethod
{
private:
  SimplexTable _table;
  Interval _interval;
public:
  ParametricMethod(
    const SimplexTable& table,
    const Interval& interval = { Range::NEG_INF, Range::POS_INF });

  void Compute();
};
/*============================================================================*/
#endif // PARAMETRIC_METHOD_H