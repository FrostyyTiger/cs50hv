#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

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
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}


bool vote(string name)
{
    //Iterate through array
    for (int k = 0; k < candidate_count; k++)
    {
        //check if vote name is equal to a candiate
        if (strcasecmp(name, candidates[k].name) == 0)
        {
            // Update vote totals given a new vote
            candidates[k].votes++;
            return true;
        }
    }
    return false;
    
}

// Print the winner (or winners) of the election
void print_winner(void)
{   
    //Find the maximum vote
    //Initialize maximum element
    int mostvotes = candidates[0].votes;
    int j = 0;
    for (j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes > mostvotes)
        {
            mostvotes = candidates[j].votes; 
        }
    }
    //check which candiates got the highest vote
    int h = 0;
    for (h = 0; h < candidate_count; h++)
    {
        if (candidates[h].votes == mostvotes)
        {
            printf("%s\n", candidates[h].name);
        }
    }
    return;
}

