#include "SimplexMethod/ObjectiveElement.h"
/*============================================================================*/
ObjectiveElement::ObjectiveElement(
  const std::vector<mpq_class>& data,
  ObjectiveElementType::ObjectiveElementType type):
  SimplexTableElement(data),
  _type(type)
{
  _toCanonical();
}
/*============================================================================*/
void ObjectiveElement::_toCanonical()
{
  if (ObjectiveElementType::MIN == _type)
    for (std::size_t i = 0; i < _data.size(); ++i)
      _data[i] = mpq_class(-1) * _data[i];

  _data.back() = mpq_class(0);
}
/*============================================================================*/