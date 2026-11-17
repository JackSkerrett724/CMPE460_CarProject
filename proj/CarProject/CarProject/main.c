/**
 * ******************************************************************************
 * @file    : main.c
 * @brief   : Main run loop
 *
 * @author  : Wil Salus
 * @date : 11/17/26
 * ******************************************************************************
*/
#include <stdint.h>
#include <stdio.h>
#include <ti/devices/msp/msp.h>
#include "lab1/leds.h"
#include "lab2/uart.h"
#include "lab4/I2C/oled.h"
#include "lab4/I2C/i2c.h"
#include "lab5/switches.h"
#include "lab5/camera.h"
#include "lab6/timers.h"

// --- CALIBRATION & PID CONSTANTS ---
#define SERVO_STRAIGHT  0.075   // Straight
#define SERVO_MIN       0.050   // left
#define SERVO_MAX       0.1   // right

#define MOTOR_SPEED     0.260   // 15% duty cycle for Demo 1
#define KP              0.00090 // Proportional gain 9:10PM 11/16 .00070 working mostly consistently
#define KD              0.00040 // Derivative gain 9:10PM 11/16 .00030 working mostly consistently

#define EDGE_THRESHOLD  110   // Minimum brightness jump to count as a valid edge 8:55PM 11/16 150 went around both ways
#define AMBIENT_CARPET_THRESHOLD 1000 //Floor vs track threshold (expect floor to be below this threshold)
#define BANK_COUNT_THRESHOLD 100
#define CONSEC_BANK_COUNT_THRESHOLD 200

unsigned char OLED_TEXT_ARR[1024];
unsigned char OLED_GRAPH_ARR[1024];



void UART0_putDecimal(uint32_t value)
{
    char buffer[10];
    int i = 0;

    // Special case for zero
    if (value == 0)
    {
        UART0_putchar('0');
        return;
    }  

    // Convert number to decimal digits
    while (value > 0)
    {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    // Digits were generated backwards, so print them backwards
    while (i > 0)
    {
        UART0_putchar(buffer[--i]);
    }
}




double clamp(double val, double min, double max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

void find_track_edges(uint16_t *cam_data, int *left_edge, int *right_edge) {
    int32_t max_rise = 0;
    int32_t max_drop = 0;
    int found_left = -1;
    int found_right = -1;
int blank_count = 0;
static int consec_blank_count = CONSEC_BANK_COUNT_THRESHOLD;
    // Scan inner pixels
    for (int i = 6; i < 121; i++) {
        int32_t diff = (int32_t)cam_data[i + 1] - (int32_t)cam_data[i - 1];

        if (diff > max_rise) {
            max_rise = diff;
            found_left = i;
        }
        if (diff < max_drop) {
            max_drop = diff;
            found_right = i;
        }
if (cam_data[i] < AMBIENT_CARPET_THRESHOLD) {
blank_count++;
}
    }

    // Only update an edge if the contrast jump is strong enough
    if (max_rise > EDGE_THRESHOLD && found_left != -1) {
        *left_edge = found_left;
    }
    if (max_drop < -EDGE_THRESHOLD && found_right != -1) {
        *right_edge = found_right;
    }
if (blank_count > 105){
consec_blank_count++;
} else {
consec_blank_count = 0;
}

if (consec_blank_count > CONSEC_BANK_COUNT_THRESHOLD){
LED1_set(0);
TIMA0_PWM_DutyCycle(0, 0.0);
TIMA0_PWM_DutyCycle(2, 0.0);
} else {
LED1_set(1);
TIMA0_PWM_DutyCycle(0, MOTOR_SPEED);
TIMA0_PWM_DutyCycle(2, MOTOR_SPEED);
}
}


int main(void) {
    LED1_init();
    S1_init();
    Camera_init();
OLED_Init();
 UART0_init();

if (!(GPIOB->GPRCM.PWREN & GPIO_PWREN_ENABLE_MASK)){
//Peripheral reset control
GPIOB->GPRCM.RSTCTL |= (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETASSERT_ASSERT | GPIO_RSTCTL_RESETSTKYCLR_CLR);
GPIOB->GPRCM.PWREN |= (GPIO_PWREN_ENABLE_ENABLE | GPIO_PWREN_KEY_UNLOCK_W);
}

if (!(GPIOA->GPRCM.PWREN & GPIO_PWREN_ENABLE_MASK)){
//Peripheral reset control
GPIOA->GPRCM.RSTCTL |= (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETASSERT_ASSERT | GPIO_RSTCTL_RESETSTKYCLR_CLR);
GPIOA->GPRCM.PWREN |= (GPIO_PWREN_ENABLE_ENABLE | GPIO_PWREN_KEY_UNLOCK_W);
}
 IOMUX->SECCFG.PINCM[IOMUX_PINCM45] |= (IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM45_PF_GPIOB_DIO19);
 IOMUX->SECCFG.PINCM[IOMUX_PINCM47] |= (IOMUX_PINCM_PC_CONNECTED | IOMUX_PINCM47_PF_GPIOA_DIO22);

GPIOB -> DOESET31_0 |= GPIO_DOUTSET31_0_DIO19_SET;
GPIOA -> DOESET31_0 |= GPIO_DOUTSET31_0_DIO22_SET;

GPIOB -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO19_SET;
GPIOA -> DOUTSET31_0 |= GPIO_DOUTSET31_0_DIO22_SET;


    // DC Motor: both channels initialized to 0%
    TIMA0_PWM_init(0, 100, 0, 0.0);
    TIMA0_PWM_init(1, 100, 0, 0.0);
 TIMA0_PWM_init(2, 100,  0, 0.0);
    TIMA0_PWM_init(3, 100, 0, 0.0);

    // Servo: 50 Hz (20,000 us), centered at 7.5%
    TIMA1_PWM_init(0, 20000, 15, SERVO_STRAIGHT);

    // Enable global interrupts for camera timers
       

    // Drive forward on Channel 0
 TIMA0_PWM_DutyCycle(0, MOTOR_SPEED);
    TIMA0_PWM_DutyCycle(1, 0.0);
    TIMA0_PWM_DutyCycle(2, MOTOR_SPEED);
    TIMA0_PWM_DutyCycle(3, 0.0);

    int left_edge = 25;
    int right_edge = 103;
    double prev_error = 0.0;
uint32_t frame_count = 0;
// LED1_set(1);

__enable_irq();
    while (1) {
        if (Camera_isDataReady()) {
  //LED1_set(0);
 
//  UART0_put("-1\r\n");
            uint16_t *line_data = Camera_getData();
            find_track_edges(line_data, &left_edge, &right_edge);


// // Send all 128 camera values
//            for (uint32_t i = 0; i < 128; i++)
//            {
//                UART0_putDecimal(line_data[i]);
//                UART0_put("\r\n");
//            }

//            // Stop value
//            UART0_put("-2\r\n");

            double track_center = (left_edge + right_edge) / 2.0;
            double error = 64.0 - track_center;
            double derivative = error - prev_error;
            prev_error = error;

            double servo_duty = SERVO_STRAIGHT + (KP * error) + (KD * derivative);
            servo_duty = clamp(servo_duty, SERVO_MIN, SERVO_MAX);
            TIMA1_PWM_DutyCycle(0, servo_duty);

if (++frame_count % 100 == 0) {
                OLED_DisplayCameraData(line_data);
            }
        }
    }
}