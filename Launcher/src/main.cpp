#include <SimplexMethod/SimplexTable.h>
#include <GomoryAlgorithm/GomoryAlgorithm.h>
#include <SimplexMethod/Utils.h>
/*============================================================================*/
#include <iostream>
/*============================================================================*/
int main()
{
  std::vector<SimplexTableElement*> data;
  std::vector<Point> points =
  {
    { mpq_class(0), mpq_class(83, 10) },
    { mpq_class(113, 10), mpq_class(172, 10) },
    { mpq_class(83, 10), mpq_class(0) },
    { mpq_class(1), mpq_class(5) },
    { mpq_class(3), mpq_class(1) }
  };

  //std::vector<Point> points =
  //{
  //  { mpq_class(76, 10), mpq_class(0) },
  //  { mpq_class(0), mpq_class(51, 10) },
  //  { mpq_class(121, 10), mpq_class(91, 10) },
  //  { mpq_class(171, 10), mpq_class(0) },
  //  { mpq_class(2), mpq_class(1) },
  //  { mpq_class(3), mpq_class(8) }
  //};

  data = CreateSimplexTableDataFromPoints(data, points);

  SimplexTable table(2, 3, data);
  std::cout << table << std::endl;

  GomoryAlgorithm gomory(table);
  std::cout << gomory.GetTable() << std::endl;

  return 0;
}
/*============================================================================*/