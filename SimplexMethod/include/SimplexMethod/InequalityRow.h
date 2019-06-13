#ifndef INEQUALITY_ROW_H
#define INEQUALITY_ROW_H
/*============================================================================*/
#include <SimplexMethod/SimplexTableRow.h>
/*============================================================================*/
namespace InequalitySignType
{
  enum InequalitySignType
  {
    LE = 0,
    GE = 1
  };
}
/*============================================================================*/
class InequalityRow:
  public SimplexTableRow
{
private:
  InequalitySignType::InequalitySignType _type;
private:
  void _toCanonical() override;
public:
  InequalityRow(
    const std::vector<Element>& data,
    InequalitySignType::InequalitySignType type);
};
/*============================================================================*/
#endif // INEQUALITY_ROW_H