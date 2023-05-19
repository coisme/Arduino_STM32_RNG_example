/*
 * STM32L4 series Random Number Generator (RNG) test.
 * 
 * @author: Osamu Koizumi
 * 
 * These compile flags are required:
 *   USE_FULL_LL_DRIVER
 *   HAL_RNG_MODULE_ENABLED
 * See build_opt.h.
 * 
 * Usage of RNG driver:
 * https://github.com/stm32duino/Arduino_Core_STM32/blob/052a49af1615fb5468ef603a0213d490d810afa2/system/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng.c#L24-L35
 *
 * Tested on B-L475E-IOT01A board, STM32L475VGT6 MCU.
 */
#include "stm32yyxx_hal_conf.h"

RNG_HandleTypeDef rng_handler;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  Serial.printf("Random Number Generator test.\n");

  // Initialize the RNG MSP
  HAL_RNG_MspInit(&rng_handler);
  
  // Initialize the RNG module
  HAL_StatusTypeDef status = HAL_OK;
  status = HAL_RNG_Init(&rng_handler);
  if(status != HAL_OK) {
    Serial.printf("Error: Get RNG handler.\n");
    while(1); // Exit
  }
}

void loop() {
  uint32_t generatedNumber = 0;

  HAL_StatusTypeDef status = 
    HAL_RNG_GenerateRandomNumber(&rng_handler, &generatedNumber);
  if(status != HAL_OK) {
    Serial.printf("Failed to generate random number.\n");
  } else {
    Serial.printf("Random number = 0x%08X\n", generatedNumber);
  }
  delay(1000);

  // If you finish using RNG, call HAL_RNG_MspDeInit()
}

void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng) {
  // Enable the RNG controller clock
   __HAL_RCC_RNG_CLK_ENABLE();

  // Set RNG register base address, defined in stm32lyyyxx.h
  hrng->Instance = RNG;
}

void HAL_RNG_MspDeInit(RNG_HandleTypeDef *hrng) {
  // Disable the RNG controller clock
  __HAL_RCC_RNG_CLK_DISABLE();
}
