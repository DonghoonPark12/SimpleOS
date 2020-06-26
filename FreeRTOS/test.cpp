int main(void)
{
    osThreadDef(LED2, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
    osThreadDef(LED3, LED_Thread3, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
    LED2_ThreadId = osThreadCreate(osThread(LED2), NULL);
    LED3_ThreadId = osThreadCreate(osThread(LED3), NULL);
}

staic void LED_Thread2(void const *argument)
{
    while(1)
    {
        HAL_GPIO_Toggle(GPIOB, LED2_Pin);
        osDelay(500);
    }
}

staic void LED_Thread3(void const *argument)
{
    while(1)
    {
        HAL_GPIO_Toggle(GPIOB, LED3_Pin);
        osDelay(500);   
    }
}
