/*
 * disPlay.c
 *
 * Created: 2026/9/26 22:31:40
 *  Author: 941107
 */ 

#include "display.h"

// 0~9 的七段数码管段码表
static const uint8_t numbers[10] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

// 显示缓冲区：disp_buffer[0] 存十位，disp_buffer[1] 存个位
static volatile uint8_t disp_buffer[2] = {0, 0};
static volatile uint8_t active_digit = 0; // 当前亮起的位选 (0: 十位, 1: 个位)

// 内部函数：向硬件输出段码 (适配你的电路: a~f 在 PC0~PC5, g 在 PB4)
static void set_segment(uint8_t pattern) {
	PORTC = (pattern & 0x3F);
	if (pattern & (1 << 6)) {
		PORTB |= (1 << PB4);
		} else {
		PORTB &= ~(1 << PB4);
	}
}

void init_display(void) {
	// 配置 PB0, PB1 (位选) 和 PB4 (g段) 为输出
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB4);
	// 配置 PC0~PC5 (a~f段) 为输出
	DDRC |= 0x3F;

	// 初始拉高位选，关闭所有显示 (消影)
	PORTB |= (1 << PB0) | (1 << PB1);
}

void update_display_buffer(uint8_t number) {
	disp_buffer[0] = (number / 10) % 10; // 十位
	disp_buffer[1] = number % 10;        // 个位
}

void refresh_display(void) {
	// 1. 先拉高所有位选关闭显示 (消影，防止交替重影)
	PORTB |= (1 << PB0) | (1 << PB1);

	// 2. 根据 active_digit 分时点亮十位或个位
	if (active_digit == 0) {
		set_segment(numbers[disp_buffer[0]]);
		PORTB &= ~(1 << PB0); // 拉低 Ds1，使能十位显示
		active_digit = 1;
		} else {
		set_segment(numbers[disp_buffer[1]]);
		PORTB &= ~(1 << PB1); // 拉低 Ds2，使能个位显示
		active_digit = 0;
	}
}
