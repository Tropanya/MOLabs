#include "SimplexMethod/SimplexTable.h"
/*============================================================================*/
#include <cassert>
#include <iostream>
/*============================================================================*/
SimplexTable::SimplexTable(
  unsigned int variableCount,
  unsigned int restrictionCount,
  const std::vector<SimplexTableElement*>& data)
{
  assert((restrictionCount == data.size() - 1) &&
    "Restriction count fail!");
  assert((variableCount == data[0]->GetData().size() - 1) &&
    "Variable count fail!");

  _solutionVars.resize(variableCount);

  for (unsigned int i = 0; i < variableCount; ++i)
    _notBasis.emplace_back(i);

  for (unsigned int i = 0; i < restrictionCount; ++i)
    _basis.emplace_back(i + variableCount);

  _fillTable(data);

  while (!_isOptimalSolution())
    RebuildTable(_getResolutionElement());

  _isOptimal = true;
}
/*============================================================================*/
void SimplexTable::_fillTable(
  const std::vector<SimplexTableElement*>& data)
{
  _data.resize(data.size());
  for (std::size_t i = 0; i < _data.size(); ++i)
    _data[i].resize(data[i]->GetData().size());

  for (std::size_t i = 0; i < data.size() - 1; ++i)
    for (std::size_t j = 0; j < data[i]->GetData().size(); ++j)
      _data[i][j] = data[i]->GetData()[j];

  for (std::size_t i = 0; i < data.back()->GetData().size(); ++i)
    _data.back()[i] = mpq_class(-1) * data.back()->GetData()[i];
}
/*============================================================================*/
ResolutionElement SimplexTable::_getResolutionElement() const
{
  ResolutionElement res;
  res.horIndex = 0;
  res.vertIndex = 0;
  res.resolutionVal = mpq_class(-1);

  mpq_class cmpVal(0);

  for (unsigned int i = 0; i < _data.back().size() - 1; ++i)
  {
    if (_data.back()[i] <= cmpVal)
    {
      res.horIndex = i;
      cmpVal = _data.back()[i];
    }
  }

  bool isFirst = true;

  for (unsigned int i = 0; i < _data.size() - 1; ++i)
  {
    if (_data[i][res.horIndex] > mpq_class(0))
    {
      cmpVal = _data[i].back() / _data[i][res.horIndex];

      if (isFirst)
      {
        res.vertIndex = i;
        res.resolutionVal = cmpVal;
        isFirst = false;
      }
      else
      {
        if (cmpVal <= res.resolutionVal)
        {
          res.vertIndex = i;
          res.resolutionVal = cmpVal;
        }
      }
    }
  }

  res.resolutionVal = _data[res.vertIndex][res.horIndex];
  assert(res.resolutionVal > 0);

  return res;
}
/*============================================================================*/
void SimplexTable::_swapBasic(
  const ResolutionElement& resolution)
{
  unsigned int tmp = _basis[resolution.vertIndex];
  _basis[resolution.vertIndex] = _notBasis[resolution.horIndex];
  _notBasis[resolution.horIndex] = tmp;
}
/*============================================================================*/
bool SimplexTable::_isOptimalSolution()
{
  bool res = true;

  for (unsigned int i = 0; i < _data.back().size() - 1; ++i)
    if (_data.back()[i] < mpq_class(0))
    {
      res = false;
      break;
    }

  return res;
}
/*============================================================================*/
void SimplexTable::RebuildTable(
  const ResolutionElement& resolution)
{
  _swapBasic(resolution);
  SimplexTableData oldData = _data;

  for (unsigned int i = 0; i < _data.size(); ++i)
    for (unsigned int j = 0; j < _data[i].size(); ++j)
      if (i == resolution.vertIndex && j == resolution.horIndex)
        _data[i][j] = mpq_class(1) / oldData[i][j];
      else if (i == resolution.vertIndex)
        _data[i][j] = oldData[i][j] / resolution.resolutionVal;
      else if (j == resolution.horIndex)
        _data[i][j] = mpq_class(-1) * (oldData[i][j] / resolution.resolutionVal);
      else
        _data[i][j] =
        (resolution.resolutionVal * oldData[i][j] -
          oldData[resolution.vertIndex][j] * oldData[i][resolution.horIndex]) /
          resolution.resolutionVal;

  for (unsigned int i = 0; i < GetVariableCount(); ++i)
  {
    auto it = std::find(_basis.begin(), _basis.end(), i);
    if (it != _basis.end())
      _solutionVars[i] = _data[std::distance(_basis.begin(), it)].back();
    else
    {
      it = std::find(_notBasis.begin(), _notBasis.end(), 0);
      _solutionVars[i] = _data[std::distance(_notBasis.begin(), it)].back();
    }
  }
}
/*============================================================================*/
void SimplexTable::AddRaw(
  SimplexTableElement* element)
{
  _basis.emplace_back(_basis.size() + _notBasis.size());
  _data.resize(_basis.size() + 1);
  _data.back().resize(element->GetData().size());

  assert(element->GetData().size() == _data[0].size());

  _data.back() = element->GetData();
  std::swap(_data.back(), _data[_data.size() - 2]);
}
/*============================================================================*/
void SimplexTable::InvertRaw(unsigned int index)
{
  for (unsigned int i = 0; i < _data[index].size(); ++i)
    _data[index][i] = mpq_class(-1) * _data[index][i];
}
/*============================================================================*/
std::ostream& operator<<(
  std::ostream& stream,
  const SimplexTable& table)
{
  for (unsigned int i = 0; i < table._data.size(); ++i)
  {
    for (unsigned int j = 0; j < table._data[i].size(); ++j)
      stream << table._data[i][j] << " ";

    stream << '\n';
  }

  return stream;
}
/*============================================================================*/