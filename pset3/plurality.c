#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
string to_case(string name, char key);

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

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int is_vote = strncmp(name, candidates[i].name, 26);
        if (is_vote == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate winner = candidates[0];
    candidate tie[candidate_count];
    int stat = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (winner.votes < candidates[i].votes)
        {
            winner = candidates[i];
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (winner.votes == candidates[i].votes && strncmp(winner.name, candidates[i].name, 26) != 0)
        {
            tie[stat] = candidates[i];
            stat++;
        }
    }
    printf("%s\n", winner.name);
    for (int i = 0; i < stat; i++)
    {
        printf("%s\n", tie[i].name);
    }
    return;
}

string to_case(string name, char key)
{
    int string_length = strlen(name);
    for (int i = 0; i < string_length; i++)
    {
        if (key == 'l')
        {
            name[i] = tolower(name[i]);
        }
        else if (key == 'u')
        {
            name[i] = toupper(name[i]);
        }
        else
        {
            printf("Internal Error");
            break;
        }
    }
    name[0] = toupper(name[0]);
    return name;
}
