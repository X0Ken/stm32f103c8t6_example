#include "delay.h"
#include "flash.h"
#include "serial.h"
#include "stm32f10x.h"
#include <stdio.h>

void init_led() {
  GPIO_InitTypeDef GPIO_InitStructure;
  /* GPIOA Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* Configure PA0 and PA1 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void gpio_toggle(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  GPIOx->ODR = GPIO_Pin;
}

int main(void) {
	int i;
  init_led();
  Serial_Init();
  SPI_Flash_Init();
  Serial_Send_Str("System Begin\r\n");
  while (SPI_Flash_ReadID() != FLASH_ID) //锟斤拷锟解不锟斤拷W25X16
  {
		i = SPI_Flash_ReadID();
		Serial_Send(i);
		Serial_Send(i>>8);
		Serial_Send(0xff);
    //Serial_Send_Str("\n\r没有读到正确的W25X16芯片ID，请检查硬件连接");
    delay(0xaFFFF);
    delay(0xaFFFF);
  }
  Serial_Send_Str("\n\r读到正确的W25X16芯片ID");
  while (1) {
    gpio_toggle(GPIOC, GPIO_Pin_13);
    delay(500000);
    Serial_Send('a');
    gpio_toggle(GPIOC, 0);
    delay(500000);
  }
}
