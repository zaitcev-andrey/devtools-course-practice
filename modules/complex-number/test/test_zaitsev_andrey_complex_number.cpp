// Copyright 2021 Zaitsev Andrey

#include <gtest/gtest.h>
#include <tuple>
#include "include/complex_number.h"

TEST(Zaitsev_Andrey_ComplexNumberTest, Double_check) {
  double re = 23.42;
  double im = 6.23;
  ComplexNumber num(re, im);

  ASSERT_EQ(num.getRe(), re);
  ASSERT_EQ(num.getIm(), im);
}

TEST(Zaitsev_Andrey_ComplexNumberTest, Arifm_Operations_Test) {
  double re1 = 12.0, re2 = 2.0, re3 = 8.0, re4 = 3.0;
  double im1 = 12.0, im2 = 2.0, im3 = 10.0, im4 = 4.0;
  ComplexNumber num1(re1, im1);
  ComplexNumber num2(re2, im2);
  ComplexNumber num3(re3, im3);
  ComplexNumber num4(re4, im4);

  ComplexNumber answer(66.0, 84.0);

  ComplexNumber result = (num1 / num2) * (num3 + num4);
  ASSERT_EQ(answer.getRe(), result.getRe());
  ASSERT_EQ(answer.getIm(), result.getIm());
}

typedef testing::TestWithParam<std::tuple<double, double, double, double>>
Zaitsev_Andrey_ComplexNumberTest_Param;

TEST_P(Zaitsev_Andrey_ComplexNumberTest_Param, Add_And_Sub_Operations_Test) {
  ComplexNumber num1(std::get<0>(GetParam()), std::get<1>(GetParam()));
  ComplexNumber num2(std::get<2>(GetParam()), std::get<3>(GetParam()));

  ComplexNumber res1 = num1 + num2;
  ComplexNumber res2 = num1 - num2;
  ComplexNumber res3 = res1 - res2;
  ComplexNumber answer = num2 + num2;

  ASSERT_EQ(res3, answer);
}

INSTANTIATE_TEST_CASE_P(/**/, Zaitsev_Andrey_ComplexNumberTest_Param,
  testing::Combine(
    testing::Values(10.0, 5.0),
    testing::Values(4.0, 8.0),
    testing::Values(7.0, 9.0),
    testing::Values(8.0, 12.0)));
