#include "SimplexMethod/TargetRow.h"
/*============================================================================*/
TargetRow::TargetRow(
  const std::vector<Element>& data,
  TargetType::TargetType type):
  SimplexTableRow(data),
  _type(type)
{
  _toCanonical();
}
/*============================================================================*/
void TargetRow::_toCanonical()
{
  if (TargetType::MIN == _type)
    for (std::size_t i = 0; i < _data.size(); ++i)
      _data[i] = Element(-1) * _data[i];

  _data.back() = Element(0);
}
/*============================================================================*/