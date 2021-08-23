#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int i, int j, string name)
{
    for (int l = 0; l < candidate_count; l++)
    {
        //check if candidate exists
        if (strcasecmp(name, candidates[l].name) == 0)
        {
            //record candidate into array
            preferences[i][j] = l;
            
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //Cycle every voter
    for (int i = 0; i < voter_count; i++)
    {
        //Cycle preferences break if candidate not elim
        for (int p = 0; p < candidate_count; p++)
        {
            int t = preferences[i][p];
            
            if (!candidates[t].eliminated)
            {
                candidates[t].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int k = 0; k < candidate_count; k++)
    {
        if (candidates[k].votes > (voter_count / 2))
        {
            printf("The Winner is %s\n", candidates[k].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int min_vote = MAX_VOTERS;
int find_min(void)
{
    //Loop through all votes
    for (int k = 0; k < candidate_count; k++)
    {
        if (min_vote > candidates[k].votes && !candidates[k].eliminated)
        {
            min_vote = candidates[k].votes;
        }
    }
    
    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //counter for how many candidates got the min vote
    int numberofdraw = 0;
    int candidatesnotelim = 0;
    //check how many candidates still in the race
    //loop through all candidate votes
    for (int k = 0; k < candidate_count; k++)
    {
        if (!candidates[k].eliminated && candidates[k].votes == min)
        {
            numberofdraw++;
            candidatesnotelim++;
        }
        else if (!candidates[k].eliminated)
        {
            candidatesnotelim++;
        }
    }
    if (numberofdraw == candidatesnotelim)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int k = 0; k < candidate_count; k++)
    {
        if (!candidates[k].eliminated && candidates[k].votes == min)
        {
            candidates[k].eliminated = true;
        }
    }
    return;
}