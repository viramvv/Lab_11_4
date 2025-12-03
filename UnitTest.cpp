#include "lab_11_4.h" // Підключаємо наш заголовний файл
#include "gtest/gtest.h" // Підключаємо Google Test
#include <vector>
#include <cmath>
#include <limits>

// Використовуємо Test Suite для тестування функції CalculateMeans
namespace {

// Тест 1: Перевірка коректності обчислення Середнього Арифметичного (AM)
TEST(CalculateMeansTest, ArithmeticMean) {
    vector<double> numbers = {10.0, 20.0, 30.0, 40.0};
    LineStats stats = CalculateMeans(numbers);

    // Очікуване середнє арифметичне: (10+20+30+40)/4 = 25.0
    // Використовуємо EXPECT_NEAR для порівняння чисел з плаваючою комою
    EXPECT_NEAR(stats.arithmeticMean, 25.0, 0.0001);
}

// Тест 2: Перевірка коректності обчислення Середнього Геометричного (GM)
TEST(CalculateMeansTest, GeometricMean) {
    vector<double> numbers = {2.0, 4.0, 8.0};
    LineStats stats = CalculateMeans(numbers);

    // Очікуване середнє геометричне: (2*4*8)^(1/3) = 64^(1/3) = 4.0
    EXPECT_NEAR(stats.geometricMean, 4.0, 0.0001);
}

// Тест 3: Перевірка порожнього вектора
TEST(CalculateMeansTest, EmptyVector) {
    vector<double> numbers = {};
    LineStats stats = CalculateMeans(numbers);

    // Повинні повернути 0.0
    EXPECT_NEAR(stats.arithmeticMean, 0.0, 0.0001);
    EXPECT_NEAR(stats.geometricMean, 0.0, 0.0001);
}

// Тест 4: Перевірка наявності від'ємних/нульових чисел (GM має бути 0)
TEST(CalculateMeansTest, NegativeOrZeroCheck) {
    vector<double> numbers_zero = {1.0, 2.0, 0.0, 4.0};
    LineStats stats_zero = CalculateMeans(numbers_zero);

    // Середнє геометричне не визначене/повинно бути 0
    EXPECT_NEAR(stats_zero.geometricMean, 0.0, 0.0001);

    vector<double> numbers_negative = {1.0, 2.0, -3.0, 4.0};
    LineStats stats_negative = CalculateMeans(numbers_negative);

    // Середнє геометричне не визначене/повинно бути 0
    EXPECT_NEAR(stats_negative.geometricMean, 0.0, 0.0001);
}

// Тест 5: Перевірка з одним числом
TEST(CalculateMeansTest, SingleNumber) {
    vector<double> numbers = {7.7};
    LineStats stats = CalculateMeans(numbers);

    // AM і GM повинні дорівнювати самому числу
    EXPECT_NEAR(stats.arithmeticMean, 7.7, 0.0001);
    EXPECT_NEAR(stats.geometricMean, 7.7, 0.0001);
}

} // end namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}