#include "Bluetooth_phone.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "Grab_launch.h"
#include "usart.h"
#include "FlashConfig.h"
#include "Freertos_Init.h"
#include "RC_Chassis.h"
uint8_t usart2_dma_buff[12],flash_flag;
void Bluetooth_Rx(){  
     BluetoothRx_Typedef * xx = (BluetoothRx_Typedef *)usart2_dma_buff;
     if(xx->hand == 0xA5) {
        if(xx->al == 0x5A) {
            if(xx->mode == 1) {
                G_L_t.Launch.barrel_up[1][0] = xx->right;
                G_L_t.Launch.barrel_up[1][1] = xx->down;
                G_L_t.Launch.barrel_up[1][2] = xx->left;
            }
             else if(xx->mode == 2) {
                G_L_t.Launch.barrel_up[0][0] = xx->right;
                G_L_t.Launch.barrel_up[0][1] = xx->down;
                G_L_t.Launch.barrel_up[0][2] = xx->left;
             }
             else if(xx->mode == 4) {
                G_L_t.Puttor_expect_up = xx->upputter;
             }else if (xx->mode == 8) {
                BaseType_t value = pdFALSE;
                vTaskNotifyGiveFromISR(vFlash_taskHandle,&value);
                portYIELD_FROM_ISR(value);
             }
        }
     }
}

void operate_flash(void * parameters) {
    FlashReadConfig(&Config);
    if(Config.InitCheck != 0x1234567)
        FlashInitConfig(&Config);
    
    G_L_t.Launch.barrel_up[1][0] = Config.RIGHT_up;
    G_L_t.Launch.barrel_up[1][1] = Config.DOWN_up;
    G_L_t.Launch.barrel_up[1][2] = Config.LEFT_up;
     G_L_t.Launch.barrel_up[0][0] = Config.RIGHT_down;
    G_L_t.Launch.barrel_up[0][1] = Config.DOWN_down;
    G_L_t.Launch.barrel_up[0][2] = Config.LEFT_down;
    G_L_t.Puttor_expect_up = Config.putter;
    
    for(;;) {
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        Config.RIGHT_up  =  G_L_t.Launch.barrel_up[1][0];
        Config.DOWN_up   =  G_L_t.Launch.barrel_up[1][1];
        Config.LEFT_up   =  G_L_t.Launch.barrel_up[1][2];
        Config.RIGHT_down=  G_L_t.Launch.barrel_up[0][0];
        Config.DOWN_down  = G_L_t.Launch.barrel_up[0][1];
        Config.LEFT_down  = G_L_t.Launch.barrel_up[0][2];
        Config.putter     = G_L_t.Puttor_expect_up;
        flash_flag = 1;
        xTimerStart(pxperiod1Timer_t,0xff);
        FlashWriteConfig(&Config);
    }
}
