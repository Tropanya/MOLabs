#include "SimplexMethod/InequalityRow.h"
/*============================================================================*/
InequalityRow::InequalityRow(
  const std::vector<Element>& data,
  InequalitySignType::InequalitySignType type):
  SimplexTableRow(data),
  _type(type)
{
  _toCanonical();
}
/*============================================================================*/
void InequalityRow::_toCanonical()
{
  if (_data.back() < Element(0))
  {
    for (std::size_t i = 0; i < _data.size(); ++i)
      _data[i] = Element(-1) * _data[i];

    if (InequalitySignType::GE == _type)
      _type = InequalitySignType::LE;
    else if (InequalitySignType::LE == _type)
      _type = InequalitySignType::GE;
  }

  if(InequalitySignType::GE == _type)
    for (std::size_t i = 0; i < _data.size(); ++i)
      _data[i] = Element(-1) * _data[i];
}
/*============================================================================*/