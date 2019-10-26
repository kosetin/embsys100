#define RCC_BASE 0x40023800
#define RCC_AHB1ENR (*((unsigned int*) (RCC_BASE+0x30)))

#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*((unsigned int*) (GPIOA_BASE + 0x00)))
#define GPIOA_ODR   (*((unsigned int*) (GPIOA_BASE + 0x14)))

/*  K   O   N  S  T  A  N T  I  N
   -*- --- -* *** - *- -* - ** -* 
*/

#define UNIT 100000
#define SPACE hold(2*UNIT)
#define K dash();  dot(); dash(); SPACE;
#define O dash(); dash(); dash(); SPACE;
#define N dash();  dot();         SPACE;
#define S  dot();  dot();  dot(); SPACE;
#define T dash();                 SPACE;
#define A  dot(); dash();         SPACE;
#define I  dot();  dot();         SPACE;

void hold(unsigned long delay)
{
  volatile unsigned long counter = 0;
  while(++counter < delay) 
  {
  }
}

void dash()
{
  //Write 1 to turn ON
  GPIOA_ODR |= 0x00000020;
  
  hold(3 * UNIT);
  
  //Write 0 to turn OFF
  GPIOA_ODR &= 0xFFFFFFDF;
  
  hold(UNIT);
}

void dot()
{
  //Write 1 to turn ON
  GPIOA_ODR |= 0x00000020;
  
  hold(UNIT);
  
  //Write 0 to turn OFF
  GPIOA_ODR &= 0xFFFFFFDF;
  
  hold(UNIT);
}

int main()
{  
  //Enable clock to peripheral
  RCC_AHB1ENR = 0x1;
  
  //Set GPIOA5 to output
  GPIOA_MODER |= 0x400;
  
  while (1)
  {
   K O N S T A N T I N
   hold(6*UNIT);
  }
  
  return 0;
}

/*
RCC Base Address: 0x40023800
RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
Address offset: 0x30
Write 0x1

GPIOA Base Address: 0x40020000
GPIO port mode register (GPIOx_MODER) (x = A..E and H)
Address offset: 0x00
Write 0x400

GPIOA Base Address: 0x40020000
GPIO port output data register (GPIOx_ODR) (x = A..E and H)
Address offset: 0x14
Write 0x20
*/