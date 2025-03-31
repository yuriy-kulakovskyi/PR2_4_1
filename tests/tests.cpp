#include <gtest/gtest.h>
#include "../classes/Matrix.h"

TEST(Tests, PerimeterTest) {
  Matrix m1;
  m1.setSize(2);
  EXPECT_EQ(m1.getSize(), 2);
}