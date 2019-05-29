#include <GomoryAlgorithm/SecondGomoryAlgorithm.h>
/*============================================================================*/
#include <SimplexMethod/Utils.h>
/*============================================================================*/
SecondGomoryAlgorithm::SecondGomoryAlgorithm(
  const VarIndices& intSolutionVars,
  const SimplexTable& table):
  GomoryAlgorithm(table)
{
  for (std::size_t i = 0; i < intSolutionVars.size(); ++i)
    _intSolutionVars.emplace_back(intSolutionVars[i]);
}
/*============================================================================*/
void SecondGomoryAlgorithm::_createAdditionalRestriction(
  unsigned int index)
{
  const std::vector<Element>& raw = _table.GetRaw(index);
  Element B = GetProperFraction(raw.back());

  std::vector<Element> elementData;
  elementData.resize(raw.size());

  for (std::size_t i = 0; i < elementData.size() - 1; ++i)
  {
    auto it = std::find(_intSolutionVars.begin(), _intSolutionVars.end(),
                        _table.GetNotBasic()[i]);

    if (it != _intSolutionVars.end())
    {
      if (GetProperFraction(raw[i]) <= B)
        elementData[i] = GetProperFraction(raw[i]);
      else
        elementData[i] =
          (B / (Element(1) - B)) * (Element(1) - GetProperFraction(raw[i]));
    }
    else
    {
      if (raw[i] >= 0)
        elementData[i] = raw[i];
      else
        elementData[i] =
          (B / (Element(1) - B)) * (Element(-1) * GetProperFraction(raw[i]));
    }
  }

  elementData.back() = GetProperFraction(raw.back());

  for (std::size_t i = 0; i < elementData.size(); ++i)
    elementData[i] = Element(-1) * elementData[i];

  _table.AddRow(&(SimplexTableRow(elementData)));
}
/*============================================================================*/