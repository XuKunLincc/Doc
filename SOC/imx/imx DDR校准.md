### IMX6Q DDR校准

#### 生成配置文件

- Density per chip selects (Gb):  Select total density of each CS in the list of this row
    一次片选信号总共有多少内存

- DRAM density (Gb)
    单个内存颗粒的大小

- DRAM Bus Width
    芯片位宽

- Number of Banks
    bank数

- Number of ROW Addresses
    行数

- Number of COLUMN Addresses
    列数

- Page Size (K)
    页大小

- Bus Width
    SOC的数据总线宽度 这个宽度是可以通过寄存器配置的

#### 校准

- DDR_Stress_Tester.exe -t mx6x -df imx6q_test.inc

- 选择ARM core 频率
    选择800MHz

- 进行Write leveling calibration
    需要输入MR1寄存器值的高八位
    setmem /32 0x021b001c =  0x00048031  // MMDC0_MDSCR, MR1 write, CS0

- 进行DQS校准
    
- 进行Read/Write delay校准

- 进行DDR压力测试


#### 生成cfg文件



#### 错误

QDS校准错误：这是由于配置出来问题，我们的SOC运行在32 bus模式下，我们错选了64位。

