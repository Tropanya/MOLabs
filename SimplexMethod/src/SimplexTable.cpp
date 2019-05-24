#include "SimplexMethod/SimplexTable.h"
/*============================================================================*/
#include <cassert>
#include <iostream>
#include <iomanip>
/*============================================================================*/
SimplexTable::SimplexTable(
  unsigned int variableCount,
  unsigned int restrictionCount,
  const std::vector<SimplexTableElement*>& data):
  _isExistSolution(true)
{
  assert((restrictionCount == data.size() - 1) &&
    "Restriction count fail!");
  assert((variableCount == data[0]->GetData().size() - 1) &&
    "Variable count fail!");

  _solutionVars.resize(variableCount);

  for (std::size_t i = 0; i < variableCount; ++i)
    _notBasis.emplace_back(i);

  for (std::size_t i = 0; i < restrictionCount; ++i)
    _basis.emplace_back(i + variableCount);

  _fillTable(data);
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
ResolutionElement SimplexTable::_getResolutionElementDual() const
{
  ResolutionElement res;
  res.horIndex = 0;
  res.vertIndex = 0;
  res.resolutionVal = mpq_class(0);

  mpq_class cmpVal(0);
  bool isFirst = true;
  for (std::size_t i = 0; i < _basis.size(); ++i)
  {
    if (_data[i].back() < mpq_class(0))
    {
      if (isFirst)
      {
        res.vertIndex = i;
        cmpVal = abs(_data[i].back());
        isFirst = false;
      }
      else
      {
        if (abs(_data[i].back()) > cmpVal)
        {
          res.vertIndex = i;
          cmpVal = abs(_data[i].back());
        }
      }
    }
  }

  _isExistSolution = false;
  for (std::size_t i = 0; i < _notBasis.size(); ++i)
  {
    if (_data[res.vertIndex][i] < mpq_class(0))
    {
      _isExistSolution = true;
      break;
    }
  }

  if (!_isExistSolution)
    return { 0, 0, mpq_class(0) };

  isFirst = true;
  for (std::size_t i = 0; i < _notBasis.size(); ++i)
  {
    if (_data[res.vertIndex][i] < mpq_class(0))
    {
      cmpVal = abs(_data.back()[i] / _data[res.vertIndex][i]);

      if (isFirst)
      {
        res.horIndex = i;
        res.resolutionVal = cmpVal;
        isFirst = false;
      }
      else
      {
        if (cmpVal < res.resolutionVal)
        {
          res.horIndex = i;
          res.resolutionVal = cmpVal;
        }
      }
    }
  }

  res.resolutionVal = _data[res.vertIndex][res.horIndex];
  return res;
}
/*============================================================================*/
ResolutionElement SimplexTable::_getResolutionElement() const
{
  ResolutionElement res;
  res.horIndex = 0;
  res.vertIndex = 0;
  res.resolutionVal = mpq_class(0);

  mpq_class cmpVal(0);
  for (std::size_t i = 0; i < _notBasis.size(); ++i)
  {
    if (_data.back()[i] <= cmpVal)
    {
      res.horIndex = i;
      cmpVal = _data.back()[i];
    }
  }

  _isExistSolution = false;
  for (std::size_t i = 0; i < _basis.size(); ++i)
  {
    if (_data[i][res.horIndex] > mpq_class(0))
    {
      _isExistSolution = true;
      break;
    }
  }

  if (!_isExistSolution)
    return { 0, 0, mpq_class(0) };

  bool isFirst = true;
  for (std::size_t i = 0; i < _basis.size(); ++i)
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
        if (cmpVal < res.resolutionVal)
        {
          res.vertIndex = i;
          res.resolutionVal = cmpVal;
        }
      }
    }
  }

  res.resolutionVal = _data[res.vertIndex][res.horIndex];
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
void SimplexTable::_simplexMethod(const ResolutionElement& resolElem)
{
  _swapBasic(resolElem);
  SimplexTableData oldData = _data;

  for (std::size_t i = 0; i < _data.size(); ++i)
  {
    for (std::size_t j = 0; j < _data[i].size(); ++j)
    {
      if (i == resolElem.vertIndex && j == resolElem.horIndex)
        _data[i][j] = mpq_class(1) / oldData[i][j];
      else if (i == resolElem.vertIndex)
        _data[i][j] = oldData[i][j] / resolElem.resolutionVal;
      else if (j == resolElem.horIndex)
        _data[i][j] = mpq_class(-1) * (oldData[i][j] / resolElem.resolutionVal);
      else
        _data[i][j] = (resolElem.resolutionVal * oldData[i][j] -
          oldData[resolElem.vertIndex][j] * oldData[i][resolElem.horIndex]) /
            resolElem.resolutionVal;
    }
  }

  for (std::size_t i = 0; i < _notBasis.size(); ++i)
  {
    auto it = std::find(_basis.begin(), _basis.end(), i);
    if (it != _basis.end())
      _solutionVars[i] = _data[std::distance(_basis.begin(), it)].back();
    else
      _solutionVars[i] = mpq_class(0);
  }
}
/*============================================================================*/
bool SimplexTable::_hasNegativeAbsoluteTerms() const
{
  for (std::size_t i = 0; i < _basis.size(); ++i)
    if (_data[i].back() < mpq_class(0))
      return true;

  return false;
}
/*============================================================================*/
bool SimplexTable::_isOptimalSolution() const
{
  bool res = true;

  for (std::size_t i = 0; i < _notBasis.size(); ++i)
  {
    if (_data.back()[i] < mpq_class(0))
    {
      res = false;
      break;
    }
  }

  return res;
}
/*============================================================================*/
void SimplexTable::DualSimplexMethod()
{
  ResolutionElement res;

  while (_hasNegativeAbsoluteTerms() && _isExistSolution)
  {
    res = _getResolutionElementDual();

    if (_isExistSolution)
      _simplexMethod(res);
  }
}
/*============================================================================*/
void SimplexTable::SimpleSimplexMethod()
{
  ResolutionElement res;

  while (!_isOptimalSolution() && _isExistSolution)
  {
    res = _getResolutionElement();

    if (_isExistSolution)
      _simplexMethod(res);
  }
}
/*============================================================================*/
void SimplexTable::Rebuild()
{
  DualSimplexMethod();
  SimpleSimplexMethod();
}
/*============================================================================*/
void SimplexTable::AddRow(
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
void SimplexTable::InvertRow(
  unsigned int index)
{
  for (std::size_t i = 0; i < _data[index].size(); ++i)
    _data[index][i] = mpq_class(-1) * _data[index][i];
}
/*============================================================================*/
bool SimplexTable::isIntSolution() const
{
  bool res = true;

  for (std::size_t i = 0; i < _solutionVars.size(); ++i)
    if (1 != _solutionVars[i].get_den())
      res &= false;

  return res;
}
/*============================================================================*/
std::ostream& operator<<(
  std::ostream& stream,
  const SimplexTable& table)
{
  for (std::size_t i = 0; i < table._data.back().size() + 1; ++i)
    stream << " ===============";

  stream << "\n|               |";

  for (std::size_t i = 0; i < table._notBasis.size(); ++i)
  {
    std::string x = ("X");
    x += std::to_string(table._notBasis[i] + 1);
    stream << std::setw(15) << std::right << x << "|";
  }

  stream << std::setw(17) << std::right << "B|\n";

  for (std::size_t i = 0; i < table._data.back().size() + 1; ++i)
    stream << " ===============";

  stream << "\n|";

  for (std::size_t i = 0; i < table._basis.size(); ++i)
  {
    stream << std::setw(14) << "X" << table._basis[i] + 1 << "|";

    for (std::size_t j = 0; j < table._data[i].size(); ++j)
      stream << std::setw(15) << table._data[i][j] << "|";

    stream << "\n";

    for (std::size_t i = 0; i < table._data.back().size() + 1; ++i)
      stream << " ===============";

    stream << "\n|";
  }

  stream << std::setw(16) << "F|";

  for (std::size_t i = 0; i < table.GetData().back().size(); ++i)
    stream << std::setw(15) << table._data.back()[i] << "|";

  stream << "\n";
  for (std::size_t i = 0; i < table._data.back().size() + 1; ++i)
    stream << " ===============";

  stream << "\n";

  return stream;
}
/*============================================================================*/