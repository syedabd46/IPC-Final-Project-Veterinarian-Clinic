/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Syed Abdullah
Student ID#: 155781198
Email      : sabdullah12@myseneca.ca
Section    : NRA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"
#include <ctype.h>

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

// Function will check if a integer value is inputed and then return it
int inputInt(void)
{
    int IntInput = 0; // Int variable for storing user input
    char NewLine; // char variable for checking for new line after int input
    // If a integer is inputed and you click enter a newline should be the 
    // result, if not a non integer was inputed

    do // do while loop continues if NewLine is not '/n'
    {
        scanf("%d%c", &IntInput, &NewLine); // User input
        if (NewLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        } // If NewLine is not /n clearinputbuffer function called to
          // refresh buffer and error message printed

    } while (NewLine != '\n');

    return IntInput; // int value returned 
}




// Check if Integer input is a positive value
int inputIntPositive(void)
{
    int PosIntInput = 0; // Int variable for storing positive user input
    char NewLine; // char variable for checking for new line after int input   

    do // do while loop continues if NewLine is not '\n' or a value of 0 or 
       // less is inputed
    {
        scanf("%d%c", &PosIntInput, &NewLine); // User input

        if (NewLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        } // If user input has non-integers this message will be printed

        else if (PosIntInput <= 0)
        {

            printf("ERROR! Value must be > 0: ");

        } // If user input is less than or equal to 0 this error message
          // will be printed

    } while (NewLine != '\n' || PosIntInput <= 0);

    return PosIntInput; // Positive int value returned

}




// Integer input and check if it's within range
int inputIntRange(int Min, int Max)
{

    int IntInput = 0; // Int variable for input
    char NewLine; // Char variable checking for \n

    do
    { // do while loop continues if input is not within range 
      // and NewLine does not equal '\n'  

        scanf("%d%c", &IntInput, &NewLine);
        // User int input and if enter is pressed NewLine should be '\n'

        if (NewLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }// If the NewLine is not '\n' it means a non integer was inputed
         // and this message will appear 

        if (IntInput < Min || IntInput > Max)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", Min,
                Max);
        } // If input is not within this range, this message will appear 


    } while (NewLine != '\n' || IntInput < Min || IntInput > Max);

    return IntInput; // integer input is returned 

}






// Character input and check if it's within string
char inputCharOption(const char CharInput[])
{

    char input; // Char variable will store character input
    int loop = 0; // variable's value will determine if loop continues
    int i = 0; // for loop counter




    do
    { // do while loop will contiue until a valid character is inputed

        scanf(" %c", &input);
        // user char input

        for (i = 0; CharInput[i] != '\0'; i++)
        {
            if (input == CharInput[i])
            {
                loop++;
            }

        } // For loop will check each index of the string for the 
          // character that was inputed, if there is a match found
          // the value of loop will be incremented 

        if (loop == 0)
        {
            printf("ERROR: Character must be one of [%s]: ", CharInput);

        } // If the value of loop has not been incremented it means that
          // the character entered was not in the string

    } while (loop == 0);

    clearInputBuffer();

    return input;
    // The character input is returned 
}




// Character string input and check if it's lenght is within range             
void inputCString(char* string, int min, int max) {

    {


        char String[80]; // Character array represting string
        int len, error = 1;
        // len is int variable for string lenght
        // error is for loop termination 


        do
        { // do while loop continues if the value of error changed 

            fgets(String, 80, stdin);
            //fegts function will take user input for a string
            // that is up to 80 characters long

            String[strlen(String) - 1] = 0;
            // This line is for the removal of the new line character
            // that is located at the end of the string. Fgets automatically   
            // assigns '\n' at the end so here I assigned the last character
            // to 0 which will mean the string actualy ends where it's 
            // suppose to

            len = (int)strlen(String);
            // strlen will get the lenght of the string and 
            // then that value will be assigned to len

            if (min == max && len != min)
            {

                printf("ERROR: String length must be exactly %d chars: ", min);

            } // If the min characters allowed is equal to the max and
              // the string lenght won't be that value this message will
              // be printed


            else if (len < min)
            {
                printf("ERROR: String length must be between %d and %d chars: ",
                    min, max);

            }// if the string's lenght is less than the min this 
             // message will be printed


            else if (len > max)
            {
                printf("ERROR: String length must be no more than %d chars: ",
                    max);

            } // If the string's lenght is greater than the max this message
              // will be printed 

            else
                error = 0; // If the string lenght is within range the loop
            // will be terminated


        } while (error == 1);


        strcpy(string, String); // The local string will be copied and 
        // assigned to the argument string using
        // strcpy


    }




}




// This fuction will validate if the argument has a 
// proper phone number and then display it

void displayFormattedPhone(const char* phoneNum)
{

    int i = 0; // for loop counter
    int digits = 0; // Used to check if argument given has only digits 
    int valid = 1;  // Used to check is string has other characters in additon
    // to numbers


    if (phoneNum == NULL)
        // If the string argument equals
        // to NULL this message will be printed
    {
        printf("(___)___-____");
    }

    else if (phoneNum != NULL)
    { // If the string argument is not equal to NULL, it will 
      // then be checked for 2 conditons 

        for (; phoneNum[i] != '\0'; i++)
        {
            if (isdigit(phoneNum[i])) // Checks if the string has numbers
            {
                digits = 1; // If there are numbers, digits changes to 1
            }
            else
            {
                valid = 0; // If there are other characters in addition to
                // numbers valid changes to 0
            }
        } // This for loop will check each character within the string using
          // the isdigit function to figure out if there are numbers 
          // within it. If there are the value of digits will be changed to
          // to 1. If there are also other non numbers in the string valid
          // will be changed to 0





        if (strlen(phoneNum) == 10 && digits == 1 && valid == 1)
        { // If the lenght of the string is 10 and the string only has
          // numbers the following actions will occur  

            printf("(");

            for (i = 0; i < 3; i++)
            {
                printf("%c", phoneNum[i]);
            } // for loop will print first 3 digits of phone number

            printf(")");

            for (i = 3; i < 6; i++)
            {
                printf("%c", phoneNum[i]);
            } // for loop will print digits 4, 5 and 6 of phone number

            printf("-");

            for (i = 6; i < 10; i++)
            {
                printf("%c", phoneNum[i]);
            } // for loop will print digits 7, 8, 9 and 10 of phone number
        }

        else if (strlen(phoneNum) != 10 || digits == 0 || valid == 0)
        {
            printf("(___)___-____");
        } // If the string lenght is not 10 and there are non numbers
          // within the string this will be printed

    }

}


void inputCStringNumbers(char* string, int min, int max) {

    {


        char String[80]; // Character array represting string
        int len, error = 1;
        // len is int variable for string lenght
        // error is for loop termination 


        do
        { // do while loop continues if the value of error changed 

            fgets(String, 80, stdin);
            //fegts function will take user input for a string
            // that is up to 80 characters long

            String[strlen(String) - 1] = 0;
            // This line is for the removal of the new line character
            // that is located at the end of the string. Fgets automatically   
            // assigns '\n' at the end so here I assigned the last character
            // to 0 which will mean the string actualy ends where it's 
            // suppose to

            len = (int)strlen(String);
            // strlen will get the lenght of the string and 
            // then that value will be assigned to len

            if (min == max && len != min)
            {

                printf("Invalid 10-digit number! Number: ");

            } // If the min characters allowed is equal to the max and
              // the string lenght won't be that value this message will
              // be printed


            else if (len < min)
            {
                printf("Invalid 10-digit number! Number: ");

            }// if the string's lenght is less than the min this 
             // message will be printed


            else if (len > max)
            {
                printf("Invalid 10-digit number! Number: ");

            } // If the string's lenght is greater than the max this message
              // will be printed 

            else
                error = 0; // If the string lenght is within range the loop
            // will be terminated


        } while (error == 1);


        strcpy(string, String); // The local string will be copied and 
        // assigned to the argument string using
        // strcpy


    }




}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

