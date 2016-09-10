/**
 * @file AllTests.cpp
 *
 * @brief Main entry point for unit tests.
 *
 * @author C. Smith
 */
#include <CppUTest/CommandLineTestRunner.h>

int main(int ac, char** av)
{
  return CommandLineTestRunner::RunAllTests(ac, av);
}
