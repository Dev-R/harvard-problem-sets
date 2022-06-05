#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

typedef struct
{
    string _name;
    int _voted;
}
voted_candidates;

voted_candidates current_most_voted[MAX];

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

//############################################################
    //  copies command-line arguments into the array candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }
    // asks the user to type in the number of voters. 
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        //  lets every voter type in a vote.
        string name = get_string("Vote: ");

        // Check for invalid vote

        if (!vote(name))
        {
            //return true to indicate a successful ballot. --> else update that candidate’s vote total to account for the new vote
            //**return false to indicate a invalid ballot.--> no change**
            printf("Invalid vote.\n");
        }
        /*
        1-If name matches one of the names of the candidates in the election, 
        2-then update that candidate’s vote total to account for the new vote.
        */
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Implementing linear search algorithm
    for (int i = 0; i <= (candidate_count - 1); i++)
    {
        // hold current voter name
        string current_name = candidates[i].name;
        //printf("%s\n", candidates[i].name);
        bool check = strcmp(name, current_name);
        if (!check)
        {
            candidates[i].votes ++;
            return true;
        }
    }
    // Candidate name doesnt exist in the list
    return false;
}

void print_winner(void)
{
    // store the value of the highest vote
    int current_max_vote = 0 ;
    // store the name  of the candidate the highest vote
    string current_max_vote_holder_name;
    // current_most_voted counter
    int j = 0;
    // loop through candidates!
    // WANT TO ENHANCE THE SOLUTION ?
    /* IMPLEMENT BUBBLE SORT ALGORITHM AND THEN CHECK IF THE MOST RIGHT VALUES ARE EQUAL, IF SO IT IS TIDE, ELSE IGNORE. IF NO VALUE EQUAL THEN THE VALUE IS THE HEIGHST.*/
    
    for (int i = 0; i <= ((candidate_count - 1)); i++)
    {
        
        if (candidates[i].votes > current_max_vote)
        {
            // hold the current highest candidate name and votes
            current_max_vote = candidates[i].votes ;
            current_max_vote_holder_name = candidates[i].name;
            // add the current highest candidate name and votes to the most voted candidates
            current_most_voted[j]._name = candidates[i].name;
            current_most_voted[j]._voted = candidates[i].votes;
            j++;
        }
        // add candidate name to the most voted candidates in case of tie
        else if (candidates[i].votes == current_max_vote && strcmp(candidates[i].name, current_max_vote_holder_name) != 0)
        {
            current_most_voted[j]._name = candidates[i].name;
            current_most_voted[j]._voted = candidates[i].votes;
            j++;
        }
        
    }
    
    // print the most election winner
    for (int i = 0; i <= j - 1; i++)
    {
        printf("%s", current_most_voted[i]._name);
        printf("\n");
    }
    
    
    
}
/*
// Print the winner (or winners) of the election
void print_winner(void)
{
    int current_greatest_value = 0;
    //int highest_v[MAX] ;
    int current_highest_vote_1, current_highest_vote_2 = 0;
    string current_highest_candidate_1, current_highest_candidate_2; 

    for (int i = 0; i <= (candidate_count - 1); i++)
    {
        if (candidates[i].votes >= current_greatest_value)
        {
            if (candidates[i].votes > current_greatest_value)
            {
                current_highest_candidate_1 = candidates[i].name;
                current_highest_vote_1 = candidates[i].votes;
                current_greatest_value = current_highest_vote_1;
            }
            else if (candidates[i].votes == current_greatest_value)
            {
                current_highest_candidate_2 = candidates[i].name;
                current_highest_vote_2 = candidates[i].votes;
                current_greatest_value = current_highest_vote_2;
            }
        }
    }
    if (current_highest_candidate_2 != 0 && strcmp(current_highest_candidate_1, current_highest_candidate_2) != 0)
    {
        printf("%s\n", current_highest_candidate_1);
        printf("%s\n", current_highest_candidate_2);
    }
    
    else
    {
        printf("%s\n", current_highest_candidate_1);
    }
}

*/