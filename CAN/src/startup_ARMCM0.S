/**************************************************************************//**
 * @file     startup_ARMCM0.s
 * @brief    CMSIS Core Device Startup File for
 *           ARMCM0 Device Series
 * @version  V5.00
 * @date     02. March 2016
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

.syntax  unified
  .arch  armv6-m

  .section .stack
  .align  3
  .equ  Stack_Size, 0x00000100
  .globl  __StackTop
  .globl  __StackLimit
__StackLimit:
  .space  Stack_Size
  .size  __StackLimit, . - __StackLimit
__StackTop:
  .size  __StackTop, . - __StackTop

  .section .heap
  .align  3
  .equ  Heap_Size, 0x00000200
  .globl  __HeapBase
  .globl  __HeapLimit
__HeapBase:
  .if  Heap_Size
  .space  Heap_Size
  .endif
  .size  __HeapBase, . - __HeapBase
__HeapLimit:
  .size  __HeapLimit, . - __HeapLimit

  .section .vectors
  .align 2
  .globl  __Vectors
__Vectors:
  .long  __StackTop            		/* Top of Stack					*/
  .long  Reset_Handler         		/* Reset Handler				*/
  .long  NMI_Handler           		/* NMI Handler 					*/
  .long  HardFault_Handler     		/* Hard Fault Handler 			*/
  .long  Reserved_IRQHandler   		/* Reserved 					*/
  .long  Reserved_IRQHandler   		/* Reserved 					*/
  .long  Reserved_IRQHandler   		/* Reserved 					*/
  .long  Reserved_IRQHandler   		/* Reserved 					*/
  .long  Reserved_IRQHandler   		/* Reserved 					*/
  .long  Reserved_IRQHandler   		/* Reserved 					*/
  .long  Reserved_IRQHandler   		/* Reserved 					*/
  .long  SVC_Handler           		/* SVCall Handler 				*/
  .long  Reserved_IRQHandler   		/* Reserved 					*/
  .long  Reserved_IRQHandler   		/* Reserved 					*/
  .long  PendSV_Handler        		/* PendSV_Handler 				*/
  .long  SysTick_Handler       		/* SysTick_Handler 				*/

  /* External interrupts */
  .long  Reserved_IRQHandler         /*  0: Reserved                   */
  .long  Reserved_IRQHandler         /*  1: Reserved                   */
  .long  Reserved_IRQHandler         /*  2: Reserved                   */
  .long  Reserved_IRQHandler         /*  3: Reserved                   */
  .long  Reserved_IRQHandler         /*  4: Reserved                   */
  .long  EXTI0_1_IRQHandler          /*  5: EXTI0_1_IRQHandler         */
  .long  EXTI2_3_IRQHandler          /*  6: EXTI2_3_IRQHandler         */
  .long  Reserved_IRQHandler         /*  7: Reserved                   */
  .long  Reserved_IRQHandler         /*  8: Reserved                   */
  .long  Reserved_IRQHandler         /*  9: Reserved                   */
  .long  Reserved_IRQHandler         /* 10: Reserved                   */
  .long  Reserved_IRQHandler         /* 11: Reserved                   */
  .long  Reserved_IRQHandler         /* 12: Reserved                   */
  .long  Reserved_IRQHandler         /* 13: Reserved                   */
  .long  Reserved_IRQHandler         /* 14: Reserved                   */
  .long  Reserved_IRQHandler         /* 15: Reserved                   */
  .long  Reserved_IRQHandler         /* 16: Reserved                   */
  .long  Reserved_IRQHandler         /* 17: Reserved                   */
  .long  Reserved_IRQHandler         /* 18: Reserved                   */
  .long  Reserved_IRQHandler         /* 19: Reserved                   */
  .long  Reserved_IRQHandler         /* 20: Reserved                   */
  .long  Reserved_IRQHandler         /* 21: Reserved                   */
  .long  Reserved_IRQHandler         /* 22: Reserved                   */
  .long  Reserved_IRQHandler         /* 23: Reserved                   */
  .long  Reserved_IRQHandler         /* 24: Reserved                   */
  .long  Reserved_IRQHandler         /* 25: Reserved                   */
  .long  Reserved_IRQHandler         /* 26: Reserved                   */
  .long  USART1_IRQHandler           /* 27: USART1_IRQHandler          */
  .long  Reserved_IRQHandler         /* 28: Reserved                   */
  .long  Reserved_IRQHandler         /* 29: Reserved                   */
  .long  Reserved_IRQHandler         /* 30: Reserved                   */
  .long  Reserved_IRQHandler         /* 31: Reserved                   */

  .size  __Vectors, . - __Vectors

  .text
  .thumb
  .thumb_func
  .align  1
  .globl  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
  /* jump into main() function */
  bl  main
  .end
  