#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bamazon.h"

int num_items = 0;

void adminCommands(char *inputFile, int numLines, int canRead) {
    // the users response to the switch statement
    int response;

    // will keep running commands until this is switched to 0
    int keepRunning = 1;

    while(keepRunning) {
        printf("Please select from the following options\n");
        printf("1. Add an item to DB\n"); //add itemnum temcategory itemname size quantity cost onsale
        printf("2. Delete Item (item number)\n"); //delete itemnum
        printf("3. Update item cost (item number)\n"); //updatecost itemnum cost
        printf("4. Update item quantity\n"); //updatequantity itemnum quantity
        printf("5. Save DB\n"); // save does not quit
        printf("6. Quit program without saving\n"); // quit without saving
        printf("7. Print Database\n"); // shows all items in the database.
        printf("8. Show items by category\n"); // shows all items that are category
        printf("9. Show items in category less than a price\n"); // shows all items in category that cost less than cost
        printf("10. Show items by category equal to size\n"); // shows all items in category that are equal to size
        printf("11. Purchase item (by item number)\n"); // purchase item with itemnum
        printf("12. Complete purchase and exit program (saves db)\n"); // quit and save

        scanf("%d",&response);

        // used for case 1
        char categ[20];
        char nam[MAX_ITEM_CHARS];
        char siz;
        int quan;
        double doub;
        int sale;

        // used for case 1, 2, 3
        item* addItem;
        int itemNum;
        // used for case 3              
        int keepRunning = 1;
        double newPrice;
        // used for case 4
        int newQuantity;
        // used in case 5
        int saveSuccess;

        //used in cases 8,9,10
        int i;
        category cat;
        char str[MAX_ITEM_CHARS];
        item *items[MAX_ITEMS];
        //char strResult[MAX_ITEM_CHARS];
        char* strptr=str;
        //used in case 9
        char sizzz;

        //used in case 10
        double costtt;
Here:
        switch(response) {
            case 1:
                printf("itemnum cat name size quan price sale\n");

                scanf("%d %s %s %c %d %lf %d",&itemNum,categ, nam, &siz, &quan, &doub, &sale);

                // adding an item
                // removing 1 from the itemNum to match the index
                addItem = add_item(itemNum-1,categ,nam,siz,quan,doub,sale);
                num_items = get_numItems();

                // testing with the name, I am unsure how else you would test if the entire item was null in this case
                if (addItem->name != NULL) {
                    printf("Item added sucessfully!\n");
                } else {
                    printf("Could not add item!\n");
                }

                break;
            case 2:
                // Get the num of items incase user inputs an invalid entry
                num_items = get_numItems();

                // delete item by item number
                printf("Please enter item number to delete from database: ");
                scanf("%d",&itemNum);
                printf("\n");

                if (itemNum > num_items){
                    printf("%d is an invalid item number!\n",itemNum);
                }else {
                    //shifting this value to an index
                    itemNum--;

                    delete_item(itemNum);
                }

                break;
            case 3:
                // update itemnum cost
                printf("Please enter item number to update the cost in the database: ");
                scanf("%d",&itemNum);
                printf("\n");
                //shifting this value to an index
                itemNum--;

                item* temp3 = malloc(sizeof(item));
                temp3 = find_item_num(itemNum);
Here2:
                while (keepRunning) {
                    printf("Please enter the new cost for %s: ", temp3->name);
                    scanf("%lf", &newPrice);
                    printf("\n");
                    if (newPrice < 0){
                        printf("Please enter a positive number\n");
                        goto Here2;
                    }
                    keepRunning = 0;
                }

                // calling this with the user provided itemNum and newPrice
                update_item(itemNum, temp3->category, temp3->name, temp3->size, temp3->quantity, newPrice, temp3->onsale);

                break;
            case 4:
                // update itemnum quantity
                printf("Please enter item number to update the quantity in the database: ");
                scanf("%d",&itemNum);
                printf("\n");
                //shifting this value to an index
                itemNum--;

                item* temp4 = malloc(sizeof(item));
                temp4 = find_item_num(itemNum);

                printf("What is the updated quantity for %s: ",temp4->name);
                scanf("%d",&newQuantity);
                printf("\n");

                update_item(itemNum, temp4->category, temp4->name, temp4->size, newQuantity, temp4->cost, temp4->onsale);

                break;
            case 5:
                // saves db but does not exit
                saveSuccess = write_db(inputFile);
                if (!saveSuccess) {
                    printf("The database file was saved!\n");
                } else {
                    printf("The database save was not successful.\n");
                }


                break;
            case 6:
                // exits but does not save
                exit(0);

                break;
            case 7:
                // prints all items in data base
                show_items();

                break;
            case 8:
                // shows all items that are category
                printf("please enter the category you'd like to search for:   ");
                scanf("%s",str);
                printf("\n");
                cat=str_to_category(strptr);
                get_category(items,cat);

                i = 0;
                while(items[i]!=NULL)
                {
                    sprint_item(strptr,items[i]);
                    i++;
                    printf("\n");
                }
                printf("done!\n");
                break;
            case 9:
                // shows all items in category that cost less than user defined cost
                printf("please enter the category you'd like to search for:   ");
                scanf("%s",str);
                printf("\n");
                cat=str_to_category(strptr);

                printf("please enter the maximum cost to be used in search:   ");
                scanf("%lf",&costtt);
                printf("\n");

                get_category_cost(items,cat,costtt);
                i = 0;
                while(items[i]!=NULL)
                {
                    sprint_item(strptr,items[i]);
                    i++;
                    printf("\n");
                }
                printf("done!\n");
                break;
            case 10:
                // show category size, shows all items in category that are equal to size
                printf("please enter the category you'd like to search for:   ");
                scanf("%s",str);
                printf("\n");
                cat=str_to_category(strptr);

                printf("Please input the size you'd like to search for:   ");
                scanf(" %c",&sizzz);
                printf("\n");
                get_category_size(items,cat,sizzz);

                i = 0;
                while(items[i]!=NULL)
                {
                    sprint_item(strptr,items[i]);
                    i++;
                    printf("\n");
                }
                printf("done!\n");
                break;
            case 11:
                // purchase item with itemnum
                break;
            case 12:
                // exits program and saves to the database
                // The shopper can only change the database by purchasing items

                saveSuccess = write_db(inputFile);
                if (!saveSuccess) {
                    printf("The database file was saved!\n");
                } else {
                    printf("The database save was not successful.\n");
                }

                exit(0);
                break;
            default:
                printf("Invalid command!\n");
                goto Here;
        }
    }
}

void userCommands(char *inputFile, int numLines, int canRead) {
    // the users response to the switch statement
    int response;

    //used in cases 3,4,5
    int i;
    category cat;
    char str[MAX_ITEM_CHARS];
    item *items[MAX_ITEMS];
    //char strResult[MAX_ITEM_CHARS];
    char* strptr=str;
    //used in case 5
    char sizzz;

    //used in case 4
    double costtt;

    // will keep running commands until this is switched to 0
    int keepRunning = 1;

    while(keepRunning) {

        printf("Please select from the following options\n");
        printf("1. Print Database\n"); // shows all items in the database.
        printf("2. Show items by category\n"); // shows all items that are category
        printf("3. Show items in category less than a price\n"); // shows all items in category that cost less than cost
        printf("4. Show items by category equal to size\n"); // shows all items in category that are equal to size
        printf("5. Purchase item (by item number)\n"); // purchase item with itemnum
        printf("6. Complete purchase and exit program (saves db)\n"); // quit and save

        scanf("%d",&response);
Here:
        switch(response) {
            case 1:
                show_items();
                break;
            case 2:
                // shows all items that are category

                printf("please enter the category you'd like to search for:   ");
                scanf("%s",str);
                printf("\n");
                cat=str_to_category(strptr);
                get_category(items,cat);

                i = 0;
                while(items[i]!=NULL)
                {
                    sprint_item(strptr,items[i]);
                    i++;
                    printf("\n");
                }
                printf("done!\n");
                break;
            case 3:
                printf("please enter the category you'd like to search for:   ");
                scanf("%s",str);
                printf("\n");
                cat=str_to_category(strptr);

                printf("please enter the maximum cost to be used in search:   ");
                scanf("%lf",&costtt);
                printf("\n");

                get_category_cost(items,cat,costtt);
                i = 0;
                while(items[i]!=NULL)
                {
                    sprint_item(strptr,items[i]);
                    i++;
                    printf("\n");
                }
                printf("done!\n");
                break;
            case 4:
                // show category size, shows all items in category that are equal to size
                printf("please enter the category you'd like to search for:   ");
                scanf("%s",str);
                printf("\n");
                cat=str_to_category(strptr);

                printf("Please input the size you'd like to search for:   ");
                scanf(" %c",&sizzz);
                printf("\n");
                get_category_size(items,cat,sizzz);

                i = 0;
                while(items[i]!=NULL)
                {
                    sprint_item(strptr,items[i]);
                    i++;
                    printf("\n");
                }
                printf("done!\n");
                break;
            case 5:
                // purchase item with itemnum
                break;
            case 6:
                // exits program and saves to the database
                // The shopper can only change the database by purchasing items
                exit(0);
                break;
            default:
                printf("Invalid command!\n");
                goto Here;
        }
    }
}

// returns the total number of lines in the file
int lineCount( char *filename) {
    // The following code was modified from the source below
    // https://www.tutorialspoint.com/c-program-to-count-the-number-of-lines-in-a-file

    char ch;
    int numLines = 0;

    //open file in read more
    FILE *fp = fopen(filename, "r");
    // returning 0 instead of -1 
    if(fp == NULL) {
        printf("File \"%s\" does not exist!!!\n",filename);
        return 0;
    }
    //read character by character and check for new line
    while((ch = fgetc(fp))!=EOF) {
        if(ch == '\n')
            numLines++;
    }
    //close the file
    fclose(fp);

    //print number of lines
    //printf("Total number of lines are: %d\n",/*linesCount*/numLines);
    return numLines;
}

int main(int argc, char **argv) {

    char* inputFile;
    // making sure the program has a file as its 2nd command
    if (argc == 1) { // The database file is missing
        printf("File not found!\n");
        exit(1);
    } else if (argc > 2) { // The number of arguments is too long
        printf("File not found!\n");
        exit(2);
    } else if (argc == 2) {
        //printf("The database provided is called %s\n", argv[1]);
        inputFile = argv[1];
    }

    int numLines = lineCount(inputFile);
    // There was an issue reading the number of lines so the program exits if numlines is 0
    if (!numLines) {
        exit(6);
    }

    // passing the file pointer and the number of lines in the program
    // *** we want to only read the database once!!!
    int canRead = read_db(inputFile, numLines);

    // test
    //printf("0 is good, -1 is bad: %d\n",canRead);

    // The file could not be read in read_db if canRead is anything but 0
    if (canRead) {
        printf("File not found!");
    }

    // valid users
    char admin[] = "bamazon";
    char shopper[] = "shopper";

    // First prompt is Enter user name:
    char userName[8];
    // This can only use letters and numbers NO SPACES!
    printf("Enter user name (bamazon or shopper): ");
    //printf("Enter user name: ");
    fgets(userName,8,stdin);
    printf("\n");

    // Test
    //printf("This is user name: %s\n",userName);

    // strcmp returns anything other than 0 it will exit
    int validUser1 = strcmp(userName, admin);
    int validUser2 = strcmp(userName, shopper);
    //printf("strcmp admin: %d shopper: %d\n",validUser1,validUser2);

    // The following commands are for the admin account - bamazon
    if (!validUser1) {
        // validUser1 == 0 so it is the admin account
        // now we need to move to the admin commands
        numLines = lineCount(inputFile);
        // There was an issue reading the number of lines so the program exits if numlines is 0
        if (!numLines) {
            exit(6);
        }
        adminCommands(inputFile, numLines, canRead);

    } else if (!validUser2) {
        // validUser2 == 0  so it is the shopper account
        // now we need to move to the shopper commands
        numLines = lineCount(inputFile);
        // There was an issue reading the number of lines so the program exits if numlines is 0
        if (!numLines) {
            exit(6);
        }
        userCommands(inputFile, numLines, canRead);

        // The last two else if's are for invalid user names
    } else if (validUser1) {
        // not a valid user
        printf("Invalid user!\n");
        exit(3);
    } else if (validUser2) {
        // not a valid user
        printf("Invalid user!\n");
        exit(3);
    }
}
