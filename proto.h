#define COL 7
#define ROW 11
#define POPULATION 1000

struct genes{
    int gene[11][7];
    int fitness;
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
