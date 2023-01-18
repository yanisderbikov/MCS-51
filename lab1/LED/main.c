//
// Created by Ян Дербиков  on 23.11.2022.
//
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <c8051F360.h>                 // SFR declarations

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define SYSCLK 3062500                 // Approximate SYSCLK frequency in Hz


sbit CLR = P1^7;
sbit CLK = P2^7;


int ii;
long li;
int position;
int* ar;
int x = 'B';

char buff[20];
int CTRL_Q=0x11;
int CTRL_W=0x17;

char code Font[96][6] = {
{0x0,0x0,0x0,0x0,0x0,0x0},
{0x0,0x0,0x5F,0x0,0x0,0x0},
{0x4,0x3,0x0,0x4,0x3,0x0},
{0x14,0x7F,0x14,0x7F,0x14,0x0},
{0x24,0x2A,0x7F,0x2A,0x12,0x0},
{0x63,0x13,0x8,0x64,0x63,0x0},
{0x30,0x4E,0x51,0x2E,0x50,0x0},
{0x0,0x4,0x3,0x0,0x0,0x0},
{0x0,0x1C,0x22,0x41,0x0,0x0},
{0x0,0x41,0x22,0x1C,0x0,0x0},
{0x2A,0x1C,0x7F,0x1C,0x2A,0x0},
{0x8,0x8,0x3E,0x8,0x8,0x0},
{0x0,0x40,0x30,0x0,0x0,0x0},
{0x8,0x8,0x8,0x8,0x8,0x0},
{0x0,0x60,0x60,0x0,0x0,0x0},
{0x60,0x10,0x8,0x4,0x3,0x0},
{0x3E,0x51,0x49,0x45,0x3E,0x0},
{0x0,0x42,0x7F,0x40,0x0,0x0},
{0x42,0x61,0x51,0x49,0x46,0x0},
{0x22,0x41,0x49,0x49,0x36,0x0},
{0x18,0x14,0x12,0x7F,0x10,0x0},
{0x27,0x45,0x45,0x45,0x39,0x0},
{0x3C,0x4A,0x49,0x49,0x30,0x0},
{0x1,0x71,0x9,0x5,0x3,0x0},
{0x36,0x49,0x49,0x49,0x36,0x0},
{0x6,0x49,0x49,0x29,0x1E,0x0},
{0x0,0x36,0x36,0x0,0x0,0x0},
{0x0,0x56,0x36,0x0,0x0,0x0},
{0x8,0x14,0x22,0x41,0x0,0x0},
{0x14,0x14,0x14,0x14,0x14,0x0},
{0x0,0x41,0x22,0x14,0x8,0x0},
{0x2,0x1,0x51,0x9,0x6,0x0},
{0x3E,0x41,0x5D,0x55,0x5E,0x0},
{0x7C,0x12,0x11,0x12,0x7C,0x0},
{0x7F,0x49,0x49,0x49,0x36,0x0},
{0x3E,0x41,0x41,0x41,0x22,0x0},
{0x41,0x7F,0x41,0x41,0x3E,0x0},
{0x7F,0x49,0x49,0x41,0x41,0x0},
{0x7F,0x9,0x9,0x9,0x9,0x0},
{0x3E,0x41,0x41,0x51,0x72,0x0},
{0x7F,0x8,0x8,0x8,0x7F,0x0},
{0x0,0x41,0x7F,0x41,0x0,0x0},
{0x21,0x41,0x41,0x3F,0x1,0x0},
{0x7F,0x8,0x14,0x22,0x41,0x0},
{0x7F,0x40,0x40,0x40,0x40,0x0},
{0x7F,0x2,0x4,0x2,0x7F,0x0},
{0x7F,0x4,0x8,0x10,0x7F,0x0},
{0x3E,0x41,0x41,0x41,0x3E,0x0},
{0x7F,0x9,0x9,0x9,0x6,0x0},
{0x3E,0x41,0x51,0x21,0x5E,0x0},
{0x7F,0x9,0x19,0x29,0x46,0x0},
{0x26,0x49,0x49,0x49,0x32,0x0},
{0x1,0x1,0x7F,0x1,0x1,0x0},
{0x3F,0x40,0x40,0x40,0x3F,0x0},
{0x1F,0x20,0x40,0x20,0x1F,0x0},
{0x7F,0x20,0x18,0x20,0x7F,0x0},
{0x63,0x14,0x8,0x14,0x63,0x0},
{0x3,0x4,0x78,0x4,0x3,0x0},
{0x61,0x51,0x49,0x45,0x43,0x0},
{0x0,0x7F,0x41,0x41,0x0,0x0},
{0x3,0x4,0x8,0x10,0x60,0x0},
{0x0,0x41,0x41,0x7F,0x0,0x0},
{0x4,0x2,0x1,0x2,0x4,0x0},
{0x40,0x40,0x40,0x40,0x40,0x0},
{0x0,0x0,0x3,0x4,0x0,0x0},
{0x30,0x4A,0x4A,0x32,0x7C,0x0},
{0x7F,0x48,0x48,0x30,0x0,0x0},
{0x30,0x48,0x48,0x48,0x0,0x0},
{0x0,0x30,0x48,0x48,0x7F,0x0},
{0x38,0x54,0x54,0x54,0x58,0x0},
{0x8,0x7E,0x9,0x1,0x2,0x0},
{0x6,0x49,0x49,0x45,0x3E,0x0},
{0x7F,0x10,0x8,0x8,0x70,0x0},
{0x0,0x48,0x7A,0x40,0x0,0x0},
{0x20,0x40,0x44,0x3D,0x0,0x0},
{0x7F,0x10,0x28,0x44,0x0,0x0},
{0x0,0x1,0x7F,0x0,0x0,0x0},
{0x78,0x4,0x18,0x4,0x78,0x0},
{0x7C,0x8,0x4,0x4,0x78,0x0},
{0x38,0x44,0x44,0x44,0x38,0x0},
{0x7E,0x12,0x12,0xC,0x0,0x0},
{0x0,0xC,0x12,0x12,0x7E,0x0},
{0x7C,0x8,0x4,0x4,0x8,0x0},
{0x48,0x54,0x54,0x54,0x24,0x0},
{0x4,0x3F,0x44,0x40,0x20,0x0},
{0x3C,0x40,0x40,0x20,0x7C,0x0},
{0x1C,0x20,0x40,0x20,0x1C,0x0},
{0x3C,0x40,0x30,0x40,0x3C,0x0},
{0x44,0x28,0x10,0x28,0x44,0x0},
{0x26,0x48,0x48,0x48,0x3E,0x0},
{0x44,0x64,0x54,0x4C,0x44,0x0},
{0x8,0x36,0x41,0x41,0x0,0x0},
{0x0,0x0,0x77,0x0,0x0,0x0},
{0x0,0x41,0x41,0x36,0x8,0x0},
{0x2,0x1,0x2,0x4,0x2,0x0},
{0x7F,0x7F,0x7F,0x7F,0x7F,0x0}};

int s;



//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void Port_IO_Init();
void Timer_Init();
void Interrupts_Init();
void Print(int pos);
void PrintRun(int pos);
int getSymbol(char a);

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void)
{


    PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer
    // enable)
    Port_IO_Init();

    //symbol = getSymbol(35);
    CLK = 0;
    CLR = 1;
    position = 0;
    for(li = 0; li <= 1000; li++){}
    CLR = 0;
    P2 = 0x7f;

    s = getSymbol('D');

    buff[1] = getSymbol('M');
    buff[2] = getSymbol('A');
    buff[3] = getSymbol('T');
    buff[4] = getSymbol('R');
    buff[5] = getSymbol('I');
    buff[6] = getSymbol('X');
    buff[7] = getSymbol('!');
    buff[8] = getSymbol(' ');

    buff[9] = getSymbol(' ');
    buff[10] = getSymbol(' ');
    buff[11] = getSymbol('M');
    buff[12] = getSymbol('A');
    buff[13] = getSymbol('T');
    buff[14] = getSymbol('R');
    buff[15] = getSymbol('I');
    buff[16] = getSymbol('X');
    buff[17] = getSymbol('!');
    buff[18] = getSymbol(' ');
    buff[19] = getSymbol(' ');
    buff[20] = getSymbol(' ');

    Timer_Init();
    Interrupts_Init();

    while (1)
    {

    }

}

void Port_IO_Init()
{

    SFRPAGE   = CONFIG_PAGE;
    P1MDOUT   = 0x80;
    P2MDOUT   = 0xFF;
    XBR1      = 0x40;

}

void Timer_Init()
{
    TCON      = 0x10;
    TMOD      = 0x02;
    TL0       = 0xCD;
    TH0       = 0xCD;
}

void Interrupts_Init()
{
    SFRPAGE   = CONFIG_PAGE;
    IE        = 0x82;
}

void Timer0_ISR (void) interrupt 1
{
CLK = 1;
CLK = 1;
CLK = 1;
CLK = 1;
CLK = 0;
position++;

PrintRun(position);

if(CTRL_Q == 0x11){

}





}

void Print(int pos){
    if (position >= 49){
        position = 0;
    }
    if (position<49){
        P2 = Font[buff[position/6+1]][position- 6*(position/6)]^0xff;
    }
}

void PrintRun(position){
    int e;
    //   int sp;
    int ii;
    if (position >= 49){
        position = 0;
        e++;
    }



    for (ii = 1; ii <9; ii++){


    }
    Print(position);

    //   if(e%2==1){
    //CLK = 1;
    //  CLK = 1;
    // CLK = 1;
    //CLK = 1;
    //CLK = 0;
    //}

}





int getSymbol(char a){
    int k ;
    k = ((int)(a))-32;
    return k;
}




//
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------