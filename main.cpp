#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <tuple>
using namespace std;
//=============================================================================
//===========MAIN FUNCTION AT LINE 140, GO THERE TO EDIT FILTERS===============
//=============================================================================



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

// ANSI Color Constants (Backgrounds)
const string ANSI_RESET = "\033[0m";
const string ANSI_BG_DARK_GREEN = "\033[48;5;22m";
const string ANSI_BG_RED = "\033[48;5;196m";
const string ANSI_BG_PURPLE = "\033[48;5;129m";
const string ANSI_BG_ORANGE = "\033[48;5;208m";
const string ANSI_BG_GREEN = "\033[48;5;46m";
const string ANSI_BG_CYAN = "\033[48;5;51m";
const string ANSI_BG_BLUE = "\033[48;5;21m";
const string ANSI_BG_BROWN = "\033[48;5;130m";
const string ANSI_BG_YELLOW = "\033[48;5;226m";
const string ANSI_BG_LIGHT_GREEN = "\033[48;5;119m";
const string ANSI_BG_LIGHT_ORANGE = "\033[48;5;215m";
const string ANSI_BG_PALE_RED = "\033[48;5;203m"; 
const string ANSI_BG_PINK = "\033[48;5;200m";
const string ANSI_BG_GOLD = "\033[43m"; // Replacing generic yellow with gold/yellow background

// Scoring constants
const int score_trait_2 = 2;
const int score_trait_4 = 6;
const int score_trait_6 = 12;

// Trait score map: Key = trait ID, Value = {score for 2 units, score for 4 units, score for 6 units}
map<int, tuple<int, int, int>> traitScores;

// Trait name map
map<int, string> traitNames = {
    {noble, "Noble"},
    {clan, "Clan"},
    {ranger, "Ranger"},
    {goblin, "Goblin"},
    {assassin, "Assassin"},
    {blaster, "Blaster"},
    {brawler, "Brawler"},
    {undead, "Undead"},
    {ace, "Ace"},
    {brutalist, "Brutalist"},
    {giant, "Giant"},
    {superstar, "Superstar"},
    {pekka_trait, "P.E.K.K.A"}
};

// Trait color map
map<int, string> traitColors = {
    {noble, ANSI_BG_GOLD},
    {clan, ANSI_BG_BLUE},
    {ranger, ANSI_BG_CYAN},
    {goblin, ANSI_BG_DARK_GREEN},
    {assassin, ANSI_BG_RED},
    {blaster, ANSI_BG_BROWN},
    {brawler, ANSI_BG_PALE_RED},
    {undead, ANSI_BG_CYAN},
    {ace, ANSI_BG_PURPLE},
    {brutalist, ANSI_BG_PALE_RED},
    {giant, ANSI_BG_YELLOW},
    {superstar, ANSI_BG_CYAN},
    {pekka_trait, ANSI_BG_PURPLE}
};

// Troop Name Constants
const std::string goblin_name = "Goblin";
const std::string spear_goblin_name = "Spear Goblin";
const std::string barbarian_name = "Barbarian";
const std::string skeleton_dragons_name = "Skeleton Dragons";
const std::string wizard_name = "Wizard";
const std::string musketeer_name = "Musketeer";
const std::string valkyrie_name = "Valkyrie";
const std::string pekka_name = "P.E.K.K.A";
const std::string prince_name = "Prince";
const std::string dart_goblin_name = "Dart Goblin";
const std::string electro_giant_name = "Electro Giant";
const std::string executioner_name = "Executioner";
const std::string witch_name = "Witch";
const std::string princess_name = "Princess";
const std::string mega_knight_name = "Mega Knight";
const std::string royal_ghost_name = "Royal Ghost";
const std::string bandit_name = "Bandit";
const std::string goblin_machine_name = "Goblin Machine";
const std::string skeleton_king_name = "Skeleton King";
const std::string golden_knight_name = "Golden Knight";
const std::string archer_queen_name = "Archer Queen";
const std::string royal_giant_name = "Royal Giant";
const std::string mini_pekka_name = "Mini P.E.K.K.A";
const std::string monk_name = "Monk";

// Troop as a struct
struct Troop {
    string name;
    int trait1;
    int trait2;
    int elixirCost;
};

// Function declarations
void initializeScores();
void setTraitScore(int trait, int s2, int s4, int s6);
vector<Troop> initializeTroops();
vector<vector<Troop>> generateTeams(const vector<Troop>& troops, int teamSize);
int gradeTeam(const vector<Troop>& team);
int calculateTeamCost(const vector<Troop>& team);
vector<vector<Troop>> filterBestTeams(const vector<vector<Troop>>& teams);
vector<vector<Troop>> filterByTrait(const vector<vector<Troop>>& teams, int trait);
vector<vector<Troop>> filterByTroop(const vector<vector<Troop>>& teams, const string& troopName);
void sortTeamsByCost(vector<vector<Troop>>& teams);
void printTeams(const vector<vector<Troop>>& teams);
void printSynergyBar(int trait, int count);


//=============================================================================
//===============================MAIN FUNCTION=================================
//=============================================================================
int main() {
    //initialize scores and troops
    initializeScores();
    vector<Troop> troops = initializeTroops();
    //set team size
    int teamSize = 6;//change this if necessary
    auto allTeams = generateTeams(troops, teamSize);

    //filter teams by troop
    allTeams = filterByTroop(allTeams, golden_knight_name); //change golden_knight to any troop name if you want to filter by troop

    //filter teams by trait
    allTeams = filterByTrait(allTeams, blaster); //change noble to any trait if you want to filter by trait

    //set specific trait scores
    // setTraitScore(noble, score_trait_2+1, score_trait_4+1, score_trait_6+1); //change noble to any trait if you want to set specific trait scores

    //generate best teams
    auto bestTeams = filterBestTeams(allTeams);
    //sort them by elixir cost
    sortTeamsByCost(bestTeams);
    //print them
    printTeams(bestTeams);
    return 0;
}


// Function to set specific trait scores
void setTraitScore(int trait, int s2, int s4, int s6) {
    traitScores[trait] = make_tuple(s2, s4, s6);
}

// Initialize scores
void initializeScores() {
   for (int i = noble; i <= pekka_trait; i++) {
       traitScores[i] = make_tuple(score_trait_2, score_trait_4, score_trait_6);
   }
}

vector<Troop> initializeTroops() {
    vector<Troop> troops = {
        {goblin_name, goblin, assassin, 2},
        {spear_goblin_name, goblin, blaster, 2},
        {barbarian_name, clan, brawler, 2},
        {skeleton_dragons_name, undead, ranger, 2},
        {wizard_name, clan, blaster, 2},
        {musketeer_name, superstar, noble, 3},
        {valkyrie_name, brutalist, clan, 3},
        {pekka_name, pekka_trait, brawler, 4},
        {prince_name, noble, brawler, 3},
        {dart_goblin_name, goblin, ranger, 3},
        {electro_giant_name, giant, superstar, 3},
        {executioner_name, blaster, ace, 3},
        {witch_name, undead, superstar, 4},
        {princess_name, noble, blaster, 4},
        {mega_knight_name, ace, brawler, 4},
        {royal_ghost_name, assassin, undead, 4},
        {bandit_name, assassin, ace, 4},
        {goblin_machine_name, goblin, brutalist, 5},
        {skeleton_king_name, undead, brutalist, 5},
        {golden_knight_name, assassin, noble, 5},
        {archer_queen_name, clan, ranger, 5},
        {royal_giant_name, giant, ranger, 2},
        {mini_pekka_name, pekka_trait, brutalist, 2},
        {monk_name, ace, superstar, 5},
    };

    return troops;
}

// Generate all possible teams of given size from a vector of troops
vector<vector<Troop>> generateTeams(const vector<Troop>& troops, int teamSize) {
    vector<vector<Troop>> teams;
    int n = troops.size();
    vector<bool> select(n, false);
    fill(select.end() - teamSize, select.end(), true);

    do {
        vector<Troop> team;
        for (int i = 0; i < n; ++i) {
            if (select[i]) team.push_back(troops[i]);
        }
        teams.push_back(team);
    } while (next_permutation(select.begin(), select.end()));
    return teams;
}

// Grade a team according to trait rules
int gradeTeam(const vector<Troop>& team) {
    map<int, int> traitCounts;
    for (const Troop& t : team) {
        traitCounts[t.trait1]++;
        traitCounts[t.trait2]++;
    }
    int score = 0;

    for (auto const& [trait, count] : traitCounts)
    {
        int s2, s4, s6;
        tie(s2, s4, s6) = traitScores[trait];

        if (count >= 6) score += s6;
        else if (count >= 4) score += s4;
        else if (count >= 2) score += s2;
    }

    return score;
}

int calculateTeamCost(const vector<Troop>& team) {
    int cost = 0;
    for (const auto& troop : team) {
        cost += troop.elixirCost;
    }
    return cost;
}

// Given all teams, return those with the best score
vector<vector<Troop>> filterBestTeams(const vector<vector<Troop>>& teams) {
    int bestScore = -1;
    vector<vector<Troop>> bestTeams;
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

// Filter teams to only include those with a specific trait
vector<vector<Troop>> filterByTrait(const vector<vector<Troop>>& teams, int trait) {
    vector<vector<Troop>> filtered;
    for (const auto& team : teams) {
        for (const auto& troop : team) {
            if (troop.trait1 == trait || troop.trait2 == trait) {
                filtered.push_back(team);
                break;
            }
        }
    }
    return filtered;
}

// Filter teams to only include those with a specific troop
vector<vector<Troop>> filterByTroop(const vector<vector<Troop>>& teams, const string& troopName) {
    vector<vector<Troop>> filtered;
    for (const auto& team : teams) {
        for (const auto& troop : team) {
            if (troop.name == troopName) {
                filtered.push_back(team);
                break;
            }
        }
    }
    return filtered;
}


void sortTeamsByCost(vector<vector<Troop>>& teams) {
    sort(teams.begin(), teams.end(), [](const vector<Troop>& a, const vector<Troop>& b) {
        return calculateTeamCost(a) < calculateTeamCost(b);
    });
}

void printTeams(const vector<vector<Troop>>& teams) {
    cout << "Number of best teams: " << teams.size() << endl;
    for (const auto& team : teams) {
        cout << "Team: ";
        for (const auto& troop : team) {
            cout << troop.name << "(" << troop.elixirCost << ") ";
        }
        cout << "\n" << ANSI_BG_PINK << "Total Cost:" << ANSI_RESET << " " << calculateTeamCost(team);
        cout << "\n" << ANSI_BG_YELLOW << " Score:" << ANSI_RESET << " " << gradeTeam(team) << endl;
        
        // Print trait bars
        map<int, int> traitCounts;
        for (const Troop& t : team) {
            traitCounts[t.trait1]++;
            traitCounts[t.trait2]++;
        }

        for (auto const& [trait, count] : traitCounts) {
            printSynergyBar(trait, count);
        }
        cout << ANSI_RESET << endl;
    }
}

void printSynergyBar(int trait, int count) {
    if (count >= 2) {
        string color = traitColors[trait];
        string name = traitNames[trait];
        int padding = (count - 1) * 4;
        
        for (int i = 0; i < padding; i++) cout << color << " " ;
        cout << name << ": " << count << ANSI_RESET;
        for (int i = 0; i < padding; i++) cout << color << " " ;
    }
}

