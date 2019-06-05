#ifndef SIMPLEX_TABLE_ROW_H
#define SIMPLEX_TABLE_ROW_H
/*============================================================================*/
#include <SimplexMethod/Element.h>
/*============================================================================*/
#include <vector>
/*============================================================================*/
typedef std::vector<Element> SimplexTableRowData;
/*============================================================================*/
class SimplexTableRow
{
protected:
  SimplexTableRowData _data;
private:
  virtual void _toCanonical() {  };
public:
  SimplexTableRow(
    const SimplexTableRowData& data);
  virtual ~SimplexTableRow();

  inline const SimplexTableRowData& GetData() const { return _data; }
};
/*============================================================================*/
#endif // SIMPLEX_TABLE_ROW_H