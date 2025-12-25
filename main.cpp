#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
#include <tuple>

// Trait constants
const int noble = 1;
const int clan = 2;
const int ranger = 3;
const int goblin = 4;
const int assassin = 5;
const int blaster = 6;
const int brawler = 7;
const int undead = 8;
const int ace = 9;
const int brutalist = 10;
const int giant = 11;
const int superstar = 12;
const int pekka_trait = 13;

// Scoring constants
const int score_trait_2 = 2;
const int score_trait_4 = 6;
const int score_trait_6 = 12;

// Trait score map: Key = trait ID, Value = {score for 2 units, score for 4 units, score for 6 units}
std::map<int, std::tuple<int, int, int>> traitScores;

// Trait name map
std::map<int, std::string> traitNames = {
    {noble, "noble"},
    {clan, "clan"},
    {ranger, "ranger"},
    {goblin, "goblin"},
    {assassin, "assassin"},
    {blaster, "blaster"},
    {brawler, "brawler"},
    {undead, "undead"},
    {ace, "ace"},
    {brutalist, "brutalist"},
    {giant, "giant"},
    {superstar, "superstar"},
    {pekka_trait, "pekka_trait"}
};

// Troop as a struct
struct Troop {
    std::string name;
    int trait1;
    int trait2;
    int elixirCost;
};

// Function declarations
void initializeScores();
void setTraitScore(int trait, int s2, int s4, int s6);
std::vector<Troop> initalizeTroops();
std::vector<std::vector<Troop>> generateTeams(const std::vector<Troop>& troops, int teamSize);
int gradeTeam(const std::vector<Troop>& team);
int calculateTeamCost(const std::vector<Troop>& team);
std::vector<std::vector<Troop>> filterBestTeams(const std::vector<std::vector<Troop>>& teams);


int main() {
    initializeScores();
    vector<Troop> troops = initalizeTroops();

    int teamSize = 6;
    // setTraitScore(giant, score_trait_2+1, score_trait_4, score_trait_6);

    auto allTeams = generateTeams(troops, teamSize);
    auto bestTeams = filterBestTeams(allTeams);

    // Sort by elixir cost ascending
    std::sort(bestTeams.begin(), bestTeams.end(), [](const std::vector<Troop>& a, const std::vector<Troop>& b) {
        return calculateTeamCost(a) < calculateTeamCost(b);
    });

    std::cout << "Number of best teams: " << bestTeams.size() << std::endl;
    for (const auto& team : bestTeams) {
        std::cout << "Team: ";
        for (const auto& troop : team) {
            std::cout << troop.name << "(" << troop.elixirCost << ") ";
        }
        std::cout << "\nTotal Cost: " << calculateTeamCost(team);
        std::cout << "\nScore: " << gradeTeam(team) << std::endl;
    }
    return 0;
}


// Function to set specific trait scores
void setTraitScore(int trait, int s2, int s4, int s6) {
    traitScores[trait] = std::make_tuple(s2, s4, s6);
}

// Initialize scores
void initializeScores() {
   for (int i = noble; i <= pekka_trait; i++) {
       traitScores[i] = std::make_tuple(score_trait_2, score_trait_4, score_trait_6);
   }
}

vector<Troop> initalizeTroops() {
    std::vector<Troop> troops = {
        {"Goblins", goblin, assassin, 2},
        {"Spear Goblins", goblin, blaster, 2},
        {"Barbarians", clan, brawler, 2},
        {"Skeleton Dragons", undead, ranger, 2},
        {"Wizard", clan, blaster, 2},
        {"Musketeer", superstar, noble, 3},
        {"Valkyrie", brutalist, clan, 3},
        {"P.E.K.K.A", pekka_trait, brawler, 4},
        {"Prince", noble, brawler, 3},
        {"Dart Goblin", goblin, ranger, 3},
        {"Electro Giant", giant, superstar, 5},
        {"Executioner", blaster, ace, 3},
        {"Witch", undead, superstar, 4},
        {"Princess", noble, blaster, 4},
        {"Mega Knight", ace, brawler, 5},
        {"Royal Ghost", assassin, undead, 4},
        {"Bandit", assassin, ace, 4},
        {"Goblin Machine", goblin, brutalist, 5},
        {"Skeleton King", undead, brutalist, 5},
        {"Golden Knight", assassin, noble, 5},
        {"Archer Queen", clan, ranger, 5},
        {"Royal Giant", giant, ranger, 2},
        {"Mini P.E.K.K.A", pekka_trait, brutalist, 2},
        {"Monk", ace, superstar, 5},
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
    traitCounts[goblin] = 0;
    int score = 0;

    for (int i = noble; i <= pekka_trait; i++)
    {
        int s2, s4, s6;
        std::tie(s2, s4, s6) = traitScores[i];

        if (traitCounts[i] >= 6)
        {
            score += s6;
        }
        else if (traitCounts[i] >= 4)
        {
            score += s4;
        }
        else if (traitCounts[i] >= 2)
        {
            score += s2;
        }
    }

    return score;
}

int calculateTeamCost(const std::vector<Troop>& team) {
    int cost = 0;
    for (const auto& troop : team) {
        cost += troop.elixirCost;
    }
    return cost;
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
