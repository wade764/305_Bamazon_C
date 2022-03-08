#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bamazon.h"

// This is the internal data structure. The
// database file is read into this data structure. It is an array of pointers to item .
// MAX_ITEMS = 300
static item *db[MAX_ITEMS];

// This is the number of items in the internal data structure.
static int num_items = 0;

// This data structure contains the
// items purchased by a shopper.
// MAX_PURCHASE = 10
static item *purchased[MAX_PURCHASE];

// This is the number of items purchased.
// purchased_items is initially assigned 0, it is incremented on each call to
// purchase_item , and it is assigned 0 on the call to checkout .
static int purchased_items = 0;

// function added to return num_items
int get_numItems() {
    return num_items;
}

// modified to take quantity
item *update_item(int itemnum, category category, char *name, char size, int quantity, double cost, int onsale) {

    char const* enumToString[] = { "clothes", "electronics", "tools", "toys"}; 

    // this line sets the item number back to the correct position 
    db[itemnum]->itemnum = itemnum+1;
    if (strcmp(enumToString[category], "clothes") == 0) {
        db[itemnum]->category = clothes;
    } else if (strcmp(enumToString[category], "electronics") == 0) {
        db[itemnum]->category = electronics;

    } else if (strcmp(enumToString[category], "tools") == 0) {
        db[itemnum]->category = tools;

    } else if (strcmp(enumToString[category], "toys") == 0) {
        db[itemnum]->category = toys;

    } else {
        printf("Unable to match the enum for category\n");
        exit(5);
    }
    strcpy(db[itemnum]->name, name);
    db[itemnum]->size = size;
    db[itemnum]->quantity = quantity;
    db[itemnum]->cost = cost;
    db[itemnum]->onsale = onsale;

    return db[itemnum];

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

        for (int i = 0; i < numLines; i++) {
            // instantiating a new db object for each line of the file
            db[i] = malloc(sizeof(item));
            num_items++;

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

// This is for adding the database internal structure
// see save function in main for writing to output
// Writes the internal data structure to the
// database filename. Returns 0 on success and -1 on failure.
// *** see pg 85 of textbook for fopen modes
// *** NOTE if the itemnum is off double check the database file for the correct number of items first before changing code
int write_db(char *filename) {

    FILE *fout = fopen(filename, "a"); // w+ Open for reading and writing, but file is overwritten if exists. 
    // 'a' appends to the end of the file

    if(filename!=NULL){

        // TEST
        //printf("This is num_items in write_db: %d\n",num_items);

        db[num_items] = malloc(sizeof(item));

        char cat[20];
        char nam[MAX_ITEM_CHARS];
        char siz;
        int quan;
        double doub;
        int sale;

        // no need to scan the item number it will just go to the next number
        scanf("%s %s %c %d %lf %d", cat, nam, &siz, &quan, &doub, &sale);

        // the plus one is important because in this case num_items is an index starting at 0
        db[num_items]->itemnum = num_items+1;

        // TEST
        //printf("db[num_items]->itemnum in write_db: %d\n",db[num_items]->itemnum);

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
        //printf("%d %s %s %c %d %.2lf %d\n", db[num_items]->itemnum, cat, db[num_items]->name, db[num_items]->size, db[num_items]->quantity, db[num_items]->cost, db[num_items]->onsale);

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
//void show_items(int numItems){
void show_items(){

    // *** Line below char const* from (Look up more on what a char const* is)
    //https://stackoverflow.com/questions/26008540/how-to-print-an-enumerated-variable-in-c

    char const* enumToString[] = { "clothes", "electronics", "tools", "toys"}; 
    // TEST
    //printf("This is numItems being passed in show_items: %d\n",numItems);

    int i = 0;                                                                                                                                                       
    //while(i < num_items)                                                                                                                                           
    while(db[i] != NULL) 
    {                                                                                                                                                                
        printf("%d %s %s %c %d %.2lf %d\n", db[i]->itemnum, enumToString[db[i]->category], db[i]->name, db[i]->size, db[i]->quantity, db[i]->cost, db[i]->onsale);   
        i++;                                                                                                                                                         
    }                                                                                                                                                                

    // DO NOT DELETE USED FOR ACTUALLY REMOVING THE ITEM STILL WORKING ON THIS
    //for (int i = 0; db[i]; i++) {
    //    if (db[i] == NULL) {

    //    } else {
    //    
    //        printf("%d %s %s %c %d %.2lf %d\n", db[i]->itemnum, enumToString[db[i]->category], db[i]->name, db[i]->size, db[i]->quantity, db[i]->cost, db[i]->onsale);

    //    }
    //}

}

// Prints the value of item *c to the
// string *s. Returns the number of characters in s.
// char s[100];
// sprint_item(s, find_item_num(2));
// printf(“%s\n”, s); // prints
int sprint_item(char *s, item *c)
{
    int n = (*c).itemnum ;
    category cat = c->category;
    char nam[MAX_ITEM_CHARS];
    strcpy(nam,(*c).name);
    char s2 = (*c).size;
    int q = (*c).quantity;
    double c2 = (*c).cost;
    int o = (*c).onsale;

    int result;
    char const* enumToString[] = { "clothes", "electronics", "tools", "toys"};                                                                                  

    // *** Modified this to the line below
    //char c3 = enumToString[cat];
    const char* c3 = enumToString[cat];


    //the function below is a c library function that takes a string pointer (s in this case), and converts other data types and inputs them to that string.
    result = sprintf(s,"Item Number: %d, Item Name: %s,Item Category: %s, Item Size: %c, Item Quantity: %d, Item Price: %lf, Item Sale Modifier: %d",n,nam,c3,s2,q,c2,o);

    //prints to terminal.
    printf("%s\n",s);

    return result;
}

// Returns the an item* of itemnum .
// Returns 0 if itemnum is not in the internal data structure.
item *find_item_num(int itemnum)
{
    // TEST
    //printf("In find_item_num bamazon.c\n");
    //printf("This is the itemnum: %d\n",itemnum);

    if (db[itemnum] == NULL) {
        printf("Invalid itemnum!\n");
        exit(7);
    }
    int i = 0;

    while(db[i])
    {

        if(db[i]->itemnum==itemnum+1){return db[i];}
        i++;
    }

    // TEST
    //printf("About to return in find_item_num bamazon.c\n");

    return 0;
}

// Fills in the *item[] with
// items where each element contains the string *s . Returns the number of
// elements in items .
// item *items[5];
// find_item_str(items, “o”); // items contains the following
// 2 electronics computer x 3 100.000000 100
// 4 toys barbie_doll x 13 4.350000 90
int find_item_str(item **items, char *s)
{

    int counter = 0;
    int i=0;

    // *** Changed char s to char sChar

    char sChar[100];//declare a string

    // This needs to be fixed see line below
    //char *s2=&sChar;//declare a string pointer
    char *s2= malloc(sizeof(char)*100);//declare a string pointer
    s2 = sChar;

    int dummy;//dummy to hold return value of sprint_item

    while(db[i] != NULL)//increment through db[]
    {
        if(strstr(db[i]->name,sChar))//check for substring s,
            {
                dummy = sprint_item(s2,db[i]);//print item.
                items[counter]=db[i];
                counter++;
            }
    }

    return counter+1;//RETURNS NUMBER OF ELEMENTS, NOT MAX INDEX.
}
// Adds an item to the internal
// data structure. If itemnum is already in the internal data structure, the values of
// itemnum are updated; otherwise a new item is added.
item *add_item(int itemnum, char *category, char *name, char size, int quantity, double cost, int onsale)
{

    //how do we check for if the item is already here?
    //if(db[itemnum-1]==NULL)

    db[num_items] = malloc(sizeof(item));

    //char cat[20];

    // NEEDED TO HAVE A DIFFERENT VARIABLE NAME HERE
    //char name[MAX_ITEM_CHARS];
    char nameTEMP[MAX_ITEM_CHARS];


    //scanf("%s %s %c %d %lf %d", cat, nam, &siz, &quan, &doub, &sale);

    // the plus one is important because in this case num_items is an index starting at 0
    db[num_items]->itemnum = num_items+1;

    char const* enumToString[] = { "clothes", "electronics", "tools", "toys"};                                                                                  

    // this was strcmp(*category, "electronics")
    if (strcmp(enumToString[db[num_items]->category], "clothes") == 0) {
        db[num_items]->category = clothes;
    } else if (strcmp(enumToString[db[num_items]->category], "electronics") == 0) {
        db[num_items]->category = electronics;

    } else if (strcmp(enumToString[db[num_items]->category], "tools") == 0) {
        db[num_items]->category = tools;

    } else if (strcmp(enumToString[db[num_items]->category], "toys") == 0) {
        db[num_items]->category = toys;

    } else {
        printf("Unable to match the enum for category\n");
        exit(5);
    }
    //strcpy(db[num_items]->name, name);
    strcpy(db[num_items]->name, nameTEMP);
    db[num_items]->size = size;
    db[num_items]->quantity = quantity;
    db[num_items]->cost = cost;
    db[num_items]->onsale = onsale;


    // moved this to above
    //char const* enumToString[] = { "clothes", "electronics", "tools", "toys"};                                                                                  



    // Test statement
    printf("%d %s %s %c %d %.2lf %d\n", db[num_items]->itemnum, enumToString[db[num_items]->category], db[num_items]->name, db[num_items]->size, db[num_items]->quantity, db[num_items]->cost, db[num_items]->onsale);

    num_items++;

    return db[num_items];
}


// Fills in the *item[] with
// items where each element is category c . Returns the number of elements in
// items .
int get_category(item **items, category c)
    // MODIFIED
    //int get_category(category c)
{

    // GCC SAYS ITS NOT BEING USED
    int i = 0;                                                                                                                                                       
    int counter = 0;                                                                                                                                               
    while(db[i] != NULL)                                                                                                                                             
    {  


        if(db[i]->category==c)
        { 
            items[counter]=db[i];
            counter++;
        }

        i++;                                                                                                                                                         
    }           
    return counter;

}
// Fills in
// the *item[] with items where each element is category c and size . Returns
// the number of elements in items .
int get_category_size(item **items, category c, char size)//pass **items by reference (&arrayName).
{
    //The purpose of this function is to fill the array you give it with the items from the db that fit matching criteria.
    //it is up to main.c to use this information from the array that is modified in this function effectively.
    //

    // GCC SAYS ITS NOT BEING USED
   int i = 0;                                                                                                                                                       
    int counter = 0;                                                                                                                                               
    while(db[i] != NULL)                                                                                                                                             
    {  

        if(db[i]->category==c)
        {
            if(db[i]->size==size)
            {
                //we need to printf in main off of the **items.
                //printf("%d %s %s %c %d %.2lf %d\n", db[i]->itemnum, enumToString[db[i]->category], db[i]->name, db[i]->size, db[i]->quantity, db[i]->cost, db[i]->onsale);   
                items[counter]=db[i];
                counter++;
            }
        }

        i++;                                                                                                                                                         
    }                                                                                                                                                                
    counter= counter+1;//THIS RETURNS THJE NUMBER OF ELEMENTS, NOT THE MAXIMUM INDEX.
    return counter;

}

// Fills
// in the *item[] with items where each element is category c and less than cost .
// Returns the number of elements in items .
int get_category_cost(item **items, category c, double cost)
{
    //The purpose of this function is to fill the array you give it with the items from the db that fit matching criteria.
    //it is up to main.c to use this information from the array that is modified in this function effectively.

    // GCC SAYS ITS NOT BEING USED
    char const* enumToString[] = { "clothes", "electronics", "tools", "toys"}; 
    int i = 0;                                                                                                                                                       
    int counter = 0;                                                                                                                                               
    while(db[i] != NULL)                                                                                                                                             
    {  

        if(db[i]->category==c)
        {
            if(db[i]->cost<cost)
            {
                //we need to printf in main off of the **items.
                //printf("%d %s %s %c %d %.2lf %d\n", db[i]->itemnum, enumToString[db[i]->category], db[i]->name, db[i]->size, db[i]->quantity, db[i]->cost, db[i]->onsale);   
                items[counter]=db[i];
                counter++;
            }
        }

        i++;                                                                                                                                                         
    }                                                                                                                                                                
    counter= counter+1;//THIS RETURNS THJE NUMBER OF ELEMENTS, NOT THE MAXIMUM INDEX.
    return counter;

}


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
                    printf("Deleting %s\n",db[itemNum]->name);
                    // *** commenting these out and just using the line below outside of the loop works
                    //db[itemNum] = (db[itemNum] + j);

                    // DONT DELETE BUT DO NOT USE RIGHT NOW, ONE OR THE OTHER
                    //free(db[itemNum]);
                    //db[itemNum] = NULL;
                    justOnce = 0;

                    // TEST
                    //printf("In justOnce delete_item\n");
                }
                // *** DON'T DELETE THE COMMENTS BELOW HERE UNTIL RESOLVED

                // this sets the items after the deleted one to the previous item number (The line number not the index) 
                // this line keeps the item numbers the same prior to delete

                db[i]->itemnum = i+1;

                // this line below shift the item numbers down one to line up with the deleted item
                //db[i]->itemnum = i;
                // Currently the problem becomes once an item is deleted it stays in the internal database as
                // 0 clothes  0 0.00 0 , so the index is still there when the user goes to enter another command

                // This is shifting the pointer to the next element
                db[itemNum] = (db[itemNum] + j);

                //free(tempDel);
            }

            num_items--;

            // TEST
            //printf("after deletion the array elements are:\n");
            //for(i = 0; i < num_items; i++) {
            //    //printf("%d\n",((db[itemNum]+i)->itemnum));
            //    printf("%d\n", db[i]->itemnum);
            //}

            return tempDel;
            //return db[itemNum];
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
    char *category_to_str(category c)
    {

        // *** COMMENTING OUT FOR COMPILE
        char result[15];
        if(c==0)
        {strcpy(result,"clothes");}
        else if(c==1)
        {strcpy(result,"electronics");}
        else if (c==2)
        {strcpy(result,"tools");}
        else if (c==3)
        {strcpy(result,"toys");}
        else
        {
            printf("Could not resolve category in [category_to_str]");
            return NULL;

        }

        char *r;
        r=&result;

        return r;

    }
    // converts the string s to a category .
    category str_to_category(const char *str)
    {

        category c;

        if (strcmp(str, "clothes") == 0) {
            c=clothes;
        } else if (strcmp(str, "electronics") == 0) {
            c = electronics;

        } else if (strcmp(str, "tools") == 0) {
            c = tools;

        } else if (strcmp(str, "toys") == 0) {
            c = toys;

        } else {
            printf("Unable to match the enum for category\n");
            exit(5);
        }

        return c;

    }
