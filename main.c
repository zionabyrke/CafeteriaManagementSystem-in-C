#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_MENU_MEALS 15
#define MAX_MENU_DRINKS 10
#define MAX_ACCOUNT 5

/* appended by Renz */
#define MAXSTRLEN 50
#define MAXBORDER 80
#define MAXORDER 20
#define MAX_MENU 20
#define DISCOUNT 0.20 // 20% OFF

#define TERMINAL_SIZE 130 // if table fits
#define PADDING_LEFT 10

/* ABOUT THE CAFETERIA */
#define CAFETERIA_NAME  "CAFETERIA NAME"
#define ADDRESS         "Legazpi City, Albay"
#define ZIP_CODE        "4500"
#define CONTACT_NO      "+456-468-987-02"

#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define ORANGE "\033[38;2;255;165;0m"

#define RESET   "\033[0m"

// # Custom Header Files
#include "System-Structure.h"
#include "System-Utility.h"
#include "System-Feature.h"
#include "System-Default.h"

int main() {

    Admin admin_accounts[MAX_ACCOUNT + 1] = { jed, raymond, renz, jayson };
    Admin *admin_accounts_ptr[MAX_ACCOUNT + 1] = { &admin_accounts[0], &admin_accounts[1], &admin_accounts[2], &admin_accounts[3], NULL };
    Admin *signed_account = NULL;

    Item dish[MAX_MENU] = {meal_A, meal_B, meal_C, meal_E, meal_F, meal_G, meal_H, meal_I, meal_J, "STOP"};
    Item drinks[MAX_MENU] = {drink_K, drink_L, drink_M, drink_N, drink_O, "STOP"};
 
    char date[20];
    generatedate(date);

    int user_role, order_count = 0;

    Order current_order;
    Order successful_orders[MAXORDER];
    
    do {
        user_role = CMS_LandingTerminal();

        switch(user_role) {
            case 1: signed_account = CMS_AdminSignIn(admin_accounts_ptr);
                    if(signed_account == NULL) {
                        continue;
                    }
                    else {
                        CMS_AdminDashboard(admin_accounts_ptr, signed_account, date);
                        break;
                    }
            case 2: CMS_CustomerDashboard(&current_order, dish, drinks, order_count);
                    CMS_DisplayReceipt(current_order, successful_orders[order_count]);
                    order_count++;
                    break;

            case 0: exit(1);
             
        }

    } while(1);
    
    return 0;
}