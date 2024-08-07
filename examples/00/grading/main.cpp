#include "gradecalculator.hh"
#include <iostream>

using namespace std;

// Informs about invalid (too big) N, G, and P points.
// Returns true, if all these three points are valid, otherwise returns false.
bool is_valid_points(unsigned int n,
                     unsigned int p1,
                     unsigned int p2,
                     unsigned int b)
{
    bool is_valid = true;
    if( n > MAX_N_POINTS )
    {
        cout << "Impossible N points" << endl;
        is_valid = false;
    }
    if( p1 > MAX_P_POINTS_PER_PROJECT or p2 > MAX_P_POINTS_PER_PROJECT )
    {
        cout << "Impossible P points" << endl;
        is_valid = false;
    }
    if( b > MAX_B_POINTS )
    {
        cout << "Impossible B points" << endl;
        is_valid = false;
    }
    return is_valid;
}

// Informs about invalid (too big) exam grade.
// Returns true, if the given exam grade is valid, otherwise returns false.
bool is_valid_exam(unsigned int e)
{
    if( e > 5 )
    {
        cout << "Impossible exam grade" << endl;
        return false;
    }
    return true;
}

// Main function.
// Asks first for N, G, and P points, and if all these points are valid,
// prints scores from weekly exercises and projects, and asks for exam grade.
// If also the given exam grade is valid, prints the total grade.
int main()
{
    cout << print_constants() << endl << endl;
    unsigned int n = 0;
    unsigned int p1 = 0;
    unsigned int p2 = 0;
    unsigned int b = 0;
    unsigned int e = 0;
    cout << "Enter N points, P1 points, P2 points, B points: ";
    cin >> n;
    cin >> p1;
    cin >> p2;
    cin >> b;

    if( is_valid_points(n, p1, p2, b) )
    {
        cout << "-> Score from weekly exercises: " << score_from_weekly_exercises(n + b) << endl;
        cout << "-> Score from projects:         " << score_from_projects(p1, p2) << endl;

        cout << "Enter exam grade (if no exam, enter zero): ";
        cin >> e;

        if( is_valid_exam(e) )
        {
            cout << "-> Total grade: " << calculate_total_grade(n, p1, p2, e)
                 << endl;
        }
    }

    return 0;
}

