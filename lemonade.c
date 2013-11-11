#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "keyboard.h"
#include "xterm_control.h"

#define CONTROL_C	3
#define MIN(x, y) (((x) > (y)) ? (x) : (y))

//prepares yo fridge
struct inv {
    int lemons;
    int sugar;
    int icecubes;
    int cups;
    double money;
    int dayCounter;
};


//calculates how many cups can be made with specified ingredient
//input number of ingredients possessed, number ingredients per cup
int mc(int numingredients, int percup) {
    return numingredients / percup;
}

//returns number of cups of lemonade sold for the day
//parameters are number of ingredients per cup
int sell(struct inv myInv, int l, int s, int i, int price) {
    int minCups = MIN(
            MIN(mc(myInv.lemons, l),
            mc(myInv.sugar, s)),
            MIN(mc(myInv.icecubes, i),
            myInv.cups)
		      );
    int numCups = minCups * (2/3);
    float fPrice = price;

    while (price > 3.00 && numCups > 0){
      price -= 0.25;
      numCups--;
    }
    if (l < 2 && numCups > 0)
      numCups--;
    if (s < 4 && numCups > 0)
      numCups--;
    if (i < 3 && numCups > 0)
      numCups--;
    return numCups + (rand() % (minCups * (1/3)));
}

//kind of an introduction to how the game works
int instructions() {
    int col, row, c;
    char *instructions = "To manage your lemonade stand, you will need to make these decisions \nevery day:\n1. How many ingredients (including sugar cubes, ice cubes, cups, and\nlemons) to buy?\n2. What price to charge for each cup of lemonade?\nTo continue, press enter.";
    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
    printf("%s", instructions);

    while ((c = getkey()) == KEY_NOTHING);
    if (c == KEY_ENTER) {
        char *newstand = "Here is your new stand. Press enter to continue."; //shows picture of stand
        xt_par2(XT_SET_ROW_COL_POS, row = 6, col = 1);
        printf("%s\n\n", newstand);
	xt_par0(XT_BG_BLACK);
	xt_par0(XT_CH_RED);
        printf("\t\t\t+|----------------------------------|+\n");
        printf("\t\t\t+|+++++++YOUR LEMONADE STAND++++++++|+\n");
        printf("\t\t\t+|+++++++++@SEASONAL PRICES+++++++++|+\n");
        printf("\t\t\t+|==================================|+\n");
        printf("\t\t\t+|+                                +|+\n");
        printf("\t\t\t+|+                    _______     +|+\n");
        printf("\t\t\t+|+                   |");
	xt_par0(XT_BG_YELLOW);
	printf(" o   o ");
	xt_par0(XT_BG_BLACK);
	printf("|    +|+\n\t\t\t+|+                   |");
	xt_par0(XT_BG_YELLOW);
	printf("       ");
	xt_par0(XT_BG_BLACK);
	printf("|    +|+\n\t\t\t+|+                   |");
	xt_par0(XT_BG_YELLOW);
	printf("   u   ");
	xt_par0(XT_BG_BLACK);
	printf("|    +|+\n\t\t\t+|+  |_|           Y   ");
	xt_par0(XT_BG_CYAN);
	printf("-------");
	xt_par0(XT_BG_BLACK);
	printf("     +|+\n");
        printf("\t\t\t+|+  |");
	xt_par0(XT_BG_YELLOW);
	printf("+");
	xt_par0(XT_BG_BLACK);
	printf("|+          |__|");
	xt_par0(XT_BG_MAGENTA);
	printf("   #   ");
	xt_par0(XT_BG_BLACK);
	printf("|_   +|+\n\t\t\t+|+  |");
	xt_par0(XT_BG_YELLOW);
	printf("+");
	xt_par0(XT_BG_BLACK);
	printf("|    ++++      [");
	xt_par0(XT_BG_MAGENTA);
	printf("   #   ");
	xt_par0(XT_BG_BLACK);
	printf("] |  +|+\n\t\t\t+|+  |");
	xt_par0(XT_BG_YELLOW);
	printf("+");
	xt_par0(XT_BG_BLACK);
	printf("|     ");
	xt_par0(XT_BG_YELLOW);
	printf("++");
	xt_par0(XT_BG_BLACK);
	printf("       {");
	xt_par0(XT_BG_MAGENTA);
	printf("   #   ");
	xt_par0(XT_BG_BLACK);
	printf("} n  +|+\n");
        printf("\t\t\t+====================================+\n");
        printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
        printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
        printf("\t\t\t++++++++++++++++++++++++++++++++++++++");
	xt_par0(XT_BG_GREEN);
        printf("\n\t\t\t+====================================+");
	xt_par0(XT_CH_WHITE);
	printf("\n");
	xt_par0(XT_BG_BLUE);
    }
    while ((c = getkey()) == KEY_NOTHING);
    if (c == KEY_ENTER) {
        xt_par0(XT_CLEAR_SCREEN);
        xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
        printf("You will begin with $10.00 CASH. You already have a lemonade stand from \nyour mother, so you do not need to buy one.\n\n");
	xt_par0(XT_CH_GREEN);
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
	xt_par0(XT_CH_WHITE);
	printf("You will have a stand out for a total of thirty days. Before each day you \nwill be prompted to purchase ingredients\nPress enter twice to play.");
        xt_par2(XT_SET_ROW_COL_POS, row = 9, col = 1);
        while ((c = getkey()) == KEY_NOTHING);
        if (c == KEY_ENTER) {
            return 0;
        } else
            return 1;
    }
}

void noMoneyToBuy(int currentMoney, int wishMoney) {
    int c, row, col;
    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
    printf("You only have this much money: %d, but wish to buy %d worth \nof goods.", currentMoney, wishMoney);
    printf("Unfortunately, the supermarket refuses to do business with \npaupers. Please contact Bill de Blasio for more tax cuts if you need \nmore money.");
    printf("If you would like to play again, please press F5 to hide your \nfailures and start a new game.");
}

void sunshine() {
    int c, row, col;
    row = 10;
    col = 1;
    char *sun = "   \\ | / \n";
    char *sol = " '-.;;;.' \n";
    char *sole = "-==;;;;;== \n";
    char * sunny = "  .';;;'. \n";
    char *suny = "   / | \\ \n";

    xt_par0(XT_CLEAR_SCREEN);
    while (col < 40) {
      
      xt_par0(XT_CH_YELLOW);
      xt_par2(XT_SET_ROW_COL_POS, row, col);
      printf("%s", sun);
      xt_par2(XT_SET_ROW_COL_POS, row+1, col);
      printf("%s",sol);
      xt_par2(XT_SET_ROW_COL_POS, row+2, col);
      printf("%s",sole);
      xt_par2(XT_SET_ROW_COL_POS, row+3, col);
      printf("%s",sunny);
      xt_par2(XT_SET_ROW_COL_POS, row+4, col);
      printf("%s", suny);
	
      row -= 2;
      col += 10;
      xt_par2(XT_SET_ROW_COL_POS, 12, 0);
      xt_par0(XT_CH_RED);
      printf("\t\t\t+|--------------------------|+\n");
      printf("\t\t\t+|+++YOUR LEMONADE STAND++++|+\n");
      printf("\t\t\t+|==========================|+\n");
      printf("\t\t\t+|+                        +|+\n");
      printf("\t\t\t+|+         -------        +|+\n");
      printf("\t\t\t+|+        |");
      xt_par0(XT_BG_YELLOW);
      printf(" 0   < ");
      xt_par0(XT_BG_BLUE);
      printf("|       +|+\n");
      printf("\t\t\t+|+  |-|   |");
      xt_par0(XT_BG_YELLOW);
      printf("   u   ");
      xt_par0(XT_BG_BLUE);
      printf("|       +|+\n");
      printf("\t\t\t+|+  |");
      xt_par0(XT_BG_YELLOW);
      printf(" ");
      xt_par0(XT_BG_BLUE);
      printf("|    |");
      xt_par0(XT_BG_CYAN);
      printf("-----");
      xt_par0(XT_BG_BLUE);
      printf("|        +|+\n");
      printf("\t\t\t+============================+\n");
      printf("\t\t\t++++++++++++++++++++++++++++++\n");
      printf("\t\t\t++++++++++++++++++++++++++++++\n");
      printf("\t\t\t+============================+\n");
      usleep(100000);
      xt_par0(XT_CLEAR_SCREEN);
    }
    while (col > 40) {

      xt_par0(XT_CH_YELLOW);
      xt_par2(XT_SET_ROW_COL_POS, row, col);
      printf("%s", sun);
      xt_par2(XT_SET_ROW_COL_POS, row+1, col);
      printf("%s",sol);
      xt_par2(XT_SET_ROW_COL_POS, row+2, col);
      printf("%s",sole);
      xt_par2(XT_SET_ROW_COL_POS, row+3, col);
      printf("%s",sunny);
      xt_par2(XT_SET_ROW_COL_POS, row+4, col);
      printf("%s", suny);
      
      row += 2;
      col += 10;
      xt_par2(XT_SET_ROW_COL_POS, 12, 0);
      xt_par0(XT_CH_RED);
      printf("\t\t\t+|--------------------------|+\n");
      printf("\t\t\t+|+++YOUR LEMONADE STAND++++|+\n");
      printf("\t\t\t+|==========================|+\n");
      printf("\t\t\t+|+                        +|+\n");
      printf("\t\t\t+|+         -------        +|+\n");
      printf("\t\t\t+|+        |");
      xt_par0(XT_BG_YELLOW);
      printf(" 0   < ");
      xt_par0(XT_BG_BLUE);
      printf("|       +|+\n");
      printf("\t\t\t+|+  |-|   |");
      xt_par0(XT_BG_YELLOW);
      printf("   u   ");
      xt_par0(XT_BG_BLUE);
      printf("|       +|+\n");
      printf("\t\t\t+|+  |");
      xt_par0(XT_BG_YELLOW);
      printf(" ");
      xt_par0(XT_BG_BLUE);
      printf("|    |");
      xt_par0(XT_BG_CYAN);
      printf("-----");
      xt_par0(XT_BG_BLUE);
      printf("|        +|+\n");
      printf("\t\t\t+============================+\n");
      printf("\t\t\t++++++++++++++++++++++++++++++\n");
      printf("\t\t\t++++++++++++++++++++++++++++++\n");
      printf("\t\t\t+============================+\n");
      usleep(100000);
      xt_par0(XT_CLEAR_SCREEN);
      if (row == 10) {
	break;
      }
    }
    xt_par0(XT_CH_WHITE);
}

//Requires input from the player to move onto the next step

struct inv getInfo(struct inv myinv) {
    int col, row, c;
    struct inv myInv = myinv;

    // buying ingredients initialization
    int numLem, numIce, numSug, numCup, numPrice, lpercup, spercup, ipercup;
    char lemons[10], ice[10], sugar[10], cups[10], price[10], lcup[10], scup[10], icup[10];
    int lemonsCounter = 0;
    int iceCounter = 0;
    int sugarCounter = 0;
    int cupsCounter = 0;
    int priceCounter = 0, lpcCounter = 0, spcCounter = 0, ipcCounter = 0;


    //displays prices
    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
    xt_par0(XT_CH_BLACK);
    printf("\t\t\t+++++++++++++++++++++++++++\n");
    printf("\t\t\t|");
    xt_par0(XT_BG_YELLOW);
    printf("  SAY HI TO THE GROCER!  ");
    xt_par0(XT_BG_BLUE);
    printf("|\n");
    printf("\t\t\t***************************\n");
    printf("\t\t\t|         ____            |\n");
    printf("\t\t\t|        {&&&&}           |\n");
    printf("\t\t\t|       |");
    xt_par0(XT_BG_YELLOW);
    printf(" $  $ ");
    xt_par0(XT_BG_BLUE);
    printf("|          |\n");
    printf("\t\t\t|       |");
    xt_par0(XT_BG_YELLOW);
    printf("  ^   ");
    xt_par0(XT_BG_BLUE);
    printf("|          |\n");
    printf("\t\t\t|        ");
    xt_par0(XT_BG_GREEN);
    printf("------");
    xt_par0(XT_BG_BLUE);
    printf("           |\n");
    printf("\t\t\t|=========================|\n");
    xt_par0(XT_CH_WHITE);
    printf("\t\t\tLemons: $0.50 per lemon\n");
    printf("\t\t\tIce Cubes: $0.10 per ice cube\n");
    printf("\t\t\tSugar: $0.10 per spoonful\n");
    printf("\t\t\tCups: $0.05 per cup\n");
    printf("\n");
    //displays inventory
    xt_par0(XT_CH_BLACK);
    printf("\t\t\t***************************\n");
    printf("\t\t\t|");
    xt_par0(XT_BG_RED);
    printf("      YOUR INVENTORY     ");
    xt_par0(XT_BG_BLUE);
    printf("|\n");
    printf("\t\t\t***************************\n");
    xt_par0(XT_CH_WHITE);
    printf("\t\t\tLemons: %d\n", myInv.lemons);
    printf("\t\t\tSpoonfuls of Sugar: %d\n", myInv.sugar);
    printf("\t\t\tIce Cubes: %d\n", myInv.icecubes);
    printf("\t\t\tCups: %d\n", myInv.cups);
    printf("\t\t\tMoney: %G\n", myInv.money);
    printf("Press enter to continue.\n");


    while ((c = getkey()) == KEY_NOTHING);
    if (c == KEY_ENTER) {
        xt_par0(XT_CLEAR_SCREEN);
        xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);

        //warning: no backspace, too bad if you type wrong
        xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
	xt_par0(XT_CH_YELLOW);
        printf("Make sure to input numbers only. Be sure to input the correct amount.\n");
        printf("If you input the wrong amount, and you do not have enough money to buy it,\nyour lemonade days are over. ");
	xt_par0(XT_CH_RED);
	printf("SO BE SURE TO INPUT EACH DIGIT CORRECTLY.");
	xt_par0(XT_CH_WHITE);

        //prompts asking how many of each to buy form the grocer
        xt_par2(XT_SET_ROW_COL_POS, row = 4, col = 1);
        char *buyLemons = "How many lemons would you like to purchase? ";
        printf("%s", buyLemons);
        xt_par2(XT_SET_ROW_COL_POS, row = 6, col = 1);
        char *buyIce = "How many ice cubes would you like to purchase? ";
        printf("%s", buyIce);
        xt_par2(XT_SET_ROW_COL_POS, row = 8, col = 1);
        char *buyCups = "How many cups would you like to purchase? ";
        printf("%s", buyCups);
        xt_par2(XT_SET_ROW_COL_POS, row = 10, col = 1);
        char *buySugar = "How many spoonfuls of sugar would you like to purchase? ";
        printf("%s", buySugar);
        xt_par2(XT_SET_ROW_COL_POS, row = 12, col = 1);
        char *setPrice = "How much do you want to sell each cup for? ";
        printf("%s", setPrice);
        //prompts asking how many of each to buy from the grocer
        xt_par2(XT_SET_ROW_COL_POS, row = 14, col = 1);
        char *setLemons = "How many lemons would you like to put in a cup? ";
        printf("%s", setLemons);
        xt_par2(XT_SET_ROW_COL_POS, row = 16, col = 1);
        char *setIce = "How many ice cubes would you like to put in a cup? ";
        printf("%s", setIce);
        xt_par2(XT_SET_ROW_COL_POS, row = 18, col = 1);
        char *setSugar = "How many cubes of sugar would you like to purchase? ";
        printf("%s", setSugar);

        //entering in the bought ingredients to inventory
        //sets how many lemons to buy
        xt_par2(XT_SET_ROW_COL_POS, row = 4, col = 45); //moves cursor
        while (1) {
            while ((c = getkey()) == KEY_NOTHING);
            if (c == KEY_F5) {
                return;
            }
            if (c >= '0' && c <= '9') {
                strcat(lemons, (char *) &c);
                putchar(c);
                if (col < 80)
                    xt_par2(XT_SET_ROW_COL_POS, row, ++col);
                lemonsCounter++;
            }
            if (c == KEY_ENTER) {
                numLem = atoi(lemons); // put in input into numbers
                break;
            }
        }
        //sets how many ice cubes to buy
        xt_par2(XT_SET_ROW_COL_POS, row = 6, col = 48);
        while (1) {
            if (c == KEY_F5) {
                return;
            }
            while ((c = getkey()) == KEY_NOTHING);
            if (c >= '0' && c <= '9') {
                strcat(ice, (char *) &c);
                putchar(c);
                if (col < 80)
                    xt_par2(XT_SET_ROW_COL_POS, row, ++col);
                iceCounter++;
            }
            if (c == KEY_ENTER) {
                numIce = atoi(ice);
                break;
            }
        }
        //sets how many cups to buy
        xt_par2(XT_SET_ROW_COL_POS, row = 8, col = 43);
        while (1) {
            if (c == KEY_F5) {
                return;
            }
            while ((c = getkey()) == KEY_NOTHING);
            if (c >= '0' && c <= '9') {
                strcat(cups, (char *) &c);
                putchar(c);
                if (col < 80)
                    xt_par2(XT_SET_ROW_COL_POS, row, ++col);
                cupsCounter++;
            }
            if (c == KEY_ENTER) {
                numCup = atoi(cups);
                break;
            }
        }
        //set how many spoonfuls of sugar to buy
        xt_par2(XT_SET_ROW_COL_POS, row = 10, col = 57);
        while (1) {
            if (c == KEY_F5) {
                return;
            }
            while ((c = getkey()) == KEY_NOTHING);
            if (c >= '0' && c <= '9') {
                strcat(sugar, (char *) &c);
                putchar(c);
                if (col < 80)
                    xt_par2(XT_SET_ROW_COL_POS, row, ++col);
                sugarCounter++;
            }
            if (c == KEY_ENTER) {
                numSug = atoi(sugar);
                break;
            }
        }

        //set price for each cup
        xt_par2(XT_SET_ROW_COL_POS, row = 12, col = 44);
        while (1) {
            if (c == KEY_F5) {
                return;
            }
            while ((c = getkey()) == KEY_NOTHING);
            if (c >= '0' && c <= '9') {
                strcat(price, (char *) &c);
                putchar(c);
                if (col < 80)
                    xt_par2(XT_SET_ROW_COL_POS, row, ++col);
                priceCounter++;
            }
            if (c == KEY_ENTER) {
                numPrice = atoi(price);
                break;
            }
        }

        //set how many lemons for each cup
        xt_par2(XT_SET_ROW_COL_POS, row = 14, col = 49);
        while (1) {
            if (c == KEY_F5) {
                return;
            }
            while ((c = getkey()) == KEY_NOTHING);
            if (c >= '0' && c <= '9') {
                strcat(lcup, (char *) &c);
                putchar(c);
                if (col < 80)
                    xt_par2(XT_SET_ROW_COL_POS, row, ++col);
                lpcCounter++;
            }
            if (c == KEY_ENTER) {
                lpercup = atoi(lcup);
                break;
            }
        }
        //set how many spoonfuls of sugar for each cup
        xt_par2(XT_SET_ROW_COL_POS, row = 16, col = 52);
        while (1) {
            if (c == KEY_F5) {
                return;
            }
            while ((c = getkey()) == KEY_NOTHING);
            if (c >= '0' && c <= '9') {
                strcat(scup, (char *) &c);
                putchar(c);
                if (col < 80)
                    xt_par2(XT_SET_ROW_COL_POS, row, ++col);
                spcCounter++;
            }
            if (c == KEY_ENTER) {
                spercup = atoi(scup);
                break;
            }
        }
        //set how many ice cubes for each cup
        xt_par2(XT_SET_ROW_COL_POS, row = 18, col = 53);
        while (1) {
            if (c == KEY_F5) {
                return;
            }
            while ((c = getkey()) == KEY_NOTHING);
            if (c >= '0' && c <= '9') {
                strcat(icup, (char *) &c);
                putchar(c);
                if (col < 80)
                    xt_par2(XT_SET_ROW_COL_POS, row, ++col);
                ipcCounter++;
            }
            if (c == KEY_ENTER) {
                ipercup = atoi(icup);
                break;
            }
        }
        if (c == KEY_F5) {
            xt_par0(XT_CLEAR_SCREEN);
	    xt_par0(XT_BG_DEFAULT);
	    xt_par0(XT_CH_DEFAULT);
            xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
            getkey_terminate();
        }
    }

    while ((c = getkey()) == KEY_NOTHING);
    if (c == KEY_ENTER) {
        //checks to see if you have enough money to buy:
        printf("%d, %d, %d, %d, %d, %d, %d, %d,", numLem, numIce, numSug, numCup, numPrice, lpercup, spercup, ipercup);
        if (myInv.money > 0) {
            int wantToSpend = (numLem * .50) + (numIce * .10) + (numSug * .10) + (numCup * .05);
            if (wantToSpend > myInv.money) {
                noMoneyToBuy(myInv.money, wantToSpend);
            }
        }

        //update inventory using the information (maybe want to update in code above some error message if the player tries to buy more than he/she can afford to
        if ((numLem * .50) + (numIce * .10) + (numSug * .10) + (numCup * .05) < myInv.money) {
            myInv.cups += numCup;
            myInv.icecubes += numIce;
            myInv.lemons += numLem;
            myInv.sugar += numSug;
        }
    }
    sunshine();

    //sells the lemonade and puts the money earned into your inventory
    myInv.money += numPrice * sell(myInv, lpercup, spercup, ipercup, numPrice);


    return myInv;

}

void play() {
    int col, row, c;
    struct inv myInv;
    myInv.lemons = 0;
    myInv.sugar = 0;
    myInv.icecubes = 0;
    myInv.cups = 0;
    myInv.money = 10.00;
    myInv.dayCounter = 1;
    while (myInv.dayCounter < 31) {
        myInv = getInfo(myInv);
        myInv.dayCounter++;
    }
    printf("Summer is now over and lemonade is not needed.");
    //game over
    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
    printf("Congratulations, you've earned $%G this past month. \nI hope you're proud of yourself.\n\n", myInv.money);
    printf("Here. Have a cookie for your hard work.\n");
    xt_par0(XT_CH_BLACK);
    printf("\t\t   ___   \n");
    printf("\t\t  .* *.  \n");
    printf("\t\t  | * *  \n");
    printf("\t\t   *--   \n");
    xt_par0(XT_CH_WHITE);
    printf("It's oatmeal raisin. Enjoy.\n");
    printf("Press F5 twice to exit.");
    while ((c == getkey()) == KEY_NOTHING);
    if (c == KEY_F5) {
        xt_par0(XT_CLEAR_SCREEN);
	xt_par0(XT_BG_DEFAULT);
	xt_par0(XT_CH_DEFAULT);
        xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
        getkey_terminate();
    }
}

void main() {
    int yesplay;
    int col, row, c;
    char *greeting = "\t\t\t***********************\n\t\t\tTHE LEMONADE STAND GAME\n\t\t\t***********************\n\n";
    char *intro = "Hi! Welcome to Lemonsville, Florida! In this small town, you are in charge of\nrunning your own lemonade stand. \nIf you would like to start a new game, press F4.\nYou may press F5 twice at any time to terminate.";
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
    row = col = 1;
    xt_par0(XT_BG_BLUE);
    xt_par0(XT_CLEAR_SCREEN);
    xt_par0(XT_BG_YELLOW);
    xt_par0(XT_CH_GREEN);
    printf("%s", greeting);
    //drawing out a lemon
    xt_par0(XT_BG_BLUE);
    xt_par0(XT_CH_WHITE);
    printf("%s\n\n\t\t\t\t ", intro);
    xt_par0(XT_BG_YELLOW);
    xt_par0(XT_CH_RED);
    printf("----\n");
    printf("\t\t\t\t-***$.\n");
    xt_par0(XT_BG_BLUE);
    printf("\t\t\t\t ");
    xt_par0(XT_BG_YELLOW);
    printf("---'\n");
    xt_par0(XT_CH_WHITE);
    xt_par0(XT_BG_BLUE);
    //finished drawing the lemon
    xt_par2(XT_SET_ROW_COL_POS, row = 14, col = 1);

    while (c != KEY_F5) {
        while ((c = getkey()) == KEY_NOTHING);
        if (c == KEY_F5) {
            break;
        } else if (c == KEY_F4) {
            sunshine();
            instructions();
        } else if (c == KEY_ENTER) {
            play();

        }
    }

    xt_par0(XT_CLEAR_SCREEN);
    xt_par0(XT_BG_DEFAULT);
    xt_par0(XT_CH_DEFAULT);
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
    getkey_terminate();
}
