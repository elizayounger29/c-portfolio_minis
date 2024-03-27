#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
int pair_strength(int i);
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

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
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
bool vote(int rank, string name, int ranks[])
{
    // make sure the vote name matches a candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, (string) candidates[i]) == 0)
        {
            // if it matches then add vote to that candidate
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // for rank 1
    for (int i = 0; i < candidate_count; i++)
    {
        // to update the subsequent ranks
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    // i versus everyone else
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // if alice is larger than bob
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }

    return;
}

int pair_strength(j)
{
    int strength = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
    return strength;
}


// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int max_strength = 0;
    int max_index = 0;
    int index_win;


    // for each pair's space swap
    for (int i = pair_count; i < pair_count; i++)
    {
        // store from largest difference
        for (int j = i; j < pair_count; j++)
        {
            int strength = pair_strength(j);
            if (strength > max_strength)
            {
                max_strength = strength;
                index_win = j;
            }
        }

        // make copy of index 0
        pair temp = pairs[i];
        // rewrite index 0 with largest win
        pairs[i] = pairs[index_win];
        // rewrite original largest win space with whatever was in index 0
        pairs[index_win] = temp;
    }

    return;
}

bool cycle(int winner, int loser)
{
    // if already true that loser wins over winner then return that yes there's a cycle.
    if (locked[loser][winner] == true)
    {
        return true;
    }

    // check that
    for (int i = 0; i < candidate_count; i++)
    {
        // if loser beat someone AND the winner also beat that person then return that there's a cycle. Check for each candidate
        if (locked[loser][i] == true && cycle(winner, i))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // if there is no cycle then
        if (!cycle(winner, loser))
        {
            locked[winner][loser] = true;
            locked[loser][winner] = false;
        }
    }

    // pairs index from 0 in order now.
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner = 0;
    int counter = 0;

    // for the number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        counter = 0;
        // add up each one's total
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                counter++;
            }
        }
        if (counter > winner)
        {
            winner = i;
        }
    }

    printf("%s is the winner!", candidates[winner]);

    return;
}