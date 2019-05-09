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
  std::vector<unsigned int> _basis;
  std::vector<unsigned int> _notBasis;

  SimplexTableData _data;
private:
  void _fillTable(const std::vector<SimplexTableElement*>& data);
  ResolutionElement _getResolutionElement() const;
  void _swapBasic(const ResolutionElement& resolution);
  void _rebuildTable();
public:
  SimplexTable(unsigned int variableCount, unsigned int restrictionCount,
               const std::vector<SimplexTableElement*>& data);

  inline const SimplexTableData& GetData() const { return _data; }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const SimplexTable& table);
};
/*============================================================================*/
#endif // SIMPLEX_TABLE_H