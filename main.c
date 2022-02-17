#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bamazon.h"
//I'm just adding this as a test - Ethan, hello there

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

int main() {
    // we need to open a scanf to allow the user to enter commands
    int response;
    printf("Please select from the following options\n");
    printf("1. Add an item to DB\n"); //add itemnum temcategory itemname size quantity cost onsale
    printf("2. Delete Item (item number)\n"); //delete itemnum
    printf("3. Update item cost (item number)\n"); //updatecost itemnum cost
    printf("4. Update item quantity\n"); //updatequantity itemnum quantity
    printf("5. Save DB\n"); // save does not quit
    printf("6. Quit program without saving\n"); // quit without saving

    // using a switch statement to evaluate commands
    // labeled loop used to continue prompt until a valid entry
Here:
//Here2:
    // must have the print here you can not combine the scanner like below
    //scanf(":%d",&response); this goes into a loop
    printf(": ");
    scanf("%d",&response);
    // if you put anything other than in int here it will go into an infinite loop

    switch(response) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:
            exit(0);

            // Trying to prompt the user if the are sure is buggy

            //printf("Exit the program without saving? y/n\n");
            //char quit;
            ////printf(": ");
            //scanf("%c",&quit);
            ////printf("%d %c %d\n",quit, 'y', 'y');
            //if (quit == 'y') {
            ////if (quit != 'y'/* || 'Y'*/) {
            //    //goto Here;
            //    exit(0);
            //} else {
            //    printf("else loop\n");
            //    //exit(0);
            //    goto Here2;
            //}
            break;
        default:
            printf("Please enter a valid number.\n");
            goto Here;
    }

}
