#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct node { //Struct creation along with needed elements
    int companyRegistrationNumber;
    char companyName[30];
    char companyCountry[30];
    int yearCompanyFound;
    char companyEmailAddress[30];
    char companyContactName[30];
    int lastOrder;
    int numOfEmployees;
    int averageAnnualOrder;
    int vatRegisteredOption;
    int averageTurnoverOption;
    int staffEmployedOption;
    int areaOfSalesOption;
    struct node* NEXT;
}companyT;

companyT* createNode();

void passwordProtectedAccess();
void menu();
void initialiseFromFile(companyT** headPtrAdd);
void addElemenetAtStart(companyT** headPtrAdd);
void addElementAtEnd(companyT* headPtr);
void displayList(companyT* headPtr);
void displaySpecficUser(companyT* headPtr);
void updateClientDetails(companyT* headPtr);
void deleteClient(companyT** headPtrAdd);
void deleteAtStart(companyT** headPtrAdd);
void deleteAtEnd(companyT* headPtr);
void deleteAtLocation(companyT* headPtr, int location);
int listLength(companyT* headPtr);
void generateStatistics(companyT* headPtr);
void printAllClientDetailsToReportFile(companyT* headPtr);
//void listClients(companyT* headPtr);
void printToClientFile(companyT* headPtr);
//void deleteAllNodes(companyT* headPtr);

void main() {
    passwordProtectedAccess();
}
void menu() {
    FILE* fileCreatePtr; //File pointer to create clients.txt file
    FILE* fileReadPtr; //File pointer to read clients.txt file
    companyT* headPtr = NULL; //Head pointer for linked list

    int userChoice;

    fileReadPtr = fopen("clients.txt", "r+");
    if (NULL == fileReadPtr) { //Checking if file exsists
        fileCreatePtr = fopen("clients.txt", "w");
        printf("\nClient File was not read and instead was created instead.\n");
    }
    initialiseFromFile(&headPtr);
    printf("\n\n---Welcome to the Menu---\nPlease select your options:\n1: Add Client(Must be unique)\n2: Display All Client Details to Screen\n3: Display Particular Client\n4: Update A Clients Details\n5: Delete a Client\n6: Generate Statistics\n7: Print All Client Details Into A Report File\n8: List All Clients In Order Of Their Last Average Turnover\n-1: Exit\nInput: ");
    scanf("%d", &userChoice);
    while (userChoice != -1) { //Menu Input
        if (userChoice == 1) {
            if (headPtr == NULL)
                addElemenetAtStart(&headPtr);
            else
                addElementAtEnd(headPtr);
        }
        else if (userChoice == 2) {
            if (headPtr == NULL)
                printf("\nThe list is empty");
            else
                displayList(headPtr);
        }
        else if (userChoice == 3) {
            if (headPtr == NULL)
                printf("\nThe list is empty");
            else
                displaySpecficUser(headPtr);
        }
        else if (userChoice == 4) {
            if (headPtr == NULL)
                printf("\nThe list is empty");
            else
                updateClientDetails(headPtr);
        }
        else if (userChoice == 5) {
            if (headPtr == NULL)
                printf("\nThe list is empty");
            else
                deleteClient(&headPtr);
        }
        else if (userChoice == 6) generateStatistics(headPtr);
        else if (userChoice == 7) printAllClientDetailsToReportFile(headPtr);
        else if (userChoice == 8) {
            if (headPtr == NULL)
                printf("\nThe list is empty");
            else
                //listClients(headPtr);
                printf("Does not exsist");
        }


        printf("\n\n---Welcome to the Menu---\nPlease select your options:\n1: Add Client(Must be unique)\n2: Display All Client Details to Screen\n3: Display Particular Client\n4: Update A Clients Details\n5: Delete a Client\n6: Generate Statistics\n7: Print All Client Details Into A Report File\n8: List All Clients In Order Of Their Last Average Turnover\n-1: Exit\nInput: ");
        scanf("%d", &userChoice);
    }

}
void passwordProtectedAccess() {
    FILE* fileCreatePtr; //File pointer to create login.txt file
    FILE* fileReadPtr; //File pointer to read login.txt file

    char usernameInput[20], passwordInput[30]; //User Input of username and password
    char fileUsername[20], filePassword[30]; //char storing file usernames and passwords temporairly

    int usernameNotFound = 1, passwordNotFound = 1, usernameLineNumber = 1, passwordLineNumber = 1;
    int usernameCounter = 0, i, passwordCounter = 0, maxcharacters = 6;

    //File Reading and creation
    fileReadPtr = fopen("login.txt", "r"); //Reading data from login file
    if (NULL == fileReadPtr) {
        fileCreatePtr = fopen("login.txt", "w"); //If login file does not exsist - create
        printf("File was not read and instead was created - please ensure you have a populated login text file \n");
        passwordProtectedAccess(); //Recall function if file not found
    }

    //Username input
    printf("Please enter your Username to access this system (6 max characters): ");
    scanf("%s", usernameInput);

    //returns line number of username entered and stores it in usernameCounter
    while (fgets(fileUsername, sizeof fileUsername, fileReadPtr)) {
        if (strstr(fileUsername, usernameInput)) //Used to match line numbers on the text file so the username and password match
            usernameCounter = usernameLineNumber;

        if (strchr(fileUsername, '\n'))
            usernameLineNumber += 1;
    }

    fileReadPtr = fopen("login.txt", "r"); //Used to reset the file pointer

    //Scanning username from file - https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/
    while (fscanf(fileReadPtr, "%s %*s", fileUsername) == 1) {
        if (strcmp(fileUsername, usernameInput) == 0)
            usernameNotFound = 2;
    }

    if (usernameNotFound != 2) {
        printf("Username Not Found - Exiting application for security reasons\n");
        exit(0);
    }
    else {
        fileReadPtr = fopen("login.txt", "r"); //Used to reset the file pointer

        printf("Please enter your Password to the corosponding username (6 max characters): ");
        int characterPosition = 0;
        char ch;
        while (1) { //Used to print * for password
            ch = getch();
            if (ch == 13) //Enter key pressed
                break;
            else if (ch == 8) { //Backspace hit
                if (characterPosition > 0) {
                    characterPosition--;
                    passwordInput[characterPosition] = '\0';
                    printf("\b \b");
                }
            }
            else if (ch == 32 || ch == 9)
                continue; //tab or space pressed
            else { //Show *
                if (characterPosition < maxcharacters) {
                    passwordInput[characterPosition] = ch;
                    characterPosition++;
                    printf("*");
                }
                else { //If input more than 6 chars
                    printf("\nInput exceeds maximum password lenght of %d, Only first characters of %d will be considered", maxcharacters, maxcharacters);
                    break;
                }
            }
        }
        passwordInput[characterPosition] = '\0'; //Adding end character to char array
        //returns line number of password entered and stores it in passwordCounter
        while (fgets(filePassword, sizeof filePassword, fileReadPtr)) {
            if (strstr(filePassword, passwordInput))
                passwordCounter = passwordLineNumber; //Used for password line number on text file to match username

            if (strchr(filePassword, '\n'))
                passwordLineNumber += 1;
        }

        fileReadPtr = fopen("login.txt", "r"); //Used to reset the file pointer
        while (fscanf(fileReadPtr, "%*s %s", filePassword) == 1) {
            if (strcmp(filePassword, passwordInput) == 0) {
                if (usernameCounter == passwordCounter) {
                    printf("\nSuccess - access granted");
                    menu();
                    passwordNotFound = 2;
                }
                else
                    passwordCounter++;
            }
        }
        if (passwordNotFound != 2) {
            printf("\nPassword was incorrectly entered - kicking out of system\n");
            exit(0);
        }
    }
}
void initialiseFromFile(companyT** headPtrAdd) {
    FILE* fileReadPtr = fopen("clients.txt", "r");//reading client file
    printf("\nPlease make sure if loading custom client data you follow the correct format.");
    char buf[100], c;
    companyT* newNode, * temp;
    int count = 0, i, cNum = 0;

    for (c = getc(fileReadPtr); c != EOF; c = getc(fileReadPtr)) {
        if (c == '\n') // Increment count if this character is newline
            count = count + 1; //Counts lines in text file
    }

    if (count >= 1) {
        //Adding first line of text file to start of linked list
        newNode = (companyT*)malloc(sizeof(companyT));
        fileReadPtr = fopen("clients.txt", "r");
        fscanf(fileReadPtr, "%d", &newNode->companyRegistrationNumber);
        fscanf(fileReadPtr, "%s", &newNode->companyName);
        fscanf(fileReadPtr, "%s", newNode->companyCountry);
        fscanf(fileReadPtr, "%d", &newNode->yearCompanyFound);
        fscanf(fileReadPtr, "%s", &newNode->companyEmailAddress);
        fscanf(fileReadPtr, "%s", &newNode->companyContactName);
        fscanf(fileReadPtr, "%d", &newNode->lastOrder);
        fscanf(fileReadPtr, "%d", &newNode->numOfEmployees);
        fscanf(fileReadPtr, "%d", &newNode->averageAnnualOrder);
        fscanf(fileReadPtr, "%d", &newNode->vatRegisteredOption);
        fscanf(fileReadPtr, "%d", &newNode->averageTurnoverOption);
        fscanf(fileReadPtr, "%d", &newNode->staffEmployedOption);
        fscanf(fileReadPtr, "%d", &newNode->areaOfSalesOption);

        newNode->NEXT = *headPtrAdd; //Make next equal null
        *headPtrAdd = newNode; //Make headptr point to new node
    }

    for (i = 0; i < (count - 1); i++) {
        //Adding remainder of file to end of list
        temp = *headPtrAdd;
        newNode = (companyT*)malloc(sizeof(companyT));
        fscanf(fileReadPtr, "%d", &newNode->companyRegistrationNumber);
        fscanf(fileReadPtr, "%s", &newNode->companyName);
        fscanf(fileReadPtr, "%s", newNode->companyCountry);
        fscanf(fileReadPtr, "%d", &newNode->yearCompanyFound);
        fscanf(fileReadPtr, "%s", &newNode->companyEmailAddress);
        fscanf(fileReadPtr, "%s", &newNode->companyContactName);
        fscanf(fileReadPtr, "%d", &newNode->lastOrder);
        fscanf(fileReadPtr, "%d", &newNode->numOfEmployees);
        fscanf(fileReadPtr, "%d", &newNode->averageAnnualOrder);
        fscanf(fileReadPtr, "%d", &newNode->vatRegisteredOption);
        fscanf(fileReadPtr, "%d", &newNode->averageTurnoverOption);
        fscanf(fileReadPtr, "%d", &newNode->staffEmployedOption);
        fscanf(fileReadPtr, "%d", &newNode->areaOfSalesOption);

        while (temp->NEXT != NULL) {
            temp = temp->NEXT;
        }
        newNode->NEXT = NULL;
        temp->NEXT = newNode;
    }
}
void addElemenetAtStart(companyT** headPtrAdd) {
    companyT* newNode;

    newNode = createNode();
    //No need to check for unique company reg when adding at start
    newNode->NEXT = *headPtrAdd;
    *headPtrAdd = newNode;
    printToClientFile(*headPtrAdd);
}
void addElementAtEnd(companyT* headPtr) {
    companyT* temp = headPtr;
    companyT* temp1;
    companyT* newNode = (companyT*)malloc(sizeof(companyT));
    companyT* checkForRegistration = headPtr;

    //Need to check for registration Number
    int checkForReg, duplicateFound;
    char clientEmail[100];
    char* resultAtSymbol, resultFullStop;
    printf("\nPlease Enter The Company Registration Number(Must be unique): ");
    scanf("%d", &checkForReg);
    while (checkForRegistration != NULL) {
        temp1 = headPtr;
        duplicateFound = 0;
        while (temp1 != NULL) { //Duplication Check
            if (checkForReg == checkForRegistration->companyRegistrationNumber) {
                duplicateFound++;
                break; //Break if duplicate is found
            }
            temp1 = temp1->NEXT;
        }
        while (duplicateFound != 0) //While duplicate is found
        {
            duplicateFound = 1;
            checkForRegistration = headPtr;
            printf("\nYou have entered the same registration number as another company, please enter a unique one: ");
            scanf("%d", &checkForReg);
            while (checkForRegistration != NULL) {
                if (checkForReg == checkForRegistration->companyRegistrationNumber)
                    duplicateFound = 3;
                if (duplicateFound != 3)
                    duplicateFound = 0; //If duplicate is not found exit while loop
                checkForRegistration = checkForRegistration->NEXT;
            }
        }
        if (checkForRegistration == NULL)
            break; //Check to avoid nullptr error
        else
            checkForRegistration = checkForRegistration->NEXT;
    }
    newNode->companyRegistrationNumber = checkForReg; //Assigning correct registration number to newNode

    printf("\nPlease enter the Company Name, Company Country, and Year it was Founded: ");
    scanf("%s %s %d", newNode->companyName, newNode->companyCountry, &newNode->yearCompanyFound);
    //Email Check
    printf("\nEnter the Company Email(Must be a valid Email):");
    scanf("%s", clientEmail);
    resultAtSymbol = strstr(clientEmail, "@"); //If there is no @ or . in the email it reutrns null
    resultFullStop = strstr(clientEmail, ".");
    while (resultAtSymbol == NULL || resultFullStop == NULL) {
        printf("\nWrong email type entered - enter a valid one with a @ and a fullstop: ");
        scanf("%s", clientEmail);
        resultAtSymbol = strstr(clientEmail, "@");
        resultFullStop = strstr(clientEmail, ".");
    }
    strcpy(newNode->companyEmailAddress, clientEmail);

    printf("\nEnter the Company Contact Name, Last Order, Number of employees and Average Annual Order:");
    scanf("%s %d %d %d", newNode->companyContactName, &newNode->lastOrder, &newNode->numOfEmployees, &newNode->averageAnnualOrder);
    printf("\nEnter if the Client is Vat Registered - 1: Yes, 2: No:");
    scanf("%d", &newNode->vatRegisteredOption);
    printf("\nEnter the Clients Average Turnover - 1: Less than €1 Million, 2: Less than €10 Million, 3: Over €10 Million:");
    scanf("%d", &newNode->averageTurnoverOption);
    printf("\nEnter the Clients Number of Staff - 1: Less than 10, 2: Less than 100, 3: Over 100:");
    scanf("%d", &newNode->staffEmployedOption);
    printf("\nEnter the Clients Area of Sales - 1: ICT, 2: Medical Devices, 3: Other area:");
    scanf("%d", &newNode->areaOfSalesOption);

    while (temp->NEXT != NULL) {
        temp = temp->NEXT;
    }

    newNode->NEXT = NULL;
    temp->NEXT = newNode;
    printToClientFile(headPtr);
}
void displayList(companyT* headPtr) {
    companyT* temp = headPtr;
    while (temp != NULL) {
        printf("\n\nComapany Reg %d\nCompany Name %s\nCompany Country %s\nYear Founded %d\n", temp->companyRegistrationNumber, temp->companyName, temp->companyCountry, temp->yearCompanyFound);
        printf("Company Email %s\nCompany Contact Name %s\nLast Order %d\nNumber of Employees %d\n", temp->companyEmailAddress, temp->companyContactName, temp->lastOrder, temp->numOfEmployees);
        printf("Average Annual Order %d\nVat Option %d\nAverage Turnover Option %d\nStaff Employed Option %d\nArea of Sales %d\n\n", temp->averageAnnualOrder, temp->vatRegisteredOption, temp->averageTurnoverOption, temp->staffEmployedOption, temp->areaOfSalesOption);
        temp = temp->NEXT;
    }
}
void displaySpecficUser(companyT* headPtr) {
    companyT* temp = headPtr;
    int userSearch, found = 0;
    printf("\nEnter the Clients Registration Number you want to display:");
    scanf("%d", &userSearch);
    while (temp != NULL) {
        if (temp->companyRegistrationNumber == userSearch) {
            found = 1;
            printf("\n\nComapany Reg %d\nCompany Name %s\nCompany Country %s\nYear Founded %d\n", temp->companyRegistrationNumber, temp->companyName, temp->companyCountry, temp->yearCompanyFound);
            printf("Company Email %s\nCompany Contact Name %s\nLast Order %d\nNumber of Employees %d\n", temp->companyEmailAddress, temp->companyContactName, temp->lastOrder, temp->numOfEmployees);
            printf("Average Annual Order %d\nVat Option %d\nAverage Turnover Option %d\nStaff Employed Option %d\nArea of Sales %d\n\n", temp->averageAnnualOrder, temp->vatRegisteredOption, temp->averageTurnoverOption, temp->staffEmployedOption, temp->areaOfSalesOption);
        }
        if (temp == NULL)
            break;
        else
            temp = temp->NEXT;
    }
    if (found == 0)
        printf("\nClient Not Found");

}
void updateClientDetails(companyT* headPtr) {
    companyT* temp = headPtr;
    int userSearch, found = 0;
    char clientEmail[100];
    char* resultAtSymbol, resultFullStop;
    //Entering data
    printf("\nEnter the Clients Registration Number you want to update - if the registration number was entered correctly then please delete the client and create a new one:");
    scanf("%d", &userSearch);
    while (temp != NULL) {
        if (temp->companyRegistrationNumber == userSearch) {
            found = 1;
            printf("\nPlease enter the Company Name, Company Country, and Year it was founded Founded: ");
            scanf("%s %s %d", temp->companyName, temp->companyCountry, &temp->yearCompanyFound);
            //Email Check
            printf("\nEnter the Company Email(Must be a valid Email):");
            scanf("%s", clientEmail);
            resultAtSymbol = strstr(clientEmail, "@");
            resultFullStop = strstr(clientEmail, ".");
            while (resultAtSymbol == NULL || resultFullStop == NULL) {
                printf("\nWrong email type entered - enter a valid one with a @ and a fullstop: ");
                scanf("%s", clientEmail);
                resultAtSymbol = strstr(clientEmail, "@");
                resultFullStop = strstr(clientEmail, ".");
            }
            strcpy(temp->companyEmailAddress, clientEmail);

            printf("\nEnter the Company Contact Name, Last Order, Number of employees and Average Annual Order:");
            scanf("%s %d %d %d", temp->companyContactName, &temp->lastOrder, &temp->numOfEmployees, &temp->averageAnnualOrder);
            printf("\nEnter if the Client is Vat Registered - 1: Yes, 2: No:");
            scanf("%d", &temp->vatRegisteredOption);
            printf("\nEnter the Clients Average Turnover - 1: Less than €1 Million, 2: Less than €10 Million, 3: Over €10 Million:");
            scanf("%d", &temp->averageTurnoverOption);
            printf("\nEnter the Clients Number of Staff - 1: Less than 10, 2: Less than 100, 3: Over 100:");
            scanf("%d", &temp->staffEmployedOption);
            printf("\nEnter the Clients Area of Sales - 1: ICT, 2: Medical Devices, 3: Other area:");
            scanf("%d", &temp->areaOfSalesOption);
        }
        if (temp == NULL)
            break;
        else
            temp = temp->NEXT;

    }


    printToClientFile(headPtr);
}
void deleteAtStart(companyT** headPtrAdd) {
    companyT* temp = *headPtrAdd; //temp pointes to value of headptr
    *headPtrAdd = (*headPtrAdd)->NEXT; //headptr points to node 2
    free(temp); //free first node from memory
    printToClientFile(*headPtrAdd);
}
void deleteAtEnd(companyT* headPtr) {
    companyT* temp = headPtr;
    companyT* prev = NULL;

    while (temp->NEXT != NULL) {
        prev = temp;
        temp = temp->NEXT;
    }

    prev->NEXT = NULL;
    free(temp);
    printToClientFile(headPtr);
}
void deleteAtLocation(companyT* headPtr, int location) {
    companyT* temp = headPtr; //temp = headptr
    companyT* prev;
    int i;

    for (i = 0; i < location - 1; i++) //i goes to location number
    {
        prev = temp;
        temp = temp->NEXT;
    }

    prev->NEXT = temp->NEXT;
    free(temp);
    printToClientFile(headPtr);
}
void deleteClient(companyT** headPtrAdd) {
    struct node* temp = *headPtrAdd;
    struct node* prev;
    int userEntryDeletion, location = 0, found = 0, locationOfElement;

    printf("\nPlease enter the company registration number you wish to delete: ");
    scanf("%d", &userEntryDeletion);
    //finding location to delete at
    while (temp != NULL) {
        location++;
        if (temp->companyRegistrationNumber == userEntryDeletion) {
            found = 1;
            locationOfElement = location;
        }
        temp = temp->NEXT;
    }
    if (found != 1)
        printf("\nRegistration Number Not Found");
    while (found != 1) {
        temp = *headPtrAdd;
        found = 2;
        location = 0;
        printf("\nPlease enter a valid company registration number: ");
        scanf("%d", &userEntryDeletion);
        while (temp != NULL) {
            location++;
            if (temp->companyRegistrationNumber == userEntryDeletion) {
                found = 1;
                locationOfElement = location;
            }
            temp = temp->NEXT;
        }
    }
    if (locationOfElement == 1)
        deleteAtStart(headPtrAdd);
    else if (locationOfElement == (listLength(*headPtrAdd)))
        deleteAtEnd(*headPtrAdd);
    else
        deleteAtLocation(*headPtrAdd, locationOfElement);

    printToClientFile(*headPtrAdd);
}
int listLength(companyT* headPtr) {
    struct node* temp = headPtr;
    int count = 0;
    while (temp != NULL) {
        count = count + 1;
        temp = temp->NEXT;
    }
    return count;
}
void generateStatistics(companyT* headPtr) {
    //Code to create statistics file
    FILE* fileCreatePtr; //File pointer to create statistics.txt file
    companyT* temp = headPtr;
    fileCreatePtr = fopen("statistics.txt", "w");

    //ICB statistics generation
    int lessThanOne = 0, lessThanTen = 0, overTen = 0;
    int sLessThanOne = 0, sLessThanTen = 0, sOverTen = 0;
    int tLessThanOne = 0, tLessThanTen = 0, tOverTen = 0;
    while (temp != NULL) {
        if (temp->areaOfSalesOption == 1) {
            if (temp->averageTurnoverOption == 1) lessThanOne++;
            if (temp->averageTurnoverOption == 2) lessThanTen++;
            if (temp->averageTurnoverOption == 3) overTen++;
        }
        if (temp->areaOfSalesOption == 2) {
            if (temp->averageTurnoverOption == 1) sLessThanOne++;
            if (temp->averageTurnoverOption == 2) sLessThanTen++;
            if (temp->averageTurnoverOption == 3) sOverTen++;
        }
        if (temp->areaOfSalesOption == 3) {
            if (temp->averageTurnoverOption == 1) tLessThanOne++;
            if (temp->averageTurnoverOption == 2) tLessThanTen++;
            if (temp->averageTurnoverOption == 3) tOverTen++;
        }
        if (temp == NULL)
            break;
        else
            temp = temp->NEXT;
    }
    fprintf(fileCreatePtr, "ICT:\nLess than 1 million euro: %d\nLess than 10 million euro: %d\nMore than 10 million euro: %d\n\n", lessThanOne, lessThanTen, overTen);
    fprintf(fileCreatePtr, "Medical Devices:\nLess than 1 million euro: %d\nLess than 10 million euro: %d\nMore than 10 million euro: %d", sLessThanOne, sLessThanTen, sOverTen);
    fprintf(fileCreatePtr, "\n\nOther Area:\nLess than 1 million euro: %d\nLess than 10 million euro: %d\nMore than 10 million euro: %d", tLessThanOne, tLessThanTen, tOverTen);
    //End of ICB Statistic Generation
    lessThanOne = 0, lessThanTen = 0, overTen = 0, tLessThanOne = 0, tLessThanTen = 0, tOverTen = 0, tLessThanOne = 0, tLessThanTen = 0, tOverTen = 0;
    //Number of Employees Statistic Generation
    temp = headPtr;
    while (temp != NULL) {
        if (temp->staffEmployedOption == 1) {
            if (temp->averageTurnoverOption == 1) lessThanOne++;
            if (temp->averageTurnoverOption == 2) lessThanTen++;
            if (temp->averageTurnoverOption == 3) overTen++;
        }
        if (temp->staffEmployedOption == 2) {
            if (temp->averageTurnoverOption == 1) sLessThanOne++;
            if (temp->averageTurnoverOption == 2) sLessThanTen++;
            if (temp->averageTurnoverOption == 3) sOverTen++;
        }
        if (temp->staffEmployedOption == 3) {
            if (temp->averageTurnoverOption == 1) tLessThanOne++;
            if (temp->averageTurnoverOption == 2) tLessThanTen++;
            if (temp->averageTurnoverOption == 3) tOverTen++;
        }
        if (temp == NULL)
            break;
        else
            temp = temp->NEXT;
    }
    fprintf(fileCreatePtr, "\n\nLess Than 10 Employees:\nLess than 1 million euro: %d\nLess than 10 million euro: %d\nMore than 10 million euro: %d\n\n", lessThanOne, lessThanTen, overTen);
    fprintf(fileCreatePtr, "Less Than 100 Employees:\nLess than 1 million euro: %d\nLess than 10 million euro: %d\nMore than 10 million euro: %d", sLessThanOne, sLessThanTen, sOverTen);
    fprintf(fileCreatePtr, "\n\nOver 100 Employees:\nLess than 1 million euro: %d\nLess than 10 million euro: %d\nMore than 10 million euro: %d", tLessThanOne, tLessThanTen, tOverTen);
    fclose(fileCreatePtr);
    printf("\nStatistics generated to statistics.txt file.");
}
void printAllClientDetailsToReportFile(companyT* headPtr) {
    FILE* fileCreatePtr = fopen("report.txt", "w");
    companyT* temp = headPtr;
    while (temp != NULL) {//Report file creation and printing 
        fprintf(fileCreatePtr, "Comapany Reg: %d\nCompany Name: %s\nCompany Country: %s\nYear Founded: %d\n", temp->companyRegistrationNumber, temp->companyName, temp->companyCountry, temp->yearCompanyFound);
        fprintf(fileCreatePtr, "Company Email: %s\nCompany Contact Name: %s\nLast Order: %d\nNumber of Employees: %d\n", temp->companyEmailAddress, temp->companyContactName, temp->lastOrder, temp->numOfEmployees);
        fprintf(fileCreatePtr, "Average Annual Order: %d\nVat Option: %d\nAverage Turnover Option: %d\nStaff Employed Option: %d\nArea of Sales: %d\n\n", temp->averageAnnualOrder, temp->vatRegisteredOption, temp->averageTurnoverOption, temp->staffEmployedOption, temp->areaOfSalesOption);
        if (temp == NULL)
            break;
        else
            temp = temp->NEXT;
    }
    fclose(fileCreatePtr);
    printf("\nReport File Created.");
}
//Attempt to sort
//void listClients(companyT* headPtr) { //Known issue is that it duplicates linked list nodes due to the initising from file.
//    //List clients in order of average turnover
//    companyT* temp, * current = headPtr;
//    int currentAvg = 0, nextAvg = 0;
//    char cName[100], cName2[100];
//
//    while (current != NULL) { // starting ptr - starts at headPtr
//        temp = current->NEXT; //Temp = starting ptr - next
//        while (temp != NULL) {
//            if (temp->averageAnnualOrder > current->averageAnnualOrder) { //If currentAvg > next Avg
//                //Changing name
//                strcpy(cName, current->companyName);
//                strcpy(cName2, temp->companyName);
//                strcpy(current->companyName, cName2);
//                strcpy(temp->companyName, cName);
//                //Changing turnover
//                currentAvg = current->averageAnnualOrder; //make int equal current avg
//                nextAvg = temp->averageAnnualOrder; //Make int next avg equal next avg
//                current->averageAnnualOrder = nextAvg; // make current equal larger number
//                temp->averageAnnualOrder = currentAvg;
//            }
//            temp = temp->NEXT;
//        }
//        printf("\nCompany Name: %s\nAverage Turnover : %d", current->companyName, current->averageAnnualOrder);
//        current = current->NEXT;
//    }
//    deleteAllNodes(headPtr);
//    //initialiseFromFile(&headPtr);
//}
void printToClientFile(companyT* headPtr) {
    FILE* fileCreatePtr = fopen("clients.txt", "w");
    companyT* temp = headPtr;//Printing to clients file
    while (temp != NULL) {
        fprintf(fileCreatePtr, "%d\t%s\t%s\t%d\t", temp->companyRegistrationNumber, temp->companyName, temp->companyCountry, temp->yearCompanyFound);
        fprintf(fileCreatePtr, "%s\t%s\t%d\t%d\t", temp->companyEmailAddress, temp->companyContactName, temp->lastOrder, temp->numOfEmployees);
        fprintf(fileCreatePtr, "%d\t%d\t%d\t%d\t%d\n", temp->averageAnnualOrder, temp->vatRegisteredOption, temp->averageTurnoverOption, temp->staffEmployedOption, temp->areaOfSalesOption);
        if (temp == NULL)
            break;
        else
            temp = temp->NEXT;
    }
    fclose(fileCreatePtr);
}
companyT* createNode() {
    companyT* newNode;
    newNode = (companyT*)malloc(sizeof(companyT));
    char clientEmail[100];
    char* resultAtSymbol, resultFullStop;
    //Function to create nodes
    printf("\nPlease Enter The Company Registration Number(Must be unique): ");
    scanf("%d", &newNode->companyRegistrationNumber);
    printf("\nPlease enter the Company Name, Company Country, and Year it was founded Founded: ");
    scanf("%s %s %d", newNode->companyName, newNode->companyCountry, &newNode->yearCompanyFound);
    //Email Check
    printf("\nEnter the Company Email(Must be a valid Email):");
    scanf("%s", clientEmail);
    resultAtSymbol = strstr(clientEmail, "@");
    resultFullStop = strstr(clientEmail, ".");
    while (resultAtSymbol == NULL || resultFullStop == NULL) {
        printf("\nWrong email type entered - enter a valid one with a @ and a fullstop: ");
        scanf("%s", clientEmail);
        resultAtSymbol = strstr(clientEmail, "@");
        resultFullStop = strstr(clientEmail, ".");
    }
    strcpy(newNode->companyEmailAddress, clientEmail);

    printf("\nEnter the Company Contact Name, Last Order, Number of employees and Average Annual Order:");
    scanf("%s %d %d %d", newNode->companyContactName, &newNode->lastOrder, &newNode->numOfEmployees, &newNode->averageAnnualOrder);
    printf("\nEnter if the Client is Vat Registered - 1: Yes, 2: No:");
    scanf("%d", &newNode->vatRegisteredOption);
    printf("\nEnter the Clients Average Turnover - 1: Less than €1 Million, 2: Less than €10 Million, 3: Over €10 Million:");
    scanf("%d", &newNode->averageTurnoverOption);
    printf("\nEnter the Clients Number of Staff - 1: Less than 10, 2: Less than 100, 3: Over 100:");
    scanf("%d", &newNode->staffEmployedOption);
    printf("\nEnter the Clients Area of Sales - 1: ICT, 2: Medical Devices, 3: Other area:");
    scanf("%d", &newNode->areaOfSalesOption);

    return newNode;
}
//Attempt to make sorting work
//void deleteAllNodes(companyT* headPtr) {
//    int sizeOfList = listLength(headPtr), i;
//    printf("\n\n%d\n\n", sizeOfList);
//    for (i = 0; i < (sizeOfList - 1); i++)
//    {
//        companyT* temp = headPtr;
//        companyT* prev = NULL;
//
//        while (temp->NEXT != NULL) {
//            prev = temp;
//            temp = temp->NEXT;
//        }
//
//        prev->NEXT = NULL;
//        free(temp);
//    }
//    companyT* temp1 = headPtr; //temp pointes to value of headptr
//    headPtr = (headPtr)->NEXT; //headptr points to node 2
//    free(temp1); //free first node from memory
//}

