#define MAX_ITEMS 300
#define MAX_ITEM_CHARS 32
#define MAX_PURCHASE 10

// In an enum the compiler reads the variables as int, with an index
// so clothes is 0, electronics is 1, etc...
typedef enum { clothes, electronics, tools, toys } category;

// You can declare the value as below
// in this case electronics = 11, tools = 12, etc...
//typedef enum { clothes = 10, electronics, tools, toys } category;

typedef struct {
        int itemnum;
        category category;
        char name[MAX_ITEM_CHARS];
        char size;
        int quantity;
        double cost;
        int onsale;
} item;

// adding get_numItems
int get_numItems();

// modified this to take the number of lines in the file
int read_db(char *filename, int numLines);

int write_db(char *filename);

void show_items();

int sprint_item(char *s, item *c);

item *find_item_num(int itemnum);

int find_item_str(item **items, char *s);

item *add_item(int itemnum, char *category, char *name, char size, int
                quantity, double cost, int onsale);

item *update_item(int itemnum, category category, char *name, char size,
                double cost, int onsale);

int get_category(item **items, category c);

int get_category_size(item **items, category c, char size);

int get_category_cost(item **items, category c, double cost);

item *purchase_item(int itemnum);

item *delete_item(int itemnum);

int checkout(char **receipt);

char *category_to_str(category c);

category str_to_category(char *s);
