#include <stdio.h>
#include <stdlib.h>

/*Ingredient Requirements for Coffee*/
#define ESPRESSO_BEANS 8         /* Defining the beans requirement for espresso coffee*/
#define ESPRESSO_WATER 30       /* Defining the water requirement for espresso coffee*/

#define CAPPUCCINO_BEANS 8        /* Defining the beans requirement for cappuccino coffee*/
#define CAPPUCCINO_WATER 30      /* Defining the water requirement for cappuccino coffee*/
#define CAPPUCCINO_MILK 70       /* Defining the milk requirement for cappuccino coffee*/

#define MOCHA_BEANS 8           /* Defining the beans requirement for mocha coffee*/
#define MOCHA_WATER 30          /* Defining the water requirement for mocha coffee*/
#define MOCHA_MILK 160          /* Defining the milk requirement for mocha coffee*/
#define MOCHA_CHOCO_SYRUP 30    /* Defining the chocolate syrup requirement for mocha coffee*/

#define COFFEE_BEANS 200        /* Defining the total coffee bean stock in the machine*/
#define WATER 5000              /*Defining the total water level in the machine*/
#define CHOCO_SYRUP 500         /*Defining the total chocolate syrup level in the machine*/
#define MILK 4000               /*Defining the total milk quantity in the machine*/

#define THRESHOLD_BEANS 24      /*Define the threshold value of the beans in the machine*/
#define THRESHOLD_WATER 100     /*Define the threshold value of the water in the machine*/
#define THRESHOLD_MILK 70       /*Define the threshold value of the milk in the machine*/
#define THRESHOLD_CHOCO_SYRUP 30 /*Define the threshold value of the chocolate syrup in the machine*/

/* Thresholds to alert for low levels */
double espresso_price = 3.5;    
double cappuccino_price = 4.5;  
double mocha_price = 5.5;       


/* Ingredient stocks, assigned to mutable data types */
int coffee_beans = COFFEE_BEANS;  
int water = WATER;
int choco_syrup = CHOCO_SYRUP;
int milk = MILK;
double total_sales = 0.0;

#define PASSWORD 12345          /*defining the password for adminisitrator access*/

/* Function Prototypes */
void payment(double price, const char* coffee_name); 
void checkThresholds(); 
void orderCoffee();
void orderEspresso();
void orderCappuccino();
void orderMocha();
void adminPanel();
void replenishIngredients();
void displayTotalSales();
void changePrice();

/* Main Function */
int main() {
    int ace = 1;  

    while (ace == 1) {
        int choice;
        printf("The Coffee Machine \n");
        printf("Main Menu \n 1. Order Coffee \n 2. Access Admin Password \n 3. Exit \n");
        scanf("%d", &choice);  

        switch (choice) {
            case 1:
                orderCoffee(); /* Goes to coffee order menu */
                break;
            case 2:
                adminPanel();  /* Go to admin panel */
                break;
            case 3:
                ace = 0;       /* Exiting the main loop */
                printf("HAVE A NICE DAY!\n");
                break;
        }
    }

    return 0;  
}

/* Function Definitions */

/* Function to handle coffee ordering */
void orderCoffee() {
    int coffee_choice;
    
    printf("Which coffee would you like to order?\n");
    printf(" 0. Exit\n");
    
    // Espresso availability check
    if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
        printf(" 1. Espresso      %5.1f\n", espresso_price);
    } else {
        printf(" 1. Espresso      Unavailable due to temporary insufficient ingredients\n");
    }

    // Cappuccino availability check
    if (coffee_beans >= CAPPUCCINO_BEANS && water >= CAPPUCCINO_WATER && milk >= CAPPUCCINO_MILK) {
        printf(" 2. Cappuccino    %5.1f\n", cappuccino_price);
    } else {
        printf(" 2. Cappuccino     Unavailable due to temporary insufficient ingredients\n");
    }

    // Mocha availability check
    if (coffee_beans >= MOCHA_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && choco_syrup >= MOCHA_CHOCO_SYRUP) {
        printf(" 3. Mocha         %5.1f\n", mocha_price);
    } else {
        printf(" 3. Mocha          Unavailable due to temporary insufficient ingredients\n");
    }
    
    scanf("%d", &coffee_choice);

    switch (coffee_choice) {
        case 1:
            orderEspresso();
            break;
        case 2:
            orderCappuccino();
            break;
        case 3:
            orderMocha();
            break;
        case 0:
            return; /*Goes back to main menu*/
        default:
            printf("Unavailable due to temporarily insufficient ingredients\n");
            break;
    }
}
/* Order functions for each coffee type, it checks if ingredients are sufficient */
void orderEspresso() {
    if (coffee_beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
        printf("Espresso: %.2f \n", espresso_price);
        printf("Confirm your selection (1 for Yes, 0 for No): ");
        int confirm;
        scanf("%d", &confirm);
        if (confirm == 1) {
            payment(espresso_price, "Espresso");
            coffee_beans -= 8;
            water -= 30;
            checkThresholds();
        }
    } else {
        printf("Unavailable due to temporarily insufficient ingredients\n");
    }
}

void orderCappuccino() {
    if (coffee_beans >= CAPPUCCINO_BEANS && water >= CAPPUCCINO_WATER && milk >= CAPPUCCINO_MILK) {
        printf("Cappuccino: %.2f \n", cappuccino_price);
        printf("Confirm your selection (1 for Yes, 0 for No): ");
        int confirm;
        scanf("%d", &confirm);
        if (confirm == 1) {
            payment(cappuccino_price, "Cappuccino");
            coffee_beans -= 8;
            water -= 30;
            milk -= 70;
            checkThresholds();
        }
    } else {
        printf("Unavailable due to temporarily insufficient ingredients\n");
    }
}

void orderMocha() {
    if (coffee_beans >= MOCHA_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && choco_syrup >= MOCHA_CHOCO_SYRUP) {
        printf("Mocha: %.2f \n", mocha_price);
        printf("Confirm your selection (1 for Yes, 0 for No): ");
        int confirm;
        scanf("%d", &confirm);
        if (confirm == 1) {
            payment(mocha_price, "Mocha");
            coffee_beans -= 8;
            water -= 30;
            milk -= 160;
            choco_syrup -= 30;
            checkThresholds();
        }
    } else {
        printf("Unavailable due to temporarily insufficient ingredients\n");
    }
}

/* Handles payment and change for the selected coffee */
void payment(double price, const char* coffee_name) {
    double total_paid = 0.0;

    while (total_paid < price) {
        double coin;
        printf("Insert a coin (0.5 and 1): ");

        /* Input validation for coin */
        if (scanf("%lf", &coin) != 1) {
            printf("Invalid input! Please insert a valid coin.\n");
            while (getchar() != '\n');  
            continue;
        }

        /*This only accepts 1 and 0.5 coins*/
        if (coin == 0.5 || coin == 1) {
            total_paid += coin;
            printf("You have paid %.2lf\n", total_paid);
        } else {
            printf("Invalid coin! Please insert a valid coin.\n");
        }
    }

    printf("The total payment is complete. \nYou have ordered a %s for %.2lf \n", coffee_name, price);
    printf("Please collect your change of %.2lf \n", total_paid - price);
    total_sales += price; /*Updates the purchase value to total sales*/
}


/* This checks if ingredients are below their threshold levels */
void checkThresholds() {
    if (coffee_beans <= THRESHOLD_BEANS) {
        printf("Insufficient coffee beans.\n Remaining beans (%d) only.\n Please refill.\n", coffee_beans);
    }
    if (water <= THRESHOLD_WATER) {
        printf("Insufficient water. \n Remaining water (%dml) only. \n Please refill.\n", water);
    }
    if (milk <= THRESHOLD_MILK) {
        printf("Insufficient milk. \n Remaining milk (%dml) only. \n Please refill.\n", milk);
    }
    if (choco_syrup <= THRESHOLD_CHOCO_SYRUP) {
        printf("Insufficient chocolate syrup. \n Remaining syrup (%dml) only. \n Please refill.\n", choco_syrup);
    }
}
/* This function randomly replenishes each ingredient with a set range */
void replenishIngredients() {
    printf("Replenish Ingredients:\n");

    int i;
    int Q;
    int L;

    for (i = 0; i < 4; i++) {
        Q = (rand() % 100 + 300);  /* Random quantity between 100 and 400 for replenishing coffee beans and chocolate syrup*/
        L = (rand() % 201 + 800);  /* Random quantity between 800 and 1000 for replenishing for the milk and water*/


        switch (i) {
            case 0:
                coffee_beans = Q;
                printf("Coffee Beans replenished to %d\n", coffee_beans);
                break;
            case 1:
                water = L;
                printf("Water replenished to %dml\n", water);
                break;
            case 2:
                choco_syrup = Q;
                printf("Chocolate Syrup replenished to %dml\n", choco_syrup);
                break;
            case 3:
                milk = L;
                printf("Milk replenished to %dml\n", milk);
                break;
        }
    }

    printf("All ingredients replenished:\n");
    printf("Coffee Beans: %d\n", coffee_beans);
    printf("Water: %dml\n", water);
    printf("Milk: %dml\n", milk);
    printf("Chocolate Syrup: %dml\n", choco_syrup);
}

/*Displays the total sales with an option to reset it*/
void displayTotalSales() {
    printf("The total sales of this machine are %.2lf$\n", total_sales);
    int sales_choice;
    printf("Do you want to reset the total sales? (1 for Yes, 0 for No): ");
    scanf("%d", &sales_choice);
    if (sales_choice == 1) {
        total_sales = 0;
        printf("Collect your total money \n");
    }
}

/* Allows the admin to change the price of each coffee */
void changePrice() {
    int price_choice;
    printf("Which coffee's price do you want to change?:\n 1. Espresso \n 2. Cappuccino \n 3. Mocha \n");
    scanf("%d", &price_choice);
    double new_price;
    if (price_choice == 1) {
        printf("Current Price of Espresso Coffee is: %.2lf Enter new price of Espresso Coffee: ", espresso_price);
        scanf("%lf", &new_price);
        espresso_price = new_price;
    } else if (price_choice == 2) {
        printf("Current Price of Cappuccino Coffee is: %.2lf Enter new price of Cappuccino Coffee: ", cappuccino_price);
        scanf("%lf", &new_price);
        cappuccino_price = new_price;
    } else if (price_choice == 3) {
        printf("Current Price of Mocha Coffee is: %.2lf Enter new price of Mocha Coffee: ", mocha_price);
        scanf("%lf", &new_price);
        mocha_price = new_price;
    } else {
        printf("Invalid choice. Please try again.\n");
    }
}

/* Admin panel with password verification */
void adminPanel() {
    int pass;
    printf("Enter admin password: ");
    scanf("%d", &pass);
    
    if (pass == PASSWORD) {
        printf("Access granted.\n");
        int alpha = 1;
        while (alpha == 1) {
            int admin_choice;
            printf("Admin Panel: \n");
            printf("Main Menu \n 1. Ingredient Stock \n 2. Replenish Stock \n 3. Total Sales \n 4. Change Coffee Prices \n 0. Exit Admin Mode \n");
            scanf("%d", &admin_choice);
            switch (admin_choice) {
                case 1:
                    printf("Ingredient Stock : \n Coffee Beans : %d \n Water : %d \n Milk : %d \n Chocolate Syrup : %d \n", coffee_beans, water, milk, choco_syrup);
                    break;
                case 2:
                    replenishIngredients();
                    break;
                case 3:
                    displayTotalSales();
                    break;
                case 4:
                    changePrice();
                    break;
                case 0:
                    alpha = 0; // Exit admin mode
                    break;
                 
            }
        }
    } else {
        printf("Incorrect password.\n");
    }
}

