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
const int clan = 1;
const int noble = 2;
const int goblin = 3;
const int undead = 4;
const int ace = 5;
const int fire = 6;
const int titan = 7;
const int warrior = 8;
const int marksman = 9;
const int tank = 10;
const int assassin = 11;
const int superstar = 12;
const int hinder = 13;
const int dragon = 14;

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
const string ANSI_BG_GOLD = "\033[43m"; 
const string ANSI_TEXT_BLACK = "\033[30m";
const string ANSI_TEXT_WHITE = "\033[37m";

// Scoring constants
const int score_trait_2 = 2;
const int score_trait_4 = 6;
const int score_trait_6 = 12;

// Trait score map: Key = trait ID, Value = {score for 2 units, score for 4 units, score for 6 units}
map<int, tuple<int, int, int>> traitScores;

// Trait name map
map<int, string> traitNames = {
    {clan, "Clan"},
    {noble, "Noble"},
    {goblin, "Goblin"},
    {undead, "Undead"},
    {ace, "Ace"},
    {fire, "Fire"},
    {titan, "Titan"},
    {warrior, "Warrior"},
    {marksman, "Marksman"},
    {tank, "Tank"},
    {assassin, "Assassin"},
    {superstar, "Superstar"},
    {hinder, "Hinder"},
    {dragon, "Dragon"}
};

// Trait color map
map<int, string> traitColors = {
    {clan, ANSI_BG_BLUE},
    {noble, ANSI_BG_GOLD},
    {goblin, ANSI_BG_DARK_GREEN},
    {undead, ANSI_BG_CYAN},
    {ace, ANSI_BG_PURPLE},
    {fire, ANSI_BG_ORANGE},
    {titan, ANSI_BG_YELLOW},
    {warrior, ANSI_BG_RED},
    {marksman, ANSI_BG_CYAN},
    {tank, ANSI_BG_LIGHT_GREEN},
    {assassin, ANSI_BG_RED},
    {superstar, ANSI_BG_PINK},
    {hinder, ANSI_BG_PURPLE},
    {dragon, ANSI_BG_LIGHT_GREEN}
};

// Troop Name Constants
const string barbarian_name = "Barbarian";
const string archer_name = "Archer";
const string valkyrie_name = "Valkyrie";
const string archer_queen_name = "Archer Queen";
const string prince_name = "Prince";
const string musketeer_name = "Musketeer";
const string knight_name = "Knight";
const string golden_knight_name = "Golden Knight";
const string goblin_demolisher_name = "Goblin Demolisher";
const string dart_goblin_name = "Dart Goblin";
const string goblin_name = "Goblin";
const string goblin_machine_name = "Goblin Machine";
const string skeleton_king_name = "Skeleton King";
const string giant_skeleton_name = "Giant Skeleton";
const string witch_name = "Witch";
const string skeleton_dragons_name = "Skeleton Dragons";
const string monk_name = "Monk";
const string pekka_name = "P.E.K.K.A";
const string wizard_name = "Wizard";
const string baby_dragon_name = "Baby Dragon";
const string royal_giant_name = "Royal Giant";
const string giant_name = "Giant";

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
    // allTeams = filterByTroop(allTeams, golden_knight_name); //change golden_knight to any troop name if you want to filter by troop

    //filter teams by trait
    allTeams = filterByTrait(allTeams, assassin); //change noble to any trait if you want to filter by trait
    allTeams = filterByTrait(allTeams, goblin); 
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
   for (int i = clan; i <= dragon; i++) {
       traitScores[i] = make_tuple(score_trait_2, score_trait_4, score_trait_6);
   }
}

vector<Troop> initializeTroops() {
    vector<Troop> troops = {
        // Clan row
        {barbarian_name, clan, warrior, 2},
        {archer_name, clan, marksman, 2},
        {valkyrie_name, clan, tank, 3},
        {archer_queen_name, clan, superstar, 5},
        // Noble row
        {prince_name, noble, warrior, 4},
        {musketeer_name, noble, marksman, 3},
        {knight_name, noble, tank, 2},
        {golden_knight_name, noble, assassin, 5},
        // Goblin row
        {goblin_demolisher_name, goblin, warrior, 3},
        {dart_goblin_name, goblin, marksman, 2},
        {goblin_name, goblin, assassin, 2},
        {goblin_machine_name, goblin, superstar, 4},
        // Undead row
        {skeleton_king_name, undead, warrior, 5},
        {giant_skeleton_name, undead, tank, 3},
        {witch_name, undead, hinder, 4},
        {skeleton_dragons_name, undead, dragon, 2},
        // Ace row
        {monk_name, ace, tank, 5},
        {pekka_name, ace, superstar, 4},
        // Fire row
        {wizard_name, fire, hinder, 2},
        {baby_dragon_name, fire, dragon, 4},
        // Titan row
        {royal_giant_name, titan, marksman, 3},
        {giant_name, titan, superstar, 3}
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
        cout << "\n" << ANSI_BG_PINK << ANSI_TEXT_BLACK << "Total Cost:" << ANSI_RESET << " " << calculateTeamCost(team);
        cout << "\n" << ANSI_BG_YELLOW << ANSI_TEXT_BLACK << " Score:" << ANSI_RESET << " " << gradeTeam(team) << endl;
        
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
        string bgColor = traitColors[trait];
        string name = traitNames[trait];
        
        // Determine text color based on background brightness
        string textColor = ANSI_TEXT_WHITE; // Default
        if (trait == noble || trait == undead || trait == titan || 
            trait == marksman || trait == tank || trait == superstar || 
            trait == dragon) {
            textColor = ANSI_TEXT_BLACK;
        }

        int padding = (count - 1) * 4;
        
        for (int i = 0; i < padding; i++) cout << bgColor << " " ;
        cout << bgColor << textColor << name << ": " << count << ANSI_RESET;
        for (int i = 0; i < padding; i++) cout << bgColor << " " ;
    }
}

