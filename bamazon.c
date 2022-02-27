#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bamazon.h"

// This is the internal data structure. The
// database file is read into this data structure. It is an array of pointers to item .
// MAX_ITEMS = 300
static item *db[MAX_ITEMS];

// This is the number of items in the internal data
// structure.
static int num_items = 0;

// This data structure contains the
// items purchased by a shopper.
// MAX_PURCHASE = 10
static item *purchased[MAX_PURCHASE];

// This is the number of items purchased.
// purchased_items is initially assigned 0, it is incremented on each call to
// purchase_item , and it is assigned 0 on the call to checkout .
static int purchased_items = 0;

// function to return num_items
int get_numItems() {
    return num_items;
}

// modified to take quantity
item *update_item(int itemnum, category category, char *name, char size, int quantity, double cost, int onsale) {
    //double newPrice;
    //int keepRunning = 1;
    //Here:
    //while (keepRunning) {
    //    printf("Please enter the new cost for %s: ", db[itemnum-1]->name);
    //    scanf("%lf", &newPrice);
    //    printf("\n");
    //    if (newPrice < 0){
    //        printf("Please enter a positive number\n");
    //        goto Here;
    //    }
    //    keepRunning = 0;
    //}
    //db[itemnum-1]->cost = newPrice;
    db[itemnum-1]->cost = cost;
    db[itemnum-1]->quantity = quantity;

    return db[itemnum-1];

}

// Reads the database filename into the
// internal data structure. Returns 0 on success and -1 on failure.
// This reads the file but should only be used once per program run
// it is limited to the numLines in the initial read of the bamdata.txt file
int read_db(char *filename, int numLines) {

    //printf("In read_db\n");
    FILE *fin = fopen(filename, "r"); // open for reading
    //printf("In read_db 2\n");

    if (filename != NULL) {

        //printf("In read_db 3\n");
        //itemnum(int) category(char[]) name(char[]) size(char) quantity(int) cost(double) onsale(int)  

        // temp holder for category
        char cat[20];

        for (int i = 0; i < numLines; i++, num_items++) {
            // instantiating a new db object for each line of the file
            db[i] = malloc(sizeof(item));

            fscanf(fin, "%d %s %s %c %d %lf %d", &db[i]->itemnum, cat, db[i]->name, &db[i]->size, &db[i]->quantity, &db[i]->cost, &db[i]->onsale); 

            if (strcmp(cat, "clothes") == 0) {
                db[i]->category = clothes;
            } else if (strcmp(cat, "electronics") == 0) {
                db[i]->category = electronics;

            } else if (strcmp(cat, "tools") == 0) {
                db[i]->category = tools;

            } else if (strcmp(cat, "toys") == 0) {
                db[i]->category = toys;

            } else {
                printf("Unable to match the enum for category\n");
                exit(5);
            }

            //printf("In read_db in while here is i: %d\n",i);
        } 

        //printf("about to return in read_db\n");

        fclose(fin);

        return 0;
    }  else {
        return -1;
    }
}

// Writes the internal data structure to the
// database filename. Returns 0 on success and -1 on failure.
// *** see pg 85 of textbook for fopen modes
int write_db(char *filename) {

    FILE *fout = fopen(filename, "a"); // w+ Open for reading and writing, but file is overwritten if exists. 
    // 'a' appends to the end of the file

    if(filename!=NULL){

        db[num_items] = malloc(sizeof(item));

        char cat[20];
        char nam[MAX_ITEM_CHARS];
        char siz;
        int quan;
        double doub;
        int sale;

        // no need to scan the item number it will just go to the next number
        scanf("%s %s %c %d %lf %d", cat, nam, &siz, &quan, &doub, &sale);

        db[num_items]->itemnum = num_items+1;
        if (strcmp(cat, "clothes") == 0) {
            db[num_items]->category = clothes;
        } else if (strcmp(cat, "electronics") == 0) {
            db[num_items]->category = electronics;

        } else if (strcmp(cat, "tools") == 0) {
            db[num_items]->category = tools;

        } else if (strcmp(cat, "toys") == 0) {
            db[num_items]->category = toys;

        } else {
            printf("Unable to match the enum for category\n");
            exit(5);
        }
        strcpy(db[num_items]->name, nam);
        db[num_items]->size = siz;
        db[num_items]->quantity = quan;
        db[num_items]->cost = doub;
        db[num_items]->onsale = sale;

        fprintf(fout, "%d %s %s %c %d %.2lf %d\n", num_items+1, cat, nam, siz, quan, doub, sale);

        fclose(fout);//close when done!

        // Test statement
        printf("%d %s %s %c %d %.2lf %d\n", db[num_items]->itemnum, cat, db[num_items]->name, db[num_items]->size, db[num_items]->quantity, db[num_items]->cost, db[num_items]->onsale);

        num_items++;
        return 0;
    } else {
        // The file was not written sucessfully...
        return -1;
    }
}

// Prints all items in the internal data structure to the
// terminal. The following is a sample display.
// 1 clothes shirt m 10 10.000000 100
// 2 electronics computer x 3 100.000000 100
// 3 tools drill x 5 75.900000 85
// 4 toys barbie_doll x 13 4.350000 90
void show_items(){

    // *** Line below char const* from (Look up more on what a char const* is)
    //https://stackoverflow.com/questions/26008540/how-to-print-an-enumerated-variable-in-c

    char const* enumToString[] = { "clothes", "electronics", "tools", "toys"}; 

    int i = 0;
    while(i < num_items)
    {
        printf("%d %s %s %c %d %.2lf %d\n", db[i]->itemnum, enumToString[db[i]->category], db[i]->name, db[i]->size, db[i]->quantity, db[i]->cost, db[i]->onsale);
        i++;
    }

}

// Prints the value of item *c to the
// string *s. Returns the number of characters in s.
// char s[100];
// sprint_item(s, find_item_num(2));
// printf(“%s\n”, s); // prints
int sprint_item(char *s, item *c);

// Returns the an item* of itemnum .
// Returns 0 if itemnum is not in the internal data structure.
item *find_item_num(int itemnum)
{
    if (db[itemnum-1] == NULL) {
        printf("Invalid itemnum!\n");
        exit(7);
    }
    int i = 0;

    //while(&db[i]!=NULL)
    while(db[i])
    {

        if(db[i]->itemnum==itemnum){return db[i];}
        i++;
    }

    return 0;
}

// Fills in the *item[] with
// items where each element contains the string *s . Returns the number of
// elements in items .
// item *items[5];
// find_item_str(items, “o”); // items contains the following
// 2 electronics computer x 3 100.000000 100
// 4 toys barbie_doll x 13 4.350000 90
int find_item_str(item **items, char *s);

// Adds an item to the internal
// data structure. If itemnum is already in the internal data structure, the values of
// itemnum are updated; otherwise a new item is added.
item *add_item(int itemnum, char *category, char *name, char size,
        int quantity, double cost, int onsale);

// Fills in the *item[] with
// items where each element is category c . Returns the number of elements in
// items .
int get_category(item **items, category c);

// Fills in
// the *item[] with items where each element is category c and size . Returns
// the number of elements in items .
int get_category_size(item **items, category c, char size);

// Fills
// in the *item[] with items where each element is category c and less than cost .
// Returns the number of elements in items .
int get_category_cost(item **items, category c, double cost);

// Returns item* of itemnum . The
// quantity of item* in the internal data structure is decremented. Returns 0 if
// itemnum is not in the internal data structure. purchase places the purchased
// item in the array purchased and increments the variable purchased_items .
item *purchase_item(int itemnum);


// *** This is still buggy in the way that the item will still display if the invenetory is printed
// the item will be replaced with 0 clothes _ 0 0.00 0
// Returns item* of itemnum . The item* is
// deleted from the internal data structure. Returns 0 if itemnum is not in the internal
// data structure.
// This will work because when saving the database if the item number equals 0 we can skip writing the line
item *delete_item(int itemNum) {
    int justOnce = 1;

    if (db[itemNum] != NULL) {

        // used as reference material and modified from example
        // https://www.tutorialspoint.com/c-program-to-delete-an-array-element-using-pointers

        int i, j;
        if(itemNum <= num_items) {
            //for(i = itemNum - 1; i < num_items; i++){ 

            item* tempDel = malloc(sizeof(item));
            tempDel = db[itemNum];

            // you take the provided index (itemNum) and shift all pointers down one index 
            for(i = itemNum; i < num_items; i++){ 
                j = i + 1;
                //*(db[itemNum]+i) = *(db[itemNum]+j);
                if (justOnce) {
                    free(db[itemNum]);
                    justOnce = 0;
                    //printf("In justOnce delete_item\n");
                }
                // this sets the items after the deleted one to the previous item number 
                db[i]->itemnum = i;

                db[itemNum] = (db[itemNum] + j);
            }

            num_items--;

            printf("after deletion the array elements are:\n");
            //for(i = 0; i < num_items - 1; i++) {
            for(i = 0; i < num_items; i++) {
                //printf("%d\n",((db[itemNum]+i)->itemnum));
                printf("%d\n", db[i]->itemnum);
            }
            // still confused why we return the item*
            //return (db[itemNum] - 1);
            return tempDel;
        }
        }
        // I believe that this will not happen because I am using find_item_num in the admin switch case 2 in main
        return 0;
        }

        // Fills in the *receipt[] with strings of all
        // the items purchased, which are in the array purchased . Returns the number of
        // elements in items . checkout assigns the variable purchased_items to 0.
        int checkout(char **receipt);

        // converts c to a string.
        // category_to_str mallocs memory for the resulting string.
        char *category_to_str(category c);

        // converts the string s to a category .
        category str_to_category(char *s);
