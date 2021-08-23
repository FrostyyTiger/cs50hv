#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    //Check only 1 command line arg
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Convert arg to int
    int key = atoi(argv[1]);
    //Convert arg to string
    string a = argv[1];
    //Check every char of arg if not a digit return error message
    for (int k = 0, c = strlen(a); k < c; k++)
    {
        if (isalpha(a[k]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    //Check if arg is a digit
    if (isdigit(*argv[1]))
    {
        //get plaintext
        string text = get_string("plaintext: ");
        //print out "ciphertext"
        printf("ciphertext: ");
        //go through text and check if alphabetical
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            if (isalpha(text[i]))
            {
                if (isupper(text[i]))
                {
                    //convert the characters to new index from ascii
                    text[i] = text[i] - 65;
                    //shift the characters by key
                    text[i] = (text[i] + key) % 26;
                    //convert back to ascii
                    text[i] = text[i] + 65;
                    printf("%c", text[i]);

                }
                if (islower(text[i]))
                {
                    //convert the characters to new index from ascii
                    text[i] = text[i] - 97;
                    //shift the characters by key
                    text[i] = (text[i] + key) % 26;
                    //convert back to ascii
                    text[i] = text[i] + 97;
                    printf("%c", text[i]);
                }
                else
                {
                    ;  
                }
            }
            else
            {
                //leave non alphabetical charcters as is
                printf("%c", text[i]);
            }

        }
        //print a space after chipertext
        printf("\n");
    }

    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
