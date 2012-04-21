#define COL 7
#define ROW 11
#define POPULATION 1000
#define RESET "\033[0m"
#define GREEN "\033[32m"      /* Green */
#define WHITE "\033[37m"      /* White */

struct genes{
    int gene[11][7];
    float fitness;
};

static int source[11][7] = {
{1, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 1, 0, 0, 0},
{1, 0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0, 0},
{1, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0},
{1, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 0, 1}
};
