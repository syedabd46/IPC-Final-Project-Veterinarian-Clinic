/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
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

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection = 0;

    do {
        printf("\nEdit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        
        scanf("%d", &selection);

       

        if (selection == 1)
        {
            clearInputBuffer();
            printf("\nName  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n");
        }
        else if (selection != 1 && selection != 2 && selection != 0)
        {
            printf("Incorrect Selection\n\n");
            
        }

        else
        { 
            printf("\n");
        }
            
        

    } while (selection != 0);
}






// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)


void displayAllPatients(const struct Patient patient[], int max, int fmt)      
{

        int i = 0;
        int found = 0;
        displayPatientTableHeader();
        // call to function to display header
       
        for (; i < max; i++)
        {// For loop will check each index of array patientNumber for a value
            
            //printf("%d\n", patient[i].patientNumber);
            if (patient[i].patientNumber != 0)
            {
                displayPatientData(&patient[i], fmt);
                found = 1; 
            } // If a ID value is found at that index, it's data will be 
              // displayed by calling the function displayPatientData
              // and 1 will be assigned to found

        }

        if (found == 0)
        {

            printf("*** No records found ***");
        } // If found is 0 it means that no Products were found within the
          // system 
        
        printf("\n");

}









// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void searchPatientData(const struct Patient patient[], int max)
{
    int selection = 0;
    // Variable selection will be used to determine which type of search
    // is to be conducted
    
    do
    { // loop will continue until 0 is inputed
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        scanf("%d", &selection); // user input for selection
        printf("\n");
        
        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
            clearInputBuffer();
            suspend();
        } // if selection is 1 a search will be conducted using the Patient
          // number by calling the function searchPatientByPatientNumber

        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            clearInputBuffer();
            suspend();
        }// if selection is 2 a search will be conducted using the Patient
      // phone number by calling the function searchPatientByPhoneNumber

      
    } while (selection == 1 || selection == 2);

}









// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void addPatient(struct Patient patient[], int max)
{
    int index = 1;
    int i = 0;
    int newnumber = 0;

    while (i < max && index == 1)
    {
        if (patient[i].patientNumber == 0)
        {
            index = i;
        }
        else
        {
            i++;
        }
    } // While loop is determined to figure out which index of array 
      // patientNumber is empty 

    if (index == 1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    } // If none are empty this message will be printed
    
    else
    {
        newnumber = nextPatientNumber(patient, max);
        patient[index].patientNumber = newnumber;
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    } // If there is a empty array, new information will be added to it
      // by calling the functions nextPatientNumber and inputPatient

}









// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void editPatient(struct Patient patient[], int max)
{
    int ID = 0; // Variable will store patient ID 
    int checkID = 0; // Variable used to check if ID inputed exists

    printf("Enter the patient number: ");
    scanf("%d", &ID);
    
    checkID = findPatientIndexByPatientNum(ID, patient, max);
    // CheckID will be assigned the value that the function call to
    // findPatientIndexByPatientNum returns
    
    if (checkID == -1)
    {
    printf("ERROR: Patient record not found!\n");

    } // If CheckID equals to -1 it means that there was no index that had
      // the value inputed for ID

    else
    {
        menuPatientEdit(&patient[checkID]);
        clearInputBuffer();

    } // If CheckID has another value it means that there was a index found
      // that had the value inputed in ID. The value assigned to checkID
      // is equal to the index in which the value of ID was found

}









// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void removePatient(struct Patient patient[], int max)                          
{
    int ID = 0; // Variable will store patient ID
    int checkID = 0; // Variable wil check if ID inputed exists 
    char selection; // Variable used to confirm product deletion

    printf("Enter the patient number: ");
    scanf("%d", &ID); // User input for ID
    

    checkID = findPatientIndexByPatientNum(ID, patient, max);
    // CheckID will be assigned the value that the function call to
   // findPatientIndexByPatientNum returns
    
    int loop = 0; // variable used for termination of loop
    
    if (checkID != -1) // This means the ID inputed was found
    {
        printf("\n");
        displayPatientData(&patient[checkID], FMT_FORM);
        // Patient information displayed using displayPatientData function
        
        printf("\nAre you sure you want to remove this patient record?"       
            " (y/n): ");

        do
        {
            scanf(" %c", &selection); // User input for selection
            


            if (selection == 'y' || selection == 'Y')
            {
                patient[checkID].patientNumber = 0;
                printf("Patient record has been removed!\n\n");
                clearInputBuffer();
                loop = 1;

            }// If y or Y is inputed, the array index in which it's 
             // information is stored will be wiped clean

            else if (selection == 'n' || selection == 'N')
            {
                printf("Operation aborted.\n\n");
                clearInputBuffer();
                loop = 1;
            }// If n or N is inputed, this message will be printed

            else
            {
                printf("\nERROR: Character must be one of [yn]: \n");
                clearInputBuffer();
            } // If any other character is inputed this message will be 
              // printed


        } while (loop == 0); // loop will continue until a correct value is 
                             // entered 
    }
    
    else if (checkID == -1)
    {
        printf("\nERROR: Patient record not found!\n\n");
        clearInputBuffer(); 
    } // If CheckID equals to -1 it means that there was no index that had
      // the value inputed for ID
    
}









//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////





// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientN = 0; //Variable will store ID being sought
    int index = 0; // index will store the value of index where ID is
    
    printf("Search by patient number: ");
    scanf("%d", &patientN); // User input for Patient ID

    index = findPatientIndexByPatientNum(patientN, patient, max);
    // Index will be assigned the value that the function call to 
    // findPatientIndexByPatientNum returns 
    
    if (index == -1)
    {
        printf("\n*** No records found ***\n\n");
    } // If the call returned -1, it means that the ID inputed was not 
      // found

    else if (index != -1)
    {
        printf("\n");
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
    } // If the value of index is another value it means that the ID 
      // inputed was found within one of the array indexes and it's
      // information will be displayed by caling the displayPatientData
      // function
}









// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    
    char PhoneNumber[80]; // variable will store phoneNumber being sought

    printf("Search by phone number: ");
    scanf("%s", PhoneNumber); // user input for phone number

    int found = 0; // varible used for termination of loop 
    int i;
    
    for (i = 0; i < max; i++)
    { //For loop will search each index of patient array for the Number
      // inputed 
        
        
        if (strcmp(patient[i].phone.number, PhoneNumber) == 0)
        { // strcmp will be used to compare the phone number inputed 
          // to the phone numbers stored within the array, it will equal
          // to 0 if a match is found 
            
            if (!found)
            {
                printf("\n");
                displayPatientTableHeader();
                found = 1;
            } 
            displayPatientData(&patient[i], FMT_TABLE);
            // If a match is found the patient data for the number will be
            // displayed and found will be assigned the value of 1 
            
        }
    }
    
    printf("\n");
    
    if (!found)
    {
        displayPatientTableHeader();
        printf("\n*** No records found ***\n\n");
    } // If a match is not found this message will be printed 

}









// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

int nextPatientNumber(const struct Patient patient[], int max)
{
    int highestPatientNum = 0; // variable will store highest ID found
    int nextPatientNum = 0; // Varibale will store next highest ID
    int i;

    for (i = 0; i < max; i++)
    { // For loop will check each patient ID value and store it to highest
      // PatientNum if it's value is higher than the previous one 
        
        
        if (patient[i].patientNumber > highestPatientNum)
        {
            highestPatientNum = patient[i].patientNumber;
        }
    }

    nextPatientNum = highestPatientNum + 1;
    // NextPatientNum will be equal to 1 plus the highest ID found

    return nextPatientNum; // nextPatientNum will be returned 
}









// Find the patient array index by patient number (returns -1 if not found)    
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    
        int index = -1; // Value assigned to index 
        int found = 0; // variable used to terminate loop
        int i;

        for (i = 0; i < max && !found; i++)
        { // For loop will check each index for ID number entered in 
          // argument 
            
            
            if (patient[i].patientNumber == patientNumber)
            {
                index = i;
                found = 1;
            } // If a ID number is found, the index value it's found at
              // will be assigned to index and the value of found will be
              // set to 1, terminated the loop
        }

        return index; // The index value will be returned 

}









//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void inputPatient(struct Patient* patient)
{
    
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);                          
    // Prints out new patient number
    
    printf("Name  : ");
    scanf("%[^\n]", patient->name);
    // User input for new patient name 
    
    inputPhoneData(&patient->phone);
    // Function call for new patient phone number input
}









// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

void inputPhoneData(struct Phone* phone)
{
    int selection = 0; // variable dictates phone type
    char Number[PHONE_LEN + 1]; // string will store phone number
    clearInputBuffer();

    printf("\nPhone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    // Range of values that selection can be
    
    printf("\n");
    
    if (selection == 1)
    {
        strncpy(phone->description, "CELL", PHONE_DESC_LEN);
        // strncpy will copy CELL string to phone->description
        
        printf("Contact: %s\n", phone->description); // description printed    
        printf("Number : ");
        inputCString(Number, 10, 10);
        // inputCSring will be called so that the user can input a valid
        // phone number which will be stored in Number
        strcpy(phone->number, Number);
        // The string stored in Number will be copied to phone->number
        // using strcpy
        printf("\n");
        
    }

    else if (selection == 2)
    {
        strncpy(phone->description, "HOME", PHONE_DESC_LEN);
        // strncpy will copy HOME string to phone->description
        
        printf("Contact: %s\n", phone->description); // description printed
        printf("Number : ");
        inputCString(Number, 10, 10);
        // inputCSring will be called so that the user can input a valid
        // phone number which will be stored in Number
        strcpy(phone->number, Number);
        // The string stored in Number will be copied to phone->number
        // using strcpy
        printf("\n");

    }

    else if (selection == 3)
    {
        strncpy(phone->description, "WORK", PHONE_DESC_LEN);
        // strncpy will copy WORK string to phone->description
        
        printf("Contact: %s\n", phone->description); // description printed
        printf("Number : ");
        inputCString(Number, 10, 10);
        // inputCSring will be called so that the user can input a valid
        // phone number which will be stored in Number
        strcpy(phone->number, Number);
        // The string stored in Number will be copied to phone->number
        // using strcpy
        printf("\n");

    }

    else if (selection == 4)
    {
        strncpy(phone->description, "TBD", PHONE_DESC_LEN);
        // strncpy will copy TBD string to phone->description
        *phone->number = '\0'; //No phone number will be inputed
        
    }


}