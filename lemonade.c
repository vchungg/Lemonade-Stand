#include <stdio.h>
#include <math.h>

#include "keyboard.h"
#include "xterm_control.h"

#define CONTROL_C    3

//weather variables
#define sweltering 40
#define sunny 30
#define cloudy 20
#define rainy 10
#define stormy 0

struct inv{
  int lemons;
  int sugar;
  int icecubes;
  int cups;
  int money;
}
  
//calculates how many cups can be made with specified ingredient
  int mc(int numingredients, cups){
    return cups / numingredients;
  }
  
//returns number of cups of lemonade sold for the day
//parameters are number of ingredients per cup
int sell(int lemons, int sugar, int icecubes, int weather){
  int maxcups = math.min(mc(lemons, inv.cups), math.min(sugar, inv.cups),
          math.min(icecubes, inv.cups));













void main() {
    int c, row, col;
    char *hello = "Welcome to your lemonade stand.|";
    xt_par2(XT_SET_ROW_COL_POS,row=1,col=1);
    row = col = 1;
    xt_par0(XT_CLEAR_SCREEN);
    printf("%s",hello);
    xt_par2(XT_SET_ROW_COL_POS,row=2,col=1);
    
    while (1) {
      // key in
      // scrolling through the places to enter in prices and buy products
        while ((c = getkey()) == KEY_NOTHING);
        if(c == KEY_F10) break;
        else if (c == KEY_UP && row > 1) 
            xt_par2(XT_SET_ROW_COL_POS,--row,col);
        else if (c == KEY_DOWN && row < 24)
            xt_par2(XT_SET_ROW_COL_POS,++row,col);
        else if (c == KEY_RIGHT && col < 80)
            xt_par2(XT_SET_ROW_COL_POS,row,++col);
        else if (c == KEY_LEFT && col > 1)
            xt_par2(XT_SET_ROW_COL_POS,row,--col);
        else if (c == KEY_ENTER) 
            xt_par2(XT_SET_ROW_COL_POS,++row,col=1);
        else if (c >= ' ' && c <= '~') {
            putchar(c);
            if (col < 80)
                ++col;
            else
                xt_par2(XT_SET_ROW_COL_POS,++row,col=1);
        }
        //
        //press F5 to sell lemonade for the day





        //









        //press F2 to exit game
        
    }
    getkey_terminate();
}
