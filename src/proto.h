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

#define COL 7 /* Columns of source array */
#define ROW 11 /* Rows of source array */
#define POPULATION 3000 /* Population size */
#define POP_RATE 0.5 /* Population renewal rate */
#define HSIZE 4 /* Heredity factor, between 0 and COL */
#define MUT_RATE 0.3 /* Mutation rate */
#define RESET "\033[0m"
#define GREEN "\033[32m" /* Green */
#define WHITE "\033[37m" /* White */

struct Organisms{
    int gene[ROW][COL];
    float fitness;
};

struct Node{
    struct Organisms organism;
    struct Node *next;
};

/* Source graph */
static int source[ROW][COL] = {
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
void push(struct Node**, struct Organisms);
void delete(struct Node**);
void sort(struct Node**);
int size(struct Node*);
void print_list(struct Node*);
void copy_list(struct Node**, struct Node**);
void print_gene(struct Organisms);
