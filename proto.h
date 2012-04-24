#define COL 7
#define ROW 11
#define POPULATION 1000
#define POP_RATE 0.5
#define RESET "\033[0m"
#define GREEN "\033[32m" /* Green */
#define WHITE "\033[37m" /* White */

struct genes{
    int gene[ROW][COL];
    float fitness;
};

struct Node{
    struct genes organism;
    struct Node *next;
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

/* Function prototypes */
void push(struct Node**, struct genes);
void delete(struct Node**);
void sort(struct Node**);
int size(struct Node**);
