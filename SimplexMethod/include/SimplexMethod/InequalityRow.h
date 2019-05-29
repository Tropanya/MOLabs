#ifndef INEQUALITY_ROW_H
#define INEQUALITY_ROW_H
/*============================================================================*/
#include <SimplexMethod/InequalitySignType.h>
#include <SimplexMethod/SimplexTableRow.h>
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