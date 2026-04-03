typedef struct item {
    char code[5];
    char item_name[100];
    float price;
	char status[20];
	int sold_item;
	float sale_item;
} Item;

typedef struct admin {
    char id[3];
    char username[20];
    char passkey[30];
} Admin;

typedef struct order {
    Item item[25];
    int quantities[25];
    float total;
    float discounted_total;
    float payment;
    float change;
    long int reference_number;
    char date[11];
    int items_ordered;
    char student_number[16];
} Order;

typedef struct date{
    char month_text[10];
    char weekday[10];
    char month_number[3];
    char year[5];
    char day[3];

} Date;