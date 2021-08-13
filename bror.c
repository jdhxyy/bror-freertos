// Copyright 2020-2020 The TZIOT Authors. All rights reserved.
// 框架层主文件
// Authors: jdh99 <jdh821@163.com>

#include "bror.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// BrorThreadCreate 创建线程
// func:线程函数
// name:线程名
// priority:线程优先级
// stackSize:堆栈大小
bool BrorThreadCreate(BrorFunc func, const char* name, BrorThreadPriority priority, int stackSize) {
    if (priority > configMAX_PRIORITIES ) {
        priority = configMAX_PRIORITIES;
    }
    priority = configMAX_PRIORITIES - priority;
    xTaskCreate(func, name, stackSize, NULL, priority, NULL);
    return true;
}

// BrorThreadDeleteMe 删除本线程
// 注意:本函数需要在线程结束处调用
void BrorThreadDeleteMe(void) {
    vTaskDelete(NULL);
}

// BrorDelay 延时
void BrorDelay(int second) {
    vTaskDelay(second * 1000 / portTICK_PERIOD_MS);
}

// BrorDelayMS 毫秒级延时
void BrorDelayMS(int ms) {
    if (ms < portTICK_PERIOD_MS) {
        ms = 1;
    } else {
        ms = ms / portTICK_PERIOD_MS;
    }
    vTaskDelay(ms);
}

// BrorYield 暂停执行让出CPU
void BrorYield(void) {
    vTaskDelay(0);
}

// BrorMutexInit 初始化锁
intptr_t BrorMutexInit(void) {
    return (intptr_t)xSemaphoreCreateMutex();
}

// BrorMutexLock 上锁
void BrorMutexLock(intptr_t lock) {
    xSemaphoreTake((SemaphoreHandle_t)lock, 1);
}

// BrorMutexUnlock 解锁
void BrorMutexUnlock(intptr_t lock) {
    xSemaphoreGive((SemaphoreHandle_t)lock);
}
