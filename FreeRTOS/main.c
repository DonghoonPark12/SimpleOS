osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t)osPriorityNormal,
  .stack_size = 128 * 4
};

osKernelInitialize();

defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
