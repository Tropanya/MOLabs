#include <SimplexMethod/SimplexTable.h>
#include <GomoryAlgorithm/GomoryAlgorithm.h>
#include <SimplexMethod/Utils.h>
/*============================================================================*/
#include <iostream>
/*============================================================================*/
int main()
{
  //std::vector<Point> points =
  //{
  //  {  7.6f,  0.0f },
  //  {  0.0f,  5.1f },
  //  { 12.1f,  9.1f },
  //  { 17.1f,  0.0f },
  //  {  2.0f,  1.0f },
  //  {  3.0f,  8.0f }
  //};

  std::vector<SimplexTableElement*> data;
  std::vector<Point> points =
  {
    { mpq_class(0), mpq_class(83, 10) },
    { mpq_class(113, 10), mpq_class(172, 10) },
    { mpq_class(83, 10), mpq_class(0) },
    { mpq_class(1), mpq_class(5) },
    { mpq_class(3), mpq_class(1) }
  };

  data = CreateSimplexTableDataFromPoints(data, points);

  SimplexTable table(2, 3, data);
  std::cout << table << std::endl;

  GomoryAlgorithm gomory(table);
  std::cout << table << std::endl;

  return 0;
}
/*============================================================================*/