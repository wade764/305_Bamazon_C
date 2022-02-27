#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bamazon.h"

//int numLines = 0;
int num_items = 0;

// This allows the owner and shopper to enter commands that are described in requirements 11 and 12

// 11. The bamazon user has the following commands.
//      a. add itemnum temcategory itemname size quantity cost onsale - adds an
//      item to the database. The parameters adhere to the rules shown in 1. An invalid
//      command results in the message Invalid add command!

//      b. delete itemnum - deletes the item with itemnum from the database. itemnum not
//      in the database results in the message Invalid itemnum!

//      c. updatecost itemnum cost - updates the cost of item with itemnum . itemnum not
//      in the database results in the message Invalid itemnum! Cost must be a
//      positive floating point number.

//      d. updatequantity itemnum quantity - updates the quantity of item with itemnum .
//      itemnum not in the database results in the message Invalid itemnum!
//      quantity must be a positive integer.

//      e. save - saves the changes to the database, but does not exit the program.

//      f. quit - quits the program and does not save changes to the database
//      Computer Systems and Architecture - Project Bamazon


// 12. The shopper and bamazon users have the following commands. When showing an item,
//      show all attributes separated by a space.

//      a. showitems - shows all items in the database.

//      b. showcategory category - shows all items that are category . No items of type
//      category results in the message No items of category! where category is
//      the string entered by the shopper.

//      c. showcategorycost category cost - shows all items in category that cost less
//      than cost . No items less than cost results in the message No items less than
//      cost! Where category and cost are entered by the shopper.

//      d. showcategorysize category size - shows all items in category that are equal
//      to size . No items of size results in the message No items of size! Where
//      category and size are entered by the shopper.

//      e. purchase itemnum - purchase item with itemnum . The quantity of the item in the
//      database with itemnum is decremented. itemnum not in the database results in
//      the message Invalid itemnum!

//      f. exit - exits the program and saves the changes to the database. The shopper
//      can only change the database by purchasing items. The owner can change the
//      database by adding, deleting, and updating items.

//      g. Any other command results in the message Invalid command!

//int get_numLines(){
//    
//    return numLines;
//}

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
                item* temp2 = malloc(sizeof(item));
                temp2 = find_item_num(itemNum);
                // passing the itemNum -1 because it will be the index of the db[]
                temp2 = delete_item(itemNum-1);

                // Test print
                char const* enumToString[] = { "clothes", "electronics", "tools", "toys"};
                printf("This is the deleted item: %d %s %s %c %d %.2lf %d\n", temp2->itemnum, enumToString[temp2->category], temp2->name, temp2->size, temp2->quantity, temp2->cost, temp2->onsale);

                // *** this will never happen because of find_item_num
                // if delete_item returns 0 it is not found in internal data structure
                //if (!canDelete) {
                //    printf("Item number not found in database.\n");
                //}

                break;
            case 3:
                // update itemnum cost
                printf("Please enter item number to update the cost in the database: ");
                scanf("%d",&itemNum);
                printf("\n");
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

                // This messes with the database
                //free(temp);

                break;
            case 4:
                // update itemnum quantity
                printf("Please enter item number to update the quantity in the database: ");
                scanf("%d",&itemNum);
                printf("\n");
                item* temp4 = malloc(sizeof(item));
                temp4 = find_item_num(itemNum);

                printf("What is the updated quantity for %s: ",temp4->name);
                scanf("%d",&newQuantity);
                printf("\n");

                update_item(temp4->itemnum, temp4->category, temp4->name, temp4->size, newQuantity, temp4->cost, temp4->onsale);

                break;
            case 5:
                // saves db but does not exit

                break;
            case 6:
                // exits but does not save
                // Stuck trying to make this more than just an exit, but it works
                exit(0);

                // Trying to prompt the user if the are sure is buggy

                //printf("Exit the program without saving? y/n\n");
                //char quit;
                ////printf(": ");
                //scanf("%c\n",&quit);
                //printf("%d %c %d\n",quit, 'y', 'y');
                //if (strcmp('y',quit) == 0) {
                //////if (quit != 'y'/* || 'Y'*/) {
                ////    //goto Here;
                //    exit(0);
                //}
                //} else if (quit != 'y'){
                //    printf("else loop\n");
                //    //exit(0);
                //goto Here;
                //}
                break;
            case 7:

                num_items = get_numItems();
                //printf("num_items: %d\n",num_items);

                //canRead = read_db(inputFile, num_items);
                //// The file could not be read in read_db if canRead is anything but 0
                //if (canRead) {
                //    printf("File not found!");
                //}


                // prints all items in data base
                //show_items(numLines);
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
                exit(0);

                // Trying to prompt the user if the are sure is buggy

                //printf("Exit the program without saving? y/n\n");
                //char quit;
                ////printf(": ");
                //scanf("%c\n",&quit);
                //printf("%d %c %d\n",quit, 'y', 'y');
                //if (strcmp('y',quit) == 0) {
                //////if (quit != 'y'/* || 'Y'*/) {
                ////    //goto Here;
                //    exit(0);
                //}
                //} else if (quit != 'y'){
                //    printf("else loop\n");
                //    //exit(0);
                //goto Here;
                //}
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

                num_items = get_numItems();
                // *** I am trying to read_db into the *db[] then print the items
                // so far this does not work...

                //canRead = read_db(inputFile, numLines);
                //// The file could not be read in read_db if canRead is anything but 0
                //if (canRead) {
                //    printf("File not found!");
                //}
                // prints all items in data base
                //show_items(numLines);
                show_items();


                break;
            case 2:
                // shows all items that are category

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

void deleteItem (int itemNum)// 11. b.
{

    //need to design data structure before this.

}

FILE* save (FILE *fout) //11. e.
{
    //FILE *f;

    //fout = fopen("output.txt", "w");
    //
    //// theres something funky here below
    //if(fout == null)
    //{
    //    printf("Error opening file!\n");
    //        exit(0);
    //}

    ////print contents after this.
    //fprint("printing to file now.\n");

    return fout;

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
    // *** 
    // we want to only read the database once!!!
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

    int validUser1 = strcmp(userName, admin);
    int validUser2 = strcmp(userName, shopper);
    //printf("strcmp admin: %d shopper: %d\n",validUser1,validUser2);

    // strcmp returns anything other than 0 it will exit

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
