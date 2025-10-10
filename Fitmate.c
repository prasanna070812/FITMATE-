#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define MAX_TRAINER_NAME_LENGTH 50
#define MAX_PREMIUMITY_LENGHT 50
#define MAX_GYMS 100
#define NO_OF_CHARS 256

int sortBy;
typedef struct GymDetails
{
    char name[MAX_NAME_LENGTH];
    float rating;
    int monthlyFee;
    int quaterlyFee;
    int annualFee;
    char premiumity[MAX_PREMIUMITY_LENGHT];
    char area[MAX_ADDRESS_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char trainerName[MAX_TRAINER_NAME_LENGTH];
    long long contactNumber;
} Gym;

Gym G[MAX_GYMS];

void loadfile(Gym G[], int *count)
{
    int gMF, gQF, gAF;
    long long int gcontact;
    float grating;
    char gname[20], gprem[20], garea[20], gaddr[20], gtname[20];
    FILE *fp = fopen("gym_details.txt", "r");
    if (fp == NULL)
    {
        printf("\nFile not Found\n");
        return;
    }

    while (fscanf(fp, "%s %f %d %d %d %s %s %s %s %lld\n", gname, &grating, &gMF, &gQF, &gAF, gprem, garea, gaddr, gtname, &gcontact) == 10)
    {
        strcpy(G[*count].name, gname);
        G[*count].rating = grating;
        G[*count].monthlyFee = gMF;
        G[*count].quaterlyFee = gQF;
        G[*count].annualFee = gAF;
        strcpy(G[*count].premiumity, gprem);
        strcpy(G[*count].area, garea);
        strcpy(G[*count].address, gaddr);
        strcpy(G[*count].trainerName, gtname);
        G[*count].contactNumber = gcontact;

        (*count)++;
        if (*count >= MAX_GYMS)
        {
            printf("Maximum number of gyms reached. Cannot load more data.\n");
            break;
        }
    }

    fclose(fp);
}

void printfdetails(Gym G[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Gym Name: %s\n", G[i].name);
        printf("Rating: %.1f\n", G[i].rating);
        printf("Monthly Fee: %d\n", G[i].monthlyFee);
        printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
        printf("Annual Fee: %d\n", G[i].annualFee);
        printf("Premiumity: %s\n", G[i].premiumity);
        printf("Area: %s\n", G[i].area);
        printf("Address: %s\n", G[i].address);
        printf("Trainer Name: %s\n", G[i].trainerName);
        printf("Contact Number: %lld\n", G[i].contactNumber);
        printf("\n\n");
    }
    return;
}

int loginUser(char username[], char password[])
{
    FILE *fp;
    char fileusername[20], filepassword[20];
    fp = fopen("users.txt", "r");
    if (fp == NULL)
    {
        printf("\n\tError opening user credentials file.");
        return 0;
    }

    while (fscanf(fp, "%s %s", fileusername, filepassword) == 2)
    {
        if (strcmp(username, fileusername) == 0 && strcmp(password, filepassword) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void createUser()
{
    FILE *fp;
    char uname[20], pass[20], fileusername[20], filepassword[20];

    fp = fopen("users.txt", "r");
    if (fp == NULL)
    {
        printf("\n\tError opening file!");
        return;
    }

tryagain:
    printf("\n\tEnter a new username: ");
    scanf("%s", uname);

    while (fscanf(fp, "%s %s\n", fileusername, filepassword) == 2)
    {
        if (stricmp(uname, fileusername) == 0)
        {
            printf("\n\tUsername already Exists, Try different username\n");
            fseek(fp, 0, SEEK_SET);
            goto tryagain;
        }
    }
    printf("\tEnter a password: ");
    scanf("%s", pass);
    fclose(fp);

    fp = fopen("users.txt", "a");
    if (fp == NULL)
    {
        printf("\n\tError opening file.");
        return;
    }

    fprintf(fp, "%s %s\n", uname, pass);
    printf("\n\tUser account created successfully!\n\n");

    fclose(fp);
}

void merge(Gym G[], int left, int mid, int right, int sortBy)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Gym L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = G[left + i];
    for (j = 0; j < n2; j++)
        R[j] = G[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        int compareResult;
        switch (sortBy)
        {
        case 1:
            compareResult = L[i].monthlyFee - R[j].monthlyFee;
            break;
        case 2:
            compareResult = L[i].quaterlyFee - R[j].quaterlyFee;
            break;
        case 3:
            compareResult = L[i].annualFee - R[j].annualFee;
            break;
        default:
            printf("\tInvalid sortBy value\n");
            return;
        }

        if (compareResult <= 0)
        {
            G[k] = L[i];
            i++;
        }
        else
        {
            G[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        G[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        G[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(Gym G[], int left, int right, int sortBy)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergesort(G, left, mid, sortBy);
        mergesort(G, mid + 1, right, sortBy);

        merge(G, left, mid, right, sortBy);
    }
}

void filters(int count)
{
    int choice, pchoice, rchoice, zchoice;
filt:
    printf("\n\t1.SORT ON RATING\n\t2.SORT ON PRICE\n\t3.SORT ON PREMIUMITY\n\t4.GO BACK\n\tENTER YOUR CHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        for (int i = 1; i < count; ++i)
        {
            Gym key = G[i];
            int j = i - 1;

            while (j >= 0 && G[j].rating > key.rating)
            {
                G[j + 1] = G[j];
                j = j - 1;
            }
            G[j + 1] = key;
        }
        printf("\n\t1.BEST RATINGS\n\t2.LEAST RATINGS\nENTER YOUR CHOICE: ");

        scanf("%d", &pchoice);

        switch (pchoice)
        {
        case 1:
            for (int i = count - 1; i >= 0; i--)
            {
                printf("Gym Name: %s\n", G[i].name);
                printf("Rating: %.1f\n", G[i].rating);
                printf("Monthly Fee: %d\n", G[i].monthlyFee);
                printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                printf("Annual Fee: %d\n", G[i].annualFee);
                printf("Premiumity: %s\n", G[i].premiumity);
                printf("Area: %s\n", G[i].area);
                printf("Address: %s\n", G[i].address);
                printf("Trainer Name: %s\n", G[i].trainerName);
                printf("Contact Number: %lld\n", G[i].contactNumber);
                printf("\n\n");
            }
            goto filt;
            break;
        case 2:
            for (int i = 0; i < count; i++)
            {
                printf("Gym Name: %s\n", G[i].name);
                printf("Rating: %.1f\n", G[i].rating);
                printf("Monthly Fee: %d\n", G[i].monthlyFee);
                printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                printf("Annual Fee: %d\n", G[i].annualFee);
                printf("Premiumity: %s\n", G[i].premiumity);
                printf("Area: %s\n", G[i].area);
                printf("Address: %s\n", G[i].address);
                printf("Trainer Name: %s\n", G[i].trainerName);
                printf("Contact Number: %lld\n", G[i].contactNumber);
                printf("\n\n");
            }
            goto filt;
            break;
        }
        break;

    case 2:
        printf("\t1.Sort by monthly Fee\n\t2.Sort by quaterly Fee\n\t3.Sort by annual Fee\n\tEnter choice:");
        scanf("%d", &sortBy);
        switch (sortBy)
        {
        case 1:
            mergesort(G, 0, count - 1, sortBy);
            printf("\n\t1. High to low\n\t2. Low to high\n\t   Enter choice:");
            scanf("%d", &rchoice);
            switch (rchoice)
            {
            case 1:
                for (int i = count - 1; i >= 0; i--)
                {
                    printf("Gym Name: %s\n", G[i].name);
                    printf("Rating: %.1f\n", G[i].rating);
                    printf("Monthly Fee: %d\n", G[i].monthlyFee);
                    printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                    printf("Annual Fee: %d\n", G[i].annualFee);
                    printf("Premiumity: %s\n", G[i].premiumity);
                    printf("Area: %s\n", G[i].area);
                    printf("Address: %s\n", G[i].address);
                    printf("Trainer Name: %s\n", G[i].trainerName);
                    printf("Contact Number: %lld\n", G[i].contactNumber);
                    printf("\n\n");
                }
                goto filt;
                break;
            case 2:
                for (int i = 0; i < count; i++)
                {
                    printf("Gym Name: %s\n", G[i].name);
                    printf("Rating: %.1f\n", G[i].rating);
                    printf("Monthly Fee: %d\n", G[i].monthlyFee);
                    printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                    printf("Annual Fee: %d\n", G[i].annualFee);
                    printf("Premiumity: %s\n", G[i].premiumity);
                    printf("Area: %s\n", G[i].area);
                    printf("Address: %s\n", G[i].address);
                    printf("Trainer Name: %s\n", G[i].trainerName);
                    printf("Contact Number: %lld\n", G[i].contactNumber);
                    printf("\n\n");
                }
                goto filt;
                break;
            }
            break;

        case 2:
            mergesort(G, 0, count - 1, sortBy);
            printf("\n\t1.HIGH TO LOW\n\t2.LOW TO HIGH\n\t  ENTER YOUR CHOICE:");
            scanf("%d", &rchoice);
            switch (rchoice)
            {
            case 1:
                for (int i = count - 1; i >= 0; i--)
                {
                    printf("Gym Name: %s\n", G[i].name);
                    printf("Rating: %.1f\n", G[i].rating);
                    printf("Monthly Fee: %d\n", G[i].monthlyFee);
                    printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                    printf("Annual Fee: %d\n", G[i].annualFee);
                    printf("Premiumity: %s\n", G[i].premiumity);
                    printf("Area: %s\n", G[i].area);
                    printf("Address: %s\n", G[i].address);
                    printf("Trainer Name: %s\n", G[i].trainerName);
                    printf("Contact Number: %lld\n", G[i].contactNumber);
                    printf("\n\n");
                }
                goto filt;
                break;
            case 2:
                for (int i = 0; i < count; i++)
                {
                    printf("Gym Name: %s\n", G[i].name);
                    printf("Rating: %.1f\n", G[i].rating);
                    printf("Monthly Fee: %d\n", G[i].monthlyFee);
                    printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                    printf("Annual Fee: %d\n", G[i].annualFee);
                    printf("Premiumity: %s\n", G[i].premiumity);
                    printf("Area: %s\n", G[i].area);
                    printf("Address: %s\n", G[i].address);
                    printf("Trainer Name: %s\n", G[i].trainerName);
                    printf("Contact Number: %lld\n", G[i].contactNumber);
                    printf("\n\n");
                }
                goto filt;
                break;
            }
            break;
        case 3:
            mergesort(G, 0, count - 1, sortBy);
            printf("\n\t1.HIGH TO LOW\n\t2.LOW TO HIGH\n\t  ENTER YOUR CHOICE:");
            scanf("%d", &rchoice);
            switch (rchoice)
            {
            case 1:
                for (int i = count - 1; i >= 0; i--)
                {
                    printf("Gym Name: %s\n", G[i].name);
                    printf("Rating: %.1f\n", G[i].rating);
                    printf("Monthly Fee: %d\n", G[i].monthlyFee);
                    printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                    printf("Annual Fee: %d\n", G[i].annualFee);
                    printf("Premiumity: %s\n", G[i].premiumity);
                    printf("Area: %s\n", G[i].area);
                    printf("Address: %s\n", G[i].address);
                    printf("Trainer Name: %s\n", G[i].trainerName);
                    printf("Contact Number: %lld\n", G[i].contactNumber);
                    printf("\n\n");
                }
                goto filt;
                break;
            case 2:
                for (int i = 0; i < count; i++)
                {
                    printf("Gym Name: %s\n", G[i].name);
                    printf("Rating: %.1f\n", G[i].rating);
                    printf("Monthly Fee: %d\n", G[i].monthlyFee);
                    printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                    printf("Annual Fee: %d\n", G[i].annualFee);
                    printf("Premiumity: %s\n", G[i].premiumity);
                    printf("Area: %s\n", G[i].area);
                    printf("Address: %s\n", G[i].address);
                    printf("Trainer Name: %s\n", G[i].trainerName);
                    printf("Contact Number: %lld\n", G[i].contactNumber);
                    printf("\n\n");
                }
                goto filt;
                break;
            }
            break;
        }
        break;

    case 3:
        printf("\n\t1.Gold\n\t2.Platinum\n\t3.Diamond\n\tENTER YOUR CHOICE:");
        scanf("%d", &zchoice);
        switch (zchoice)
        {
        case 1:
            for (int i = 0; i < count; i++)
            {
                if (stricmp("Gold", G[i].premiumity) == 0)
                {
                    printf("Gym Name: %s\n", G[i].name);
                    printf("Rating: %.1f\n", G[i].rating);
                    printf("Monthly Fee: %d\n", G[i].monthlyFee);
                    printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                    printf("Annual Fee: %d\n", G[i].annualFee);
                    printf("Premiumity: %s\n", G[i].premiumity);
                    printf("Area: %s\n", G[i].area);
                    printf("Address: %s\n", G[i].address);
                    printf("Trainer Name: %s\n", G[i].trainerName);
                    printf("Contact Number: %lld\n", G[i].contactNumber);
                    printf("\n\n");
                }
            }
            goto filt;
            break;
        case 2:
            for (int i = 0; i < count; i++)
            {
                if (stricmp("Platinum", G[i].premiumity) == 0)
                {
                    printf("Gym Name: %s\n", G[i].name);
                    printf("Rating: %.1f\n", G[i].rating);
                    printf("Monthly Fee: %d\n", G[i].monthlyFee);
                    printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                    printf("Annual Fee: %d\n", G[i].annualFee);
                    printf("Premiumity: %s\n", G[i].premiumity);
                    printf("Area: %s\n", G[i].area);
                    printf("Address: %s\n", G[i].address);
                    printf("Trainer Name: %s\n", G[i].trainerName);
                    printf("Contact Number: %lld\n", G[i].contactNumber);
                    printf("\n\n");
                }
            }
            goto filt;
            break;
        case 3:
            for (int i = 0; i < count; i++)
            {
                if (stricmp("Diamond", G[i].premiumity) == 0)
                {
                    printf("Gym Name: %s\n", G[i].name);
                    printf("Rating: %.1f\n", G[i].rating);
                    printf("Monthly Fee: %d\n", G[i].monthlyFee);
                    printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
                    printf("Annual Fee: %d\n", G[i].annualFee);
                    printf("Premiumity: %s\n", G[i].premiumity);
                    printf("Area: %s\n", G[i].area);
                    printf("Address: %s\n", G[i].address);
                    printf("Trainer Name: %s\n", G[i].trainerName);
                    printf("Contact Number: %lld\n", G[i].contactNumber);
                    printf("\n\n");
                }
            }
            goto filt;
            break;
        }
        break;
        case 4:  break;

    }
    return;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void badchartable(char *str, int size, int badchar[NO_OF_CHARS])
{
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
    {
        badchar[i] = -1;
    }
    for (i = 0; i < size; i++)
    {
        badchar[(int)str[i]] = i;
    }
}

int checklist(char key[], int count)
{
    int flag = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmpi(key, G[i].name) == 0)
            return 1;
    }
    for (int i = 0; i < count; i++)
    {
        int m = strlen(key);
        int n = strlen(G[i].name);
        int badchar[NO_OF_CHARS];

        badchartable(key, m, badchar);

        int s = 0;
        while (s <= (n - m))
        {
            int j = m - 1;
            while (j >= 0 && key[j] == G[i].name[s + j])
            {
                j--;
            }

            if (j < 0)
            {
                printf("\n\tDid you mean = %s\n", G[i].name);
                flag = 1;
                break;
            }
            else
            {
                s += max(1, j - badchar[G[i].name[s + j]]);
            }
        }
    }
    if (flag == 0)
    {
        printf("\n\tThe Gym is not enlisted\n");
    }
    return 1000;
}

void serachGym(int count)
{
    char searchedName[40];

lable:
    printf("\n\tEnter the gym name: ");
    scanf("%s", searchedName);
    if (checklist(searchedName, count) == 1000)
    {
        goto lable;
    }

    for (int i = 0; i < count; i++)
    {
        if (stricmp(searchedName, G[i].name) == 0)
        {
            printf("Gym Name: %s\n", G[i].name);
            printf("Rating: %.1f\n", G[i].rating);
            printf("Monthly Fee: %d\n", G[i].monthlyFee);
            printf("Quaterly Fee: %d\n", G[i].quaterlyFee);
            printf("Annual Fee: %d\n", G[i].annualFee);
            printf("Premiumity: %s\n", G[i].premiumity);
            printf("Area: %s\n", G[i].area);
            printf("Address: %s\n", G[i].address);
            printf("Trainer Name: %s\n", G[i].trainerName);
            printf("Contact Number: %lld\n", G[i].contactNumber);
            printf("\n\n");
        }
    }
}

void addGym()
{
    FILE *fp = fopen("gym_details.txt", "a");

    if (fp == NULL)
    {
        printf("\nError opening file for appending.\n");
        return;
    }

    Gym newGym;

    printf("Enter Gym Name: ");
    scanf("%s", newGym.name);

    printf("Enter Rating: ");
    scanf("%f", &newGym.rating);

    printf("Enter Monthly Fee: ");
    scanf("%d", &newGym.monthlyFee);

    printf("Enter Quaterly Fee: ");
    scanf("%d", &newGym.quaterlyFee);

    printf("Enter Annual Fee: ");
    scanf("%d", &newGym.annualFee);

    printf("Enter Premiumity: ");
    scanf("%s", newGym.premiumity);

    printf("Enter Area: ");
    scanf("%s", newGym.area);

    printf("Enter Address: ");
    scanf("%s", newGym.address);

    printf("Enter Trainer Name: ");
    scanf("%s", newGym.trainerName);

    printf("Enter Contact Number: ");
    scanf("%lld", &newGym.contactNumber);

    fprintf(fp, "%s %.1f %d %d %d %s %s %s %s %lld\n",
            newGym.name, newGym.rating, newGym.monthlyFee, newGym.quaterlyFee,
            newGym.annualFee, newGym.premiumity, newGym.area, newGym.address,
            newGym.trainerName, newGym.contactNumber);

    printf("\n\tGym Enlisted successfully!\n");

    fclose(fp);
}

int main()
{
     printf("\n\t+==============================================================================================+\n");
    printf("\t||   ________   _________   _________   _____________    ___________    _________   ________  ||\n");
    printf("\t||  |  ______| |___   ___| |___   ___| |  ___   ___  |  |  _______  |  |___   ___| |  ______| ||\n");
    printf("\t||  | |_____       | |         | |     | |   | |   | |  | |       | |      | |     | |        ||\n");
    printf("\t||  | |_____|      | |         | |     | |   | |   | |  | |_______| |      | |     | |____    ||\n");
    printf("\t||  | |            | |         | |     | |   | |   | |  | |_______| |      | |     | |----    ||\n");
    printf("\t||  | |         ___| |___      | |     | |   |_|   | |  | |       | |      | |     | |______  ||\n");
    printf("\t||  |_|        |_________|     |_|     |_|         |_|  |_|       |_|      |_|     |________| ||\n");
    printf("\t||                                                                                            ||\n");
    printf("\t+==============================================================================================+\n\n");
    printf("\t************************************************************************************************\n");
    printf("\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\t------------------------------------------------------------------------------------------------\n");
    printf("\t|||||||       Where Dedication Meets Innovation <> Your Ideal Gym Awaits You!            |||||||\n");
    printf("\t------------------------------------------------------------------------------------------------\n");
    printf("\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\t************************************************************************************************\n\n\n\n\n");

    int choice, count = 0, lchoice;
    loadfile(G, &count);
    char username[20], password[20];
    do
    {

    login:
        printf("\tLOGIN CREDENTIALS:\n\n");
        printf("\t1.LOGIN\n\t2.CREATE NEW ACCOUNT\n\t3.QUIT\n\n\tENTER YOUR CHOICE:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\n\tENTER YOUR USERNAME: ");
            scanf("%s", username);
            printf("\tENTER YOUR PASSWORD: ");
            scanf("%s", password);
            if (loginUser(username, password))
            {
                printf("\n\tLOGIN SUCCESSFUL!\n");

            loggedin:
                printf("\n\t1.LIST ALL GYMS\n\t2.APPLY FILTERS\n\t3.SEARCH GYM\n\t4.ADD YOUR GYM\n\t5.LOGOUT\n\tENTER YOUR CHOICE:");
                scanf("%d", &lchoice);

                switch (lchoice)
                {

                case 1:
                    printfdetails(G, count);
                    goto loggedin;
                    break;
                case 2:
                    filters(count);
                    goto loggedin;
                    break;
                case 3:
                    serachGym(count);
                    goto loggedin;
                    break;
                case 4:
                    addGym();
                    goto loggedin;
                    break;
                case 5:
                    goto login;
                    break;
                default:
                    goto login;
                }
            }
            else
                printf("\n\tLOGIN FAILED!\n\n");
            break;

        case 2:
            createUser();
            break;

        case 3:
            break;
        }
    } while (choice != 3);
    return 0;
}
