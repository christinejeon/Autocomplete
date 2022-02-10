#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"


//Part1
void read_in_terms(struct term **terms, int *pnterms, char *filename)
{
    int count = 0;
    char line[200];
    //starting block will take on the value of
    //a pointer to the first element in the block of terms.
    struct term *starting_block;

    //placeholder variables
    int i = 0;
    int n = 0;
    int q = 0;

    //Step 1: open the file and store it in fp.
    FILE *fp = fopen(filename, "r");

    fgets(line, sizeof(line), fp);

    while(1) {
        int finality;
        finality = fgets(line, sizeof(line), fp); //read in at most sizeof(line) characters
        //(including '\0') into line.
        if (finality == NULL){
            break;
        }
        count ++;
    }
    fclose(fp);

    *pnterms = count;
    //set pnterms to the number of lines:

    //malloc a big chunk of memory for all the terms
    //and set the necessary pointer to it.
    struct term *first_term = (struct term *)malloc(sizeof(struct term) * count);
    *terms = first_term;

    FILE *mp = fopen(filename, "r");

    /*
     * Not terribly efficient, but I'm reopening the file and building a list containing its lines
     */
    fgets(line, sizeof(line), mp);

    while(i < count) {

        fgets(line, sizeof(line), mp); //read in at most sizeof(line) characters
        //(including '\0') into line.

        //split lines and save in weight and term in terms
        int cnt = 0;
        char * ranking = strtok(line, "\t");

        for (int j = 0; ranking[j]; j++) //get rid of blank space of str ranking
        {
            if (isspace(ranking[j]) == 0)
            {
                ranking[cnt] = ranking[j];
                cnt++;
            }
        }
        ranking[cnt] = NULL; //end str ranking
        first_term[i] .weight = strtod(ranking, ranking[cnt]); //save str num in weight as double

        char * city_name = strtok(NULL, "\n");

        strcpy(first_term[i] .term, city_name);

        i ++;
    }

    //sort the terms in lexicographic order
    //qsort -> how to make comparing ft
    qsort(first_term, *pnterms, sizeof(first_term[0]), strcmp);

    //at this point we should have a functioning superlist
    //containing each line

    return;
}

//Part2a
int lowest_match(struct term *terms, int nterms, char *substr)
{
    int mid_ind;
    int len_substr = strlen(substr);
    int lbound = 0; //left(lower) bound
    int rbound = nterms - 1; //right(upper) bound
    int res_sc = 1; //save result of strncmp

    while (lbound <= rbound)
    {
        mid_ind = (lbound + rbound) / 2;

        //compare if the substr same as str of mid
        res_sc = strncmp(&terms[mid_ind], substr, len_substr);

        if (res_sc < 0) // terms is smaller than substr
        {
            lbound = mid_ind + 1;
        }
        else if (res_sc > 0) // terms is larger than substr
        {
            rbound = mid_ind - 1;
        }
        else //substr is the same as beginning of terms[mid_ind]
        {
            if (strncmp(&terms[lbound], substr, len_substr) < 0) //lbound term is different(smaller) val
            {
                lbound++;
            }
            else //lbound is the first index of same val
            {
                return lbound;
            }
        }
    }

    // DNE in the list
    return -1;

}

//Partb
int highest_match(struct term *terms, int nterms, char *substr)
{
    int mid_ind;
    int len_substr = strlen(substr);
    int lbound = 0; //left(lower) bound
    int rbound = nterms - 1; //right(upper) bound
    int res_sc = 1; //save result of strncmp

    while (lbound <= rbound)
    {
        mid_ind = (lbound + rbound) / 2;

        //compare if the substr same as str of mid
        res_sc = strncmp(&terms[mid_ind], substr, len_substr);

        if (res_sc < 0) // terms is smaller than substr
        {
            lbound = mid_ind + 1;
        }
        else if (res_sc > 0) // terms is larger than substr
        {
            rbound = mid_ind - 1;
        }
        else // substr is the same as beginning of terms[mid_ind]
        {
            if (strncmp(&terms[rbound], substr, len_substr) > 0) //rbound term is different(larger) val
            {
                rbound--;
            }
            else // rbound is the last index of same val
            {
                return rbound;
            }
        }
    }

    // DNE in the list
    return -1;

}

//Part3

int dblcmp(struct term *a, struct term *b)
{
    double a_w = a->weight;
    double b_w = b->weight;

    //sort by weight in descending order
    return ((int)b_w - (int)a_w);
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr)
{
    int term_lind, term_rind; //left/right bound's index of terms

    //find region of answers
    term_lind = lowest_match(terms, nterms, substr);
    term_rind = highest_match(terms, nterms, substr);
    *n_answer = term_rind - term_lind + 1;

    // make space in answer
    struct term *first_answer = (struct term *)malloc(sizeof(struct term) * (*n_answer));
    *answer = first_answer;

    //copy the answer part of struct term terms to answer
    for (int i = 0; i < *n_answer; i++)
    {
        strcpy(first_answer[i].term, terms[term_lind + i].term);
        first_answer[i].weight = terms[term_lind + i].weight;
    }
     //sort by weight
    qsort(first_answer, *n_answer, sizeof(first_answer[0]), dblcmp);

}
