#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

char secret_word[WORD_SIZE];
char tries[26];
int attempts = 0;

void main()
{
    select_word();

    do
    { //begin the game

        system("clear");
        header();

        draw_gallow();
        draw_letters();

        recive_guess();

    }while(!win() && !hanged());

    system("clear");
    

    if(win())
    {
        printf("\nCongratulations, you won!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n\n");
        add_word();

    } else
    {
        draw_gallow();
        printf("\nGosh, you ware hanged!\n");
        printf("The secret word was **%s**\n\n", secret_word);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

}

int win() //know when the user win the game
{
    for(int i=0; i<strlen(secret_word); i++)
    {
        if(!have_letter(secret_word[i]))
        {
            return 0;
        }
    }
    return 1;
}

int wrong_tries()
{
    int misses = 0;
    for(int i=0; i<attempts; i++)
    {
        int have = 0;
        for(int j=0; j < strlen(secret_word); j++)
        {
            if(tries[i] == secret_word[j])
            {
                have = 1;
                break;
            }
        }
        if(!have) misses++;
    }
    return misses;
}
int hanged() //know when the user is hanged
{
    
    return wrong_tries() >= 6;
}

int have_letter(char letter) //verify if the user's guess has in the secret word 
{
    for(int j=0; j<attempts; j++)
    {
        if(tries[j]==letter)
        {
            return 1;
        }
    }
    return 0;
}

void recive_guess() //recive the player's guess and save in tries
{
    char guess;
    scanf(" %c", &guess);

    tries[attempts] = guess;
    attempts++;
}

void header() //print game header
{
    printf("************************\n");
    printf("***   HANGMAN GAME   ***\n");
    printf("************************\n\n");
}

void draw_gallow()
{
    int errors = wrong_tries();
    
    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %s    \n", (errors >= 1 ?"(_)" : "   "));
    printf(" |      %c%c%c  \n", (errors >= 4 ? '\\' : ' '), (errors >= 2 ? '|' : ' '), (errors >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (errors >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n",(errors >= 5 ? '/' : ' '), (errors >= 6 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n\n\n");
}

void draw_letters() //draw the letter if it is in the secret word or draw an underscore if not 
{


    for(int i=0; i<strlen(secret_word); i++)
        {   
            int find = have_letter(secret_word[i]);
            
            if(find)
            {
                printf("%c ", secret_word[i]);
            }else
            {
                printf("_ ");
            }
            
        }
        printf("\n");
}

void select_word() //select a word and put in a char string
{
    FILE* file = fopen("words.txt", "r"); //open a file in read mode
    if(file == 0)
    {
        printf("ERROR when trying to open the file\n");
        exit(1);
    }

    int number_of_words;
    fscanf(file, "%d", &number_of_words);

    srand(time(0));
    int rand_num = rand() % number_of_words;

    for(int i = 0; i <= rand_num; i++) //get the word and put in secret_word
    {
        fscanf(file, "%s", secret_word);
    }

    fclose(file); //close the file
}

void add_word()
{
    char want;

    printf("Do you want to add a new word in the game? (Y/N) ");
    scanf(" %c", &want);    

    if(want == 'Y')
    {
        char new_word[WORD_SIZE];
        printf("What's the new word? ");
        scanf("%s", new_word);

        FILE* file = fopen("words.txt", "r+");
        if(file == 0)
        {
            printf("ERROR when trying to open the file\n");
            exit(1);
        }

        int number_of_words;
        fscanf(file, "%d", &number_of_words); 
        number_of_words++;

        fseek(file, 0, SEEK_SET);
        fprintf(file, "%d", number_of_words);
        
        fseek(file, 0, SEEK_END);
        fprintf(file, "\n%s", new_word);

        fclose(file);
    }
    
}

