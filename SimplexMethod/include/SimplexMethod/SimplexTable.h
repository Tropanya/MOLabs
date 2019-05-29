#ifndef SIMPLEX_TABLE_H
#define SIMPLEX_TABLE_H
/*============================================================================*/
#include <SimplexMethod/SimplexTableRow.h>
/*============================================================================*/
typedef std::vector<SimplexTableRowData> SimplexTableData;
typedef std::vector<unsigned int> VarIndices;
/*============================================================================*/
struct ResolutionElement
{
  unsigned int vertIndex;
  unsigned int horIndex;
  Element resolutionVal;
};
/*============================================================================*/
class SimplexTable
{
private:
  mutable bool _isExistSolution;

  VarIndices _basis;
  VarIndices _notBasis;

  std::vector<Element> _targetFuncVars;
  std::vector<Element> _solutionVars;

  SimplexTableData _data;
private:
  void _fillTable(
    const std::vector<SimplexTableRow*>& data);
  ResolutionElement _getResolutionElementDual() const;
  ResolutionElement _getResolutionElement() const;
  void _swapBasic(
    const ResolutionElement& resolution);
  void _simplexMethod(
    const ResolutionElement& resolElem);
  bool _hasNegativeAbsoluteTerms() const;
  bool _isOptimalSolution() const;
public:
  SimplexTable(
    unsigned int variableCount,
    unsigned int restrictionCount,
    const std::vector<SimplexTableRow*>& data);

  void DualSimplexMethod();
  void SimpleSimplexMethod();
  void Rebuild();
  void AddRow(
    SimplexTableRow* element);

  void InvertRow(
    unsigned int index);

  Element ComputeTargetFunc() const;
  bool isIntSolution() const;

  inline unsigned int GetRestrictionCount() const { return _basis.size(); }
  inline const std::vector<Element> GetSolutionVars() const
  { return _solutionVars; }

  inline const VarIndices& GetBasic() const { return _basis; }
  inline const VarIndices& GetNotBasic() const { return _notBasis; }
  inline const std::vector<Element> GetRaw(
    unsigned int index) const { return _data[index]; }
  inline const SimplexTableData& GetData() const { return _data; }
  inline bool isExistSolution() const { return _isExistSolution; }

  friend std::ostream& operator<<(
    std::ostream& stream,
    const SimplexTable& table);
};
/*============================================================================*/
#endif // SIMPLEX_TABLE_H