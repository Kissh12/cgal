#include "include/Saver.h"
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Shape_regularization/regularize_contours.h>

namespace SR = CGAL::Shape_regularization;

template<class Traits>
void test_closed_contour_6_edges() {

  using FT      = typename Traits::FT;
  using Point_2 = typename Traits::Point_2;
  using Contour = std::vector<Point_2>;
  using Saver   = SR::Tests::Saver<Traits>;

  using CD = SR::Contours::Longest_direction_2<Traits, Contour>;

  Saver saver;
  const Contour contour = {
    Point_2(0, 0), Point_2(  FT(5) / FT(10), -FT(1) / FT(20)),
    Point_2(1, 0), Point_2(FT(105) / FT(100), FT(5) / FT(10)),
    Point_2(1, 1), Point_2(0, 1)
  };
  assert(contour.size() == 6);

  // saver.export_closed_contour(contour, "cl6_input", 100);

  const bool is_closed = true;
  CD directions(contour, is_closed);

  std::vector<Point_2> regularized;
  SR::Contours::regularize_closed_contour(
    contour, directions, std::back_inserter(regularized),
    CGAL::parameters::all_default());

  const std::size_t num_directions =
    directions.number_of_directions();

  // saver.export_closed_contour(regularized, "cl6_output", 100);

  assert(num_directions == 1);
  assert(regularized.size() == 4);
}

int main() {
  test_closed_contour_6_edges< CGAL::Simple_cartesian<double> >();
  test_closed_contour_6_edges< CGAL::Exact_predicates_inexact_constructions_kernel >();
  test_closed_contour_6_edges< CGAL::Exact_predicates_exact_constructions_kernel >();
  std::cout << "test_closed_contour_6_edges: SUCCESS" << std::endl;
  return EXIT_SUCCESS;
}
