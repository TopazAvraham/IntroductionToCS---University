/*********************
* Topaz Avraham
* 206842627
* ex_5
*********************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Word {
    char** translations;
    struct Word* next;
} Word;

typedef struct {
    char** languages;
    int numOfLanguages;
    Word* wordList;
} Dictionary;

typedef struct {
    Word* head;
    Word* tail;
}List;

void menu(Dictionary*, int*, List**, int*);
void printMenu();
Dictionary* createNewDictionary(Dictionary*, int*, int*);
void countLanguagesOfDictionary(char*, int*);
int assignLanguagesToDictionary(Dictionary*, char*, int, const int*);
List** addNewWordToDictionary(Dictionary*, int*, List**);
void printListOfDictionaries(Dictionary*, const int*);
void printLanguagesOfDictionary(Dictionary*, int);
Word* createNewWord(char*, Dictionary*, int);
void insertNodeToTail(List*, Dictionary*, int, char*);
List** updateArrayOfLists(const int*, List**, int*);
void searchWordInDictionary(Dictionary*, int*, List**);
char** findValueRec(List*, char*);
char** findValueHelper(Word*, char*);
void deleteWordInDictionary(Dictionary*, int*, List**);
void removeWordWithTranslationsFromList(List*, char**, int);
Dictionary* deleteDictionary(Dictionary*, int*, List**);
void freeListRec(List*, int);
void freeListHelper(Word*, List*, int);
void freeWordTranslations(char**, int);
void deleteAllDictionaries(Dictionary*, int*, List**);
Dictionary* deleteSpecificDictionary(Dictionary*, int*, List**);

void main() {

    Dictionary* dictionaries = NULL;
    int numOfDictionaries = 0;
    List** lst = NULL;
    int maxDictionariesReached = 0;
    menu(dictionaries, &numOfDictionaries, lst, &maxDictionariesReached);
}

void menu(Dictionary* dictionaries, int* numOfDictionaries, List** lst, int* maxDictionariesReached) {

    int digit = 0;
    printMenu();
    while (digit != 6) {

        if ((digit >= 1) && (digit <= 6)) {
            printMenu();
        }


        scanf("%d", &digit);

        switch (digit) {
        case 1:
            dictionaries = createNewDictionary(dictionaries, numOfDictionaries, maxDictionariesReached);
            lst = updateArrayOfLists(numOfDictionaries, lst, maxDictionariesReached);
            if (dictionaries == NULL) {
                printf("The creation of the dictionary has failed!\n");
                break;
            }
            else {
                printf("The dictionary has been created successfully!\n");
            }
            break;
        case 2:
            if ((*numOfDictionaries) == 0) {
                printf("This option is not available right now, try again:\n");
                digit = 0;
            }
            else {
                lst = addNewWordToDictionary(dictionaries, numOfDictionaries, lst);
                if (lst != NULL) {
                    printf("The word has been added successfully!\n");
                }
                else {
                    printf("The addition of the word has failed!\n");
                }
            }
            break;
        case 3:
            if ((*numOfDictionaries) == 0) {
                printf("This option is not available right now, try again:\n");
                digit = 0;
            }
            else {
                deleteWordInDictionary(dictionaries, numOfDictionaries, lst);
            };
            break;
        case 4:
            if ((*numOfDictionaries) == 0) {
                printf("This option is not available right now, try again:\n");
                digit = 0;
            }
            else {
                searchWordInDictionary(dictionaries, numOfDictionaries, lst);
            };
            break;
        case 5:
            if ((*numOfDictionaries) == 0) {
                printf("This option is not available right now, try again:\n");
                digit = 0;
            }
            else {
                dictionaries = deleteDictionary(dictionaries, numOfDictionaries, lst);
            };
            break;
        case 6:
            deleteAllDictionaries(dictionaries, numOfDictionaries, lst);
            //free(dictionaries);
            printf("Bye!\n");
            break;
        default:
            printf("Wrong option, try again:\n");
        }
    }
}

void printMenu() {
    printf("Welcome to the dictionaries manager!\n"
        "Choose an option:\n"
        "1. Create a new dictionary.\n"
        "2. Add a word to a dictionary.\n"
        "3. Delete a word from a dictionary.\n"
        "4. Find a word in a dictionary.\n"
        "5. Delete a dictionary.\n"
        "6. Exit.\n");
}

List** updateArrayOfLists(const int* numOfDictionaries, List** lst, int* maxDictionariesReached) {

    if (*numOfDictionaries - 1 == 0 && (*maxDictionariesReached == 0)) {
        lst = malloc(sizeof(List*));
        if (lst == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return lst;
        }
        lst[*numOfDictionaries - 1] = malloc(sizeof(List));
    }
    else {
        lst = realloc(lst, (*numOfDictionaries + 1) * sizeof(List*));
        if (lst == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return lst;
        }
        lst[*numOfDictionaries - 1] = malloc(sizeof(List));
    }

    if ((*maxDictionariesReached) < (*numOfDictionaries)) {
        *maxDictionariesReached = *numOfDictionaries;
    }
    return lst;
}

Dictionary* createNewDictionary(Dictionary* dictionaries, int* numOfDictionaries, int* maxDictionariesReached) {

    int languagesCounter = 0, allocationSuccess;
    printf("Define a new dictionary:\n");
    char* stringOfLanguages = malloc(1 * sizeof(char));
    if (stringOfLanguages == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return dictionaries;
    }
    stringOfLanguages[0] = 0;
    char isEnd[2] = { 0 };
    int counter = 1;
    scanf(" %c", &(isEnd[0]));
    while (isEnd[0] != '\n') {
        stringOfLanguages = realloc(stringOfLanguages, (sizeof(char) + (counter + 1)));
        if (stringOfLanguages == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return dictionaries;
        }
        strcat(stringOfLanguages, isEnd);
        counter++;
        scanf("%c", &(isEnd[0]));
    }



    if (*numOfDictionaries == 0) {
        dictionaries = malloc(sizeof(Dictionary));
        if (dictionaries == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return dictionaries;
        }
        else {
            (*numOfDictionaries)++;
        }
    }
    else {
        dictionaries = realloc(dictionaries, ((*numOfDictionaries + 1) * sizeof(Dictionary)));
        if (dictionaries == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return dictionaries;
        }
        else {
            (*numOfDictionaries)++;
        }
    }

    countLanguagesOfDictionary(stringOfLanguages, &languagesCounter);
    allocationSuccess = assignLanguagesToDictionary(dictionaries, stringOfLanguages, languagesCounter, numOfDictionaries);
    if (!allocationSuccess) {
        return NULL;
    }
    dictionaries[*numOfDictionaries - 1].numOfLanguages = languagesCounter;
    dictionaries[*numOfDictionaries - 1].wordList = NULL;

    free(stringOfLanguages);
    return dictionaries;
}

void countLanguagesOfDictionary(char* stringOfLanguages, int* languagesCounter) {

    char* p = NULL;
    char* temp = malloc(strlen(stringOfLanguages) + 1);
    if (temp == NULL) {
        printf("The creation of the dictionary has failed!\n");
        return;
    }
    strcpy(temp, stringOfLanguages);

    for (p = strtok(temp, ","); p != NULL; p = strtok(NULL, ",")) {
        (*languagesCounter)++;
    }
    free(temp);
}

int assignLanguagesToDictionary(Dictionary* dictionaries, char* stringOfLanguages,
    int languagesCounter, const int* numOfDictionaries) {
    int allocationSuccess = 1;
    dictionaries[*numOfDictionaries - 1].languages = malloc((languagesCounter) * sizeof(char*));
    if (dictionaries[*numOfDictionaries - 1].languages == NULL) {
        allocationSuccess = 0;
        return allocationSuccess;
    }
    else {
        int i = 0;
        char* p = NULL;
        char* secondTemp = malloc(strlen(stringOfLanguages) + 1);
        if (secondTemp == NULL) {
            printf("The creation of the dictionary has failed!\n");
            return 0;
        }
        strcpy(secondTemp, stringOfLanguages);

        for (p = strtok(secondTemp, ","); i < (languagesCounter); p = strtok(NULL, ",")) {
            dictionaries[*numOfDictionaries - 1].languages[i] = malloc((strlen(p) * sizeof(char)) + 1);
            if (dictionaries[*numOfDictionaries - 1].languages[i] == NULL) {
                allocationSuccess = 0;
                return allocationSuccess;
            }
            else {
                strcpy(dictionaries[*numOfDictionaries - 1].languages[i++], p);
            }
        }
        free(secondTemp);
    }
    return allocationSuccess;
}

List** addNewWordToDictionary(Dictionary* dictionaries, int* numOfDictionaries, List** lst) {

    printListOfDictionaries(dictionaries, numOfDictionaries);
    int selection;
    scanf("%d", &selection);

    while (selection > (*numOfDictionaries) || (selection <= 0 && ((*numOfDictionaries) != 0))) {
        printf("Wrong option, try again:\n");
        scanf("%d", &selection);
    }

    printf("Enter a word in ");
    printLanguagesOfDictionary(dictionaries, selection);

    char* newWordWithTranslations = malloc(1 * sizeof(char));
    if (newWordWithTranslations == NULL) {
        printf("The addition of the word has failed!\n");
        free(newWordWithTranslations);
        return lst;
    }
    newWordWithTranslations[0] = 0;
    char isEnd[2] = { 0 };
    int counter = 1;
    scanf(" %c", &(isEnd[0]));
    while (isEnd[0] != '\n') {
        newWordWithTranslations = realloc(newWordWithTranslations, (sizeof(char) + (counter + 1)));
        if (newWordWithTranslations == NULL) {
            printf("The addition of the word has failed!\n");
            free(newWordWithTranslations);
            return lst;
        }
        strcat(newWordWithTranslations, isEnd);
        counter++;
        scanf("%c", &(isEnd[0]));
    }

    if (dictionaries[selection - 1].wordList == NULL) {
        insertNodeToTail(lst[selection - 1], dictionaries, selection, newWordWithTranslations);
        lst[selection - 1]->head = dictionaries[selection - 1].wordList;
        lst[selection - 1]->tail = dictionaries[selection - 1].wordList;
        free(newWordWithTranslations);
        return lst;
    }
    else {
        insertNodeToTail(lst[selection - 1], dictionaries, selection, newWordWithTranslations);
        free(newWordWithTranslations);
        return lst;
    }
}

void insertNodeToTail(List* lst, Dictionary* dictionaries, int selection, char* newWordWithTranslations) {

    int i = 0;
    char* temp = malloc(strlen(newWordWithTranslations) + 1);
    if (temp == NULL) {
        printf("The addition of the word has failed!\n");
        return;
    }
    strcpy(temp, newWordWithTranslations);
    char* p = NULL;

    if (dictionaries[selection - 1].wordList == NULL) {
        dictionaries[selection - 1].wordList = (Word*)malloc(1 * sizeof(Word));
        if (dictionaries[selection - 1].wordList == NULL) {
            printf("The addition of the word has failed!\n");
            return;
        }
        dictionaries[selection - 1].wordList->translations = malloc(dictionaries[selection - 1].numOfLanguages * sizeof(char*));
        if (dictionaries[selection - 1].wordList->translations == NULL) {
            printf("The addition of the word has failed!\n");
            return;
        }

        for (p = strtok(temp, ","); i < dictionaries[selection - 1].numOfLanguages; p = strtok(NULL, ",")) {
            dictionaries[selection - 1].wordList->translations[i] = malloc((strlen(p) * sizeof(char)) + 1);
            if (dictionaries[selection - 1].wordList->translations[i] == NULL) {
                printf("The addition of the word has failed!\n");
                return;
            }
            strcpy(dictionaries[selection - 1].wordList->translations[i], p);
            i++;
        }
        dictionaries[selection - 1].wordList->next = NULL;
    }
    else {
        Word* newWord = createNewWord(temp, dictionaries, selection);
        if (newWord == NULL) {
            printf("The addition of the word has failed!\n");
            return;
        }
        if (lst->head == NULL) {
            lst->tail = newWord;
            lst->head = lst->tail;
        }
        else {
            lst->tail->next = newWord;
            lst->tail = newWord;
        }
    }
    free(temp);
}

Word* createNewWord(char* temp, Dictionary* dictionaries, int selection) {
    int i = 0;
    Word* newWord = (Word*)malloc(sizeof(Word));
    if (newWord == NULL) {
        printf("The addition of the word has failed!\n");
        return newWord;
    }
    newWord->translations = malloc(dictionaries[selection - 1].numOfLanguages * sizeof(char*));
    if (newWord->translations == NULL) {
        printf("The addition of the word has failed!\n");
        return newWord;
    }

    char* p = NULL;

    for (p = strtok(temp, ","); i < dictionaries[selection - 1].numOfLanguages; p = strtok(NULL, ",")) {
        newWord->translations[i] = malloc((strlen(p) * sizeof(char)) + 1);
        if (newWord->translations[i] == NULL) {
            printf("The addition of the word has failed!\n");
            return newWord;
        }
        strcpy(newWord->translations[i], p);
        i++;
    }

    newWord->next = NULL;
    return newWord;
}

void printListOfDictionaries(Dictionary* dictionaries, const int* numOfDictionaries) {

    printf("Choose a dictionary:\n");

    for (int i = 0; i < (*numOfDictionaries); i++) {
        printf("%d. ", (i + 1));
        for (int j = 0; j < dictionaries[i].numOfLanguages; j++) {
            printf("%s", dictionaries[i].languages[j]);
            if (j + 1 < dictionaries[i].numOfLanguages) {
                printf(",");
            }
        }
        printf("\n");
    }
}

void printLanguagesOfDictionary(Dictionary* dictionaries, int selection) {
    for (int j = 0; j < dictionaries[selection - 1].numOfLanguages; j++) {
        printf("%s", dictionaries[selection - 1].languages[j]);
        if (j + 1 < dictionaries[selection - 1].numOfLanguages) {
            printf(",");
        }
    }
    printf(":\n");

}

void searchWordInDictionary(Dictionary* dictionaries, int* numOfDictionaries, List** lst) {

    printListOfDictionaries(dictionaries, numOfDictionaries);
    int selection;
    scanf("%d", &selection);

    while (selection > (*numOfDictionaries) || (selection <= 0 && ((*numOfDictionaries) != 0))) {
        printf("Wrong option, try again:\n");
        scanf("%d", &selection);
    }

    printf("Enter a word in %s:\n", dictionaries[selection - 1].languages[0]);

    char* lookFor = malloc(1 * sizeof(char));
    if (lookFor == NULL) {
        printf("The search has failed successfully!\n");
        return;
    }
    lookFor[0] = 0;
    char isEnd[2] = { 0 };
    int counter = 1;
    scanf(" %c", &(isEnd[0]));
    while (isEnd[0] != '\n') {
        lookFor = realloc(lookFor, (sizeof(char) + (counter + 1)));
        if (lookFor == NULL) {
            printf("The search has failed successfully!\n");
            return;
        }
        strcat(lookFor, isEnd);
        counter++;
        scanf("%c", &(isEnd[0]));
    }


    if (dictionaries[selection - 1].wordList == NULL) {
        printf("There are no translations for \"%s\" in this dictionary.\n", lookFor);
        free(lookFor);
        return;
    }

    if (lst[selection - 1]->head == NULL) {
        printf("There are no translations for \"%s\" in this dictionary.\n", lookFor);
        free(lookFor);
        return;
    }

    char** differentTranslationsOfWord = findValueRec(lst[selection - 1], lookFor);

    if (differentTranslationsOfWord == NULL) {
        printf("There are no translations for \"%s\" in this dictionary.\n", lookFor);
        free(lookFor);
        return;
    }
    else {
        printf("The translations are:\n");
        for (int i = 1; i < dictionaries[selection - 1].numOfLanguages; i++) {
            printf("%s: %s", dictionaries[selection - 1].languages[i], differentTranslationsOfWord[i]);
            if (i + 1 != dictionaries[selection - 1].numOfLanguages) {
                printf(", ");
            }
        }
        printf("\n");
    }
    free(lookFor);
}

char** findValueRec(List* dictionaryList, char* lookFor) {
    return findValueHelper(dictionaryList->head, lookFor);
}

char** findValueHelper(Word* head, char* lookFor) {
    if (head == NULL) {
        return NULL;
    }
    if (strcmp(head->translations[0], lookFor) == 0) {
        return head->translations;
    }
    return findValueHelper(head->next, lookFor);
}

void deleteWordInDictionary(Dictionary* dictionaries, int* numOfDictionaries, List** lst) {

    printListOfDictionaries(dictionaries, numOfDictionaries);
    int selection;
    scanf("%d", &selection);

    while (selection > (*numOfDictionaries) || (selection <= 0 && ((*numOfDictionaries) != 0))) {
        printf("Wrong option, try again:\n");
        scanf("%d", &selection);
    }

    printf("Enter a word in %s:\n", dictionaries[selection - 1].languages[0]);

    char* lookFor = malloc(1 * sizeof(char));
    if (lookFor == NULL) {
        printf("The deletion of the word has failed!\n");
    }
    lookFor[0] = 0;
    char isEnd[2] = { 0 };
    int counter = 1;
    scanf(" %c", &(isEnd[0]));
    while (isEnd[0] != '\n') {
        lookFor = realloc(lookFor, (sizeof(char) + (counter + 1)));
        if (lookFor == NULL) {
            printf("The deletion of the word has failed!\n");
        }
        strcat(lookFor, isEnd);
        counter++;
        scanf("%c", &(isEnd[0]));
    }

    char isSure;
    printf("Are you sure? (y/n)\n");
    scanf(" %c", &isSure);

    if (isSure != 'y') {
        printf("The deletion of the word has been canceled.\n");
        free(lookFor);
        return;
    }

    if (dictionaries[selection - 1].wordList == NULL) {
        printf("The deletion of the word has failed!\n");
        free(lookFor);
        return;
    }


    char** differentTranslationsOfWord = findValueRec(lst[selection - 1], lookFor);

    if (differentTranslationsOfWord == NULL) {
        printf("The deletion of the word has failed!\n");
        free(lookFor);
        return;
    }

    removeWordWithTranslationsFromList(lst[selection - 1], differentTranslationsOfWord, dictionaries[selection - 1].numOfLanguages);
    free(lookFor);
    printf("The word has been deleted successfully!\n");
}

void removeWordWithTranslationsFromList(List* lst, char** differentTranslationsOfWord, int numOfLanguages) {

    Word* current, * next;
    current = lst->head;
    if (current == NULL) {
        return;
    }
    if (current->translations == differentTranslationsOfWord) {//אם הערך להסרה זה ההיד
        lst->head = current->next;

        if (lst->head == NULL) {//אם הוא היה הצומת היחיד
            freeWordTranslations(current->translations, numOfLanguages);
            free(current);
            free(lst->head);
            return;
        }
        else {//אם יש עוד מילים אחריו
            freeWordTranslations(current->translations, numOfLanguages);
            free(current);
            //free(lst->head);
            //lst->head = current->next;
            return;
        }
    }
    next = current->next;
    while (next) {
        if (next->translations == differentTranslationsOfWord) {

            current->next = next->next;
            if (current->next == NULL) {
                lst->tail = current;
            }
            freeWordTranslations(next->translations, numOfLanguages);
            free(next);
            return;
        }
        else {
            current = next;
            next = current->next;
        }
    }
}


Dictionary* deleteDictionary(Dictionary* dictionaries, int* numOfDictionaries, List** lst) {

    printListOfDictionaries(dictionaries, numOfDictionaries);
    int selection;
    scanf("%d", &selection);

    while (selection > (*numOfDictionaries) || (selection <= 0 && ((*numOfDictionaries) != 0))) {
        printf("Wrong option, try again:\n");
        scanf("%d", &selection);
    }

    char isSure;
    printf("Are you sure? (y/n)\n");
    scanf(" %c", &isSure);

    if (isSure != 'y') {
        printf("The deletion of the dictionary has been canceled.\n");
        return dictionaries;
    }

    int numOfLanguagesInTheDictionaryToDelete = dictionaries[selection - 1].numOfLanguages;

    if (dictionaries[selection - 1].wordList == NULL) {
        int temp = selection;
        free(lst[temp - 1]);
        for (; temp < (*numOfDictionaries); temp++) {
            lst[temp - 1] = lst[temp];
        }

        for (int i = 0; i < dictionaries[selection - 1].numOfLanguages; i++) {
            free(dictionaries[selection - 1].languages[i]);
        }
        free(dictionaries[selection - 1].languages);
        temp = selection;

        for (; temp < (*numOfDictionaries); temp++) {
            dictionaries[temp - 1] = dictionaries[temp];
        }
        free(dictionaries[selection - 1].wordList);
        Dictionary* newDict = realloc(dictionaries, ((*numOfDictionaries - 1) * sizeof(Dictionary)));

        if (newDict == NULL && (*numOfDictionaries != 1)) {
            printf("1The deletion of the dictionary has failed!\n");
            return dictionaries;
        }
        dictionaries = newDict;
        (*numOfDictionaries)--;
        printf("The dictionary has been deleted successfully!\n");

        return dictionaries;
    }

    else {
        freeListRec(lst[selection - 1], numOfLanguagesInTheDictionaryToDelete);
        int temp = selection;
        free(lst[temp - 1]);
        for (; temp < (*numOfDictionaries); temp++) {
            lst[temp - 1] = lst[temp];
        }

        for (int i = 0; i < dictionaries[selection - 1].numOfLanguages; i++) {
            free(dictionaries[selection - 1].languages[i]);
        }
        free(dictionaries[selection - 1].languages);

        temp = selection;
        for (; temp < (*numOfDictionaries); temp++) {
            dictionaries[temp - 1] = dictionaries[temp];
        }

        Dictionary* newDict = realloc(dictionaries, ((*numOfDictionaries - 1) * sizeof(Dictionary)));

        if (newDict == NULL && (*numOfDictionaries != 1)) {
            printf("The deletion of the dictionary has failed!\n");
            return dictionaries;
        }
        dictionaries = newDict;
        (*numOfDictionaries)--;
        printf("The dictionary has been deleted successfully!\n");
        return dictionaries;
    }
}

void freeListRec(List* lst, int numOfLanguagesInTheDictionaryToDelete) {
    freeListHelper(lst->head, lst, numOfLanguagesInTheDictionaryToDelete);
}

void freeListHelper(Word* head, List* lst, int numOfLanguagesInTheDictionaryToDelete) {
    if (head == NULL) {
        return;
    }
    freeListHelper(head->next, lst, numOfLanguagesInTheDictionaryToDelete);
    removeWordWithTranslationsFromList(lst, head->translations, numOfLanguagesInTheDictionaryToDelete);
}

void freeWordTranslations(char** differentTranslationsOfWord, int numOfLanguages) {

    for (int i = 0; i < numOfLanguages; i++) {
        free(differentTranslationsOfWord[i]);
    }

    free(differentTranslationsOfWord);
}

void deleteAllDictionaries(Dictionary* dictionaries, int* numOfDictionaries, List** lst) {

    for (int i = (*numOfDictionaries); i > 0; i--) {
        dictionaries = deleteSpecificDictionary(dictionaries, numOfDictionaries, lst);
    }
    free(dictionaries);
    free(lst);
}

Dictionary* deleteSpecificDictionary(Dictionary* dictionaries, int* numOfDictionaries, List** lst) {

    int selection = (*numOfDictionaries);
    int numOfLanguagesInTheDictionaryToDelete = dictionaries[selection - 1].numOfLanguages;

    if (dictionaries[selection - 1].wordList == NULL) {
        int temp = selection;
        free(lst[temp - 1]);
        for (; temp < (*numOfDictionaries); temp++) {
            lst[temp - 1] = lst[temp];
        }

        for (int i = 0; i < dictionaries[selection - 1].numOfLanguages; i++) {
            free(dictionaries[selection - 1].languages[i]);
        }
        free(dictionaries[selection - 1].languages);
        temp = selection;

        for (; temp < (*numOfDictionaries); temp++) {
            dictionaries[temp - 1] = dictionaries[temp];
        }
        free(dictionaries[selection - 1].wordList);
        Dictionary* newDict = realloc(dictionaries, ((*numOfDictionaries - 1) * sizeof(Dictionary)));

        if (newDict == NULL && (*numOfDictionaries != 1)) {
            printf("The deletion of the dictionary has failed!\n");
            return dictionaries;
        }
        dictionaries = newDict;
        (*numOfDictionaries)--;
        return dictionaries;
    }

    else {
        freeListRec(lst[selection - 1], numOfLanguagesInTheDictionaryToDelete);
        int temp = selection;
        free(lst[temp - 1]);
        for (; temp < (*numOfDictionaries); temp++) {
            lst[temp - 1] = lst[temp];
        }

        for (int i = 0; i < dictionaries[selection - 1].numOfLanguages; i++) {
            free(dictionaries[selection - 1].languages[i]);
        }
        free(dictionaries[selection - 1].languages);

        temp = selection;
        for (; temp < (*numOfDictionaries); temp++) {
            dictionaries[temp - 1] = dictionaries[temp];
        }

        Dictionary* newDict = realloc(dictionaries, ((*numOfDictionaries - 1) * sizeof(Dictionary)));

        if (newDict == NULL && (*numOfDictionaries != 1)) {
            printf("The deletion of the dictionary has failed!\n");
            return dictionaries;
        }
        dictionaries = newDict;
        (*numOfDictionaries)--;
        return dictionaries;
    }
}


