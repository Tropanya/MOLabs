#include "GomoryAlgorithm/GomoryAlgorithm.h"
/*============================================================================*/
#include <SimplexMethod/Utils.h>
#include <iostream>
/*============================================================================*/
GomoryAlgorithm::GomoryAlgorithm(
  SimplexTable& table)
{
  bool isFractNums = true;

  for (unsigned int i = 0; i < table.GetVariableCount(); ++i)
    if (1 == table.GetData()[i].back().get_den())
      isFractNums &= false;

  std::vector<mpq_class> properFractionNums;

  if (isFractNums)
  {
    unsigned int index = 0;
    mpq_class cmpVal = GetProperFraction(table.GetData()[index].back());

    for (unsigned int i = 0; i < table.GetVariableCount(); ++i)
      if (GetProperFraction(table.GetData()[i].back()) > cmpVal)
        index = i;

    _createAdditionalRestriction(index, table);
    std::cout << table << std::endl;
  }
  else
    return;
}
/*============================================================================*/
void GomoryAlgorithm::_createAdditionalRestriction(
  unsigned int index,
  SimplexTable& table)
{
  const std::vector<mpq_class>& raw = table.GetRaw(index);

  std::vector<mpq_class> elementData;
  elementData.resize(raw.size());

  for (unsigned int i = 0; i < elementData.size() - 1; ++i)
  {
    if (raw[i] < mpq_class(0))
      elementData[i] = mpq_class(-1) *
        (GetProperFraction(raw[i]) - (GetTotalPart(raw[i]) - mpq_class(-1)));
    else
      elementData[i] = mpq_class(-1) * GetProperFraction(raw[i]);
  }

  elementData.back() = mpq_class(-1) * GetProperFraction(raw.back());

  table.AddRaw(&(SimplexTableElement(elementData)));
}
/*============================================================================*/