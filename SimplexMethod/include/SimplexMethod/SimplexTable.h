#ifndef SIMPLEX_TABLE_H
#define SIMPLEX_TABLE_H
/*============================================================================*/
#include <SimplexMethod/SimplexTableElement.h>
/*============================================================================*/
typedef std::vector<SimplexTableElementData> SimplexTableData;
/*============================================================================*/
struct ResolutionElement
{
  unsigned int vertIndex;
  unsigned int horIndex;
  mpq_class resolutionVal;
};
/*============================================================================*/
class SimplexTable
{
private:
  bool _isOptimal;

  std::vector<unsigned int> _basis;
  std::vector<unsigned int> _notBasis;

  std::vector<mpq_class> _solutionVars;

  SimplexTableData _data;
private:
  void _fillTable(
    const std::vector<SimplexTableElement*>& data);
  ResolutionElement _getResolutionElement() const;
  void _swapBasic(
    const ResolutionElement& resolution);
  bool _isOptimalSolution() const;
public:
  SimplexTable(
    unsigned int variableCount,
    unsigned int restrictionCount,
    const std::vector<SimplexTableElement*>& data);

  void RebuildTable(
    const ResolutionElement& resolution);
  void AddRaw(
    SimplexTableElement* element);

  void InvertRaw(
    unsigned int index);

  inline unsigned int GetVariableCount() const { return _notBasis.size(); }
  inline unsigned int GetRestrictionCount() const { return _basis.size(); }
  inline const std::vector<mpq_class> GetSolutionVars() const
  { return _solutionVars; }

  inline const std::vector<unsigned int>& GetBasic() const { return _basis; }
  inline const std::vector<mpq_class> GetRaw(
    unsigned int index) const { return _data[index]; }
  inline const SimplexTableData& GetData() const { return _data; }
  inline bool IsOptimal() const { return _isOptimal; }

  friend std::ostream& operator<<(
    std::ostream& stream,
    const SimplexTable& table);
};
/*============================================================================*/
#endif // SIMPLEX_TABLE_H