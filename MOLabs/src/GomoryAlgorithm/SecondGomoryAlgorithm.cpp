#include <GomoryAlgorithm/SecondGomoryAlgorithm.h>
/*============================================================================*/
#include <SimplexMethod/Utils.h>
/*============================================================================*/
SecondGomoryAlgorithm::SecondGomoryAlgorithm(
  const VarIndices& intSolutionVars,
  const SimplexTable& table):
  GomoryAlgorithm(table)
{
  for (unsigned int i = 0; i < intSolutionVars.size(); ++i)
    _intSolutionVars.emplace_back(intSolutionVars[i]);
}
/*============================================================================*/
void SecondGomoryAlgorithm::_createAdditionalRestriction(
  unsigned int index)
{
  const std::vector<mpq_class>& raw = _table.GetRaw(index);
  mpq_class B = GetProperFraction(raw.back());

  std::vector<mpq_class> elementData;
  elementData.resize(raw.size());

  for (unsigned int i = 0; i < elementData.size() - 1; ++i)
  {
    auto it = std::find(_intSolutionVars.begin(), _intSolutionVars.end(),
                        _table.GetNotBasic()[i]);

    if (it != _intSolutionVars.end())
    {
      if (GetProperFraction(raw[i]) <= B)
        elementData[i] = GetProperFraction(raw[i]);
      else
        elementData[i] =
          (B / (mpq_class(1) - B)) * (mpq_class(1) - GetProperFraction(raw[i]));
    }
    else
    {
      if (raw[i] >= 0)
        elementData[i] = raw[i];
      else
        elementData[i] =
          (B / (mpq_class(1) - B)) * (mpq_class(-1) * GetProperFraction(raw[i]));
    }
  }

  elementData.back() = GetProperFraction(raw.back());

  for (unsigned int i = 0; i < elementData.size(); ++i)
    elementData[i] = mpq_class(-1) * elementData[i];

  _table.AddRaw(&(SimplexTableElement(elementData)));
}
/*============================================================================*/