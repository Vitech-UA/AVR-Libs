
#include "MCP41010.h"
#define F_CPU 8000000UL







int main(void)
{
	MCP41010_Init();
	
	
	
	
    while(1)
    {
		
		//MCP41010_WriteValue(180);
			MCP41010_WriteOm(8000); //Приймає 96..8000 Ом.
			_delay_ms(300);
		
		
		
  
		
    }

}