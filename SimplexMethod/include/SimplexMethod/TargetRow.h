#ifndef TARGER_ROW_H
#define TARGER_ROW_H
/*============================================================================*/
#include <SimplexMethod/TargetType.h>
#include <SimplexMethod/SimplexTableRow.h>
/*============================================================================*/
class TargetRow:
  public SimplexTableRow
{
private:
  TargetType::TargetType _type;
private:
  void _toCanonical() override;
public:
  TargetRow(
    const std::vector<Element>& data,
    TargetType::TargetType type);
};
/*============================================================================*/
#endif // TARGER_ROW_H