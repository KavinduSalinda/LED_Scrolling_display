#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <font.h>
#include <string.h>

#define BAUDRATE 9600 
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

#define MUL_DDR DDRB
#define MUL_PORT PORTB
#define CAT_DDR DDRA
#define CAT_PORT PORTA

void init_pins0(void);
void serial_run(void);

void USART_init(void);
char end;
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);
//int check_if_valid(char character);

int length = 0,pin =2;
unsigned int adress, count2, count3,i,i2, chara_num=10;
volatile  unsigned int count=0;
unsigned char movee[40];
unsigned char msg[100];  //
unsigned char new_msg[100];  //

//unsigned char list[85] = " !#$%&'()*+,-./0123456789:;<?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[^_abcdefghijklmnopqrstuvwxyz";


int main(void){
    init_pins0();
   // USART_init();  // Call the USART initialization code
   // _delay_ms(10);
// list[9]=' ';
unsigned char list[]="<<HI I'M BACK>>  " ;
/*
int index=0;
char end;

	while (1){
		end = USART_receive();
		if(end=='#'){
			break;
		}
		else {
				msg[index]='\0';
				msg[index]=end;
				index++;
		}
	}

int new_count;
		for (int i=0;i<index;i++){
			if(check_if_valid(msg[i])==1){
				new_msg[new_count]='\0';
				new_msg[new_count]=msg[i];
				new_count++;
			}
		}

*/

//for (int t = 0; t < 1; t++){
        //list[t] = USART_receive();
       // list[t] = "k";

//    }

    int arraySize = sizeof(list);          // calculate size in bytes
    int intSize = sizeof(list[0]);
    length = arraySize / intSize;     // length 
	
	for (int y = 0; y <= 40; y++) {
        movee[y] = 0;

		while ( y <= 40){
			for (int x = 0; x < length-1; x++) {
				adress = list[x] - 32;
				adress = adress * 8;    
				for (count2 = adress; count2 < adress + 8; count2++) {
					for (count3 = 0; count3 < 40; count3++) {
						 movee[count3] = movee[count3 + 1];
					}
					movee[39] = Character[count2];
					for (i2 = 0; i2 <8; i2++) {
						MUL_PORT |= 1<<1;
						serial_run();
						for (i = 0; i <= 40; i++) {
						CAT_PORT = ~movee[i];
						_delay_us(15);
						MUL_PORT &= ~(1<<1);
						serial_run();
						}
					}
				}
			}
		}	
	}
}

void init_pins0(void){
	CAT_DDR=0xff;
	MUL_DDR=0xff;
}
void serial_run(void){
    MUL_PORT |= 1<<0;
	MUL_PORT &= ~(1<<0);
    MUL_PORT |= 1<<2;
	MUL_PORT &= ~(1<<2);
}

/* Initialize USART */
void USART_init(void){
    UCSRB |= (1 << RXEN) | (1 << TXEN);				/* Enable USART transmitter and receiver */
	UCSRC |= (1 << URSEL)| (1 << UCSZ0) | (1 << UCSZ1);	/* Write USCRC for 8 bit data and 1 stop bit */ 
	UBRRL = BAUD_PRESCALLER;							/* Load UBRRL with lower 8 bit of prescale value */
	UBRRH = (BAUD_PRESCALLER >> 8);					/* Load UBRRH with upper 8 bit of prescale value */
}
/* Function to receive byte/char */
unsigned char USART_receive(void){
  while(!(UCSRA & (1<<RXC)));
  return (UDR);
}
/* Function to send byte/char */
void USART_send( unsigned char data){  
  UDR = data;
  while(!(UCSRA & (1<<UDRE)));
}
/* Send string */
void USART_putstring(char* StringPtr){
 int i=0;			
	while (StringPtr[i]!=0)
	{
		USART_send(StringPtr[i]);		/* Send each char of string till the NULL */
		i++;
	}
  
}
/*
int check_if_valid(char character){

	char my_list[85]={" !#$%&'()*+,-./0123456789:;<?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[^_abcdefghijklmnopqrstuvwxyz"};
	
	for (int i=0;i<sizeof(my_list);i++){
	
		if(character==my_list[i]){
			return 1;
		}
		
		else if(i==(sizeof(my_list)-1)){
			return 0;
		}
		
		else {
			continue;
		}
		
	}
	return 0;
}
*/
