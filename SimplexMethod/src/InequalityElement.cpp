#include "SimplexMethod/InequalityElement.h"
/*============================================================================*/
InequalityElement::InequalityElement(
  const std::vector<mpq_class>& data,
  InequalitySignType::InequalitySignType type):
  SimplexTableElement(data),
  _type(type)
{
  _toCanonical();
}
/*============================================================================*/
void InequalityElement::_toCanonical()
{
  if (_data.back() < mpq_class(0))
  {
    for (std::size_t i = 0; i < _data.size(); ++i)
      _data[i] = mpq_class(-1) * _data[i];

    if (InequalitySignType::GE == _type)
      _type = InequalitySignType::LE;
    else if (InequalitySignType::LE == _type)
      _type = InequalitySignType::GE;
  }

  if(InequalitySignType::GE == _type)
    for (std::size_t i = 0; i < _data.size(); ++i)
      _data[i] = mpq_class(-1) * _data[i];
}
/*============================================================================*/