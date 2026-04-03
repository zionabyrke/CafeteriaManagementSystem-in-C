
// # Helper funtions
void clearterminal();
void error(const char *message);
void success(const char *message);
void loading(const int secs);
void marginleft(const int margin);
void repeatchar(const char symbol, const int repetitions);
void tablefaccounts(Admin *admin_accounts_ptr[]);
void sortfaccount(Admin *admin_accounts_ptr);
//Date generatedate();
int checkfid(Admin *admin_accounts_ptr[], char id[]);
int checkfusername(Admin *admin_accounts_ptr[], char username[]);
void generatedate(char date[]);

int itemlen(Item[]);
int int_arrlen(int[]);
int strlen_2D(char[][MAXSTRLEN]);
int strlen_3D(char[][10][MAXSTRLEN]);
void duplicateItems(Item[], char[][10][MAXSTRLEN]);
void duplicatePurchase(Order, char[][10][MAXSTRLEN]);
void getLongestStr(char[][10][MAXSTRLEN], char[][MAXSTRLEN], int[]);
void rowByRow_print(char[][10][MAXSTRLEN], int[], int);
void generateBorderStr(char[], int[], char, char);
void headers_print(char[][MAXSTRLEN], int[]);
void dualTable(char[][10][MAXSTRLEN], char[][10][MAXSTRLEN],
                char[][MAXSTRLEN], char[][MAXSTRLEN], char[][MAXSTRLEN]);
void singleTable(char[][10][MAXSTRLEN],char[][MAXSTRLEN],char[][MAXSTRLEN]);


void generatedate(char date[]) {

    char date_size[20];
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    strftime(date, sizeof(date_size), "%B %d, %Y", local_time);
}

void repeatchar(const char symbol, const int repetitions) {
    for(int i = 0; i < repetitions; i++) {
        printf("%c", symbol);
    }
}
void marginleft(const int margin) {
    for(int i = 0; i < margin; i++) {
        printf(" ");
    }
}
void loading(int secs) {
    clock_t start = clock();
    while ((clock() - start) / CLOCKS_PER_SEC < secs);
}
void error(const char* message) {
    printf("\033[31m%s\033[0m\n\n", message);
}
void success(const char* message) {
    printf("\033[32m%s\033[0m\n", message);
}

int uniqueID(Admin *admin_accounts_ptr[], char id[]) {

    for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
        if(strcmp(admin_accounts_ptr[i]->id, id) == 0) {
            return 0;
        }
    }

    return 1;
}
int uniqueUsername(Admin *admin_accounts_ptr[], char username[]) {

    for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
        if(strcmp(admin_accounts_ptr[i]->username, username) == 0) {
            return 0;
        }
    }

    return 1;
}

/* appended by Renz */
void clearterminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
int itemlen(Item menu[]){
    int cnt = 0;
    for(; cnt <= MAX_MENU; ++cnt)
        if(strcmp(menu[cnt].code, "STOP") == 0)
            break;
    return cnt;
}
int int_arrlen(int arr[]){
    int cnt = 0;
    for(; arr[cnt] != 12345 && cnt <= MAXSTRLEN; ++cnt);
    return cnt;
}
int strlen_2D(char str[][MAXSTRLEN]){
    int cnt = 0;
    for(; cnt <= MAXSTRLEN; ++cnt)
        if(strcmp(str[cnt], "STOP") == 0)
            break;
    return cnt;
}
int strlen_3D(char str[][10][MAXSTRLEN]){
    int cnt = 0;
    for(; cnt <= MAXSTRLEN; ++cnt)
        if(strcmp(str[cnt][0], "STOP") == 0)
            break;
    return cnt;
} // ALL YOU NEED IS TO COPY YOUR STRUCT MEMBERS AS STRINGS
void duplicateItems(Item items[], char str[][10][MAXSTRLEN]){
    int i, rows = itemlen(items);
    for(i = 0; i < rows; i++){
        strcpy(str[i][0], items[i].code);
        strcpy(str[i][1], items[i].item_name);
        sprintf(str[i][2], "%.2f", items[i].price); // FOR FLOAT & INTEGERS
        strcpy(str[i][3], items[i].status);
        sprintf(str[i][4], "%.2f", items[i].sale_item);
    }
    strcpy(str[i][0], "STOP"); //sentinel value
}
void duplicatePurchase(Order order, char s[][10][MAXSTRLEN]){
    int i;
    for ( i = 0; i < order.items_ordered; i++ ){
        strcpy(s[i][0], order.item[i].code);
        strcpy(s[i][1], order.item[i].item_name);
        sprintf(s[i][2], "%.2f", order.item[i].price);
        sprintf(s[i][3], "%d", order.quantities[i]);
    }
    strcpy(s[i][0], "STOP"); //sentinel value
}
void duplicateOrdersReceipt(Order curr, char s[][10][MAXSTRLEN]){
    int i;
    for(i = 0; i < curr.items_ordered; i++){
        strcpy(s[i][0], curr.item[i].item_name);
        sprintf(s[i][1], "%d", curr.quantities[i]);
        sprintf(s[i][2], "%.2f", curr.item[i].price);
    }   strcpy(s[i][0], "STOP");
}
void getLongestStr(char str[][10][MAXSTRLEN], char hdrs[][MAXSTRLEN], int lens[]){
    int i, j, cols, rows;
    cols = strlen_2D(hdrs);
    rows = strlen_3D(str);
    for(i = 0; i < cols; i++){
        lens[i] = strlen(hdrs[i]);
    }
    lens[i] = 12345; //sentinel value

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            if(lens[j] < strlen(str[i][j]))
                lens[j] = strlen(str[i][j]);
        }
    }
}   
void rowByRow_print(char str[][10][MAXSTRLEN], int pds[], int currentrow){
    int i, j, cols = int_arrlen(pds);
    for(i = 0; i < cols; i++){
        if(str[currentrow][i][1] == '.' || str[currentrow][i][2] == '.'
            || str[currentrow][i][3] == '.' || str[currentrow][i][4] == '.'
            || str[currentrow][i][5] == '.' || str[currentrow][i][6] == '.')

            printf("| %*s ", pds[i], str[currentrow][i]);
        else
            printf("| %-*s ", pds[i], str[currentrow][i]);
        }
    printf("|%6s", " ");
}
void generateBorderStr(char bs[], int l[], char div, char border){
    int i = 0, j, k = 0;
    int cols = int_arrlen(l);
    while(i < cols){
        bs[k] = div;
        for(j = 0; j < l[i] + 3; j++)
            bs[++k] = border;
        i++;
    }
    bs[k] = div;
    bs[k + 1] = '\0';
}
void headers_print(char hdr[][MAXSTRLEN], int pds[]){
    int i, cols = int_arrlen(pds);
    for(int i = 0; i < cols; i++)
        printf("| %-*s ", pds[i], hdr[i]);
    printf("|%6s", "");
}
void dualTable(char str1[][10][MAXSTRLEN], char str2[][10][MAXSTRLEN], char hdr1[][MAXSTRLEN], char hdr2[][MAXSTRLEN], char cats[][MAXSTRLEN]){
    int i, j, sp1, sp2, spBetween, endtable1, fit;
    int rw1, rw2, c1, c2;
    char b1[MAXBORDER], b2[MAXBORDER];

    c1 = strlen_2D(hdr1);
    c2 = strlen_2D(hdr2);
    rw1 = strlen_3D(str1);
    rw2 = strlen_3D(str2);

    int pd1[c1 + 1], pd2[c2 + 1];
    
    getLongestStr(str1, hdr1, pd1);
    getLongestStr(str2, hdr2, pd2);
    generateBorderStr(b1, pd1, '+', '-');
    generateBorderStr(b2, pd2, '+', '-');

    sp1 = (strlen(b1) - strlen(cats[2]) - 8)/2;

    if((strlen(b1) + strlen(b2) + 16) <= TERMINAL_SIZE)
        fit = 1;
    else fit = 0;

    printf("%*s==== %s DASHBOARD ( %s%s%s ) ====\n\n", PADDING_LEFT, "", cats[0], BLUE, cats[1], RESET);
    if(fit == 1){
        sp2 = (strlen(b2) - strlen(cats[3]) - 8)/2;
        spBetween = strlen(b1) - strlen(cats[2]) - sp1 + 6 - 8;
        endtable1 = strlen(b1) + 6;

        printf("%*s%*s--- %s%s%s ---", sp1, "", PADDING_LEFT, "", BLUE, cats[2], RESET);
        printf("%*s%*s--- %s%s%s ---\n", sp2, "", spBetween, "", BLUE, cats[3], RESET);
        printf("%*s%s%6s%s\n", PADDING_LEFT, "", b1, "", b2);

        marginleft(10);
        headers_print(hdr1, pd1);    
        headers_print(hdr2, pd2);

        printf("\n%*s%s%*s%s\n",PADDING_LEFT, "", b1, 6, "", b2);

        for(i = 0, j = 0; (i < rw1) || (j < rw2); i++, j++){
            marginleft(10);
            if(i < rw1)
                rowByRow_print(str1, pd1,  i);
            else
                printf("%*s%-*s", PADDING_LEFT, "", endtable1, "");

            if(j < rw2)
                rowByRow_print(str2, pd2,  j);
            /*------ THIS IS
                    NEW LINE ------*/
            if(i < rw1)
                printf("\n%*s%s%-*s", PADDING_LEFT, "", b1, 6, "");
            else
                printf("\n%*s%-*s", PADDING_LEFT, "", endtable1, "");

            if(j < rw2)
                printf("%s", b2);
            printf("\n");
        }
    }

    else{
        strcpy(cats[0], "DOUBLE");
        singleTable(str1, hdr1, cats);
        printf("\n");

        strcpy(cats[2], cats[3]);
        singleTable(str2, hdr2, cats);
    }

}
void singleTable(char str[][10][MAXSTRLEN], char hdrs[][MAXSTRLEN], char cats[][MAXSTRLEN]){
    int i, rows, cols, sp, datesp;
    char border[MAXBORDER];
    rows = strlen_3D(str);
    cols = strlen_2D(hdrs);

    int pds[cols + 1];

    getLongestStr(str, hdrs, pds);
    generateBorderStr(border, pds, '+', '-');

    sp = (strlen(border) - strlen(cats[2]) - 8)/2;
    datesp = strlen(border) - strlen(cats[3]) - 24;
    
    if(strcmp(cats[0], "DOUBLE") != 0){
        printf("%*s==== %s DASHBOARD ( %s%s%s ) ====\n\n", PADDING_LEFT, "", cats[0], BLUE, cats[1], RESET);
    }
    printf("%*s%*s--- %s%s%s ---\n", PADDING_LEFT, "", sp,  "", BLUE, cats[2], RESET);

    printf("%*s%s\n%*s", PADDING_LEFT, "", border, PADDING_LEFT, "");
    headers_print(hdrs, pds);
    printf("\n%*s%s\n", PADDING_LEFT, "",  border);

    for(i = 0; i < rows; i++){
        marginleft(10);
        rowByRow_print(str, pds, i);
        printf("\n%*s%s\n", PADDING_LEFT, "",  border);
    }
}

/* customer */
void orderQuantity(Order *order, Item *item){
    char tmp[10]; int i, buf = 0;
    do{
        printf("%*sQuantity: ", PADDING_LEFT, "");
        scanf(" %s", tmp);
        for(i = 0; i < strlen(tmp); i++){
            if((tmp[i] < '0') || (tmp[i] > '9')){
                buf = -1;
                break;
            }
            else buf = 1;
        }
        if(buf == 1){
            order->quantities[order->items_ordered] = atoi(tmp);
            if(order->quantities[order->items_ordered] >= 0){
                item->sold_item += order->quantities[order->items_ordered];  //kung need
                item->sale_item = item->sold_item * item->price;             //
                order->total += (order->quantities[order->items_ordered] * item->price);
                break;
            }
            else buf = 0;
        }
        if(buf < 1) {
            printf("%*s%sInvalid quantity. Try again.\n%s", PADDING_LEFT, "", RED, RESET);
        }
    }while(1);

    order->item[order->items_ordered] = *item;
    order->items_ordered++;
}
void displayOrder(Order purc){
    char str[purc.items_ordered + 1][10][MAXSTRLEN];
    char hdr[10][MAXSTRLEN] = {"CODE", "ITEM NAME", "PRICE", "QUANTITY", "STOP"};
    char cts[3][MAXSTRLEN] = {"CUSTOMER", "Payment","YOUR ORDER"};

    duplicatePurchase(purc, str);
    singleTable(str, hdr, cts);
    printf("\n%*sTotal: %10.2f\n\n", PADDING_LEFT, "",  purc.total);
}