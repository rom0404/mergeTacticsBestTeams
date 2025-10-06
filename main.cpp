#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;
map<string, int> bestTeamsTroop;
const int twoWeight = 2;
const int fourWeight = 4;
map<string, int> traits = {
    {"noble", 1},
    {"jug", 2},
    {"clan", 3},
    {"ranger", 4},
    {"goblin", 5},
    {"assassin", 6},
    {"blaster", 7},
    {"brawler", 8},
    {"undead", 9},
    {"fire", 10},
    {"mage", 11},
    {"avenger", 12},
    {"ace", 13},
    {"electric", 14}};

struct Troop
{
    string name;
    int trait1;
    int trait2;
};

vector<Troop> troops = {

    {"knight", 1, 2},
    {"archer", 3, 4},
    {"goblin", 5, 6},
    {"sgob", 5, 7},
    {"barb", 3, 8},
    {"sdrags", 9, 4},
    {"wizard", 10, 11},
    {"musketeer", 7, 1},
    {"valk", 2, 3},
    {"pekka", 13, 12},
    {"prince", 1, 8},
    {"gskeleton", 8, 9},
    {"dgoblin", 5, 4},
    {"egiant", 14, 12},
    {"exe", 7, 13},
    {"witch", 9, 12},
    {"babyd", 10, 7},
    {"princess", 1, 4},
    {"ewiz", 14, 11},
    {"megaknight", 13, 8},
    {"ghost", 6, 9},
    {"bandit", 6, 13},
    {"gmachine", 5, 2},
    {"sking", 9, 2},
    {"goldenknight", 6, 1},
    {"queen", 3, 12},
};

// Generate all possible teams of given size from a vector of troops
vector<vector<Troop>> generateTeams(const vector<Troop> &troops, int teamSize)
{
    vector<vector<Troop>> teams;
    int n = troops.size();
    vector<bool> select(n, false);
    fill(select.end() - teamSize, select.end(), true);

    do
    {
        vector<Troop> team;
        for (int i = 0; i < n; ++i)
        {
            if (select[i])
                team.push_back(troops[i]);
        }
        teams.push_back(team);
    } while (next_permutation(select.begin(), select.end()));
    return teams;
}

// Grade a team according to trait rules
int gradeTeam(const vector<Troop> &team)
{
    map<int, int> traitCounts;
    for (const Troop &t : team)
    {
        traitCounts[t.trait1]++;
        traitCounts[t.trait2]++;
    }
    int score = 0;

    for (int i = 1; i < 15; i++)
    {
        if (traitCounts[i] == 2 || traitCounts[i] == 3)
        {

            score += twoWeight;
        }
        else if (traitCounts[i] == 4 || traitCounts[i] == 5)
        {
            score += fourWeight;
        }
    }

    return score;
}

bool cmp(pair<string, int> &a,
         pair<string, int> &b)
{
    return a.second < b.second;
}

// Function to sort the map according
// to value in a (key-value) pairs
void sort(map<string, int> &M)
{

    // Declare vector of pairs
    vector<pair<string, int>> A;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto &it : M)
    {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    // Print the sorted value
    for (auto &it : A)
    {

        cout << it.first << ' '
             << it.second << endl;
    }
}

void mostCommonTroops(vector<vector<Troop>> &teams)
{
    for (const auto &team : teams)
    {
        for (const auto &troop : team)
        {
            bestTeamsTroop[troop.name]++;
        }
    }

    sort(bestTeamsTroop);
}

// Given all teams, return those with the best score
vector<vector<Troop>> filterBestTeams(const vector<vector<Troop>> &teams)
{
    int bestScore = -1;
    vector<vector<Troop>> bestTeams;
    for (const auto &team : teams)
    {
        int score = gradeTeam(team);
        if (score > bestScore)
        {
            bestScore = score;
            bestTeams.clear();
            bestTeams.push_back(team);
        }
        else if (score == bestScore)
        {
            bestTeams.push_back(team);
        }
    }
    return bestTeams;
}

// Example usage
int main()
{
    int teamSize = 6;

    auto allTeams = generateTeams(troops, teamSize);
    auto bestTeams = filterBestTeams(allTeams);

    cout << "Number of best teams: " << bestTeams.size() << endl;
    for (const auto &team : bestTeams)
    {
        cout << "Team: ";
        for (const auto &troop : team)
        {
            cout << troop.name << " ";
        }
        cout << "\nScore: " << gradeTeam(team) << endl;
    }

    cout << "\n\n";
    mostCommonTroops(bestTeams);
    return 0;
}
