#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bamazon.h"

int num_items = 0;

// declaring the save function
int save(char* filename);

void adminCommands(char *inputFile, int numLines, int canRead) {
    // the users response to the switch statement
    int response;

    // will keep running commands until this is switched to 0
    int keepRunning = 1;

    // used for write_db, tells if the item was sucessfully added to database
    int addItem;

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

        // used for case 2, 3
        int itemNum;
        // used for case 3              
        int keepRunning = 1;
        double newPrice;
        // used for case 4
        int newQuantity;
        // used in case 5
        int saveSuccess;

Here:
        switch(response) {
            case 1: 
                // adding an item
                addItem = write_db(inputFile);
                num_items = get_numItems();

                if (!addItem) {
                    printf("Item added sucessfully!\n");
                } else {
                    printf("Could not add item!\n");
                }

                break;
            case 2:
                // delete item by item number
                printf("Please enter item number to delete from database: ");
                scanf("%d",&itemNum);
                printf("\n");
                //shifting this value to an index
                itemNum--;

                // I am not using the retuned item* in this case so I am commenting out
                // DO NOT DELETE
                // COMMENTING OUT FOR TEST
                //item* temp2 = malloc(sizeof(item));
                //temp2 = find_item_num(itemNum);
                //// passing the itemNum -1 because it will be the index of the db[]
                //temp2 = delete_item(itemNum);

                delete_item(itemNum);

                // Test print
                //char const* enumToString[] = { "clothes", "electronics", "tools", "toys"};
                //printf("This is the deleted item: %d %s %s %c %d %.2lf %d\n", temp2->itemnum, enumToString[temp2->category], temp2->name, temp2->size, temp2->quantity, temp2->cost, temp2->onsale);

                break;
            case 3:
                // update itemnum cost
                printf("Please enter item number to update the cost in the database: ");
                scanf("%d",&itemNum);
                printf("\n");
                //shifting this value to an index
                itemNum--;

                item* temp3 = malloc(sizeof(item));
                //temp3 = find_item_num(itemNum-1);
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
                saveSuccess = save(inputFile);
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

                break;
            case 9:
                // shows all items in category that cost less than user defined cost

                break;
            case 10:
                // show category size, shows all items in category that are equal to size

                break;
            case 11:
                // purchase item with itemnum

                break;
            case 12:
                // exits program and saves to the database
                // The shopper can only change the database by purchasing items

                saveSuccess = save(inputFile);
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
                get_category();//(item**items,category c)
                break;
            case 3:
                // shows all items in category that cost less than user defined cost

                break;
            case 4:
                // show category size, shows all items in category that are equal to size

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

// currently using delete_item in bamazon.c

//void deleteItem (int itemNum)// 11. b.
//{
//
//    //need to design data structure before this.
//
//}

// creating a function that will save the database to the output file
// returns 0 for good write and -1 for bad
int save(char* filename) //11. e.
{
    // used for writing the correct number to the file
    int addMe = 0;

    int num_items = get_numItems();
    item* temp5[MAX_ITEMS];

    // referenced the following source for fopen
    // https://www.tutorialspoint.com/c_standard_library/c_function_fopen.htm

    FILE *fout = fopen(filename, "w"); // "w" Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
    // 'a' appends to the end of the file

    if(filename!=NULL){

        // TEST
        //printf("This is num_items in save main.c: %d\n", num_items);

        for (int i = 0; i < num_items; i++) {

            temp5[i] = malloc(sizeof(item));
            temp5[i] = find_item_num(i);

            // TEST
            //printf("In save, after find_item_num\n");

            char const* enumToString[] = { "clothes", "electronics", "tools", "toys"};

            // To avoid a seg fault if the item is null, then you skip else it writes to the file
            if (temp5[i] == NULL) {
                addMe++;
                //printf("In save, the item is NULL and addMe is: %d\n",addMe);
            } else {

                // subtracting addMe to get the item number to line up right
                fprintf(fout, "%d %s %s %c %d %.2lf %d\n", (temp5[i]->itemnum)-addMe, enumToString[temp5[i]->category], temp5[i]->name, temp5[i]->size, temp5[i]->quantity, temp5[i]->cost, temp5[i]->onsale);
            }
        }

        fclose(fout);//close when done!

        //// Test statement
        //printf("%d %s %s %c %d %.2lf %d\n", db[num_items]->itemnum, cat, db[num_items]->name, db[num_items]->size, db[num_items]->quantity, db[num_items]->cost, db[num_items]->onsale);

        return 0;
    } else {
        // The file was not written sucessfully...
        return -1;
    }
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
