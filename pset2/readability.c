#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    //prompt user for text
    string text = get_string("Text: ");
    //number of letters in the text
    float numberofletters = 0;
    //number of words in the text
    float numberofwords = 1;
    //number of sentences in the text
    float numberofsentences = 0;
    //characters needed to determine if a sentence end
    char c1 = '!';
    char c2 = '.';
    char c3 = '?';
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]))
        {
            numberofletters++;
        }
        if (isupper(text[i]))
        {
            numberofletters++;
        }
        if (isspace(text[i]))
        {
            numberofwords++;
        }
        if (text[i] == c1)
        {
            numberofsentences++;
        }
        if (text[i] == c2)
        {
            numberofsentences++;
        }
        if (text[i] == c3)
        {
            numberofsentences++;
        }
        else
        {
            ;
        }

    }
    //average letters per 100 words
    float avgletters = (numberofletters / numberofwords) * 100;
    //average words per 100 sentences
    float avgsentences = (numberofsentences / numberofwords) * 100;

    //formula for the index
    int index = round(0.0588 * avgletters - 0.296 * avgsentences - 15.8);

    //if higher than 16 print 16+
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}