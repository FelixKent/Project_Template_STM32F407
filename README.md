# The Project Template for STM32F407ZGT6 V2 Development Board with StdLib

## 项目简介

本项目为 STM32F407ZGT6 V2 开发板的嵌入式标准库（StdLib）项目模板，基于 Keil MDK 开发。项目中已包含 STM32F407ZGT6 开发板的启动文件、通信协议与 STM32 标准外设库等功能。

## 硬件环境
- STM32F407ZGT6 野火霸天虎开发板 V2
- 连接线：Micro USB
- 调试接口：Fire CMSIS-DAP (SW接口) / ST-Link V2 (JTAG接口)

## 开发环境

- Keil MDK 5.40
- Keil MDK ARM GCC Compiler V5.06

## 项目结构

```shell
├─com：通信协议
├─hardware：硬件驱动
├─library：外设库源文件
├─MDK：keil生成，是一些目标文件和中间文件
│  ├─DebugConfig
│  ├─Listings
│  └─Objects
├─OS：所移植的系统源文件
│  ├─task.c：用户编写的任务
│  ├─task.h
│  ├─config
│  ├─inc
│  └─src
├─Startup：单片机初始化文件
│  ├─core_cm4.h：内核寄存器的定义
│  ├─core_cmFunc.h----+
│  ├─core_cmInstr.h	  |----操作内核相关文件
│  ├─core_cmSimd.h----+
│  ├─startup_stm32f40_41xxx.s：启动文件
│  ├─stm32f4xx.h：外设寄存器的定义    
│  ├─system_stm32f4xx.c：系统初始化，配置系统时钟    
│  └─system_stm32f4xx.h
├─User：用户主函数源文件
│  ├─main.c：用户编写的主函数 
│  ├─main.h
│  ├─stm32f4xx_conf.h：具体板卡型号的配置
│  ├─stm32f4xx_it.c：用户编写的中断服务程序
│  └─stm32f4xx_it.h      
└─README.md：项目说明文档

```


