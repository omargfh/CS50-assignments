#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define MAX_CHAR 26

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
void sort_pairs(void);
void lock_pairs(void);
bool condorect_cycle(int a, int b);
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
    // Check if name is valid
    for (int i = 0; i < candidate_count; i++)
    {
        int is_vote = strncmp(name, candidates[i], MAX_CHAR);
        if (is_vote == 0)
        {
            // Update ranks at the rank-th preference for the i-th candidate
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (ranks[k] == j)
                    {
                        break;
                    }
                    else if (ranks[k] == i)
                    {
                        preferences[i][j]++;
                        break;
                    }
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair pair_victory;
    int pair_victory_index, stat;
    for (int i = 0; i < pair_count - 1; i++)
    {
        pair_victory = pairs[i];
        pair_victory_index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            pair margin = pairs[j];
            if (preferences[margin.winner][margin.loser] > preferences[pair_victory.winner][pair_victory.loser])
            {
                pair_victory = margin;
                pair_victory_index = j;
                stat++;
            }
        }
        if (stat > 0)
        {
            pairs[pair_victory_index] = pairs[i];
            pairs[i] = pair_victory;
        }
        stat = 0;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (i == 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            if (!condorect_cycle(pairs[i].winner, pairs[i].loser))
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
        }

    }
    return;
}

bool condorect_cycle(int a, int b)
{
    if (locked[b][a] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][a] == true)
        {
            return condorect_cycle(i, b);
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    string winners[MAX];
    int winners_count = 0;
    bool column_lost = false;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                column_lost = true;
                break;
            }
        }
        if (!column_lost)
        {
            winners[winners_count] = candidates[i];
            winners_count++;
        }
        column_lost = false;
    }
    for (int i = 0; i < winners_count; i++)
    {
        printf("%s\n", winners[i]);
    }
    return;
}

