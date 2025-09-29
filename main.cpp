#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

// Troop as a struct
struct Troop {
    std::string name;
    int trait1;
    int trait2;
};


vector<Troop> initalizeTroops() {
    std::vector<Troop> troops = {

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

    return troops;
}

// Generate all possible teams of given size from a vector of troops
std::vector<std::vector<Troop>> generateTeams(const std::vector<Troop>& troops, int teamSize) {
    std::vector<std::vector<Troop>> teams;
    int n = troops.size();
    std::vector<bool> select(n, false);
    std::fill(select.end() - teamSize, select.end(), true);

    do {
        std::vector<Troop> team;
        for (int i = 0; i < n; ++i) {
            if (select[i]) team.push_back(troops[i]);
        }
        teams.push_back(team);
    } while (std::next_permutation(select.begin(), select.end()));
    return teams;
}

// Grade a team according to trait rules
int gradeTeam(const std::vector<Troop>& team) {
    std::map<int, int> traitCounts;
    for (const Troop& t : team) {
        traitCounts[t.trait1]++;
        traitCounts[t.trait2]++;
    }
    //remove goblin trait
    traitCounts[5] = 0;
    int score = 0;
    
    for (int i = 1; i < 15; i++)
    {
        if (traitCounts[i]==2 || traitCounts[i]==3)
        {
            score += 2;
        } else if (traitCounts[i] == 4 || traitCounts[i] == 5)
        {
            score += 4;
        }
    }

    return score;
}

// Given all teams, return those with the best score
std::vector<std::vector<Troop>> filterBestTeams(const std::vector<std::vector<Troop>>& teams) {
    int bestScore = -1;
    std::vector<std::vector<Troop>> bestTeams;
    for (const auto& team : teams) {
        int score = gradeTeam(team);
        if (score > bestScore) {
            bestScore = score;
            bestTeams.clear();
            bestTeams.push_back(team);
        }
        else if (score == bestScore) {
            bestTeams.push_back(team);
        }
    }
    return bestTeams;
}

// Example usage
int main() {
    vector<Troop> troops = initalizeTroops();

    int teamSize = 6;

    auto allTeams = generateTeams(troops, teamSize);
    auto bestTeams = filterBestTeams(allTeams);

    std::cout << "Number of best teams: " << bestTeams.size() << std::endl;
    for (const auto& team : bestTeams) {
        std::cout << "Team: ";
        for (const auto& troop : team) {
            std::cout << troop.name << " ";
        }
        std::cout << "\nScore: " << gradeTeam(team) << std::endl;
    }
    return 0;
}

//trait decoding

/*
1 noble
2 jug
3 clan
4 ranger
5 goblin
6 assassin
7 blaster
8 brawler
9 undead
10 fire
11 mage
12 avenger
13 ace
14 electric
*/