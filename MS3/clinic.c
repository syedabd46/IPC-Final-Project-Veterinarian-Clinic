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
#define MAX_APPOINTMENTS 50
#define MAX_PETS 20
#define CURRENT_YEAR 2023


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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)

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
// (Copy your code from MS#2)

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
// (Copy your code from MS#2)

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
// (Copy your code from MS#2)

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
// (Copy your code from MS#2)

void removePatient(struct Patient patient[], int max)
{
    int ID = 0; // Variable will store patient ID
    int checkID = 0; // Variable wil check if ID inputed exists 
    char selection[10]; // Variable used to confirm product deletion

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
            scanf(" %s", selection); // User input for selection



            if ((selection[0] == 'y' || selection[0] == 'Y') && 
                strlen(selection) == 1)
            {
                patient[checkID].patientNumber = 0;
                printf("Patient record has been removed!\n\n");
                clearInputBuffer();
                loop = 1;

            }// If y or Y is inputed, the array index in which it's 
             // information is stored will be wiped clean

            else if (selection[0] == 'n' || selection[0] == 'N')
            {
                printf("Operation aborted.\n\n");
                clearInputBuffer();
                loop = 1;
            }// If n or N is inputed, this message will be printed

            else if (strlen(selection) > 1)
            {
                printf("ERROR: Character must be one of [yn]: ");
                
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

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:

void viewAllAppointments(struct ClinicData* data)                           
{
    displayScheduleTableHeader(NULL, 1); // Call to function to display header

    int i = 0; // Variable for loops
    int j = 0; // Variable for loops
    


    for (i = 0; i < MAX_APPOINTMENTS - 1; i++)
    {
        for (j = i + 1; j < MAX_APPOINTMENTS; j++)
        {
            if (sortAppointments(data, i, j) > 0)
            {

                struct Appointment temp = data->appointments[i];
                data->appointments[i] = data->appointments[j];
                data->appointments[j] = temp;
            }
        }
    } // The purpose of this code block is for the sorting of the data
      // within appointment. The function sortAppointment is called 
      // and depending on it's output the values stored within the indexes of
      // i and j are switched


    
    
    
    
    for (i = 0; i < MAX_APPOINTMENTS; i++)
    // This for loop is for the display of appointment date, time, patient 
    // number and patient name
    
    {
            
        if (data->appointments[i].patientNumber > 0)
        // This if statement was used to handle a bug in which everytime
        // I searched for a appointment a empty one would be added to the 
        // list with the patient number of 00
        
        {

            if (data->appointments[i].date.year != 0)
            { // This if statement was used to handle a bug in which everytime
              // I searched for a appointment a empty one would be added to the 
              // list with a year of 00

                
                printf("%d-", data->appointments[i].date.year); // display year


                if (data->appointments[i].date.month < 10)
                {
                    printf("0%d-", data->appointments[i].date.month);

                } // display month, if the month is a single digit value
                  // a zero has to be added before hand 

                
                else if (data->appointments[i].date.month >= 10)
                {
                    printf("%d-", data->appointments[i].date.month);

                } // display month


                if (data->appointments[i].date.day < 10)
                {
                    printf("0%d", data->appointments[i].date.day);

                } // display day, if the day is a single digit value
                  // a zero has to be added before hand

                else if (data->appointments[i].date.day >= 10)
                {
                    printf("%d", data->appointments[i].date.day);

                } // display day
                  

                if (data->appointments[i].time.hour < 10)
                {
                    printf(" 0%d:", data->appointments[i].time.hour);

                } // display hour, if the hour is a single digit value
                  // a zero has to be added before hand

                
                else if (data->appointments[i].time.hour >= 10)
                {
                    printf(" %d:", data->appointments[i].time.hour);

                } // display hour

                
                if (data->appointments[i].time.min == 0)
                {
                    printf("0%d ", data->appointments[i].time.min);

                } // display minute, if the minute is a single digit value
                  // a zero has to be added before hand

                else
                {
                    printf("%d ", data->appointments[i].time.min);

                } // display minute

                if (data->appointments[i].patientNumber < 10000)
                {
                    printf("0%d ", data->appointments[i].patientNumber);

                } // Display patient number If the patient number is below 
                  //10000 a zero would have to be added prior to the number 
                  // due to formatting

                
                else
                {
                    printf("%d ", data->appointments[i].patientNumber);

                } // Display patient number

                
                

                
                for (j = 0; j < MAX_PETS; j++)

                { // For loop used to display the patient name
                  
                  
                    if (data->appointments[i].patientNumber 
                        == data->patients[j].patientNumber)
                    {  // If statement was trying to match the patient number  
                       // in the appointment array with the patient number
                       // within the patients array. Once matched 
                       // the corresponding name in the patients array would 
                       // be printed
                        
                        printf("%s", data->patients[j].name);

                        
                        if (strlen(data->patients[j].name) == 15)
                        {
                            printf(" ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 14)
                        {
                            printf("  ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 13)
                        {
                            printf("   ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 12)
                        {
                            printf("    ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 11)
                        {
                            printf("     ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 10)
                        {
                            printf("      ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 9)
                        {
                            printf("       ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 8)
                        {
                            printf("        ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 7)
                        {
                            printf("         ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 6)
                        {
                            printf("          ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 5)
                        {
                            printf("           ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 4)
                        {
                            printf("            ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 3)
                        {
                            printf("             ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 2)
                        {
                            printf("              ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 1)
                        {
                            printf("               ");
                        } // For spacing after name, it depends on the 
                          // name lenght 

                        
                        else if (strlen(data->patients[j].name) == 0)
                        {
                            printf("                ");
                        } // For spacing after name, it depends on the 
                          // name lenght 


                    }
                }


                for (j = 0; j < MAX_PETS; j++)

                {  // For loop used to display the patient
                   // phone number 
                    
                    if (data->appointments[i].patientNumber 
                        == data->patients[j].patientNumber)
                    { 
                       // If statement was trying to match the patient number  
                       // in the appointment array with the patient number
                       // within the patients array. Once matched 
                       // the corresponding phone in the patients array would 
                       // be printed
                        
                        
                        
                        char* phone = data->patients[j].phone.number;
                        // phone array will store phone number
                        
                        int len = strlen(phone);
                        // len will store phone lenght
                        
                        if (len == 10)
                        {
                            printf("(%c%c%c)%c%c%c-%c%c%c%c ",
                                phone[0], phone[1], phone[2], phone[3], 
                                phone[4],phone[5], phone[6], phone[7], 
                                phone[8], phone[9]);
                        
                        } // The the lenght of the phone number is correct
                          // it will be printed with the correct formatting

                        else
                        {
                            printf("(___)___-____ ");
                        
                        } // This will print if the patient has no phone number
                          // registered 
                    }
                }

                for (j = 0; j < MAX_PETS; j++)
                { 
                   // For loop used to display the patient
                   // phone descriptions
                    
                    if (data->appointments[i].patientNumber == 
                        data->patients[j].patientNumber)
                    
                    { // If statement was trying to match the patient number  
                       // in the appointment array with the patient number
                       // within the patients array. Once matched 
                       // the corresponding phone description in the 
                       // patients array would be printed
                        
                        
                        char* des = data->patients[j].phone.description;
                        // char array des will store the phone description
                        
                        int len = strlen(des);
                        // len will store the lenght of des
                        
                        if (len == 4)
                        {
                            printf("(%c%c%c%c)",
                                des[0], des[1], des[2], des[3]);

                        } // Formatting for phone description if it's lenght
                          // is 4

                        else if (len == 3)
                        {
                            printf("(%c%c%c)", des[0], 
                                des[1], des[2]);

                        } // Formatting for phone description if it's lenght
                          // is 3
                    }
                }

                printf("\n");

            }
        }
   
    }
    
    printf("\n");

}





// View appointment schedule for the user input date
// Todo:

void viewAppointmentSchedule(struct ClinicData* data)                          
{
    int year;  // Local variable to store year
    int month; // Local variable to store month
    int day;   // Local variable to store day
    int Latestday = 0; // Local variable to figure out last day of month

    
        printf("Year        : ");
        year = inputIntPositive(); 
        // The inputIntPositive Function is called for the input of year

       
        printf("Month (1-12): ");
        month = inputIntRange(1, 12);
        // The inputIntRange Function is called for the input of month
        

    Latestday = getLatestDay(month, year);
    // The getLatestDay Function is called for the last day of month
        
        printf("Day (1-%d)  : ", Latestday);
        // Latest day is required so that the day display can be adjusted
        // based on the month 
        
        day = inputIntRange(1, Latestday);
        // The inputIntRange Function is called for the input of day
        
        
        printf("\n");

    struct Date selectedDate; // local struct selectedDate declared
    
    selectedDate.year = year; // year value assigned
    selectedDate.month = month; // month value assigned
    selectedDate.day = day; // day value assigned

    int i, j;

    
    for (i = 0; i < MAX_APPOINTMENTS; i++)
    { 
        
        for (j = i + 1; j < MAX_APPOINTMENTS; j++)
        {
            if (sortAppointments(data, i, j) > 0)
            {
                struct Appointment temp = data->appointments[i];
                data->appointments[i] = data->appointments[j];
                data->appointments[j] = temp;
            }
        }
    } // The purpose of this code block is for the sorting of the data
      // within appointment. The function sortAppointment is called 
      // and depending on it's output the values stored within the indexes of  
      // i and j are switched

    
    displayScheduleTableHeader(&selectedDate, 0);
    // display the schedule table for the selected date                         
    
    for (i = 0; i < MAX_APPOINTMENTS; i++)
    { // for loop will be used to search the appointment array for the 
      // selected year, month and day
        
        if (data->appointments[i].date.year == selectedDate.year &&
            data->appointments[i].date.month == selectedDate.month &&
            data->appointments[i].date.day == selectedDate.day)
        
        { // if there is a match found, it will be displayed
            
            
            if (data->appointments[i].patientNumber != 0)
            { // if statment used to prevent bug where a appointment with
              // patient number 0 was being added

                printf("%d:", data->appointments[i].time.hour);
                // display hour

                
                if (data->appointments[i].time.min == 0)
                {
                    printf("0%d ", data->appointments[i].time.min);
                } // display if minute is 0

                else
                {
                    printf("%d ", data->appointments[i].time.min);
                } // display if minute is greater than 0

                printf("0%d ", data->appointments[i].patientNumber);
                  // display patient number with correct formatting
                
                
                for (j = 0; j < MAX_PETS; j++)
                
                // For loop used to display the patient
                // names
                
                {
                    if (data->appointments[i].patientNumber 
                        == data->patients[j].patientNumber)
                    { 
                       // If statement was trying to match the patient number  
                       // in the appointment array with the patient number
                       // within the patients array. Once matched 
                       // the corresponding name in the 
                       // patients array would be printed
                        
                        
                        printf("%s", data->patients[j].name);

                        if (strlen(data->patients[j].name) == 15)
                        {
                            printf(" ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 14)
                        {
                            printf("  ");
                        }// For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 13)
                        {
                            printf("   ");
                        }// For spacing after name, it depends on the 
                          // name lenght

                        
                        
                        else if (strlen(data->patients[j].name) == 12)
                        {
                            printf("    ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 11)
                        {
                            printf("     ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 10)
                        {
                            printf("      ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                       
                        else if (strlen(data->patients[j].name) == 9)
                        {
                            printf("       ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 8)
                        {
                            printf("        ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 7)
                        {
                            printf("         ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 6)
                        {
                            printf("          ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 5)
                        {
                            printf("           ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 4)
                        {
                            printf("            ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 3)
                        {
                            printf("             ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 2)
                        {
                            printf("              ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 1)
                        {
                            printf("               ");
                        } // For spacing after name, it depends on the 
                          // name lenght

                        
                        else if (strlen(data->patients[j].name) == 0)
                        {
                            printf("                ");
                        } // For spacing after name, it depends on the 
                          // name lenght


                    }

                }

                for (j = 0; j < MAX_PETS; j++)

                { // For loop used to display the patient
                  // phone 
                   
                    if (data->appointments[i].patientNumber
                        == data->patients[j].patientNumber)

                       // If statement was trying to match the patient number  
                       // in the appointment array with the patient number
                       // within the patients array. Once matched 
                       // the corresponding phone in the 
                       // patients array would be printed
                    {
                        
                        char* phone = data->patients[j].phone.number;
                        // char array phone will store phone number
                        
                        int len = strlen(phone);
                        // len will store phone number lnght 

                        if (len == 10)
                        {
                            printf("(%c%c%c)%c%c%c-%c%c%c%c ",
                                phone[0], phone[1], phone[2], phone[3], 
                                phone[4],phone[5], phone[6], 
                                phone[7], phone[8], phone[9]);
                        
                        } // If a number has been registered it will be
                          // displayed
                    }
                }

                for (j = 0; j < MAX_PETS; j++)
                // For loop used to display the patient
                // phone descriptions
                
                {
                    if (data->appointments[i].patientNumber 
                        == data->patients[j].patientNumber)
                       // If statement was trying to match the patient number  
                       // in the appointment array with the patient number
                       // within the patients array. Once matched 
                       // the corresponding phone in the 
                       // patients array would be printed
                    
                    {
                        char* des = data->patients[j].phone.description;
                        // char array des will store phone description
                        
                        int len = strlen(des);
                        // len will store phone description 

                        if (len == 4)
                        {
                            printf("(%c%c%c%c)\n",
                                des[0], des[1], des[2], des[3]);

                        }// display for description if it's lenght is 4 

                        else if (len == 3)
                        {
                            printf("(___)___-____ (%c%c%c)\n", 
                                des[0], des[1], des[2]);

                        }// display for description if its lenght is 3
                    }
                }
            
            
}

        }

    }

    printf("\n");
}


// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* Appoints, int MaxAppoints,
    struct Patient* patient, int maxPatients)
{
    int i = 0; // Variable for loop
    int patientNum; // Variable to store patient number
    int IDindex; // Variable to store index where patient number is stored
    int found = 0; // Variable used to check if appointment time is free
    int AppoinmentReady = 0; // Variable to end loop
    int freeslot = 0; // Variable used to array index which is free
    int available = 0; // variable used to determine if any appointment slots
                       // are available

    struct Date date = {0}; // Local struct date
    struct Time time = {0}; // Local struct time

    printf("Patient Number: ");
    patientNum = inputIntPositive();
    // inputIntPositive function called for input of patient number

    IDindex = findPatientIndexByPatientNum(patientNum, patient, maxPatients);
    // findPatientIndexByPatientNum called using patientNum as 1 of the        
    // arguments to determine if there is a patient who exists with the 
    // entered ID number

    for (i = 0; i < MaxAppoints; i++)
    {
        if (Appoints[i].patientNumber == 0)
        {
            available = 1;
        }
    } // Purpose of this for loop is to check if there are any available
      // spots for appointments. If there are avalible will be set to 1
    
    
    if (available == 1)
    { // indicates there are appointment spots available
        do
        {

            if (IDindex >= 0)
            { // indicates there is patient with the entered patient number

                do // do while loop will continue until a valid appointment 
                   // is entered
                
                {
                    found = 0;

                    printf("Year        : ");
                    date.year = inputIntPositive();
                    // Value for year found by calling inputIntPositve

                    printf("Month (1-12): ");
                    date.month = inputIntRange(1, 12);
                    // Value for month found by calling inputIntRange

                    if (date.month == 1 || date.month == 3 || date.month == 5 ||
                        date.month == 7 || date.month == 8 || date.month == 10
                        || date.month == 12)

                    {
                        printf("Day (1-%d)  : ", getLatestDay(date.month, date.year));
                        date.day = inputIntRange(1, getLatestDay(date.month, date.year));
                    } // Day display varies based on month. This ones for 
                      // months that have 31 days 

                    
                    else if (date.month == 4 || date.month == 6 ||
                        date.month == 9 || date.month == 11)
                    {
                        printf("Day (1-%d)  : ", getLatestDay(date.month, date.year));
                        date.day = inputIntRange(1, getLatestDay(date.month, date.year));
                    } // Day display varies based on month. This ones for 
                      // months that have 30 days 

                    
                    else if (date.month == 2 && date.year % 4 == 0)
                    {
                        printf("Day (1-%d)  : ", getLatestDay(date.month, date.year));
                        date.day = inputIntRange(1, getLatestDay(date.month, date.year));
                    } // Day display varies based on month. This ones for 
                      // febuuary on a leap year

                    else if (date.month == 2)
                    {
                        printf("Day (1-%d)  : ", getLatestDay(date.month, date.year));
                        date.day = inputIntRange(1, getLatestDay(date.month, date.year));
                    } // Day display varies based on month. This ones for 
                      // a regular febuary 


                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);
                    // value for hour found by calling inputIntRange

                    
                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);
                    // value for minute found by calling inputIntRange


                    for (i = 0; i < MaxAppoints; i++)
                    {
                        if (date.year == Appoints[i].date.year
                            && date.month == Appoints[i].date.month &&
                            date.day == Appoints[i].date.day
                            && time.hour == Appoints[i].time.hour
                            && time.min == Appoints[i].time.min)

                        {
                            found = 1;
                        }

                    } // This for loop is checking the Appoints array for if
                      // a appointment already exists for the time entered.
                      // If it does found is set to 1

                    if (found == 1)
                    {
                        printf("\nERROR: Appointment timeslot"
                            " is not available!\n\n");
                    } // This error message will display if a date and time
                      // entered that is already taken 

                    
                    else if ((time.hour < START_HOURS || time.hour > END_HOURS)
                        || (time.hour == END_HOURS && time.min > 0) ||
                        (time.min != 0 && time.min != APPOINTMENT_TIME))

                    {

                        printf("ERROR: Time must be between"
                            " %02d:00 and %02d:00 in %02d minute"
                            " intervals.\n\n", START_HOURS, END_HOURS,
                            APPOINTMENT_TIME);

                    } // if statement will check hour and minute input for
                      // correct values. If they are incorrect this error        
                      // message will be displayed 


                } while (found == 1);


                do
                { // This do while loop initiates if the appointment
                  // entered is available year, month and day wise, however
                  // still needs to be verifed hour and minute wise 
                    
                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);

                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);


                    if ((time.hour < 10 || time.hour > 14) ||
                        (time.hour == 14 && time.min > 0) ||
                        (time.min != 0 && time.min != 30))

                    {

                        printf("ERROR: Time must be between %02d:00"
                            " and %02d:00 in %02d minute intervals.\n\n",
                            START_HOURS, END_HOURS, APPOINTMENT_TIME);

                    }

                } while ((time.hour < 10 || time.hour > 14) ||
                    (time.hour == 14 && time.min > 0) ||
                    (time.min != 0 && time.min != 30));

            }

            
            for (i = 0; i < MaxAppoints; i++)
            {
                if (Appoints[i].patientNumber < 1 && freeslot == 0)
                {
                    freeslot = i;
                }
            
            } // The purpose of this for loop is to search the Appoints
              // array for the next free array index so that the value
              // the user entered can be stored within it

            
            
            Appoints[freeslot].date = date;
            Appoints[freeslot].time = time;
            Appoints[freeslot].patientNumber = patientNum;

            // The user inputted values for date, time and patientnum
            // are stored in the next available free slot within the
            // Appoints array

            printf("\n*** Appointment scheduled! ***\n\n");

            AppoinmentReady = 1;

        
        
        } while (AppoinmentReady == 0);

    }

    else
    {
    printf("\nNo appointment slots available\n");
    }

}


// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* Appoints, 
    int MaxAppoints, struct Patient* patient, int maxPatients)
{

    
    int checkID = 0; 
    int PatientNumber = 0;
    int year = 0, month = 0, day = 0;
    int i = 0;
    int found = 0;
    int checkAppoints = 0;

    printf("Patient Number: ");
    PatientNumber = inputIntPositive();
    // Patient number is inputed using the funtion inputIntPostive


    checkID = findPatientIndexByPatientNum(PatientNumber, patient, maxPatients);
    // The number entered is validated by using it as a argument in the
    // findPatientIndexByPatientNum function. We need to check if the 
    // patient exists. If it does a number other than -1 will be returned
    
    
    if (checkID != -1)
    {
        for (i = 0; i < MaxAppoints; i++)
        {
            if (PatientNumber == Appoints[i].patientNumber)
            {
                checkAppoints = 1;
            }

        } // This for loop will check if the patient number inputed has
          // registered for a appointment
        
        
        if (checkAppoints > 0)
        { // If the patient has registered the code block will execute
            
            printf("Year        : ");
            year = inputIntPositive(); // input for year

            printf("Month (1-12): ");
            month = inputIntRange(1, 12); // input for month

            if (month == 1 || month == 3 || month == 5 ||
                month == 7 || month == 8 || month == 10
                || month == 12)

            {
                printf("Day (1-31)  : "); // day display depends on month
                day = inputIntRange(1, 31); // input for day
            } 

            else if (month == 4 || month == 6 || month == 9 || month == 11)
            {
                printf("Day (1-30)  : "); // day display depends on month
                day = inputIntRange(1, 30); // input for day
            }

            else if (month == 2 && year % 4 == 0)
            {
                printf("Day (1-29)  : "); 
                // day display depends on month and if its a leap year
               
                day = inputIntRange(1, 29); // input for day
            }

            else if (month == 2)
            {
                printf("Day (1-28)  : "); 
                // day display depends on month and if its not a leap year
                
                day = inputIntRange(1, 28); // input for day
            }

            for (i = 0; i < MaxAppoints; i++)

            {
                if (year == Appoints[i].date.year && 
                    month == Appoints[i].date.month && 
                    day == Appoints[i].date.day)
                {
                    found = i;
                }
            
            } // For loop wil validate whether the entered values match 
              // a appointment

            
            if (found > 0)
             // If a appointment with the date and time entered exists the
             // following code block will execute
            {

                for (i = 0; i < maxPatients; i++)
                { // for loop will be used to determine patient name, phone
                  // number and phone description
                    
                    if (PatientNumber == patient[i].patientNumber)
                    {
                        printf("\nName  : %s\n", patient[i].name);
                        // patient name displayed
                        printf("Number: 0%d\n", patient[i].patientNumber);
                        char* phone = patient[i].phone.number;
                        int len = strlen(phone);

                        if (len == 10)
                        {
                            printf("Phone : (%c%c%c)%c%c%c-%c%c%c%c ",
                                phone[0], phone[1], phone[2], phone[3], 
                                phone[4],phone[5], phone[6], 
                                phone[7], phone[8], phone[9]);
                        
                        } // patient number displayed

                        else

                        {
                            printf("Phone : ");
                        }

                        printf("(%s)\n", patient[i].phone.description);
                        // patient description displayed
                        
                        char option;
                        
                        
                        printf("Are you sure you want to remove this" 
                            " appointment (y,n): ");
                        scanf(" %c", &option);

                        
                        
                        if (option == 'y')
                        
                        {
                            for (i = 0; i < MaxAppoints; i++)
                            {
                                if (PatientNumber == Appoints[i].patientNumber 
                                    && year == Appoints[i].date.year && 
                                    month == Appoints[i].date.month 
                                    && day == Appoints[i].date.day)
                                {
                                    Appoints[i].patientNumber = 0;
                                    Appoints[i].date.day = 0;
                                    Appoints[i].date.month = 0;
                                    Appoints[i].date.year = 0;
                                    Appoints[i].time.hour = 0;
                                    Appoints[i].time.min = 0;

                                }
                            
                            } // for loop will be used to match the patient
                              // number, year, and day to it's correct appoint
                              // ment. Once matched the appointment will be
                              // set to 0
                            
                            
                            clearInputBuffer();
                            printf("\nAppointment record has been rem"
                                "oved!\n\n");
                        }

                        else

                        {
                            printf("\n");
                            clearInputBuffer();

                        }
                         
                     
                    }
                
                    }

            }

            else
            {
                printf("\nNo Appointment found for that day\n");
            }

}
         
        else
        {
            printf("\nPatient has no appointments scheduled\n\n");
        }

}

    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }


}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)

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
// (Copy your code from MS#2)

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
// (Copy your code from MS#2)

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
// (Copy your code from MS#2)

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

int sortAppointments(struct ClinicData* data, int i, int j)
{
    struct Appointment* List = data->appointments;

    if (List[i].date.year < List[j].date.year) return -1;
    if (List[i].date.year > List[j].date.year) return 1;
    if (List[i].date.month < List[j].date.month) return -1;
    if (List[i].date.month > List[j].date.month) return 1;
    if (List[i].date.day < List[j].date.day) return -1;
    if (List[i].date.day > List[j].date.day) return 1;
    if (List[i].time.hour < List[j].time.hour) return -1;
    if (List[i].time.hour > List[j].time.hour) return 1;
    if (List[i].time.min < List[j].time.min) return -1;
    if (List[i].time.min > List[j].time.min) return 1;

    return 0; 
    
    // Function is being used to sort appointment date and time
    // based on lowest to highest, returns 1 if i is greater

}

int getLatestDay(int month, int year)
{
    int day = 0;
    
    if (month == 1 || month == 3 || month == 5 ||
        month == 7 || month == 8 || month == 10
        || month == 12)

    {
       day = 31;
    }

    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
       day = 30;
    }

    else if (month == 2 && year % 4 == 0)
    {
       day = 29;
    }

    else if (month == 2)
    {
       day = 28;
    }
    
    return day;
    
    // Function will return the value of the last day of the month 

}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)

void inputPatient(struct Patient* patient)
{
    
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    // Prints out new patient number
    
    printf("Name  : ");
    
    
    do
    
    {
        scanf(" %[^\n]*c", patient->name);
        

        if (strlen(patient->name) > 15)
        {

            printf("ERROR: String length must be no more than 15 chars: ");
        }
    
    } while (strlen(patient->name) > 15);
    
    
    // User input for new patient name 

    inputPhoneData(&patient->phone);
    // Function call for new patient phone number input
}

// Get user input for phone contact information
// (Copy your code from MS#2)

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
        inputCStringNumbers(Number, PHONE_LEN, PHONE_LEN);
       
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
        inputCStringNumbers(Number, PHONE_LEN, PHONE_LEN);
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
        inputCStringNumbers(Number, PHONE_LEN, PHONE_LEN); 
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

    



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:

int importPatients(const char* datafile, struct Patient patients[], int max)
{

    FILE* file = NULL;
    int i = 0;


    file = fopen(datafile, "r");

    if (file != NULL)
    {
        while (i < max && fscanf(file, "%d|%20[^|]|%4s|%15[^\n]\n", 
            &patients[i].patientNumber,
            patients[i].name, patients[i].phone.description, 
            patients[i].phone.number) > 0)
        {

            if (strcmp(patients[i].phone.number, "") == 0)
            {
                strcpy(patients[i].phone.description, "TBD");
            }

            i++;
        }
        
        // Patient number, name, phone number and description will be read 
        // from file 
    }

    else
    {
        printf("Error reading file\n");

        i = 0;
    }


    fclose(file);

    return i;

    // Function will read the contents of the text file holding
    // Patient information 
}


// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:

int importAppointments(const char* datafile, 
    struct Appointment appoints[], int max)
{
    FILE* file = NULL;
    int i = 0;

    file = fopen(datafile, "r");

    if (file != NULL)
    {
        while (i < max && fscanf(file, "%d,%d,%d,%d,%d,%d", 
            &appoints[i].patientNumber, &appoints[i].date.year, 
            &appoints[i].date.month,
            &appoints[i].date.day, &appoints[i].time.hour,
            &appoints[i].time.min) == 6)
        {
            i++;
        }


    } // patient number, appointment date and time will be read from file

    else
    {
        printf("Error reading file\n");
        i = 0;
    }


    fclose(file);

    return i;

    // Function will read the contents of the text file
    // holding appointment information

}