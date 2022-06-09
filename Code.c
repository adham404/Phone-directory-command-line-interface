#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int day, month, year;
} Date;

typedef struct{
    char firstName[20], lastName[20];
    Date birth;
    char address[40];
    char number[12];
    char email[30];
    int tot;
} Entry;

Entry entries[100];
int numOfEntries = 0;

void showMenu();
int menuSelect(int *loaded);
void loadFile(int *loaded);
void searchMenu();
void deleteEntry();
void addEntery();
void modifyEntry();
void printSorted();
void sortByName();
void sortByDOB();
void printing();
void saveFile();
int exitApp();

void validateNames(char name[]);
void validateDOB(int *day, int *month, int *year);
void validateNumber(char number[]);
void validateEmail(char email[]);
void lowerCase(char name[]);        // A FUNCTION TO TURN A STRING TO LOWERCASE
void firstToUpper(char name[]);     // A FUNCTION TO CAPITALIZE FIRST LETTER OF NAME
char *checkForCharacter(char str[]); // A FUNCTION TO ENSURE THERE ARE ONLY NUMBERS IN A STRING
void checkForNull(char str[]);     // A FUNCTION TO MAKE SURE THE USER DOES NOT ENTER AN EMPTY INPUT

int main(){
    int choice, loaded=0;
    showMenu();
    do{
        choice = menuSelect(&loaded);
    }while(choice);
    return 0;
}


void showMenu(){
    printf("[1] Load a Directory.\t\t\t");
    printf("[5] Modify a Specific Entry.\n");
    printf("[2] Search for a Specific Entry.\t");
    printf("[6] Print Entire Sorted Directory.\n");
    printf("[3] Add a New Entry.\t\t\t");
    printf("[7] Save Current Directory.\n");
    printf("[4] Delete an Entry.\t\t\t");
    printf("[0] Exit.\n");
    printf("___________________________________________________________________\n");
}

int menuSelect(int *loaded){
    int valid, choice;
    char *choiceTest;
    printf("Please Select an Option: ");
    gets(choiceTest);
    do{
        choice = atoi(checkForCharacter(choiceTest));
        valid = 1;
        switch(choice){
        case 1:
            if(*loaded)
                printf("Directory Already Loaded.\n");
            else
                loadFile(loaded);
            break;
        case 2:
            if(!*loaded)
                printf("Please Load Directory First.\n");
            else
                searchMenu();
            break;
        case 3:
            if(!*loaded)
                printf("Please Load Directory First.\n");
            else
                addEntery();
            break;
        case 4:
            if(!*loaded)
                printf("Please Load Directory First.\n");
            else
                deleteEntry();
            break;
        case 5:
            if(!*loaded)
                printf("Please Load Directory First.\n");
            else
                modifyEntry();
            break;
        case 6:
            if(!*loaded)
                printf("Please Load Directory First.\n");
            else
                printSorted();
            break;
        case 7:
            if(!*loaded)
                printf("Please Load Directory First.\n");
            else
                saveFile();
            break;
        case 0:
            if(exitApp())
                return 0;
            break;
        default:
            printf("Please Enter a Valid Number: ");
            gets(choiceTest);
            valid = 0;
        }
    }while(!valid);
    return 1;
}

void loadFile(int *loaded){
    FILE *f1;
    f1 = fopen("directory.txt","r");
    if(f1){
        *loaded = 1;
        while(!feof(f1)){
            fscanf(f1,"%[^,],", entries[numOfEntries].lastName);
            lowerCase(entries[numOfEntries].lastName);
            fscanf(f1,"%[^,],", entries[numOfEntries].firstName);
            lowerCase(entries[numOfEntries].firstName);
            fscanf(f1,"%d-%d-%d,", &entries[numOfEntries].birth.day, &entries[numOfEntries].birth.month, &entries[numOfEntries].birth.year);
            fscanf(f1,"%[^,],", entries[numOfEntries].address);
            fscanf(f1,"%[^,],", entries[numOfEntries].number);
            fscanf(f1,"%[^\n]\n", entries[numOfEntries].email);
            numOfEntries++;
        }
        fclose(f1);
        printf("------------------------------\n");
        printf("Directory Successfully Loaded.\n");
        printf("------------------------------\n");
    }
    else
        printf("Directory Not Found.\n");
}

void searchMenu(){
    char name[10];
    printf("------------------------------\n");
    printf("Enter last name: ");
    gets(name);
    validateNames(name);
    int i,valid=0, num=1;
    for(i=0; i<numOfEntries; i++){
        if(strcmp(entries[i].lastName,name) == 0){
            valid = 1;
            break;
        }
    }
    if(!valid){
        printf("\nThis last name couldn't be found.\n");
        printf("------------------------------\n");
    }
    else{
        printf("Data of Entries with the same last name:\n");
        printf("___________________________________________________________________\n");
        for(i=0; i<numOfEntries; i++){
            if(strcmp(entries[i].lastName,name) == 0){
                printf("%d - %s, ", num, entries[i].firstName);
                printf("%d-%d-%d, ",entries[i].birth.day,entries[i].birth.month,entries[i].birth.year);
                printf("%s, ",entries[i].address);
                printf("%s, ",entries[i].number);
                printf("%s\n",entries[i].email);
                num++;
            }
        }
            printf("___________________________________________________________________\n");
    }
}

void addEntery(){
    char day[10], month[10], year[10];
    if (numOfEntries == 100 ){
        printf("------------------------------\n");
        printf("You exceeded the number of entries.\n");
        printf("------------------------------\n");
    }
    else{
        printf("------------------------------\n");
        printf("Enter last name: ");
        gets(entries[numOfEntries].lastName);
        validateNames(entries[numOfEntries].lastName);
        printf("Enter first name: ");
        gets(entries[numOfEntries].firstName);
        validateNames(entries[numOfEntries].firstName);
        printf("Enter date of birth:\n");
        printf("Day: ");
        gets(day);
        entries[numOfEntries].birth.day = atoi(checkForCharacter(day));
        printf("Month: ");
        gets(month);
        entries[numOfEntries].birth.month = atoi(checkForCharacter(month));
        printf("Year: ");
        gets(year);
        entries[numOfEntries].birth.year = atoi(checkForCharacter(year));
        validateDOB(&entries[numOfEntries].birth.day, &entries[numOfEntries].birth.month, &entries[numOfEntries].birth.year);
        printf("Enter address: ");
        gets(entries[numOfEntries].address);
        checkForNull(entries[numOfEntries].address);
        printf("Enter phone number: ");
        gets(entries[numOfEntries].number);
        validateNumber(entries[numOfEntries].number);
        printf("Enter email: ");
        gets(entries[numOfEntries].email);
        validateEmail(entries[numOfEntries].email);
        numOfEntries++;
        printf("\nEntry Successfully Added.\n");
        printf("------------------------------\n");
    }
}


void deleteEntry(){
    char last[10], first[10];
    printf("------------------------------\n");
    printf("Please Enter the Last Name: ");
    gets(last);
    validateNames(last);
    printf("Please Enter the First Name: ");
    gets(first);
    validateNames(first);
    int i, n=0;
    for(i=0; i<numOfEntries; i++){
        if(strcmp(last, entries[i].lastName) || strcmp(first, entries[i].firstName)){
            strcpy(entries[n].lastName, entries[i].lastName);
            strcpy(entries[n].firstName, entries[i].firstName);
            entries[n].birth.day = entries[i].birth.day;
            entries[n].birth.month = entries[i].birth.month;
            entries[n].birth.year = entries[i].birth.year;
            strcpy(entries[n].number, entries[i].number);
            strcpy(entries[n].email, entries[i].email);
            strcpy(entries[n].address, entries[i].address);
            n++;
        }
    }
    numOfEntries = n;
    if(n == i){
        printf("\n%s, %s does not exist in the Telephone Book\n", last, first);
        printf("------------------------------\n");
    }
    else{
        printf("\nEntry Was Deleted.\n");
        printf("------------------------------\n");
    }
}

void modifyEntry(){
    int found=0, i;
    char searchLast[20], searchFirst[20];
    char day[10], month[10], year[10], addressTest[40];
    printf("------------------------------\n");
    printf("Please Enter the Last name: ");
    gets(searchLast);
    validateNames(searchLast);
    printf("Please Enter the first name: ");
    gets(searchFirst);
    validateNames(searchFirst);
    for(i=0; i<numOfEntries; i++){
        if(strcmp(searchLast, entries[i].lastName) == 0 && strcmp(searchFirst, entries[i].firstName) == 0){
            found = 1;
            printf("Please enter the changed last name: ");
            gets(entries[i].lastName);
            validateNames(entries[i].lastName);
            printf("Please enter the changed first name: ");
            gets(entries[i].firstName);
            validateNames(entries[i].firstName);
            printf("Please enter the changed date of birth:\n");
            printf("Day: ");
            gets(day);
            entries[i].birth.day = atoi(checkForCharacter(day));
            printf("Month: ");
            gets(month);
            entries[i].birth.month = atoi(checkForCharacter(month));
            printf("Year: ");
            gets(year);
            entries[i].birth.year = atoi(checkForCharacter(year));
            validateDOB(&entries[i].birth.day, &entries[i].birth.month, &entries[i].birth.year);
            printf("Please enter the changed address: ");
            gets(entries[i].address);
            checkForNull(entries[i].address);
            printf("Please enter the changed number: ");
            gets(entries[i].number);
            validateNumber(entries[i].number);
            printf("Please enter the changed email: ");
            gets(entries[i].email);
            validateEmail(entries[i].email);
            break;
        }
    }
    if(found){
        printf("\nEntry Successfully Modified.\n");
        printf("------------------------------\n");
    }
    else{
        printf("\nEntry Not Found.\n");
        printf("------------------------------\n");
    }
}

void printSorted(){
    int i, x;
    char test[10];
    printf("------------------------------\n");
    printf("[1] To sort by name.\n");
    printf("[2] To sort by DOB.\n");
    printf("Choice: ");
    for(i=0; i<1; i++){
        gets(test);
        x = atoi(checkForCharacter(test));
        if(x<1 || x>2){
            printf("Invalid please enter a valid number(1 or 2): ");
            i--;
        }
    }
    if(x == 1)
        sortByName();
    else
        sortByDOB();
}

void sortByName(){
    Entry temp;
    int i, j;
    for(i=0; i<numOfEntries; i++){
        for(j=0; j<numOfEntries-i-1; j++){
            if (strcmp(entries[j].lastName,entries[j+1].lastName) > 0){
                temp = entries[j];
                entries[j] = entries[j+1];
                entries[j+1] = temp;
            }
        }
    }
    printing();
}

void sortByDOB(){
    int i, j;
    for(j=0; j<numOfEntries; j++){
        int yearsd = entries[j].birth.year-1;
        int monthsd = entries[j].birth.month-1;
        int days = entries[j].birth.day;
        entries[j].tot = 0;
        entries[j].tot = (((yearsd)-((yearsd)%4))/4)*366+((yearsd)-(((yearsd)-((yearsd)%4))/4))*365;
        for(i=0; i<12; i++){
            if(monthsd == 0)
                break;
            if(monthsd%2 == 0 && monthsd != 2)
                entries[j].tot = entries[j].tot + 30;
            else if(monthsd%2 != 0)
                entries[j].tot = entries[j].tot + 31;
            else if(monthsd == 2){
                if(entries[j].birth.year%4 == 0)
                    entries[j].tot = entries[j].tot + 29;
                else
                    entries[j].tot = entries[j].tot + 28;
            }
            monthsd--;
        }
        entries[j].tot = entries[j].tot + days;
    }
    Entry temp;
    for(i=0; i<numOfEntries; i++){
        for(j=0; j<numOfEntries-i-1; j++){
            if(entries[j].tot<entries[j+1].tot){
                temp = entries[j];
                entries[j] = entries[j+1];
                entries[j+1] = temp;
            }
        }
    }
    printing();
}

void printing(){
    int i;
    printf("___________________________________________________________________\n");
    for(i=0; i<numOfEntries; i++){
        firstToUpper(entries[i].lastName);
        firstToUpper(entries[i].firstName);
        printf("%d - %s, ", i+1, entries[i].lastName);
        printf("%s, ", entries[i].firstName);
        printf("%d-%d-%d, ", entries[i].birth.day, entries[i].birth.month, entries[i].birth.year);
        printf("%s, ", entries[i].address);
        printf("%s, ", entries[i].number);
        printf("%s\n", entries[i].email);
        lowerCase(entries[i].lastName);
        lowerCase(entries[i].firstName);

    }
    printf("___________________________________________________________________\n");
}

void saveFile(){
    FILE*f1;
    f1 = fopen("directory.txt","w");
    int i;
    for(i=0; i<numOfEntries; i++){
        firstToUpper(entries[i].lastName);
        fprintf(f1,"%s,", entries[i].lastName);
        firstToUpper(entries[i].firstName);
        fprintf(f1,"%s,", entries[i].firstName);
        fprintf(f1,"%d-%d-%d,", entries[i].birth.day, entries[i].birth.month, entries[i].birth.year);
        fprintf(f1,"%s,", entries[i].address);
        fprintf(f1,"%s,", entries[i].number);
        fprintf(f1,"%s\n", entries[i].email);
        lowerCase(entries[i].firstName);
        lowerCase(entries[i].lastName);
    }
    printf("------------------------------\n");
    printf("New Directory Saved.\n");
    printf("------------------------------\n");
    fclose(f1);
}

int exitApp(){
    char sure[4];
    printf("------------------------------\n");
    printf("WARNING: Any unsaved progress will be lost.\n");
    printf("Are you sure you want to quit? ");
    gets(sure);
    do{
        lowerCase(sure);
        if(strcmp(sure, "yes") && strcmp(sure, "no")){
            printf("Please enter a valid answer(yes, no): ");
            gets(sure);
        }
    }while(strcmp(sure, "yes") && strcmp(sure, "no"));
    printf("------------------------------\n");
    if(!strcmp(sure, "no"))
        return 0;
    return 1;
}


void validateNames(char name[]){
    int valid, i;
    do{
        checkForNull(name);
        valid = 1;
        for(i=0; name[i]; i++){
            if(name[i]<65 || (name[i]>90 && name[i]<97) || name[i]>122){
                valid = 0;
                printf("Please enter a valid name(no numbers, spaces or special characters): ");
                gets(name);
            }
        }
    }while(!valid);
    lowerCase(name);
}

void validateDOB(int *day, int *month, int *year){
    Date test;
    int valid;
    char dayTest[10], monthTest[10], yearTest[10];
    do{
        valid = 1;
        if(*year > 2021 || *year < 1930){
            valid = 0;
            printf("Please enter a valid year(between 1930 and 2021): ");
            gets(yearTest);
            *year = atoi(checkForCharacter(yearTest));
        }
        if(*month > 12 || *month < 1){
            valid = 0;
            printf("Please enter a valid month(between 1 and 12): ");
            gets(monthTest);
            *month = atoi(checkForCharacter(monthTest));
        }
        if((*day > 30 || *day < 1) && (*month == 4 || *month == 6 || *month == 9 || *month == 11)){
            valid = 0;
            printf("Please enter a valid day(between 1 and 30): ");
            gets(dayTest);
            *day = atoi(checkForCharacter(day));
            }
        else if((*day > 31 || *day < 1) && (*month == 1 || *month == 3 || *month == 5 || *month == 7 || *month == 8 || *month == 10 || *month == 12)){
            valid = 0;
            printf("Please enter a valid day(between 1 and 31): ");
            gets(dayTest);
            *day = atoi(checkForCharacter(day));
        }
        if((*day > 29 || *day < 1) && *month == 2 && *year%4 == 0){
            valid = 0;
            printf("This is a leap year, please enter a day between 1 and 29: ");
            gets(dayTest);
            *day = atoi(checkForCharacter(day));
        }
        else if((*day > 28 || *day < 1) && *month == 2 && *year%4 != 0){
            valid = 0;
            printf("This is February, please enter a day between 1 and 28: ");
            gets(dayTest);
            *day = atoi(checkForCharacter(day));
        }

    }while(!valid);
}

void validateNumber(char number[]){
    int valid, i;
    do{
        valid = 1;
        if(strlen(number) != 11){
            valid = 0;
            printf("Please enter a number of 11 digits: ");
            gets(number);
        }
        else if(number[0] != '0' || number[1] != '1' || (number[2] != '0' && number[2] != '1' && number[2] != '2' && number[2] != '5')){
            valid = 0;
            printf("Please enter a number that starts with either 010, 011, 012 or 015: ");
            gets(number);
        }
        else{
            for(i=0; number[i]; i++){
                if(number[i] > 57 || number[i] < 48){
                    valid = 0;
                    printf("Please enter a valid number(no characters): ");
                    gets(number);
                }
            }
        }
    }while(!valid);
}

void validateEmail(char email[]){
    int valid, i, j, siteLength;
    char test[] = ".com";
    do{
        i=strlen(email)-1;
        valid = 1;
        if(email[0] != '@'){
            if(strlen(email) < 10)
                valid = 0;
            for(j=3; j>=0; j--){
                if(email[i] != test[j]){
                    valid = 0;
                    break;
                }
                i--;
            }
            if(valid){
                for(i=1; i<strlen(email)-5; i++){
                    valid = 0;
                    if(email[i] == '@'){
                        valid = 1;
                        break;
                    }
                }
                for(i=0; i<strlen(email)-1; i++){
                    if(email[i] == ' '){
                        valid = 0;
                        break;
                    }
                }
            }
        }
        else
            valid = 0;
        if(!valid){
            printf("Please enter an email in the form of (example@email.com) with no spaces: ");
            gets(email);
        }
    }while(!valid);
}

void lowerCase(char name[]){
    int i;
    for(i=0; name[i]; i++)
        name[i] = tolower(name[i]);
}

void firstToUpper(char name[]){
    int i;
    name[0] = toupper(name[0]);
    for(i=1; name[i]; i++)
        name[i] = tolower(name[i]);
}

char* checkForCharacter(char str[]){
    int valid, i;
    do{
        checkForNull(str);
        valid = 1;
        for(i=0; str[i]; i++){
            if(str[i] < 48 || str[i] > 57){
                valid = 0;
                printf("Please enter positive numbers only: ");
                gets(str);
                break;
            }
        }
    }while(!valid);
    return str;
}

void checkForNull(char str[]){
    int valid;
    do{
        valid = 1;
        if(str[0] == '\0'){
            valid = 0;
            printf("Please don't enter an empty choice: ");
            gets(str);
        }
    }while(!valid);
}
