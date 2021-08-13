// Copyright 2020-2020 The TZIOT Authors. All rights reserved.
// ��ܲ����ļ�
// Authors: jdh99 <jdh821@163.com>

#include "bror.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// BrorThreadCreate �����߳�
// func:�̺߳���
// name:�߳���
// priority:�߳����ȼ�
// stackSize:��ջ��С
bool BrorThreadCreate(BrorFunc func, const char* name, BrorThreadPriority priority, int stackSize) {
    if (priority > configMAX_PRIORITIES ) {
        priority = configMAX_PRIORITIES;
    }
    priority = configMAX_PRIORITIES - priority;
    xTaskCreate(func, name, stackSize, NULL, priority, NULL);
    return true;
}

// BrorThreadDeleteMe ɾ�����߳�
// ע��:��������Ҫ���߳̽���������
void BrorThreadDeleteMe(void) {
    vTaskDelete(NULL);
}

// BrorDelay ��ʱ
void BrorDelay(int second) {
    vTaskDelay(second * 1000 / portTICK_PERIOD_MS);
}

// BrorDelayMS ���뼶��ʱ
void BrorDelayMS(int ms) {
    if (ms < portTICK_PERIOD_MS) {
        ms = 1;
    } else {
        ms = ms / portTICK_PERIOD_MS;
    }
    vTaskDelay(ms);
}

// BrorYield ��ִͣ���ó�CPU
void BrorYield(void) {
    vTaskDelay(0);
}

// BrorMutexInit ��ʼ����
intptr_t BrorMutexInit(void) {
    return (intptr_t)xSemaphoreCreateMutex();
}

// BrorMutexLock ����
void BrorMutexLock(intptr_t lock) {
    xSemaphoreTake((SemaphoreHandle_t)lock, 1);
}

// BrorMutexUnlock ����
void BrorMutexUnlock(intptr_t lock) {
    xSemaphoreGive((SemaphoreHandle_t)lock);
}
