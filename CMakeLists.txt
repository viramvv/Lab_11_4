# Встановлюємо сучасну мінімальну версію CMake для сумісності з Google Test
cmake_minimum_required(VERSION 3.14)

# Ініціалізуємо проєкт
project(Lab_11_4 CXX)

# Встановлення стандарту C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ----------------------------------------------------
# Створення цільової бібліотеки для нашої логіки
# ----------------------------------------------------
# Це гарантує, що код lab_11_4.cpp буде скомпільований лише один раз
# і буде доступний як для основної програми, так і для тестів.
add_library(lab_11_4_logic lab_11_4.cpp)

# ----------------------------------------------------
# 1. Створення основного виконуваного файлу (коду)
# ----------------------------------------------------
add_executable(Lab_11_4_App
        main.cpp
)
# Прив'язуємо основну програму до нашої бібліотеки логіки
target_link_libraries(Lab_11_4_App PRIVATE lab_11_4_logic)

# ----------------------------------------------------
# 2. Налаштування Google Test для юніт-тестів
# ----------------------------------------------------

# Використовуємо FetchContent для завантаження Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# ----------------------------------------------------
# 3. Створення виконуваного файлу для тестів
# ----------------------------------------------------

# Виконавчий файл для тестування.
add_executable(UnitTest
        UnitTest.cpp
)

# Підключення: Тести (UnitTest) повинні бути пов'язані з Google Test та нашою логікою
target_link_libraries(UnitTest
        PRIVATE
        GTest::gtest_main
        lab_11_4_logic
)