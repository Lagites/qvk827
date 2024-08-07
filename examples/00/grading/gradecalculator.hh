#ifndef GRADECALCULATOR_HH
#define GRADECALCULATOR_HH

#include <string>

// The constant values below are valid at the beginning of the course.
// At the end of the course, if you use this program to calculate your total
// grade, check the values and update them identical with those in Plussa,
// if needed.
const unsigned int MAX_P_POINTS_PER_PROJECT = 50;
const unsigned int MAX_P_POINTS = 2 * MAX_P_POINTS_PER_PROJECT;
const unsigned int MAX_N_POINTS = 670;
const unsigned int MAX_M_POINTS = 60;
const unsigned int MAX_B_POINTS = 10;

// Calculates the total grade by calling the other functions below.
unsigned int calculate_total_grade(unsigned int n, unsigned int p1,
                                   unsigned int p2, unsigned int e);

// Calculates score from weekly exercises.
unsigned int score_from_weekly_exercises(unsigned int n);

// Calculates score from projects.
unsigned int score_from_projects(unsigned int p1, unsigned int p2);

// Prints the values of the constants used in calculations to a string and
// returns the string.
std::string print_constants();

#endif // GRADECALCULATOR_HH
