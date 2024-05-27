#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
    int P;  // Number of projects
    cin >> P;
    
    vector<int> mentees_required(P);  // Number of mentees required for each project
    for (int i = 0; i < P; ++i) {
        cin >> mentees_required[i];
    }
    
    int N;  // Total number of students
    cin >> N;
    
    vector<int> scores(N);  // Scores of the students
    
    for (int i = 0; i < N; ++i) {
        cin >> scores[i];
    }
  
    vector<vector<int>> preferences(N, vector<int>(P));  // Preferences of each student
    vector<tuple<int, int, vector<int>>> students;  // Tuple of (score, index, preference)
  
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < P; ++j) {
            cin >> preferences[i][j];
            preferences[i][j]--;  //  0-based indexing
        }
        // make a tuple with the student's score, index, and preferences, and add it to the students vector
        students.push_back(make_tuple(scores[i], i, preferences[i]));
    }
    
    // Sort students based on scores in descending order
    sort(students.rbegin(), students.rend());
    
    // Vector to track the number of students assigned to each project
    vector<int> assigned_count(P, 0);    // initialized with 0 as elements
    
    // Vector to store the result (student number, assigned project)
    vector<pair<int, int>> results;
    
    // Allocate students to projects based on their preferences and available slots
    for (const auto &student : students) {
        int score, index;
        vector<int> prefs;
        tie(score, index, prefs) = student;
        
        for (int pref : prefs) {
            if (assigned_count[pref] < mentees_required[pref]) {
                assigned_count[pref]++;
                results.push_back(make_pair(index + 1, pref + 1));  // again converting to 1-based index
                break;
            }
        }
    }
    
    // Sort results by student index to maintain the order of student allocation in ascending order
    sort(results.begin(), results.end());
    
    // Output the allocation results
    for (const auto &result : results) {
        cout << result.first << " " << result.second << endl;
    }

    return 0;
}
