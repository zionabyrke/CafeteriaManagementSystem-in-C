// Feature: Landing Page
int CMS_LandingTerminal();

// Feature: Unique Dashboards
void CMS_AdminDashboard(Admin *admin_accounts_ptr[], Admin *signed_account, char date[]);
void CMS_CustomerDashboard(Order *, Item[], Item[], int);
void CMS_PaymentSession(Order *);
void CMS_DisplayMenu(Item[], Item[]);
void CMS_DisplayReceipt(Order, Order);
void CMS_StudentDiscount(Order *);


// Feature: Admin Account Validation
Admin* CMS_AdminSignIn(Admin *admin_accounts_ptr[]);
void CMS_AccountsSettings(Admin *admin_accounts_ptr[], Admin *signed_account);
void CMS_TableAccounts(Admin *admin_accounts_ptr[]);
void CMS_AddAccount(Admin *admin_accounts_ptr[]);
void CMS_EditAccount(Admin *admin_accounts_ptr[]);
void CMS_DeleteAccount(Admin *admin_accounts_ptr[], Admin *signed_account);

// Feature: Inventory System dito ung sa pag-add, pag-edit, pag-delete ng menu
//void CMS_InventorySystem();
//void CMS_EditMenu();
//void CMS_AddMenu();
//void CMS_DeleteMenu();
//void CMS_SortMenu();

// Feature: Transaction History
void CMS_TransactionHistory(Order *orders[]);
void CMS_TransactionDetails(Order order);
void SystemHeader(char *system_header, int width);






int CMS_LandingTerminal() {

    clearterminal();
    printf("\n\n\n\n\n%80s", "+---------------------------------------------------------------------+");
    printf("\n%10s %s%s%s %70s  %s\n", "|", "\033[38;2;255;165;0m \xE2\x97\x8F\033[0m", "\033[1;33m \xE2\x97\x8F\033[0m", "\033[1;32m \xE2\x97\x8F\033[0m", "[ \033[1;31mX\033[0m ]", "|");
    printf("%10s %69s\n%10s%46s%24s\n", "|", "|", "|","WELCOME TO OUR CAFETERIA", "|");
    printf("%10s %69s\n", "|", "|");
    printf("%10s %69s\n", "|", "|");
    printf("%10s %69s\n", "|", "|");
    printf("%10s %48s %20s\n", "|","[ 1 ] Admin      [ 2 ] Customer", "|");
    printf("%10s %69s\n", "|", "|");
    printf("%10s %69s\n", "|", "|");
    printf("%80s\n\n", "+---------------------------------------------------------------------+");

    // # User input
    char input_action[100];
    do {
        printf("%20s","Action: ");
        scanf("%s", input_action);
        marginleft(12);
        
        // Check if th user enters '1'
        if(strcmp(input_action, "1") == 0) {
            success("Entering as an Admin. Please wait...");
            loading(1);
            return 1;
        }
        else if(strcmp(input_action, "2") == 0) {
            success("Entering as a Customer. Please wait...");
            loading(1);
            return 2;
        }
        else if(strcmp(input_action, "X") == 0 || strcmp(input_action, "x") == 0) {
            printf("Exit");
            return 0;
        }
        else {
            error("Invalid input. Try again.");
            continue;
        }
    } while(true);
    
}

Admin* CMS_AdminSignIn(Admin *admin_accounts_ptr[]) {
    /**** Parameters ****/
    /* Admin *admin_accounts_ptr[] */

    /**** Return Values ****/
    /*
     1.) NULL
     2.) Memory Address  
    */

    /**** Function Algorithm ****/
    /*
     1.) Display the header of the CMS_AdminSignIn()
     2.) Ask the user to input his/her input_username: 
         - If the user enters "X" or "x", return NULL
     3.) Ask the user to input his/her input_passkey:
     4.) Search inside admin_accounts_ptr[] if an account has a username and passkey that matches the input_username and input_passkey
         - If an account is found, return its memory address
         - If an account is not found, loob back to step 2 
    */

    /**** Variables used ****/
    /*
     1.) int last_stdin;  -  used to remove '\n' character inside the stdin before the user enters input_username
                          -  used to remove '\n' character from the last index of input_username and input_passkey since fgets() works differently from scanf()
     2.) char input_username[] - used to store the user's inputted username
     3.) char input_passkey[] - used to store the user's inputted passkey
    */
    clearterminal();
    printf("\n\n\n\n\n%81s", "+---------------------------------------------------------------------+\n");
    printf("%10s %s%s%s %70s  %s\n", "|", "\033[38;2;255;165;0m \xE2\x97\x8F\033[0m", "\033[1;33m \xE2\x97\x8F\033[0m", "\033[1;32m \xE2\x97\x8F\033[0m", "[ \033[1;31mX\033[0m ]", "|");
    printf("%10s %69s\n", "|", "|");
    printf("%10s %69s\n", "|", "|");
    printf("%10s %69s\n%10s%48s%22s\n", "|", "|", "|","---- Admin Login Form -----", "|");
    printf("%10s %69s\n", "|", "|");
    printf("%10s %69s\n", "|", "|");
    printf("%10s %69s\n", "|", "|");
    printf("%81s\n\n", "+---------------------------------------------------------------------+\n");

    int last_stdin;
    char input_username[50];
    char input_passkey[50];

    // # Clean the stdin ( standard input buffer );
    last_stdin = getchar();
    last_stdin = '\0';

    do {
        // # Take the username of the user using fgets()
        marginleft(10);
        printf("Username: ");  
        fgets(input_username, sizeof(input_username), stdin);
        
        // # Swap the '\n' in the input_username[] with '\0' since if fgets() is executed, the input_username[] will include the '\n' that is entered by the user
        last_stdin = strlen(input_username);
        input_username[last_stdin - 1] = '\0';

        // # Check if the user enters 'x' or 'X', if this is true, then exit the loop
        if(strcmp(input_username, "X") == 0 || strcmp(input_username, "x") == 0) {
            return NULL;
        }

        // # Take the passkey of the user using fgets()
        marginleft(10);
        printf("Passkey: ");
        fgets(input_passkey, sizeof(input_passkey), stdin);

        // # Clean the input_passkey[]
        last_stdin = 0;
        last_stdin = strlen(input_passkey);
        input_passkey[last_stdin - 1] = '\0';
        
        // # This loop will iterate through the admin_accounts_ptr[] until it found a matching pair then immediately return it if found.
        for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
            if(strcmp(input_username, admin_accounts_ptr[i]->username) == 0 && strcmp(input_passkey, admin_accounts_ptr[i]->passkey) == 0) {
                marginleft(10);
                printf("\033[32mEntered as [ %s ]. Please wait...\033[0m\n", admin_accounts_ptr[i]->username);
                loading(2);
                // # Return the memory address of the matched account
                return admin_accounts_ptr[i];
            }
        }

        // # Handle the error when the input_username and input_passkey is not found
        marginleft(10);
        error("Account not found. Try again.");
        continue;

    
    } while(1);
}

void CMS_AdminDashboard(Admin *admin_accounts_ptr[], Admin *signed_account, char date[]) {

    int exit_function = 0;

    do {
        clearterminal();
        SystemHeader("         ==== ADMIN DASHBOARD ====", 70);
        marginleft(12); printf("%s %s!", "Welcome", signed_account->username);
        marginleft(25); printf("%25s\n\n\n\n\n", date);
        marginleft(10); printf("%30s %31s\n", "[ 1 ] Inventory System", "[ 2 ] Transaction History");
        marginleft(10); printf("%31s %26s\n\n\n", "[ 3 ] Accounts Settings", "[ \033[1;31mX\033[0m ] Exit");
        marginleft(10); printf("+"); repeatchar('-', 70); printf("+\n\n");

        char input_action[20];
        do {
            marginleft(12);
            printf("Action: ");
            scanf("%s", input_action);

            if(strcmp(input_action, "1") == 0) {
                printf("Inventory");
                break;
            }
            else if(strcmp(input_action, "2") == 0) {
                printf("Transaction History");
                break;
            }
            else if(strcmp(input_action, "3") == 0) {
                CMS_AccountsSettings(admin_accounts_ptr, signed_account);
                break;
            }
            else if(strcmp(input_action, "X") == 0 || strcmp(input_action, "x") == 0) {
                exit_function = 1;
                break;
            }
            else {
                marginleft(12);
                error("Invalid input. Try again.");
                continue;
            }

        } while(1);

    } while(exit_function == 0);
    
   

    

    
}

void CMS_TableAccounts(Admin *admin_accounts_ptr[]) {
    // # To make the table responsive, get the longest length of character of username and passkey in the admin_accounts_ptr[]
    int cellsize_username = strlen("USERNAMES");
    int cellsize_passkey = strlen("PASSKEYS");
    int cellsize_id = strlen("ID");
    int table_size = 0;

    for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {

        // # Ensure that the iterated username and passkey are not empty
        //if(admin_accounts_ptr[i]->username != '\0' && admin_accounts_ptr[i]->passkey[0] != '\0') {
            table_size += 1;
            
            // # Calculate the max length of each username and passkey and id
            int id_length = strlen(admin_accounts_ptr[i]->id);
            int username_length = strlen(admin_accounts_ptr[i]->username);
            int passkey_length = strlen(admin_accounts_ptr[i]->passkey);

            // # Update the cellsizes if necessary
            if(username_length > cellsize_username) {
                cellsize_username = username_length;
            }
            if(passkey_length > cellsize_passkey) {
                cellsize_passkey = passkey_length;
            }
            if(id_length > cellsize_id) {
                cellsize_id = id_length;
            }

        //}
    }


    // # Table Header
    // # ID columns  |  Username columns  |  Passkey columns
    marginleft(10);
    printf("  Accounts: %d/%d\n", table_size, MAX_ACCOUNT);
    marginleft(10);
    printf("  +------+"); repeatchar('-', (cellsize_username + 4)); printf("+"); repeatchar('-', (cellsize_passkey + 4)); printf("+\n");
    marginleft(10);
    printf("  |  ID  |  USERNAMES"); repeatchar(' ', (cellsize_username - strlen("USERNAMES"))); printf("  |  PASSKEYS"); repeatchar(' ', (cellsize_passkey - strlen("PASSKEYS"))); printf("  |\n");
    marginleft(10);
    printf("  +------+"); repeatchar('-', (cellsize_username + 4)); printf("+"); repeatchar('-', (cellsize_passkey + 4)); printf("+\n");   

    fflush(stdout);
    // # Table Body
    for(int j = 0; j < table_size; j++) {
        marginleft(10);
        printf("  |  %s", admin_accounts_ptr[j]->id);
        printf("  |  %s", admin_accounts_ptr[j]->username); repeatchar(' ', (cellsize_username - strlen(admin_accounts_ptr[j]->username))); printf("  |  %s", admin_accounts_ptr[j]->passkey); repeatchar(' ', (cellsize_passkey - strlen(admin_accounts_ptr[j]->passkey))); printf("  |\n");
       // marginleft(10);
        //printf("\n");
       // printf("  +------+"); repeatchar('-', (cellsize_username + 4)); printf("+"); repeatchar('-', (cellsize_passkey + 4)); printf("+\n");
    }
    marginleft(10);
    printf("  +------+"); repeatchar('-', (cellsize_username + 4)); printf("+"); repeatchar('-', (cellsize_passkey + 4)); printf("+\n");

}

void CMS_AccountsSettings(Admin *admin_accounts_ptr[], Admin *signed_account) {



    int exit_function = 0;

    do {
        // # Calculate the table width of admin_accounts_ptr[]
        int table_width = 0;
        int username_width = strlen("USERNAMES");
        int passkey_width = strlen("PASSKEYS");
        int id_width = strlen("ID");

        for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
            if(strlen(admin_accounts_ptr[i]->username) > username_width) {
                username_width = strlen(admin_accounts_ptr[i]->username);
            }
            if(strlen(admin_accounts_ptr[i]->passkey) > passkey_width) {
                passkey_width = strlen(admin_accounts_ptr[i]->passkey);
            }
            if(strlen(admin_accounts_ptr[i]->id) > id_width) {
                id_width = strlen(admin_accounts_ptr[i]->id);
            }
        }
        table_width = ((username_width + 4) + (passkey_width + 4) + (id_width + 4)) + 36;


        clearterminal();
        SystemHeader("==== ADMIN DASHBOARD ( Account Settings ) ====", table_width);
        CMS_TableAccounts(admin_accounts_ptr); printf("\n");
        marginleft(12); printf("[ 1 ] Create Account      [ 2 ] Edit Account      [ 3 ] Delete Account\n\n");
        marginleft(10); printf("+"); repeatchar('-', table_width); printf("+\n\n");

        char input_action[20];

        do {
            marginleft(12);
            printf("Action: ");
            scanf("%s", input_action);

            if(strcmp(input_action, "1") == 0) {
                CMS_AddAccount(admin_accounts_ptr);
                break;
            }
            else if(strcmp(input_action, "2") == 0) {
                CMS_EditAccount(admin_accounts_ptr);
                break;
            }
            else if(strcmp(input_action, "3") == 0) {
                CMS_DeleteAccount(admin_accounts_ptr, signed_account);
                break;
            }
            else if(strcmp(input_action, "X") == 0 || strcmp(input_action, "x") == 0) {
                exit_function = 1;
                return;
            }
            else {
                marginleft(12);
                error("Invalid input. Try again.");
            }
        } while(1);

    } while(exit_function == 0);
    

    

    

   

}

void CMS_AddAccount(Admin *admin_accounts_ptr[]) {

    // # Calculate the table width of admin_accounts_ptr[]
    int table_width = 0;
    int number_account = 0;

    int username_width = strlen("USERNAMES");
    int passkey_width = strlen("PASSKEYS");
    int id_width = strlen("ID");

    for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
        if(strlen(admin_accounts_ptr[i]->username) > username_width) {
            username_width = strlen(admin_accounts_ptr[i]->username);
        }
        if(strlen(admin_accounts_ptr[i]->passkey) > passkey_width) {
            passkey_width = strlen(admin_accounts_ptr[i]->passkey);
        }
        if(strlen(admin_accounts_ptr[i]->id) > id_width) {
            id_width = strlen(admin_accounts_ptr[i]->id);
        }

        number_account += 1;
    }

    // # Calculate the total width
    table_width = ((username_width + 4) + (passkey_width + 4) + (id_width + 4)) + 36;

    char last_char_input = getchar();

    clearterminal();
    SystemHeader("==== ADMIN DASHBOARD ( Create Account ) ====", table_width);
    CMS_TableAccounts(admin_accounts_ptr);

    // # If the account array is full, the admin cant add a new account
    if(number_account >= MAX_ACCOUNT) {
        marginleft(12);
        error("Admin account is already full.");

        // # Ask the admin to exit
        char input_action[20];
        do {
            marginleft(12);
            printf("Exit ( y ): ");
            scanf("%s", input_action);

            if(strcmp(input_action, "Y") == 0 || strcmp(input_action, "y") == 0 || strcmp(input_action, "X") == 0 || strcmp(input_action, "x") == 0) {
                return;
            }
            else {
                marginleft(12);
                error("Invalid input. Try again.");
                continue;
            }
        } while(1);
    }

    // # If the account array is not full
    else {

        Admin *new_account = (Admin *)malloc(sizeof(Admin));

        char input_id[20];
        char input_passkey[20];
        char input_username[20];

        int last_char_input;

        // # Take the input ID
        printf("\n");
        do{
            marginleft(12);
            printf("Account ID: ");
            fgets(input_id, sizeof(input_id), stdin);
            
            last_char_input = strlen(input_id);
            input_id[last_char_input - 1] = '\0';

            // # Check if the input id length.
            if(strlen(input_id) >= 3) {
                marginleft(12);
                error("An Account ID must be a maximum of two ( 2 ) characters. Try again.");
                continue;
            }

            // # Check if input id is unique
            else if(uniqueID(admin_accounts_ptr, input_id) == 0) {
                marginleft(12);
                printf("\033[0;31mAn Account ID of [ %s ] already exists. Please input a unique ID.\033[0m\n\n", input_id);
                continue;
                
            }
            else if(strcmp(input_id, "X") == 0 || strcmp(input_id, "x") == 0) {
                return;
            }

            // # If the two condition above is false, then the input id is valid
            else {
                input_id[2] = '\0';
                strcpy(new_account->id, input_id);
                break;
            }

        } while(1);

        

        // # Take the input username
        do{
            marginleft(12);
            printf("Account Username: ");
            fgets(input_username, sizeof(input_username), stdin);

            last_char_input = strlen(input_username);
            input_username[last_char_input - 1] = '\0';
            
            if(strlen(input_username) == 0 || input_username[0] == '\n') {
                marginleft(12);
                error("Please fill the Account Username.");
                continue;
            }
            else if(strlen(input_username) >= 20) {
                marginleft(12);
                error("Account Username must be a maximum of twenty ( 20 ) characters. Try again.");
                continue;
            }
            else if(uniqueUsername(admin_accounts_ptr, input_username) == 0) {
                marginleft(12);
                printf("\033[0;31mAn Account Username of [ %s ] already exists. Please input a unique username.\033[0m\n\n", input_username);
                continue;
            }
            else {
                strcpy(new_account->username, input_username);
                break;
            }

        } while(1);

        // # Take the input passkey
        do {
            marginleft(12);
            printf("Account Passkey: ");
            fgets(input_passkey, sizeof(input_passkey), stdin);

            last_char_input = strlen(input_passkey);
            input_passkey[last_char_input - 1] = '\0';

            if(strlen(input_passkey) == 0 || input_passkey[0] == '\n') {
                marginleft(12);
                error("Please fill the Account Passkey.");
                continue;
            }
            else if(strlen(input_passkey) >= 30) {
                marginleft(12);
                error("Account Passkey must be a maximum of thirty ( 30 ) characters. Try again.");
                continue;
            }
            else {
                strcpy(new_account->passkey, input_passkey);
                break;
            }
        } while(1);

        printf("\n");
        marginleft(12);
        printf("\033[32mCreate: [ %s - %s - %s ] \033[0m\n", new_account->id, new_account->username, new_account->passkey);

        // # Ask for confirmation
        char input_confirmation[20];
        do {
            marginleft(12);
            printf("Confirm ( y / n ): ");

            scanf("%s", input_confirmation);

            if(strcmp(input_confirmation, "Y") == 0 || strcmp(input_confirmation, "y") == 0) {
                
                // # Insert at the last index of admin_accounts_ptr[] the new account
                int last_index = 0;
                for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
                    last_index += 1;
                }

                admin_accounts_ptr[last_index] = new_account;
                admin_accounts_ptr[last_index + 1] = NULL;

                printf("\n");
                fflush(stdout);
                marginleft(12);
                success("Saving the inputs. Please wait...");
                fflush(stdout);
                loading(1);
                return; 
            }
            else if(strcmp(input_confirmation, "N") == 0 || strcmp(input_confirmation, "n") == 0) {

                printf("\n");
                fflush(stdout);
                marginleft(12);
                printf("\033[0;33mDiscarding the inputs. Please wait...\033[0m");
                fflush(stdout);
                loading(1);
                return;
            }
            else {
                marginleft(12);
                error("Invalid input. Try again.");
                continue;
            }
        } while(1);
        
    }
}

void CMS_DeleteAccount(Admin *admin_accounts_ptr[], Admin *signed_account) {

    // # Calculate the table width of admin_accounts_ptr[]
    int table_width = 0;
    int number_account = 0;

    int username_width = strlen("USERNAMES");
    int passkey_width = strlen("PASSKEYS");
    int id_width = strlen("ID");

    for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
        if(strlen(admin_accounts_ptr[i]->username) > username_width) {
            username_width = strlen(admin_accounts_ptr[i]->username);
        }
        if(strlen(admin_accounts_ptr[i]->passkey) > passkey_width) {
            passkey_width = strlen(admin_accounts_ptr[i]->passkey);
        }
        if(strlen(admin_accounts_ptr[i]->id) > id_width) {
            id_width = strlen(admin_accounts_ptr[i]->id);
        }

        number_account += 1;
    }

    // # Calculate the total width
    table_width = ((username_width + 4) + (passkey_width + 4) + (id_width + 4)) + 36;
    char last_char_input = getchar();

    clearterminal();
    SystemHeader("==== ADMIN DASHBOARD ( Delete Account ) ====", table_width);
    CMS_TableAccounts(admin_accounts_ptr);

    marginleft(12);
    printf("\033[0;33mWarning: You cannot delete the currently signed account [ %s - %s - %s ].\033[0m\n\n", signed_account->id, signed_account->username, signed_account->passkey);

    Admin *found_account = NULL;
    char input_id[20];
    do {
        marginleft(12);
        printf("Account ID: ");
        scanf("%s", input_id);

        if(strcmp(input_id, signed_account->id) == 0) {
            marginleft(12);
            error("You cannot delete the currently signed account. Try again.");
            continue;
        }
        else {
            // # Search for the account using the input_id
            for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
                if(strcmp(input_id, admin_accounts_ptr[i]->id) == 0) {
                    found_account = admin_accounts_ptr[i];
                    break;
                }
            }

            if(found_account == NULL) {
                marginleft(12);
                printf("\033[0;31mAccount ID of [ %s ] not found. Try again.\033[0m\n\n", input_id);
                continue;
            }
            else {
                break;
            }
        }
    } while(1);

    printf("\n");    marginleft(12);
    printf("\033[0;32mDelete: [ %s - %s - %s ]\033[0m\n", found_account->id, found_account->username, found_account->passkey);

    char input_confirmation[20];
        do {
            marginleft(12);
            printf("Confirm ( y / n ): ");

            scanf("%s", input_confirmation);

            if(strcmp(input_confirmation, "Y") == 0 || strcmp(input_confirmation, "y") == 0) {
                
                // # Insert at the last index of admin_accounts_ptr[] the new account
                int last_index = 0;
                int found_account_index = 0;
                for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
                    last_index += 1;

                    if(strcmp(admin_accounts_ptr[i]->id, input_id) == 0) {
                        found_account_index = i;
                    }
                }

                admin_accounts_ptr[found_account_index] = admin_accounts_ptr[last_index - 1];
                admin_accounts_ptr[last_index - 1] = NULL;

                printf("\n");
                marginleft(12);
                success("Deleting the account. Please wait...");
                fflush(stdout);
                loading(1);
                return; 
            }
            else if(strcmp(input_confirmation, "N") == 0 || strcmp(input_confirmation, "n") == 0) {
                printf("\n");
                fflush(stdout);
                marginleft(12);
                printf("\033[0;33mDiscarding the inputs. Please wait...\033[0m");
                fflush(stdout);
                loading(1);
                return;
            }
            else {
                marginleft(12);
                error("Invalid input. Try again.");
                continue;
            }
        } while(1);

    
}

void CMS_EditAccount(Admin *admin_accounts_ptr[]) {
    // # Calculate the table width of admin_accounts_ptr[]
    int table_width = 0;
    int number_account = 0;

    int username_width = strlen("USERNAMES");
    int passkey_width = strlen("PASSKEYS");
    int id_width = strlen("ID");

    for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
        if(strlen(admin_accounts_ptr[i]->username) > username_width) {
            username_width = strlen(admin_accounts_ptr[i]->username);
        }
        if(strlen(admin_accounts_ptr[i]->passkey) > passkey_width) {
            passkey_width = strlen(admin_accounts_ptr[i]->passkey);
        }
        if(strlen(admin_accounts_ptr[i]->id) > id_width) {
            id_width = strlen(admin_accounts_ptr[i]->id);
        }

        number_account += 1;
    }

    // # Calculate the total width
    table_width = ((username_width + 4) + (passkey_width + 4) + (id_width + 4)) + 36;

    clearterminal();
    SystemHeader("==== ADMIN DASHBOARD ( Edit Account ) ====", table_width);
    CMS_TableAccounts(admin_accounts_ptr);

    if(number_account == 0) {
        marginleft(12);
        error("The account are empty.");

        char input_action[20];

        do {
            marginleft(12);
            printf("Exit ( y / n ): ");
            scanf("%s", input_action);

            if(strcmp(input_action, "Y") == 0 || strcmp(input_action, "y") == 0 || strcmp(input_action, "X") == 0 || strcmp(input_action, "x") == 0) {
                return;
            }
            else {
                marginleft(12);
                error("Invalid input. Try again.");
                continue;
            }
        } while(1);
    }

    else {
        char last_char_input = getchar();
        last_char_input = '\0';

        char input_id[20];
        char input_passkey[50];
        char input_username[50];

        int last_index_input = 0;
        Admin *found_account = NULL;

        printf("\n");
        do {
            marginleft(12);
            printf("Account ID: ");
            fgets(input_id, sizeof(input_id), stdin);

            last_index_input = strlen(input_id);
            input_id[last_index_input - 1] = '\0';

    
            if(strcmp(input_id, "X") == 0 || strcmp(input_id, "x") == 0) {
                return;
            }

            for(int i = 0; admin_accounts_ptr[i] != NULL; i++) {
                if(strcmp(admin_accounts_ptr[i]->id, input_id) == 0) {
                    found_account = admin_accounts_ptr[i];
                    break;
                }
            }

            if(found_account == NULL) {
                marginleft(12);
                printf("\033[31mAccount ID of [ %s ] is not found. Try again.\033[0m\n\n", input_id);
                continue;
            }
            else {
                break;
            }

        } while(1);

        printf("\n");
        marginleft(12);
        printf("\033[0;33mEnter 'n' to skip.\033[0m\n");
        marginleft(12);
        printf("\033[0;32mEditing: [ %s - %s - %s ]\033[0m\n\n", found_account->id, found_account->username, found_account->passkey);

        // # ID
        do {
            marginleft(12);
            printf("New Account ID: ");
            fgets(input_id, sizeof(input_id), stdin);

            last_index_input = strlen(input_id);
            input_id[last_index_input - 1] = '\0';

            if(strcmp(input_id, "X") == 0 || strcmp(input_id, "x") == 0) {
                marginleft(12);
                error("The letter/s 'x' and 'X' are used by the system to redirect the user. Try again.");
                continue;
            }
            if(strcmp(input_id, "N") == 0 || strcmp(input_id, "n") == 0) {
                strcpy(input_id, found_account->id);
                break;
            }
            if(strlen(input_id) >= 3) {
                marginleft(12);
                error("Account ID must be a maximum of two ( 2 ) characters. Try again.");
                continue;
            }
            else if(uniqueID(admin_accounts_ptr, input_id) == 0) {
                marginleft(12);
                printf("\033[0;31mAn Account ID of [ %s ] already exists. Please input an unique ID.\033[0m\n\n", input_id);
                continue;
            }
            else {
                break;
            }
        } while(1);

        // # Username
        do {
            marginleft(12);
            printf("New Account Username: ");
            fgets(input_username, sizeof(input_username), stdin);

            last_index_input = strlen(input_username);
            input_username[last_index_input - 1] = '\0';

            if(strcmp(input_username, "X") == 0 || strcmp(input_username, "x") == 0) {
                marginleft(12);
                error("The letter/s 'x' and 'X' are used by the system to redirect the user. Try again.");
                continue;
            }
            if(strcmp(input_username, "N") == 0 || strcmp(input_username, "n") == 0) {
                strcpy(input_username, found_account->username);
                break;
            }
            if(strlen(input_username) >= 20) {
                marginleft(12);
                error("Account Username must be a maximum of twenty ( 20 ) characters. Try again.");
                continue;
            }
            else if(strlen(input_username) == 0 || input_username[0] == '\n') {
                marginleft(12);
                error("Please fill the Account Username.");
                continue;
            }
            else if(uniqueUsername(admin_accounts_ptr, input_username) == 0) {
                marginleft(12);
                printf(RED "An Account Username of [ %s ] already exists. Please input an unique username.\n\n" RESET, input_username);
                continue;
            }
            else {
                break;
            }
        } while(1);

        // # Passkey
        do {
            marginleft(12);
            printf("New Account Passkey: ");
            fgets(input_passkey, sizeof(input_passkey), stdin);

            last_index_input = strlen(input_passkey);
            input_passkey[last_index_input - 1] = '\0';

            if(strcmp(input_passkey, "N") == 0 || strcmp(input_passkey, "n") == 0) {
                strcpy(input_passkey, found_account->passkey);
                break;
            }
            if(strlen(input_passkey) >= 30) {
                marginleft(12);
                error("Account Passkey must be a maximum of twenty ( 30 ) characters. Try again.");
                continue;
            }
            else if(strlen(input_passkey) == 0 || input_passkey[0] == '\n') {
                marginleft(12);
                error("Please fill the Account Passkey.");
                continue;
            }
            else {
                break;
            }
        } while(1);

        printf("\n");
        marginleft(12);
        printf(GREEN "Update: [ %s - %s - %s ]\n" RESET, input_id, input_username, input_passkey);

        // # Confirmation
        char input_confirmation[20];

        do {
            marginleft(12);
            printf("Confirm ( y / n ): ");
            scanf("%s", input_confirmation);

            if(strcmp(input_confirmation, "Y") == 0 || strcmp(input_confirmation, "y") == 0) {
                printf("\n"); fflush(stdout);
                marginleft(12);
                success("Updating the account. Please wait...");
                loading(1);

                strcpy(found_account->id, input_id);
                strcpy(found_account->username, input_username);
                strcpy(found_account->passkey, input_passkey);
                return;
            }
            else if(strcmp(input_confirmation, "NY") == 0 || strcmp(input_confirmation, "n") == 0) {
                printf("\n"); fflush(stdout);
                marginleft(12);
                success("Discarding the inputs. Please wait...");
                loading(1);
                return;
            }
            else {
                marginleft(12);
                error("Invalid input. Try again.");
                continue;
            }
        } while(1);
    }
}

void SystemHeader(char *system_header, int width) {
    // # Generate the border
    printf("\n");
    marginleft(10);
    printf("+");
    repeatchar('-', width);
    printf("+\n");

    // # Generate the Header
    marginleft(10);
    printf(" %s%s%s", "\033[38;2;255;165;0m \xE2\x97\x8F\033[0m", "\033[1;33m \xE2\x97\x8F\033[0m", "\033[1;32m \xE2\x97\x8F\033[0m");

    marginleft(width - 12);
    printf("%s\n", "[ \033[1;31mX\033[0m ]");
    
    marginleft(24);
    printf("%s\n\n\n", system_header);


}

/* CUSTOMER */
void CMS_CustomerDashboard(Order *pendingOrder, Item dish[], Item drinks[], int orderCount){
    int i, index, flag = 0, buf = 0;
    int t1 = itemlen(dish), t2 = itemlen(drinks);
    char key[MAXSTRLEN], done[1];

    index = flag = pendingOrder->total = pendingOrder->items_ordered = 0;

    clearterminal();
    CMS_DisplayMenu(dish, drinks);
    
    do{
        printf("\n%*sOrder: ", PADDING_LEFT, "");
        scanf(" %s", key);
        for(i = 0; i < strlen(key); i++)
            key[i] = toupper(key[i]);

        for(index = 0, flag = 0; (index < t1) || (index < t2); index++){
            if(strcmp(key, dish[index].code) == 0){
                flag = 1;
                break;
            }
            else if(strcmp(key, drinks[index].code) == 0){
                flag = 2;
                break;
            }
        }
        if((index < t1) || (index < t2)){
            if(flag == 1){
                if(strcmp(dish[index].status, "Sold out") == 0){
                    printf("%*s%sItem sold out. Pick another.%s", PADDING_LEFT, "", RED, RESET);
                    continue;
                } // <0 or >0 strcmp is dangerous
                else{
                    orderQuantity(pendingOrder, &dish[index]);
                }
            }
            else if(flag == 2)
                if(strcmp(drinks[index].status, "Sold out") == 0){
                    printf("%*s%sItem sold out. Pick another.%s", PADDING_LEFT, "", RED, RESET);
                    continue;
                }
                else{
                    orderQuantity(pendingOrder, &drinks[index]);
                }
        }

        else{
            printf("%*s%sCode not found. Try again.%s", PADDING_LEFT, "", RED, RESET); 
            continue;
        }
        printf("%*sDone (y/n): ", PADDING_LEFT, "");
        scanf(" %s", done);
        done[0] = tolower(done[0]);

    }while(done[0] != 'y');

    // DISPLAY ORDER
    printf("\n%*s%sRequest is being processed. Please wait...%s", PADDING_LEFT, "", GREEN, RESET);
    loading(1);
    clearterminal();
    displayOrder(*pendingOrder);
    CMS_StudentDiscount(pendingOrder);

    // PROCEED PAYMENT
    CMS_PaymentSession(pendingOrder);

    /* GENERATE REF NO. & TIME */
    pendingOrder->reference_number = orderCount + 1;

    time_t now = time(&now);
    struct tm*local_time = localtime(&now);
    strftime(pendingOrder->date, sizeof(pendingOrder->date), "%m-%d-%Y", local_time);

}
void CMS_PaymentSession(Order *order){
    int i, buf;
    char tmp[10];
    do{
        printf("\n%*sPayment: ", PADDING_LEFT, "");
        scanf(" %s", tmp);
        for(i = 0; i < strlen(tmp); i++){
            if((tmp[i] < '0') || (tmp[i] > '9')){
                buf = -1;
                break;
            }
            else buf = 1;
        }
        if(buf == 1){
            order->payment = atof(tmp);
            if(order->payment >= order->discounted_total){
                order->change = order->payment - order->discounted_total;
                printf("%*s%sPayment successful.\n%s", PADDING_LEFT, "", GREEN, RESET);
                printf("\n%*sChange: %.2f\n\n", PADDING_LEFT, "", order->change);
                break;
            }
            else buf = 0;
        }
        if(buf < 1){
            marginleft(10);
            printf("%*s%sInsufficient or invalid amount. Try again.%s", PADDING_LEFT, "", RED, RESET);
        }            
    }while(1);
}
void CMS_StudentDiscount(Order *order){
    int i, noOfIDs, flag = 0;
    char key[16], temp[16];
    
    do{
        printf("%*sStudent ID ( Enter 'n' to skip ): ", PADDING_LEFT, "");
        scanf (" %s", key);
        marginleft(10);
    
        if(tolower(key[0]) == 'n'){
            strcpy(order->student_number, "N/A");
            return;
        }
        else{
            FILE*validIDs=fopen("Student-IDs.txt", "rt");
            fscanf(validIDs,"%d",&noOfIDs);
            for(i = 0; i< noOfIDs; i++){
                fscanf(validIDs,"%s",temp);
                if(strcmp(temp, key)==0){
                    strcpy(order->student_number, key);
                    flag = 1;
                    break;
                }
                else flag = 0;
            }
            fclose(validIDs);
            if(i <= noOfIDs && flag != 0){
                order->discounted_total = order->total - (order->total * DISCOUNT);
                printf("Discounted Total: %.2f\n", order->discounted_total);
                return;
            }    
            else{
                printf("%sStudent ID not found. Try again.%s\n\n", RED, RESET);
            }
        }
                
    }while(1);
    loading(3);
}

/* TABLES */
void CMS_DisplayMenu(Item tb1[], Item tb2[]){  // YOU CAN ADD OR DELETE COLUMN HEADERS
    char hdrs1[10][MAXSTRLEN] = {"CODE", "ITEM NAME", "PRICE", "STATUS", "STOP"};
    char hdrs2[10][MAXSTRLEN] = {"CODE", "ITEM NAME", "PRICE", "STATUS", "STOP"};
    char cts[][MAXSTRLEN] = {"CUSTOMER", "Request Order","MEALS", "DRINKS"};

    char s1[itemlen(tb1) + 1][10][MAXSTRLEN]; // Item ARRAY LENGTH by NO. OF Item MEMBERS by MAXSTRLEN
    char s2[itemlen(tb2) + 1][10][MAXSTRLEN];

    duplicateItems(tb1, s1); // DUPLICATE FIRST BEFORE USING DUAL TABLE
    duplicateItems(tb2, s2);
    dualTable(s1, s2, hdrs1, hdrs2, cts);
}
void CMS_DisplayReceipt(Order current, Order successful_orders){
    FILE *receipt_ptr = fopen("receipt.txt", "wt");
    int longeststr[4], align[4], borderlen, rows, cols;
    char str[current.items_ordered + 1][10][MAXSTRLEN];
    char hdrs[4][MAXSTRLEN] = {"Name", "Qty", "Price", "STOP"};
    char border[MAXBORDER];

    duplicateOrdersReceipt(current, str);
    getLongestStr(str, hdrs, longeststr);
    generateBorderStr(border, longeststr, ':', ':');
    clearterminal();

    borderlen = strlen(border);
    rows = strlen_3D(str);
    cols = strlen_2D(hdrs);
    align[0] = (borderlen - strlen(CAFETERIA_NAME))/2;
    align[1] = (borderlen - strlen(ADDRESS))/2;
    align[2] = (borderlen - strlen(ZIP_CODE) - 10)/2;
    align[3] = (borderlen - strlen(CONTACT_NO) - 6)/2;

    fprintf(receipt_ptr, "%*s%s\n", align[0], "", CAFETERIA_NAME);
    fprintf(receipt_ptr, "%*s%s\n", align[1], "", ADDRESS);
    fprintf(receipt_ptr, "%*sZip Code: %s\n", align[2], "", ZIP_CODE);
    fprintf(receipt_ptr, "%*sTel.: %s\n", align[3], "", CONTACT_NO);

    printf("%*s%*s%s\n", PADDING_LEFT, "", align[0], "", CAFETERIA_NAME);
    loading(1); printf("%*s%*s%s\n", PADDING_LEFT, "", align[1], "", ADDRESS);
    loading(1); printf("%*s%*sZip Code: %s\n", PADDING_LEFT, "", align[2], "", ZIP_CODE);
    printf("%*s%*sTel.: %s\n", PADDING_LEFT, "", align[3], "", CONTACT_NO);

    fprintf(receipt_ptr, "%s\n\n", border);
    printf("%*s%s\n\n", PADDING_LEFT, "", border);
    
    fprintf(receipt_ptr, "Date:%*s\n", borderlen - 5, current.date);
    fprintf(receipt_ptr, "Reference no.:%*s%09d\n", borderlen - 23, "", current.reference_number);
    fprintf(receipt_ptr, "Student ID:%*s\n\n", borderlen - 11, current.student_number);
    fprintf(receipt_ptr, "%s\n\n", border);

    loading(1); printf("%*sDate:%*s\n", PADDING_LEFT, "", borderlen - 5, current.date);
    loading(1); printf("%*sReference no.:%*s%09d\n", PADDING_LEFT, "", borderlen - 23, "", current.reference_number);
    loading(1); printf("%*sStudent ID:%*s\n\n", PADDING_LEFT, "", borderlen - 11, current.student_number);
    printf("%*s%s\n\n%*s", PADDING_LEFT, "", border, PADDING_LEFT, "");

    for(int i = 0; i < cols; i++){
        fprintf(receipt_ptr, "%-*s%*s", longeststr[i], hdrs[i], 5, "");
        printf("%-*s%*s", longeststr[i], hdrs[i], 5, "");
    }

    for(int i = 0; i <= rows; i++){
        fprintf(receipt_ptr, "\n%-*s%*s", longeststr[0], str[i][0], 4, "");
        fprintf(receipt_ptr, "  %-*s  ", longeststr[1], str[i][1]);
        fprintf(receipt_ptr, "  %*s", longeststr[2], str[i][2]);

        printf("\n%*s%-*s%*s", PADDING_LEFT, "", longeststr[0], str[i][0], 4, "");
        printf("  %-*s  ", longeststr[1], str[i][1]);
        printf("  %*s", longeststr[2], str[i][2]);
    }
    fprintf(receipt_ptr, "\n\n%s\n\n", border);
    fprintf(receipt_ptr, "Total%*.2f\n", borderlen - 5, current.total);

    printf("\n\n%*s%s\n\n", PADDING_LEFT, "", border);
    loading(1); printf("%*sTotal%*.2f\n", PADDING_LEFT, "", borderlen - 5, current.total);

    if(strcmp(current.student_number, "N/A") == 0){
        fprintf(receipt_ptr, "Student Discount%*s\n", borderlen - 16, current.student_number);
        fprintf(receipt_ptr, "Discounted Total%*s\n", borderlen - 16, current.student_number);

        loading(1); printf( "%*sStudent Discount%*s\n", PADDING_LEFT, "", borderlen - 16, current.student_number);
        loading(1); printf( "%*sDiscounted Total%*s\n", PADDING_LEFT, "", borderlen - 16, current.student_number);
    }
    else{
        fprintf(receipt_ptr, "Student Discount%*.0f%%\n", borderlen - 17, DISCOUNT * 100);
        fprintf(receipt_ptr, "Discounted Total%*.2f\n", borderlen - 16, current.discounted_total);

        loading(1); printf("%*sStudent Discount%*.0f%%\n", PADDING_LEFT, "", borderlen - 17, DISCOUNT * 100);
        loading(1); printf("%*sDiscounted Total%*.2f\n", PADDING_LEFT, "", borderlen - 16, current.discounted_total);
    }

    fprintf(receipt_ptr, "Cash%*.2f\n", borderlen - 4, current.payment);
    fprintf(receipt_ptr, "Change%*.2f\n\n", borderlen - 6, current.change);

    loading(1); printf("%*sCash%*.2f\n", PADDING_LEFT, "", borderlen - 4, current.payment);
    loading(1); printf("%*sChange%*.2f\n\n", PADDING_LEFT, "", borderlen - 6, current.change);

    fprintf(receipt_ptr, "%*s%s\n", (borderlen - 24)/2, "", "------------------------");
    fprintf(receipt_ptr, "%*s%s\n", (borderlen - 10)/2, "", "THANK YOU!");
    fprintf(receipt_ptr, "%*s%s\n", (borderlen - 22)/2, "", "Glad to see you again!");

    printf("%*s%*s%s\n", PADDING_LEFT, "", (borderlen - 24)/2, "", "------------------------");
    printf("%*s%*s%s\n", PADDING_LEFT, "", (borderlen - 10)/2, "", "THANK YOU!");
    printf("%*s%*s%s\n", PADDING_LEFT, "", (borderlen - 22)/2, "", "Glad to see you again!");

    successful_orders = current;
    loading(3);
    fclose(receipt_ptr);
}