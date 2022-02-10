#include <stdio.h>
#include <stdlib.h>
#include "autocomplete.h"

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");

    int lm = lowest_match(terms, nterms, "Tor");
    int hm = highest_match(terms, nterms, "Tor");
    printf("lowest match: %d\nlowest term: %s\n", lm, terms[lm].term); //Tor, Egypt
    printf("highest match: %d\nhighest term: %s\n", hm, terms[hm].term); //Tora,

    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");

    printf("\n---Autocomplete---\n");
    for (int i = 0; i < n_answer; i++)
    {
        printf("%lf %s\n", answer[i].weight, answer[i].term);
    }
    //free allocated blocks here -- not required for the project, but good practice
    return 0;
}

