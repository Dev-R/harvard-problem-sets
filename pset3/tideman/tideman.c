#include <stdio.h>

#include <cs50.h>

#include <ctype.h>

#include <string.h>

#include <wctype.h>

#include <math.h>

#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
// stores the order of the candidates as the user input them argv
int candidates_listing_order[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int voter_count_global;

int lock_pairs_recursion_V2(int pair_number);
int lock_pairs_recursion(int i, int j);
// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool check_string_in_arr(string arr[], int arr_len, string word);
int main(int argc, string argv[]) {
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = argv[i + 1];
        candidates_listing_order[i] = i;
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");
    voter_count_global = voter_count;
    //int preference_rank_counter = 0 ;
    // Query for votes
    for (int i = 0; i < voter_count; i++) {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];
        // Query for each rank
        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) {
                printf("Invalid vote.\n");
                return 3;
            }

        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[]) {
    // Implementing linear search algorithm
    for (int i = 0; i <= (candidate_count - 1); i++) {
        // hold current voter name
        string current_name = candidates[i];
        //printf("%s\n", candidates[i].name);
        bool check = strcmp(name, current_name);
        if (!check) {
            //candidates[i].votes ++;
            ranks[rank] = i;
            //printf("current candidate: %s, current level: %i",name, ranks[ preference_rank_counter ] );
            //printf("\n");
            return true;
        }
    }

    // Candidate name doesnt exist in the list
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[]) {
    // stores the candidates that has been assigned to the record_preference
    int k = 0;
    string preference_tracker[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    //accessing candidates ranks array
    {
        int reset = 0;
        // hold current voter name
        string current_name = candidates[ranks[i]];
        //bool check = check_string_in_arr(preference_tracker, k, current_name);
        for (int j = 0; j < candidate_count; j++) {
            //printf("%s\n", candidates[i].name);
            bool state = check_string_in_arr(preference_tracker, k, candidates[j]);
            if (state) {
                if (ranks[i] == j) {
                    preferences[ranks[i]][j] = 0;
                } else {
                    preferences[ranks[i]][j]++;
                    if (reset == 0) {
                        preference_tracker[k] = current_name;
                        reset++;
                        k++;
                    }
                }

            }

        }
    }
    // YOU DID WELL TODAY !
}

// check whether a word exist in an array
bool check_string_in_arr(string arr[], int arr_len, string word) {
    if (arr_len == 0) {
        return true;
    } else {

        for (int i = 0; i < arr_len; i++) {

            if (strcmp(word, arr[i]) == 0) {
                //printf("word: %s, exist !\n", word);
                return false;
            }

        }
        return true;
    }

}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
    //int z = 0;
    // i = y
    //int pair_num = 0;
    int sum, a, b;
    //for (int i = 0; i < voter_count_global; i++)
    {
        for (int y = 0, z = 0; y < candidate_count - 1; y++, z++) {
            int k = 1;
            // j = x
            for (int x = 0 + z; x < candidate_count; x++) {
                // comparing candidate A to B 
                //string current_candidate_A = candidates[y];
                //string current_candidate_B = candidates[y + j];
                if (y != x) {
                    if (preferences[y][x] > preferences[x][y]) {
                        //a = preferences[y][x];
                        //b = preferences[x][y];
                        if (y + k > candidate_count - 1) {
                            break;
                        }
                        sum = y + k;
                        pairs[pair_count].winner = y;
                        pairs[pair_count].loser = y + k;
                        pair_count++;
                        k++;
                    } else if (preferences[x][y] > preferences[y][x]) {
                        if (y + k > candidate_count - 1) {
                            break;
                        }
                        pairs[pair_count].winner = y + k;
                        pairs[pair_count].loser = y;
                        pair_count++;
                        k++;
                    }
                }
            }

        }

    }
    //pair_count = pair_num;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
    // implementing bulbble sort algorithm
    int swap_counter = -1;
    do {
        swap_counter = 0;

        for (int i = 0; i < pair_count - 2; i++) {
            // store the i'th winner and loser
            int winner_1 = pairs[i].winner;
            int loser_1 = pairs[i].loser;
            // store the i + 1 winner and loser
            int winner_2 = pairs[i + 1].winner;
            int loser_2 = pairs[i + 1].loser;
            // look at each adj, if out out of order swap

            if (preferences[winner_1][loser_1] < preferences[winner_2][loser_2]) {
                // stores temp value for swapping
                int tmp_win = winner_1;
                int tmp_lose = loser_1;
                // swapping i with the i + 1 value
                pairs[i].winner = winner_2;
                pairs[i].loser = loser_2;
                // swapping i + 1 with the i value
                pairs[i + 1].winner = tmp_win;
                pairs[i + 1].loser = tmp_lose;

                swap_counter++;
            }
        }
    }
    while (swap_counter != 0);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {
    /*
    for (int i = candidate_count; i >= 0; i--)
    {
        if (lock_pairs_recursion_V2(i) == 1)
        {
            break;
        }
    }
    */

    // locking pairs individually
    for (int i = 0; i < candidate_count - 1; i++) {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    /*
    //
    for(int i = 0; i < candidate_count - 1; i++)
    {
        int j = 0;
       if(lock_pairs_recursion(i, j) == 1)
       {
           break;
       }
    }
    */

    return;
}

// Print the winner of the election
void print_winner(void) {
    // int candidate_count = 0;
    int no_edge_counter = 0;
    for (int i = 0; i < candidate_count - 1; i++) {
        for (int j = 0; j < candidate_count - 1; j++) {
            if (locked[j][i] == false) {
                no_edge_counter++;
            }
        }
        if (no_edge_counter == candidate_count - 1) {
            printf("%s\n", candidates[i]);
            return;
        }

    }

}

int lock_pairs_recursion_V2(int pair_number) {
    for (int k = 0; k <= pair_number; k++)
    // loop through all pairs
    {
        // check wheter the loser has been locked or not
        int false_counter = 0;
        // this will store the lock place if it exist in a pair
        int existing_lock_place_holder;
        for (int i = 0; i < candidate_count - 1; i++) {
            if (locked[pairs[k].loser][pairs[i].winner] == false) {

                false_counter++;

            } else {
                // if loser has won before, then check user
                existing_lock_place_holder = i;

                return (lock_pairs_recursion_V2(pairs[k].loser));
            }
        }

        if (false_counter == candidate_count - 1) {
            // if no lock'edge' exist lock pair
            locked[pairs[k].winner][pairs[k].loser] = true;

        }

    }
    return 1;
}

int lock_pairs_recursion(int i, int j) {
    //base case
    for (int k = 0; k < candidate_count - 1; k++) {
        int verify_winner_cycle = 0;
        for (int x = 0; x < candidate_count - 1; x++) {
            if (locked[i][x] == false) {
                verify_winner_cycle++;
            }
        }

        if (verify_winner_cycle == candidate_count - 1) {
            return 1;
        }
    }
    //recursive case

    if (locked[pairs[i].loser][pairs[i].winner] == false) {
        locked[pairs[i].winner][pairs[i].loser] = true;
        i++;
        return lock_pairs_recursion(pairs[i].loser, pairs[i].winner);
    } else if (locked[pairs[i].loser][pairs[i].winner] == true) {
        return lock_pairs_recursion(pairs[i].loser, pairs[i].winner);
    }

    return 0;
}

/*
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <wctype.h>
#include <math.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[], int preference_rank_counter);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }
    
    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }
    
    pair_count = 0;
    int voter_count = get_int("Number of voters: ");
    string name ;
    int j = 0;
    int preference_rank_counter = 0 ;
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference, 
        int ranks[candidate_count];
        preference_rank_counter = 0 ;
        
        for (j = 0; j < candidate_count; j++)
        {
            
        }
        // keep track of the candidate ranks 
        name = get_string("Rank %i: ", j + 1);
        if (!vote(j, name, ranks, preference_rank_counter))
        
        {
            printf("Invalid vote.\n");
            return 3;
        }
        else
        {
                preference_rank_counter++;
        }
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[], int preference_rank_counter)
{
    // Implementing linear search algorithm
    for (int i = 0; i <= (candidate_count - 1); i++)
    {
        // hold current voter name
        string current_name = candidates[i];
        //printf("%s\n", candidates[i].name);
        bool check = strcmp(name, current_name);
        if (!check)
        {
            //candidates[i].votes ++;
            printf("current candidate: %s, current level: %i",name, ranks[ (rank - preference_rank_counter) - 1 ] );
            ranks[ (rank - preference_rank_counter) - 1 ] = rank;

            return true;
        }
    }
    
    // Candidate name doesnt exist in the list
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int k = 0;
    // i = y
    for (int y = 0; y < candidate_count - 1; y++)
    {
        int incrementer = 1;
        // j = x
        for (int x = 0, j = 0; x < candidate_count ; x++, j++)
        {
            // comparing candidate A to B 
            string current_candidate_A = candidates[y];
            string current_candidate_B = candidates[y + j];
            if (y != x)
            {
                if (y == candidate_count - 2 && x == candidate_count - 1)
                {
                    break;
                }
                 if (preferences[y][x] > preferences[y + j][x - j])
                {
                    // winner
                    //pairs[k].winner = ranks[y];       // FIX THIS RANKS SHIT, IT REPLACE THE WINNER WITH THE WRONG VALUE
                    // loser
                   // pairs[k].loser = ranks[y + incrementer];
                    if (y  != candidate_count - 2)
                    {
                        k++;
                    }
                    incrementer++;
                }
            }
            else if(preferences[y + j][x - j] > preferences[y][x])
            {
                // winner
                //pairs[k].winner = candidates_listing_order[y + incrementer];
                // loser
                //pairs[k].loser = candidates_listing_order[y];
                
                if (y != candidate_count - 2)
                {
                    k++;
                }
                incrementer++;
            }
        }
    }
    return;
}
*/