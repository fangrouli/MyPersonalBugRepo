#include "../common/encoding.h"
#include "../uart/uart_config.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef signed short   ee_s16;
typedef unsigned short ee_u16;
typedef signed int     ee_s32;
typedef double         ee_f32;
typedef unsigned char  ee_u8;
typedef unsigned int   ee_u32;

/*
#define CORETIMETYPE   ee_u32
typedef ee_u32 		   CORE_TICKS;
typedef ee_u32         ee_ptr_int;
typedef double 		   secs_ret;

CORETIMETYPE
barebones_clock()
{
	return (CORETIMETYPE) read_csr(cycle);
}

#define GETMYTIME(_t)              (*_t = barebones_clock())
#define MYTIMEDIFF(fin, ini)       ((fin) - (ini))
#define TIMER_RES_DIVIDER          1
#define CLOCKS_PER_SEC			   50000000
#define EE_TICKS_PER_SEC           (CLOCKS_PER_SEC / TIMER_RES_DIVIDER)

static CORETIMETYPE start_time_val, stop_time_val;
*/
#if PERFORMANCE_RUN
volatile ee_s32 seed1_volatile = 0x0;
volatile ee_s32 seed2_volatile = 0x0;
volatile ee_s32 seed3_volatile = 0x66;
ee_s32 seed1 = 0x0;
ee_s32 seed2 = 0x0;
ee_s32 seed3 = 0x66;
#endif
ee_s32 seed4 = 10;
ee_s32 seed5 = 0;
volatile ee_s32 seed4_volatile = 10;
volatile ee_s32 seed5_volatile = 0;
/*
void
start_time(void)
{
    GETMYTIME(&start_time_val);
}

void
stop_time(void)
{
    GETMYTIME(&stop_time_val);
}

CORE_TICKS
get_time(void)
{
    CORE_TICKS elapsed
        = (CORE_TICKS)(MYTIMEDIFF(stop_time_val, start_time_val));
    return elapsed;
}
*/
int main(){
	UartStdOutInit();
	printf("UART ready.\n");
	//start_time();
	ee_s16 num1 = 0;
	ee_u16 num2 = 0;
	ee_u8  num3 = 0;
	ee_u32 num4 = 0;
	ee_s32 num5 = 0;
	
	printf("seed5_volatile=0x%x\n", seed5_volatile);
    printf("seed4_volatile=0x%x\n", seed4_volatile);
    printf("seed3_volatile=0x%x\n", seed3_volatile);
    printf("seed2_volatile=0x%x\n", seed2_volatile);
    printf("seed1_volatile=0x%x\n", seed1_volatile);
    printf("num1=0x%x\n", num1);
    printf("num2=0x%x\n", num2);
    printf("num3=0x%x\n", num3);
    printf("num4=0x%x\n", num4);
    printf("num5=0x%x\n", num5);
	/*
	ee_s16 num1 = 0x1234;
	ee_u32 num2 = 0xABCD;
	ee_s16 num3 = 0;
	secs_ret num4 = 3.14159;
	secs_ret num5 = 2718.92;
	
	unsigned long long int_part = (unsigned long long)num4;
    double frac_part = num4 - (double)int_part;
	
	
	for (int i = 0; 1 < 5; i++){
		printf("iteration %d.\n", i);
		//printf("hex 0x%x.\n", num1); //0x1234
		//printf("int %d.\n", num2); //43981
		//printf("long unsigned %lu.\n", num2);//43981
		printf("float 1: %f.\n", num4); //3.1416
		printf("float 2: %f.\n", num5); //2718.92
		stop_time();
		printf("time now: %lu.\n", get_time());
	}*/
	
}
