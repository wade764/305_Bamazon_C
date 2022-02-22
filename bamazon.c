#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bamazon.h"

// This is the internal data structure. The
// database file is read into this data structure. It is an array of pointers to item .
static item *db[MAX_ITEMS];

// This is the number of items in the internal data
// structure.
static int num_items = 0;

// This data structure contains the
// items purchased by a shopper.
static item *purchased[MAX_PURCHASE];

// This is the number of items purchased.
// purchased_items is initially assigned 0, it is incremented on each call to
// purchase_item , and it is assigned 0 on the call to checkout .
static int purchased_items = 0;

// Reads the database filename into the
// internal data structure. Returns 0 on success and -1 on failure.
int read_db(char *filename) {

    printf("In read_db\n");

    FILE *fin = fopen(filename, "r"); // open for reading
    int i = 0;
    // thinking how I can determine if the file can be opended or not

    printf("In read_db 2\n");

    if (filename != NULL) {

        printf("In read_db 3\n");
        //*** HERE I am not certain I am reading in the data with the correct format specifier
        //itemnum(int) category(char[]) item(char[]) size(char) quantity(int) cost(double) onsale(int)  
        //        while (fscanf(fin, "%d %s %s %c %d %lf %d", &db[i]->itemnum, &db[i]->category, &db[i]->name, &db[i]->size, &db[i]->quantity, &db[i]->cost, &db[i]->onsale) != EOF) { 
        while (fscanf(fin, "%d[' '] %d[' '] %s[' '] %c[' '] %d[' '] %lf[' '] %d['\n']", &db[i]->itemnum, &db[i]->category, &db[i]->name, &db[i]->size, &db[i]->quantity, &db[i]->cost, &db[i]->onsale) != EOF) { 

            printf("In read_db in while here is i: %d\n",i);
            i++;
        }

        printf("about to return in read_db\n");

        fclose(fin);
        return 0;
    } else
        return -1;
    }

    // Writes the internal data structure to the
    // database filename. Returns 0 on success and -1 on failure.

    // *** see pg 85 of textbook for fopen modes
    int write_db(char *filename) {
        FILE *fout = fopen(filename, "w+"); // w+ Open for reading and writing, but file is overwritten if exists. 
        if(filename!=NULL){

            //increments through the item pointer array and prints them.
            int i = 0;
            while(&db[i]!=NULL)//does this need to be "while(**items)"???
            {
                fprintf(fout, "%d %p %p %c %d %lf %d", &db[i]->itemnum, &db[i]->category, &db[i]->name, &db[i]->size, &db[i]->quantity, &db[i]->cost, &db[i]->onsale);
                i++;
            }

            fclose(fout);//close when done!

        }
        return 0;
    }
    // Prints all items in the internal data structure to the
    // terminal. The following is a sample display.

    // 1 clothes shirt m 10 10.000000 100
    // 2 electronics computer x 3 100.000000 100
    // 3 tools drill x 5 75.900000 85
    // 4 toys barbie_doll x 13 4.350000 90
    void show_items(){

        int i = 0;
        while(&db[i]!=NULL)
        {
            printf("%d %p %p %c %d %lf %d \n", &db[i]->itemnum, &db[i]->category, &db[i]->name, &db[i]->size, &db[i]->quantity, &db[i]->cost, &db[i]->onsale);
            i++;
        }


        //loop through list of pointers to items,
        //print each one.
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
        int i = 0;
        while(&db[i]!=NULL)
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

    // Returns item* of itemnum . The item* is
    // deleted from the internal data structure. Returns 0 if itemnum is not in the internal
    // data structure.
    item *delete_item(int itemnum);

    // Fills in the *receipt[] with strings of all
    // the items purchased, which are in the array purchased . Returns the number of
    // elements in items . checkout assigns the variable purchased_items to 0.
    int checkout(char **receipt);

    // converts c to a string.
    // category_to_str mallocs memory for the resulting string.
    char *category_to_str(category c);

    // converts the string s to a category .
    category str_to_category(char *s);
