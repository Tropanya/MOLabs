#ifndef TARGER_ROW_H
#define TARGER_ROW_H
/*============================================================================*/
#include <SimplexMethod/SimplexTableRow.h>
/*============================================================================*/
namespace TargetType
{
  enum TargetType
  {
    MIN = 0,
    MAX = 1
  };
}
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