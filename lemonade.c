#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "keyboard.h"
#include "xterm_control.h"

#define CONTROL_C	3

//prepares yo fridge
struct inv{
  int lemons;
  int sugar;
  int icecubes;
  int cups;
  float money;
};
 

//calculates how many cups can be made with specified ingredient
//input number of ingredients possessed, number ingredients per cup
  int mc(int numingredients, int percup){
    return numingredients / percup;
  }

  //returns number of cups of lemonade sold for the day
  //parameters are number of ingredients per cup
  //needs to be refined
  int sell(struct inv myInv, int l, int s, int i, int price){
    int maxcups = fmin(fmin(mc(myInv.lemons, l), mc(myInv.sugar, s)), fmin(mc(myInv.icecubes, i), myInv.cups)));
    int soldcups = (rand() % maxcups / 2) + maxcups / 2;
    return soldcups;
  }

void instructions(int col, int row, int c);
void play(int col, int row, int c);

void main() {
    int yesplay;
    int col, row, c;
    char *greeting = "THE LEMONADE STAND GAME.\n";
    char *intro = "Hi! Welcome to Lemonsville, Florida! In this small town, you are in charge of\nrunning your own lemonade stand. \nIf you would like to start a new game, press F4.\nYou may press F5 at any time to terminate.";
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
    row = col = 1;
    xt_par0(XT_CLEAR_SCREEN);
    printf("%s", greeting);
    printf("%s", intro);
    xt_par2(XT_SET_ROW_COL_POS, row = 6, col = 1);

    while (c != KEY_F5) {
	while ((c = getkey()) == KEY_NOTHING);
	if (c == KEY_F5) {
	    break;
	} else if (c == KEY_F4) {
	    instructions(col, row, c);
	} else if (c == KEY_ENTER) {
	    play(col, row, c);
	}
    }

    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
    getkey_terminate();
}

void instructions(int col, int row, int c) {
    int days = 0;
    char *instructions = "To manage your lemonade stand, you will need to make these decisions \nevery day:\n1. How many ingredients (including sugar cubes, ice cubes, cups, and lemons) to buy?\n2. What price to charge for each cup of lemonade?\nTo continue, press enter.";
    xt_par0(XT_CLEAR_SCREEN);
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
    printf("%s", instructions);

    while ((c = getkey()) == KEY_NOTHING);
    if (c == KEY_ENTER) {
	char *newstand = "Here is your new stand. Press enter to continue."; //shows picture of stand
	xt_par2(XT_SET_ROW_COL_POS, row = 6, col = 1);
	printf("%s\n\n", newstand);
	printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t+++++++++YOUR LEMONADE STAND++++++++++\n");
	printf("\t\t\t+++++++++++@SEASONAL PRICES+++++++++++\n");
	printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t+++\t\t\t\t\t   +++\n");
	printf("\t\t\t+++\t\t\t\t\t   +++\n");
	printf("\t\t\t+++\t\t\t\t\t   +++\n");
	printf("\t\t\t+++\t\t\t\t\t   +++\n");
	printf("\t\t\t+++\t\t\t\t\t   +++\n");
	printf("\t\t\t+++\t+++\t\t\t\t   +++\n");
	printf("\t\t\t+++\t++++\t\t\t\t   +++\n");
	printf("\t\t\t+++\t+++\t++++\t\t\t   +++\n");
	printf("\t\t\t+++\t+++\t ++\t\t\t   +++\n");
	printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t++++++++++++++++++++++++++++++++++++++\n");
    }
    while ((c = getkey()) == KEY_NOTHING);
    if (c == KEY_ENTER) {
	char *start = "You will begin with $10.00 CASH. You already have a lemonade stand from \nyour mother, so you do not need to buy one.\nYou will have a stand out for a total of thirty days. Before each day you \nwill be advised of the weather forecast and be prompted to purchase ingredients.\nPress enter to play.";
	xt_par0(XT_CLEAR_SCREEN);
	xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
	printf("%s", start);
	xt_par2(XT_SET_ROW_COL_POS, row = 6, col = 1);
	while ((c = getkey()) == KEY_NOTHING);
	if (c == KEY_ENTER) {
	    return 0;
	}
    }
}


struct inv getInfo(int col, int row, int c, struct inv myinv) {
  struct inv myInv = myinv;
    int daysCounter = 1;
    
    
    // buying ingredients:
    int numLem, numIce, numSug, numCup, numPrice, lpercup, spercup, ipercup;
    char lemons[10], ice[10], sugar[10], cups[10], price[10], lcup[10], scup[10], icup[10];
    int lemonsCounter = 0;
    int iceCounter = 0;
    int sugarCounter = 0;
    int cupsCounter = 0;
    int priceCounter = 0, lpcCounter = 0, spcCounter = 0, ipcCounter = 0;
    
    //showing prices for each item
    xt_par0(XT_CLEAR_SCREEN); 
    printf("The prices for each ingredient are listed below.\n");
    printf("    +++++\n");
    printf("   +++++++\n");
    printf("    +++++\n");
    printf("Lemons: $0.50 per lemon\n");
    printf("Ice Cubes: $0.10 per ice cube\n");
    printf("Sugar: $0.10 per spoonful\n");
    printf("Cups: $0.25 per cup\n");
    
    
    //prompts asking how many of each to buy form the grocer
    xt_par2(XT_SET_ROW_COL_POS, row = 6, col = 1);
    char *buyLemons = "How many lemons would you like to purchase? ";
    printf("%s", buyLemons);
    xt_par2(XT_SET_ROW_COL_POS, row = 7, col = 1);
    char *buyIce = "How many ice cubes would you like to purchase? ";
    printf("%s", buyIce);
    xt_par2(XT_SET_ROW_COL_POS, row = 8, col = 1);
    char *buyCups = "How many cups would you like to purchase? ";
    printf("%s", buyCups);
    xt_par2(XT_SET_ROW_COL_POS, row = 9, col = 1);
    char *buySugar = "How many spoonfuls of sugar would you like to purchase? ";
    printf("%s", buySugar);
    char *setPrice = "How much do you want to sell each cup for? ";
    printf("%s", setPrice);
    //prompts asking how many of each to buy form the grocer
    xt_par2(XT_SET_ROW_COL_POS, row = 11, col = 1);
    char *setLemons = "How many lemons would you like to put in a cup? ";
    printf("%s", setLemons);
    xt_par2(XT_SET_ROW_COL_POS, row = 13, col = 1);
    char *setIce = "How many ice cubes would you like to put in a cup? ";
    printf("%s", setIce);
    xt_par2(XT_SET_ROW_COL_POS, row = 15, col = 1);
    char *setSugar = "How many cubes of sugar would you like to purchase? ";
    printf("%s", setSugar);

    //entering in the bought ingredients to inventory
    //sets how many lemons to buy
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 45); //moves cursor
    while (1) {
	while ((c = getkey()) == KEY_NOTHING);
	if (c == KEY_F5) {
	    return;
	}
	if (c >= '0' && c <= '9') {
	    strcat(lemons, c);
	    putchar(c);
	    if (col < 80)
		xt_par2(XT_SET_ROW_COL_POS, row, ++col);
	    lemonsCounter++;
	}
	if (c == KEY_ENTER) {
	    numLem = atoi(lemons);	// put in input into numbers
	    break;
	}
    }
    //sets how many ice cubes to buy
    xt_par2(XT_SET_ROW_COL_POS, row = 3, col = 48);
    while (1) {
	if (c == KEY_F5) {
	    return;
	}
	while ((c = getkey()) == KEY_NOTHING);
	if (c >= '0' && c <= '9') {
	    strcat(ice, c);
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
    xt_par2(XT_SET_ROW_COL_POS, row = 5, col = 43);
    while (1) {
	if (c == KEY_F5) {
	    return;
	}
	while ((c = getkey()) == KEY_NOTHING);
	if (c >= '0' && c <= '9') {
	    strcat(cups, c);
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
    xt_par2(XT_SET_ROW_COL_POS, row = 7, col = 57);
    while (1) {
	if (c == KEY_F5) {
	    return;
	}
	while ((c = getkey()) == KEY_NOTHING);
	if (c >= '0' && c <= '9') {
	    strcat(sugar, c);
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
    xt_par2(XT_SET_ROW_COL_POS, row = 9, col = 44);
    while (1) {
	if (c == KEY_F5) {
	    return;
	}
	while ((c = getkey()) == KEY_NOTHING);
	if (c >= '0' && c <= '9') {
	    strcat(price, c);
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
    xt_par2(XT_SET_ROW_COL_POS, row = 11, col = 49);
    while (1) {
	if (c == KEY_F5) {
	    return;
	}
	while ((c = getkey()) == KEY_NOTHING);
	if (c >= '0' && c <= '9') {
	    strcat(lcup, c);
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
    xt_par2(XT_SET_ROW_COL_POS, row = 13, col = 52);
    while (1) {
	if (c == KEY_F5) {
	    return;
	}
	while ((c = getkey()) == KEY_NOTHING);
	if (c >= '0' && c <= '9') {
	  strcat(scup, c);
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
    xt_par2(XT_SET_ROW_COL_POS, row = 15, col = 53);
    while (1) {
	if (c == KEY_F5) {
	    return;
	}
	while ((c = getkey()) == KEY_NOTHING);
	if (c >= '0' && c <= '9') {
	    strcat(icup, c);
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


    //sells the lemonade and puts the money earned into your inventory
    myInv.money += numPrice * sell(myInv, lpercup, spercup, ipercup, numPrice);
    return myInv;
}


void play(int col, int row, int c){
  struct inv myInv;
  myInv.lemons = 0;
  myInv.sugar = 0;
  myInv.icecubes = 0;
  myInv.cups = 0;
  myInv.money = 10.00;
  int dayCounter = 1;
  while (dayCounter < 31){
    myInv = getInfo(col,row,c,myInv);
    dayCounter++;
  }
}
