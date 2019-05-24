#ifndef SIMPLEX_TABLE_ROW_H
#define SIMPLEX_TABLE_ROW_H
/*============================================================================*/
#include <mpir.h>
#include <mpirxx.h>
/*============================================================================*/
#include <vector>
/*============================================================================*/
typedef std::vector<mpq_class> SimplexTableRowData;
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