#include "../matrix.hpp"
#include "gtest/gtest.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

// i remember point about equality of doubles
// but i haven't come around to learn how to do it correctly yet
// i will do it at some point i promise...
TEST(matrix, vector_constructor) {
  vector<double> vec{1.0, 2.0, 3.0, 4.0};
  SqMatrix m(vec);
  EXPECT_EQ(m[1][2], 0);
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(m[i][i], vec[i]);
  }
}

TEST(matrix, sum) {
  vector<double> vec{1.0, 2.0, 3.0, 4.0};
  vector<double> vec2{2.0, 3.0, 4.0, 5.0};
  vector<double> vec3{3.0, 5.0, 7.0, 9.0};
  SqMatrix m(vec);
  SqMatrix m2(vec2);
  SqMatrix m3 = m + m2;
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(m3[i][i], vec3[i]);
  }
}

TEST(matrix, eqsum) {
  vector<double> vec{1.0, 2.0, 3.0, 4.0};
  vector<double> vec2{2.0, 3.0, 4.0, 5.0};
  vector<double> vec3{3.0, 5.0, 7.0, 9.0};
  SqMatrix m(vec);
  SqMatrix m2(vec2);
  SqMatrix m3 = m + m2;
  SqMatrix m4 = m;
  m4 += m2;
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(m3[i][i], vec3[i]);
  }
  for (size_t i = 0; i < vec.size(); ++i) {
    for (size_t j = 0; j < vec.size(); ++j) {
      EXPECT_EQ(m4[i][j], m3[i][j]);
    }
  }
  EXPECT_EQ(m3, m4);
}

TEST(matrix, prod) {
  vector<double> vec{1.0, 2.0, 3.0, 4.0};
  vector<double> vec2{2.0, 3.0, 4.0, 5.0};
  vector<double> vec3{2.0, 6.0, 12.0, 20.0};
  SqMatrix m(vec);
  SqMatrix m2(vec2);
  SqMatrix m3 = m * m2;
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(m3[i][i], vec3[i]);
  }
}

TEST(matrix, eqprod) {
  vector<double> vec{1.0, 2.0, 3.0, 4.0};
  vector<double> vec2{2.0, 3.0, 4.0, 5.0};
  vector<double> vec3{2.0, 6.0, 12.0, 20.0};
  SqMatrix m(vec);
  SqMatrix m2(vec2);
  SqMatrix m3 = m * m2;
  SqMatrix m4(m);
  m4 *= m2;
  for (size_t i = 0; i < vec.size(); ++i) {
    for (size_t j = 0; j < vec.size(); ++j) {
      EXPECT_EQ(m3[i][j], m4[i][j]);
    }
  }
  EXPECT_EQ(m4, m3);
}

TEST(matrix, prodscalar) {
  vector<double> vec{1.0, 2.0, 3.0, 4.0};
  SqMatrix m(vec);
  m = m * 2;
  for (size_t i = 0; i < vec.size(); ++i) {
    m[i][i] = 2 * vec[i];
  }
}

TEST(matrix, eqprodscalar) {
  vector<double> vec{1.0, 2.0, 3.0, 4.0};
  SqMatrix m(vec);
  m *= 2;
  for (size_t i = 0; i < vec.size(); ++i) {
    m[i][i] = 2 * vec[i];
  }
}

TEST(matrix, cast) {
  vector<double> vec{1.0, 2.0, 3.0, 4.0};
  SqMatrix m(vec);
  double casted = (double)m;
  EXPECT_EQ(casted, 10);
}

TEST(matrix, cast2) {
  vector<double> vec{1.0, 2.0, 3.0, 4.0};
  SqMatrix m(vec);
  double casted = (double)m;
  SqMatrix testMatrix = m + vec;
  EXPECT_EQ(casted, 10);
}

TEST(review, reviewTest1) {
  vector<double> vec{1.0, 2.0, 3.0, 4.0};
  SqMatrix m(vec);
  SqMatrix testMatrix = m + vec;
  SqMatrix testMatrix2 = vec + m;
  EXPECT_EQ(testMatrix, testMatrix2);
}
