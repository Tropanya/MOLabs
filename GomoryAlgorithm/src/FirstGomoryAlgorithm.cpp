#include "GomoryAlgorithm/FirstGomoryAlgorithm.h"
/*============================================================================*/
#include <SimplexMethod/Utils.h>
/*============================================================================*/
FirstGomoryAlgorithm::FirstGomoryAlgorithm(
  const SimplexTable& table):
  GomoryAlgorithm(table)
{
  for (unsigned int i = 0; i < _table.GetSolutionVars().size(); ++i)
    _intSolutionVars.emplace_back(i);
}
/*============================================================================*/
void FirstGomoryAlgorithm::_createAdditionalRestriction(
  unsigned int index)
{
  const std::vector<mpq_class>& raw = _table.GetRaw(index);

  std::vector<mpq_class> elementData;
  elementData.resize(raw.size());

  for (unsigned int i = 0; i < elementData.size(); ++i)
    elementData[i] = mpq_class(-1) * GetProperFraction(raw[i]);

  _table.AddRaw(&(SimplexTableElement(elementData)));
}
/*============================================================================*/