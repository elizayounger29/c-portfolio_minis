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

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// winner
candidate leader[1];

// Function prototypes
bool vote(string name);
void print_winner();

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

    // check that voting entry was correct
    //for (int i = 0; i < voter_count; i++)
    //{
    //printf("%s = %i\n", candidates[i].name, candidates[i].votes);
    //}

    // Display winner of election
    print_winner();

    //compare leader and tie
}


// Update vote totals given a new vote
bool vote(string name)
{

    int j = 0;
    int k = candidate_count;

    // compare name to each name in candidate list
    for (int i = 0; i < k; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
        }
        else
        {
            j++;
        }
    }

    // if no name matches the input
    if (j == k)
    {
        return false;
    }
    else
    {
        return true;
    }
}


// Print the winner (or winners) of the election
void print_winner()
{
    leader[0].name = candidates[0].name;
    leader[0].votes = candidates[0].votes;

    for (int j = 0; j < candidate_count; j++)
    {
        // new leader
        if (leader[0].votes < candidates[j + 1].votes)
        {
            leader[0].name = candidates[j + 1].name;
            leader[0].votes = candidates[j + 1].votes;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == leader[0].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}