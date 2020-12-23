#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream file;
    // file.open("testing6.txt");
    file.open("customsQuestions.txt");

    unordered_map<char, int> questionsAsked;

    int partOne = 0, partTwo = 0;
    int totalAskedGroup = 0, totalPeopleGroup = 0;
    string line;
    while (getline(file, line)) {
        if (!line.length()) {
            // Found next batch of questions
            partOne += totalAskedGroup;

            // Find the total questions that were answered by all
            int totalAllAns = 0;
            for (auto kv : questionsAsked) {
                // cout << kv.first << " " << kv.second << endl;
                if (kv.second == totalPeopleGroup) totalAllAns++;
            }
            partTwo += totalAllAns;
            // cout << "Total People: " << totalPeopleGroup << "; Part 1 > " << totalAskedGroup << "; Part 2 > " << totalAllAns << endl << endl;

            // New batch of questions for new group
            questionsAsked.clear();
            totalAskedGroup = 0, totalPeopleGroup = 0;
        } else {
            // Still on current batch of questions
            // Loop through the current line
            totalPeopleGroup++;
            for (auto c : line) {
                // If question hasn't been asked add it to list
                if (questionsAsked.find(c) == questionsAsked.end()) {
                    totalAskedGroup++;
                    questionsAsked.insert(make_pair(c, 1));
                } else {
                    questionsAsked[c] = questionsAsked[c] + 1;
                }
            }
        }
    }

    partOne += totalAskedGroup;

    int totalAllAns = 0;
    for (auto kv : questionsAsked) {
        // cout << kv.first << " " << kv.second << endl;
        if (kv.second == totalPeopleGroup) totalAllAns++;
    }
    partTwo += totalAllAns;
    // cout << "Total People: " << totalPeopleGroup << "; Part 1 > " << totalAskedGroup << "; Part 2 > " << totalAllAns << endl << endl;

    cout << "Part 1 Total: > " << partOne << endl;
    cout << "Part 2 Total: > " << partTwo << endl;

    file.close();
    return 0;
}
