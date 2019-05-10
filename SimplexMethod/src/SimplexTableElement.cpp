#include "SimplexMethod/SimplexTableElement.h"
/*============================================================================*/
SimplexTableElement::SimplexTableElement(
  const SimplexTableElementData& data):
  _data(data)
{
  _toCanonical();
}
/*============================================================================*/
SimplexTableElement::~SimplexTableElement()
{  }