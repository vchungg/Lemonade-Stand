#include <stdio.h>
#include <math.h>

#include "keyboard.h"
#include "xterm_control.h"

#define CONTROL_C	3

//weather variables
#define sweltering 40
#define sunny 30
#define cloudy 20
#define rainy 10
#define stormy 0

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

void play(int col, int row, int c) {
    int daysCounter = 0;
    int numLem, numIce, numSug, numCup;
    char *lemons[10], *ice[10], *sugar[10], *cups[10];
    int lemonsCounter = 0;
    int iceCounter = 0;
    int sugarCounter = 0;
    int cupsCounter = 0;

    xt_par0(XT_CLEAR_SCREEN); //PRINTS ALL THE QUESTIONS
    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 1);
    char *buyLemons = "How many lemons would you like to purchase? ";
    printf("%s", buyLemons);
    xt_par2(XT_SET_ROW_COL_POS, row = 3, col = 1);
    char *buyIce = "How many ice cubes would you like to purchase? ";
    printf("%s", buyIce);
    xt_par2(XT_SET_ROW_COL_POS, row = 5, col = 1);
    char *buyCups = "How many cups would you like to purchase? ";
    printf("%s", buyCups);
    xt_par2(XT_SET_ROW_COL_POS, row = 7, col = 1);
    char *buySugar = "How many cubes of sugar would you like to purchase? ";
    printf("%s", buySugar);

    xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 45); //moves cursor
    while (1) {
	if (c >= 0 && c <= 9) {
	    *lemons[lemonsCounter] = c;
	    putchar(c);
	    if (col < 80)
		xt_par2(XT_SET_ROW_COL_POS, row, ++col);
	    lemonsCounter++;
	}
	if (c == KEY_ENTER) {
	    break;
	}
    }
    xt_par2(XT_SET_ROW_COL_POS, row = 3, col = 48);

    while (1) {
	if (c >= 0 && c <= 9) {
	    *ice[iceCounter] = c;
	    putchar(c);
	    if (col < 80)
		xt_par2(XT_SET_ROW_COL_POS, row, ++col);
	    iceCounter++;
	}
	if (c == KEY_ENTER) {
	    break;
	}
    }


    xt_par2(XT_SET_ROW_COL_POS, row = 5, col = 43);
    while (1) {
	if (c >= 0 && c <= 9) {
	    *sugar[sugarCounter] = c;
	    putchar(c);
	    if (col < 80)
		xt_par2(XT_SET_ROW_COL_POS, row, ++col);
	    sugarCounter++;
	}
	if (c == KEY_ENTER) {
	    break;
	}
    }



    xt_par2(XT_SET_ROW_COL_POS, row = 7, col = 53);
    while (1) {
	if (c >= 0 && c <= 9) {
	    *cups[cupsCounter] = c;
	    putchar(c);
	    if (col < 80)
		xt_par2(XT_SET_ROW_COL_POS, row, ++col);
	    cupsCounter++;
	}
	if (c == KEY_ENTER) {
	    break;
	}
    }


    //    xt_par0(XT_CLEAR_SCREEN);
    //    char *buyLemons = "How many lemons would you like to purchase? ";
    //    printf("%s", buyLemons);
    //    xt_par2(XT_SET_ROW_COL_POS, row = 2, col = 45);
    //    while (c != KEY_ENTER) {
    //	if (c >= 0 && c <= 9) {
    //	    *lemons[lemonsCounter] = c;
    //	    putchar(c);
    //	    lemonsCounter++;
    //	}
    //    }
    //    if (c == KEY_ENTER) {
    //	printf("\n");
    //	char *buyIce = "How many ice cubes would you like to purchase? ";
    //	printf("%s", buyIce);
    //	xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 48);
    //	while (c != KEY_ENTER) {
    //	    if (c >= 0 && c <= 9) {
    //		*lemons[lemonsCounter] = c;
    //		putchar(c);
    //		lemonsCounter++;
    //	    }
    //	}
    //    }
    //    if (c == KEY_ENTER) {
    //	printf("\n");
    //	char *buyCups = "How many cups would you like to purchase? ";
    //	printf("%s", buyCups);
    //	xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 41);
    //	while (c != KEY_ENTER) {
    //	    if (c >= 0 && c <= 9) {
    //		*lemons[lemonsCounter] = c;
    //		putchar(c);
    //		lemonsCounter++;
    //	    }
    //	}
    //    }
    //    if (c == KEY_ENTER) {
    //	printf("\n");
    //	char *buySugar = "How many cubes of sugar would you like to purchase? ";
    //	printf("%s", buySugar);
    //	xt_par2(XT_SET_ROW_COL_POS, row = 1, col = 49);
    //	while (c != KEY_ENTER) {
    //	    if (c >= 0 && c <= 9) {
    //		*lemons[lemonsCounter] = c;
    //		putchar(c);
    //		lemonsCounter++;
    //	    }
    //	}
    //    }


    //incorporate what you were working on before in here

}








//    while (1) {
//        //incorporate arrow keys and typing
//        while ((c = getkey()) == KEY_NOTHING); //to terminate
//        if (c == KEY_F5) {
//            break;
//        } else if (c == KEY_UP && row > 1)
//            xt_par2(XT_SET_ROW_COL_POS, --row, col);
//        else if (c == KEY_DOWN && row < 24)
//            xt_par2(XT_SET_ROW_COL_POS, ++row, col);
//        else if (c == KEY_RIGHT && col < 80)
//            xt_par2(XT_SET_ROW_COL_POS, row, ++col);
//        else if (c == KEY_LEFT && col > 1)
//            xt_par2(XT_SET_ROW_COL_POS, row, --col);
//        else if (c == KEY_ENTER)
//            xt_par2(XT_SET_ROW_COL_POS, ++row, col = 1);
//        else if (c >= ' ' && c <= '~') {
//            putchar(c);
//            if (col < 80)
//                ++col;
//            else
//                xt_par2(XT_SET_ROW_COL_POS, ++row, col = 1);
//        }
//    }
