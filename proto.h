/*
    Copyright (C) 2012
    Kouzoupis Antonis

    This file is part of genalg.

    genalg is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    genalg is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with genalg.  If not, see <http://www.gnu.org/licenses/>.
*/

#define COL 7
#define ROW 11
#define POPULATION 5000
#define POP_RATE 0.5 /* Population renewal rate */
#define HSIZE 4 /* Heredity factor, between 0 and COL */
#define MUT_RATE 0.2 /* Mutation rate */
#define RESET "\033[0m"
#define GREEN "\033[32m" /* Green */
#define WHITE "\033[37m" /* White */

struct Genes{
    int gene[ROW][COL];
    float fitness;
};

struct Node{
    struct Genes organism;
    struct Node *next;
};

static int source[11][7] = {
{1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 0, 0}
};

/* Function prototypes */
void push(struct Node**, struct Genes);
void delete(struct Node**);
void sort(struct Node**);
int size(struct Node*);
