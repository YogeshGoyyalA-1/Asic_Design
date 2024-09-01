# ASIC Design Class Repository

## GitHub Repository: Yogesh Goyal, IMT2021542

This repository contains all the documentation and snapshots related to the experiments conducted during the lab sessions for the ASIC Design Class

---

## Contents of the Repository

- **Documentation:** Detailed explanations and observations for each experiment.
- **Snapshots:** Visual aids showing the procedures and steps involved in the experiments.

---

## Labs
<details>
<summary><strong>Laboratory 1:</strong> Create a C program to find the sum of `n` natural numbers, compile it using the GCC compiler, and verify the output after execution.</summary>

### Step-by-Step Procedure:

**Step 1:** Create a new `sum1ton.c` file in the specified directory (asic_flow) in a Linux environment using gedit editor.
![Step 1](./Lab1/1.png)

- Save your C program
![2.png](./Lab1/2.png)

**Step 2:** Compile the source code `sum1ton.c` using gcc compiler (`gcc sum1ton.c`) which will generate an executable a.out file. Run the executable file(`./a.out`) in terminal window to view the output.
![3.png](./Lab1/3.png)

**Observation** 
- Sum of first 100 natural numbers come out to be 5050

</details>

<details>
<summary><strong>Laboratory 2:</strong> Compile the C program written in Laboratory 1 using the RISCV compiler.</summary>

### Step-by-Step Procedure:

# **Compilation using O1 flag**

**Step 1:** Compile `sum1ton.c` using RISCV Compiler using the command given below
```bash
riscv64-unknown-elf-gcc -O1 -mabi=lp64-march=rv64i -o sum1ton.o  sum1ton.c
```

- `riscv64-unknown-elf-gcc`: The compiler for RISC-V 64-bit target.
- `O1`: Applies moderate optimizations for a good balance between performance and compilation time.
- `mabi=lp64`: Specifies the ABI (Application Binary Interface) as LP64, meaning "Long and Pointer are 64-bit."
- `march=rv64i`: Sets the architecture to RISC-V 64-bit with the RV64I instruction set.
- `o sum1ton.o`: Outputs the compiled code to a file named sum1ton.o.
- `sum1ton.c`: The source file to be compiled.


- Also to check whether sum1ton.o has been created or not type the following command
```bash
ls -ltr sum1ton.o
```

![Step 1](./Lab2/5.png)

**Step 2:** To generate the assembly code of the c program written type the following command in a new terminal window
```bash
riscv64-unknown-elf-objdump -d sum1ton.o
```
![Step 1](./Lab2/4.png)

![Step 1](./Lab2/6.png)
- It will give a bunch of assembly language code

**Step 3:** Use pipe less command with the command used in step 2 as shown below which allows us to scroll through the output interactively.

```bash
riscv64-unknown-elf-objdump -d sum1ton.o | less
```
- The assembly version of the C program is displayed. Type /main to navigate to the section of the code related to the main function (int main()).

![Step 1](./Lab2/7.png)
![Step 1](./Lab2/8.png)

- To determine the number of instructions in the "main" section, you can either count each instruction individually or use an alternative method: subtract the address of the first instruction in the subsequent section from the address of the first instruction in the "main" section. Then, divide the result by 4, as each instruction occupies 4 bytes in a byte-addressable memory system.

![Step 1](./Lab2/10.jpg)

- No of instructions in the main function comes out to be (0x101C0 - 0x10184)/4 = 0x3C/4 = 0xF = 15 instructions

# **Compilation using Ofast flag**

**Step 4:** Repeat Step1 and instead of O1 flag use Ofast Flag and follow all the steps after that in the similar manner
```bash
riscv64-unknown-elf-gcc -Ofast -mabi=lp64-march=rv64i -o sum1ton.o  sum1ton.c
```
![Step 1](./Lab2/9.png)
![Step 1](./Lab2/11.jpg)

- Generate the assembly code for the file and observe that the number of bytes utilized decreases from 15 to 12.

**Observation** 
- **O1**: Provides moderate optimizations, balancing performance and compilation time, and adheres strictly to standards.
- **Ofast**: Applies aggressive optimizations for maximum performance, but might break some programs as it may not follow all standards.
</details>

<details>
<summary><strong>Laboratory 3:</strong> Determine the output of the C program using the RISC-V Compiler using Spike simulator, and then debug the code</summary>

### Step-by-Step Procedure:

# **Compilation**

**Step 1:** Compile `sum1ton.c` using RISCV Compiler using the command given below
```bash
riscv64-unknown-elf-gcc -O1 -mabi=lp64-march=rv64i -o sum1ton.o  sum1ton.c
```
**Step 2:** Now we have compiled our program using RISCV compiler and we need to run in order to get the output 
similar to the ./a.out we do using gcc compiler. To do that use Spike Simulator and type the following command 
given below

```bash
spike pk sum1ton.o
```

![Step 1](./Lab3/1.png)

**Observation** 
- We have verified that output is same using the gcc and the riscv compiler

# **Debugging**

## Debugging the Assembly Code

![Step 1](./Lab3/2.png)

To debug the assembly code of your compiled C program using the Spike simulator, follow these steps:

**Step 1:** Run the following command given below
```bash
spike -d pk sum1ton.o
```

- `spike`: The Spike RISC-V simulator.
- `d`: Starts the simulator in debug mode.
- `pk`: Proxy kernel, a small environment that provides minimal OS services.
- `sum1ton.o`: The compiled object file of your C program.

We will let the Spike debugger run until it reaches the 100b0 instruction within the main function by running the command given below. From there, we will proceed with manual debugging, checking the a2 register before and after execution.To move on to next instruction press Enter

```bash
until pc 0 100b0
```
To check a registers Value type the following command 
```bash
reg 0 a2
```

![Step 1](./Lab3/3.png)

**Observation**
- Notably, the lui a2, 0x1 instruction changes the a2 register's value from `0x0000000000000000` to `0x0000000000001000`.

Next, we will manually debug the instruction addi sp, sp, -16, which reduces the stack pointer (sp) by 16. To do this run all the instructions till 100b8 by using the following command
```bash
until pc 0 100b8
```
To check stack pointer's Value type the following command 
```bash
reg 0 sp
```
![Step 1](./Lab3/4.png)

![Step 1](./Lab3/5.jpeg) 
![Step 1](./Lab3/6.jpeg)

**Observation**
- In the assembly code, it's evident that the stack pointer's value is being decreased by `0x10` in hexadecimal notation. This hexadecimal value translates to a reduction of 16 in decimal notation. Thus, the stack pointer is effectively being reduced by `16` units in decimal form.

</details>

<details>
<summary><strong>Laboratory 4:</strong> Identifying Different RISC-V Instructions.</summary>

![Step 1](./Lab4/1.png)

# RISC-V Instruction Formats


**RISC-V architecture employs a variety of instruction formats to accommodate different types of operations. The six main formats are R-Type, I-Type, S-Type, B-Type, U-Type, and J-Type, each tailored for specific purposes like arithmetic, logical operations, immediate values, branching, memory access, and jumps. Below is a brief description of each format and its usage**

## R Type
- 'R' stands for register which means that operations are carried on the Registers and not on memory location
- This format encompasses arithmetic and logical operations.
- Suitable for operations involving three registers.
- The R-type format includes fields for two source registers, one destination register, a function code, and an opcode.
  - **Examples:** ADD, SUB, OR, XOR, AND etc.
  - **Format:**
    ```
    funct7 (7 bits): Function code for more instruction details.
    rs2 (5 bits): Second source register.
    rs1 (5 bits): First source register.
    funct3 (3 bits): Function code for basic instruction details.
    rd (5 bits): Destination register.
    opcode (7 bits): Base operation code for R-type instructions.
    ```

## I Type
- I stand for immediate which means that operations use Registers and Immediate value for their execution and are not related with memory location
- Commonly used for arithmetic with immediate values, load operations, and certain branch instructions.
- The I-type format includes fields for a source register, destination register, an immediate value, a function code, and an opcode.
  - **Format:**
    ```
    immediate (12 bits): Immediate value for operations.
    rs1 (5 bits): Source register.
    funct3 (3 bits): Function code for instruction details.
    rd (5 bits): Destination register.
    opcode (7 bits): Base operation code for I-type instructions.
    ```

## S Type
- S stands for Store, meaning it stores register values into memory.
- The S-type format includes fields for two source registers, an immediate value for the memory offset, a function code, and an opcode.
  - **Format:**
    ```
    imm[11:5] (7 bits): Upper 7 bits of the immediate value.
    rs2 (5 bits): Second source register (data to be stored).
    rs1 (5 bits): First source register (base address register).
    funct3 (3 bits): Function code for instruction details.
    imm[4:0] (5 bits): Lower 5 bits of the immediate value.
    opcode (7 bits): Base operation code for S-type instructions.
    ```

## B Type
- B-type instructions manage conditional branch operations, altering the flow of execution based on comparisons between two registers.
- The B-type format includes fields for two source registers, an immediate value for the branch offset, a function code, and an opcode.
  - **Format:**
    ```
    imm[12] (1 bit): The 12th bit of the immediate value.
    imm[10:5] (6 bits): The 10th to 5th bits of the immediate value.
    rs2 (5 bits): Second source register.
    rs1 (5 bits): First source register.
    funct3 (3 bits): Function code for instruction details.
    imm[4:1] (4 bits): The 4th to 1st bits of the immediate value.
    imm[11] (1 bit): The 11th bit of the immediate value.
    opcode (7 bits): Base operation code for B-type instructions.
    ```

## U Type
- U-type instructions deal with large immediate values, typically for loading upper immediate values or computing addresses.
- The U-type format includes fields for a destination register, a large immediate value, and an opcode.
  - **Format:**
    ```
    immediate[31:12] (20 bits): The upper 20 bits of the immediate value.
    rd (5 bits): Destination register.
    opcode (7 bits): Base operation code for U-type instructions.
    ```

## J Type
- J-type instructions handle jump operations, allowing for altering the program control flow by jumping to a specific address.
- These are used for unconditional jumps, such as calling functions or implementing loops.
  - **Format:**
    ```
    imm[20] (1 bit): The 20th bit of the immediate value.
    imm[10:1] (10 bits): The 10th to 1st bits of the immediate value.
    imm[11] (1 bit): The 11th bit of the immediate value.
    imm[19:12] (8 bits): The 19th to 12th bits of the immediate value.
    rd (5 bits): Destination register where the return address is stored.
    opcode (7 bits): Operation code for J-type instructions.
    ```

## Analyzing and Decoding each Instruction given to us
```
ADD r0, r1, r2
SUB r2, r0, r1
AND r1, r0, r2
OR r8, r1, r5
XOR r8, r0, r4
SLT r0, r1, r4
ADDI r2, r2, 5
SW r2, r0, 4
SRL r6, r1, r1
BNE r0, r0, 20
BEQ 10, r0, 15
LW r3, r1, 2
SLL r5, r1, r1
```
```
1. ADD r0, r1, r2
```
- Opcode for ADD = 0110011
- rd = r0 = 00000
- rs1 = r1 = 00001
- rs2 = r2 = 00010
- func3 = 000
- func7 = 0000000
- Instruction Type- R Type
- **32-bit Instruction:** `0000000_00010_00001_000_00000_0110011`
```
2. SUB r2, r0, r1
```
- Opcode for SUB = 0110011
- rd = r2 = 00010
- rs1 = r0 = 00000
- rs2 = r1 = 00001
- func3 = 000
- func7 = 0100000
- Instruction Type- R Type
- **32-bit Instruction:** `0100000_00001_00000_000_00010_0110011`
```
3. AND r1, r0, r2
```
- Opcode for AND = 0110011
- rd = r1 = 00001
- rs1 = r0 = 00000
- rs2 = r2 = 00010
- func3 = 111
- func7 = 0000000
- Instruction Type- R Type
- **32-bit Instruction:** `0000000_00010_00000_111_00001_0110011`
```
4. OR r8, r1, r5
```
- Opcode for OR = 0110011
- rd = r8 = 01000
- rs1 = r1 = 00001
- rs2 = r5 = 00101
- func3 = 110
- func7 = 0000000
- Instruction Type- R Type
- **R Type 32-bit Instruction:** `0000000_00101_00001_110_01000_0110011`
```
5. XOR r8, r0, r4
```
- Opcode for XOR = 0110011
- rd = r8 = 01000
- rs1 = r0 = 00000
- rs2 = r4 = 00100
- func3 = 100
- func7 = 0000000
- Instruction Type- R Type
- **32-bit Instruction:** `0000000_00100_00000_100_01000_0110011`
```
6. SLT r0, r1, r4
```
- Opcode for SLT = 0110011
- rd = r0 = 00000
- rs1 = r1 = 00001
- rs2 = r4 = 00100
- func3 = 010
- func7 = 0000000
- Instruction Type- R Type
- **32-bit Instruction:** `0000000_00100_00001_010_00000_0110011`
```
7. ADDI r2, r2, 5
```
- Opcode for ADDI = 0010011
- rd = r2 = 00010
- rs1 = r2 = 00010
- imm = 000000000101
- func3 = 000
- Instruction Type- I Type
- **I Type 32-bit Instruction:** `000000000101_00010_000_00010_0010011`
```
8. SW r2, r0, 4
```
- Opcode for SW = 0100011
- rs1 = r0 = 00000
- rs2 = r2 = 00010
- imm = 0000000 0100
- func3 = 010
- Instruction Type- S Type
- **32-bit Instruction:** `0000000_00010_00000_010_00100_0100011`
```
9. SRL r6, r1, r1
```
- Opcode for SRL = 0110011
- rd = r6 = 00110
- rs1 = r1 = 00001
- rs2 = r1 = 00001
- func3 = 101
- func7 = 0000000
- Instruction Type- R Type
- **32-bit Instruction:** `0000000_00001_00001_101_00110_0110011`
```
10. BNE r0, r0, 20
```
- Opcode for BNE = 1100011
- rs1 = r0 = 00000
- rs2 = r0 = 00000
- imm[12:1] = 20 = 000000010100
- func3 = 001
- Instruction Type- B Type
- **32-bit Instruction:** `0_000001_00000_00000_001_0100_0_1100011`
```
11. BEQ r0, r0, 15
```
- Opcode for BEQ = 1100011
- rs1 = r0 = 00000
- rs2 = r0 = 00000
- Imm[12:1] = 15 = 000000001111
- func3 = 000
- Instruction Type- B Type
- **32-bit Instruction:** `0_000000_00000_00000_000_1111_0_1100011`
```
12. LW r3, r1, 2
```
- Opcode for LW = 0000011
- rd = r3 = 00011
- rs1 = r1 = 00001
- imm = 000000000010
- func3 = 010
- Instruction Type- I Type
- **32-bit Instruction:** `000000000010_00001_010_00011_0000011`
```
13. SLL r5, r1, r1
```
- Opcode for SLL = 0110011
- rd = r5 = 00101
- rs1 = r1 = 00001
- rs2 = r1 = 00001
- func3 = 001
- func7 = 0000000
- Instruction Type- R Type
- **32-bit Instruction:** `0000000_00001_00001_001_00101_0110011`

| Instruction | Type | 32-bit Representation                      | Hexadecimal Notation  |
|-------------|------|-------------------------------------------|-----------------------|
| ADD r0, r1, r2 | R    | 0000000_00010_00001_000_00000_0110011     | 0x00208033            |
| SUB r2, r0, r1 | R    | 0100000_00001_00000_000_00010_0110011     | 0x40100133            |
| AND r1, r0, r2 | R    | 0000000_00010_00000_111_00001_0110011     | 0x002070B3            |
| OR r8, r1, r5  | R    | 0000000_00101_00001_110_01000_0110011     | 0x0050E433            |
| XOR r8, r0, r4 | R    | 0000000_00100_00000_100_01000_0110011     | 0x00404433            |
| SLT r0, r1, r4 | R    | 0000000_00100_00001_010_00000_0110011     | 0x0040A033            |
| ADDI r2, r2, 5 | I    | 000000000101_00010_000_00010_0010011      | 0x00510113            |
| SW r2, r0, 4   | S    | 0000000_00010_00000_010_00100_0100011     | 0x00202223            |
| SRL r6, r1, r1 | R    | 0000000_00001_00001_101_00110_0110011     | 0x0010D333            |
| BNE r0, r0, 20 | B    | 0_000001_00000_00000_001_0100_0_1100011   | 0x02001463            |
| BEQ r0, r0, 15 | B    | 0_000000_00000_00000_000_1111_0_1100011   | 0x00000F63            |
| LW r3, r1, 2   | I    | 000000000010_00001_010_00011_0000011      | 0x0020A183            |
| SLL r5, r1, r1 | R    | 0000000_00001_00001_001_00101_0110011     | 0x001092B3            |

</details>

<details>
<summary><strong>Laboratory 5:</strong> Execute the RISC-V ISA in the Reference Verilog Code and Get the Output Waveform.</summary>

---
##### As illustrated in the figure below, all the instructions in the provided Verilog file are hardcoded. This means that, instead of adhering to the standard RISC-V bit patterns, the designer has implemented custom bit patterns for each instruction.

<img src="./Lab5/13.png" alt="description" width="500"/>



### Differences between Standard RISC-V ISA and Hardcoded ISA

| Operation           | Standard RISC-V ISA | Hardcoded ISA   |
|---------------------|---------------------|-----------------|
| ADD R6, R2, R1      | 32'h00110333         | 32'h02208300    |
| SUB R7, R1, R2      | 32'h402083b3         | 32'h02209380    |
| AND R8, R1, R3      | 32'h0030f433         | 32'h0230a400    |
| OR R9, R2, R5       | 32'h005164b3         | 32'h02513480    |
| XOR R10, R1, R4     | 32'h0040c533         | 32'h0240c500    |
| SLT R1, R2, R4      | 32'h0045a0b3         | 32'h02415580    |
| ADDI R12, R4, 5     | 32'h004120b3         | 32'h00520600    |
| BEQ R0, R0, 15      | 32'h00000f63         | 32'h00f00002    |
| SW R3, R1, 2        | 32'h0030a123         | 32'h00209181    |
| LW R13, R1, 2       | 32'h0020a683         | 32'h00208681    |
| SRL R16, R14, R2    | 32'h0030a123         | 32'h00271803    |
| SLL R15, R1, R2     | 32'h002097b3         | 32'h00208783    |

### Custom Instructions provided in previous task

| Instruction    | Type | 32-bit Representation                | Hexadecimal Notation |
|----------------|------|--------------------------------------|----------------------|
| ADD r0, r1, r2 | R    | 0000000_00010_00001_000_00000_0110011 | 0x00208033           |
| SUB r2, r0, r1 | R    | 0100000_00001_00000_000_00010_0110011 | 0x40100133           |
| AND r1, r0, r2 | R    | 0000000_00010_00000_111_00001_0110011 | 0x002070B3           |
| OR r8, r1, r5  | R    | 0000000_00101_00001_110_01000_0110011 | 0x0050E433           |
| XOR r8, r0, r4 | R    | 0000000_00100_00000_100_01000_0110011 | 0x00404433           |
| SLT r0, r1, r4 | R    | 0000000_00100_00001_010_00000_0110011 | 0x0040A033           |
| ADDI r2, r2, 5 | I    | 000000000101_00010_000_00010_0010011  | 0x00510113           |
| SW r2, r0, 4   | S    | 0000000_00010_00000_010_00100_0100011 | 0x00202223           |
| SRL r6, r1, r1 | R    | 0000000_00001_00001_101_00110_0110011 | 0x0010D333           |
| BNE r0, r0, 20 | B    | 0_000001_00000_00000_001_0100_0_1100011 | 0x02001463           |
| BEQ r0, r0, 15 | B    | 0_000000_00000_00000_000_1111_0_1100011 | 0x00000F63           |
| LW r3, r1, 2   | I    | 000000000010_00001_010_00011_0000011  | 0x0020A183           |
| SLL r5, r1, r1 | R    | 0000000_00001_00001_001_00101_0110011 | 0x001092B3           |


## **Functional Simulation**

*NOTE:* Here we have used Verilog code and the testbench of RISC-V from the GitHub repository [iiitb_rv32i](https://github.com/vinayrayapati/rv32i/tree/main).

1. Clone the Repository and change the directory as follows
    ```bash
   git clone https://github.com/vinayrayapati/iiitb_rv32i
    cd rv32i  
   ```


2. To compile the Verilog code, use the following command:
   ```bash
   iverilog -o iiitb_rv32i iiitb_rv32i.v iiitb_rv32i_tb.v
   ```

3. Run this command to execute the test bench and generate a .vcd file:
     ```bash
    vvp iiitb_rv32i
   ```
4. View the Test Bench in GTKWave:

    ```bash
    gtkwave iiitb_rv32i.vcd
    ```
![Step 1](./Lab5/1.png)
![Step 1](./Lab5/2.png)

### Output Waveform
The output waveform illustrates the execution of instructions within a 5-stage pipelined architecture.


Outputs
```
1. ADD R6, R2, R1
```
![Step 1](./Lab5/3.png)

```
2. SUB R7, R1, R2
```
![Step 1](./Lab5/4.png)

```
3. AND R8, R1, R3
```
![Step 1](./Lab5/5.png)

```
4. OR R9, R2, R5
```
![Step 1](./Lab5/6.png)

```
5. XOR R10, R1, R4
```
![Step 1](./Lab5/7.png)

```
6. SLT R1, R2, R4
```
![Step 1](./Lab5/8.png)

```
7. ADDI R12, R4, 5
```
![Step 1](./Lab5/9.png)

```
8. BEQ R0, R0, 15
```
![Step 1](./Lab5/10.png)

```
9. SW R3, R1, 2
```
![Step 1](./Lab5/11.png)
```

10. LW R13, R1, 2
```
![Step 1](./Lab5/12.png)

**Observation**:- We observe a variation between bit pattern of RISCV code and hardcoded ISA.
</details>

<details>
<summary><strong>Laboratory 6:</strong> Finding Two's Complement of a 4 bit Number</summary>

# Twosify: Two's Compliment of a number
### Understanding Two's Complement

Two's complement is a mathematical operation on binary numbers, often used to represent signed integers in computing. To find the two's complement of a binary number:

1. **Invert all the bits** (change 0 to 1 and 1 to 0).
2. **Add 1** to the least significant bit (LSB) of the inverted number.

### Step-by-Step Procedure:

# **Calculation of Two's Complement**

## Compilation using gcc

**Step 1:** Create a new `twosify.c` file in the specified directory (asic_flow) in a Linux environment using gedit editor and save your c program. You can find the c program here `Lab6/twosify.c`
![Step 1](./Lab6/1.png)

**Step 2:** Compile the c program using the gcc compiler using the command below
```bash
gcc twosify.c
```
**Step 3:** Now the run the executable file (a.out) using the following command
```bash
./a.out
```
![Step 1](./Lab6/2.png)

## Compliation using RISCV Compiler

**Step 1:** Compile `twosify.c` using the RISCV Compiler with the command below:
```bash
riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o twosify.o twosify.c
```
![Step 2](./Lab6/4.png)
**Step 2:** After compiling the program using the RISCV compiler, run it to obtain the output. Similar to how you would use ./a.out with the GCC compiler, use the Spike Simulator with the following command:

```bash
spike pk twosify.o
```
![Step 2](./Lab6/5.png)

**Observation**:- We can observe the output that is the two's compliment of number `3` is verified and coming the same using gcc and the riscv compiler.
</details>

<details>
<summary><strong>Laboratory 7:</strong> Digital Logic with TL-Verilog using Makerchip </summary>

## Combinational Circuits in TL-Verilog

**Introduction to TL-Verilog and Makerchip:**
Makerchip supports the Transaction-Level Verilog (TL-Verilog) standard, which represents a significant advancement by removing the need for the legacy features of traditional Verilog and introducing a more streamlined syntax. TL-Verilog enhances design efficiency by adding powerful constructs for pipelines and transactions, making it easier to develop complex digital circuits.


### 1. Inverter
Code is given below
```tl-verilog
$out = ! $in;
```
The generated block diagram and waveforms are as shown

![Step 2](./Lab7/1.png)


### 2. 2-Input And Gate(&&)
Code is given below
```tl-verilog
$out = $in1 && $in2;
```
The generated block diagram and waveforms are as shown

![Step 2](./Lab7/2.png)

### 3. 2-Input OR Gate
Code is given below
```tl-verilog
$out = $in1 || $in2;
```
The generated block diagram and waveforms are as shown

![Step 2](./Lab7/3.png)

### 4. 2-Input XOR Gate
Code is given below
```tl-verilog
$out = $in1 ^ $in2;
```
The generated block diagram and waveforms are as shown

![Step 2](./Lab7/4.png)

### 5. Arithmetic Operation on Vectors
Code is given below
```tl-verilog
$out[4:0] = $in1[3:0] + $in2[3:0];
```
The generated block diagram and waveforms are as shown

![Step 2](./Lab7/5.png)

### 6. 2:1 MUX
Code is given below
```tl-verilog
$out = $sel ? $in1 : $in0;
```
The generated block diagram and waveforms are as shown

![Step 2](./Lab7/6.png)

### 7. 2:1 MUX Using Vectors
Code is given below
```tl-verilog
$out[7:0] = $sel ? $in1[7:0] : $in0[7:0];
```
The generated block diagram and waveforms are as shown

![Step 2](./Lab7/7.png)

### 8. Combinational Calculator Implementation in TL-Verilog

**Calculator Overview:**
In this section, we demonstrate a basic combinational calculator implemented using TL-Verilog on the Makerchip platform. The calculator performs four fundamental arithmetic operations: addition, subtraction, multiplication, and division.

```tl-verilog
$val1[31:0] = $rand1[3:0];
$val2[31:0] = $rand2[3:0];

$sum[31:0]  = $val1[31:0] + $val2[31:0];
$diff[31:0] = $val1[31:0] - $val2[31:0];
$prod[31:0] = $val1[31:0] * $val2[31:0];
$quot[31:0] = $val1[31:0] / $val2[31:0];

$out[31:0]  = $sel[1] ? ($sel[0] ? $quot[31:0] : $prod[31:0])
                      : ($sel[0] ? $diff[31:0] : $sum[31:0]);
```
Description: 
In this code snippet, two random 4-bit values, `$rand1[3:0]` and `$rand2[3:0]`, are assigned to the 32-bit variables `$val1[31:0]` and `$val2[31:0]`, respectively. The calculator then performs four arithmetic operations on these values:

The result of one of these operations is selected by a multiplexer (MUX), controlled by the selection bits `$sel[1:0]`. The MUX determines which operation's output is assigned to `$out[31:0]`.

The generated block diagram and waveforms are as shown
![Step 2](./Lab7/8.png)

#### **Observation**:- The following screenshot shows the implementation of the combinational circuit using the code above on the Makerchip platform. It also displays the generated block diagram and the simulation waveform, providing insight into the circuit's operation.

## Sequential Circuits in TL-Verilog

A sequential circuit is a type of digital circuit that uses memory components to retain data, enabling it to generate outputs based on both the current inputs and the circuit's prior state. This distinguishes it from combinational circuits, where the output is solely determined by the present inputs without any regard to past activity. Sequential circuits rely on feedback loops and storage elements like flip-flops or registers to keep track of their internal state over time. This internal state, combined with the present input, influences the circuit's behavior, allowing it to perform tasks that require a history of previous inputs or operations, such as counting, storing data, or sequencing events.

### 1. Fibbonacci Series
- Next Value is the sum of previous two values
![Step 2](./Lab7/9.png)

Code is given below
```tl-verilog
$reset = *reset;
$num[31:0] = $reset ? 1 : (>>1$num + >>2$num);
```
The generated block diagram and waveforms are as shown

![Step 2](./Lab7/10.png)

### 2. Free Running Counter
- Next Value increments by 1 of the previous value
![Step 2](./Lab7/11.png)

Code is given below
```tl-verilog
$reset = *reset;
$cnt[31:0] = $reset ? 0 : (>>1$cnt + 1);
```
The generated block diagram and waveforms are as shown

![Step 2](./Lab7/12.png)

### 3. Sequential Calculator
- Works the same way as combinational calculator but mimics real scenario in which the result of the previous operation is considered as one of the operand for the next operation. Upon reset the result becomes zero.


Code is given below
```tl-verilog
$reset = *reset;
   
$val1[31:0] = >>1$out;
$val2[31:0] = $rand[3:0];
   
$sum[31:0] =  $val1[31:0] +  $val2[31:0];
$diff[31:0] =  $val1[31:0] -  $val2[31:0];
$prod[31:0] =  $val1[31:0] *  $val2[31:0];
$quot[31:0] =  $val1[31:0] /  $val2[31:0];
   
   
$out[31:0] = $reset ? 32'h0 : ($choose[1] ? ($choose[0] ? $quot : $prod):($choose[0] ? $diff : $sum));

```
The generated block diagram and waveforms are as shown

![Step 2](./Lab7/13.png)

## Pipelined Logic

In Transaction-Level Verilog (TL-Verilog), pipelined logic is elegantly expressed through the use of pipeline constructs that inherently represent the flow of data across different stages of a digital design. Each pipeline stage in TL-Verilog corresponds to a clock cycle, where operations are performed on data as it progresses through the pipeline. This approach allows for clear and concise modeling of sequential logic, where each stage automatically handles the propagation of state and values to the next cycle. By leveraging TL-Verilog's pipeline notation, designers can easily describe complex, multi-stage operations with a focus on the transaction flow, simplifying the design and verification process while enhancing readability and maintainability.

### 1. To produce the Pipeline Design
- To produce the given block Diagram logic shown below. 4 error conditions in the pipeline and aggregrating them to result in a single error indication.
![Step 2](./Lab7/14.png)

Code is given below
```tl-verilog
$reset = *reset;
$clk_yog = *clk;
|comp
  @1
    $err1 = $bad_input || $illegal_op;
  @3
    $err2 = $over_flow || $err1;
  @6
    $err3 = $div_by_zero || $err2;
```
The generated block diagram and waveforms are as shown and can be compared with the one which had to be produced and can verify it is the same

![Step 2](./Lab7/15.png)

### 2. 2 Cycle Calculator 
- 
<img src="./Lab7/16.png" alt="description" width="500"/>

Code is given below
```tl-verilog
|calc
  @1
    $reset = *reset;
    $clk_yog = *clk;
   
    $val1[31:0] = >>2$out[31:0];
    $val2[31:0] = $rand2[3:0];
    $sel[1:0] = $rand3[1:0];
   
    $sum[31:0] = $val1[31:0] + $val2[31:0];
    $diff[31:0] = $val1[31:0] - $val2[31:0];
    $prod[31:0] = $val1[31:0] * $val2[31:0];
    $quot[31:0] = $val1[31:0] / $val2[31:0];
         
    $count = $reset ? 0 : >>1$count + 1;
         
  @2
    $valid = $count;
    $inv_valid = !$valid;
    $calc_reset = $reset | $inv_valid;
    $out[31:0] = $calc_reset ? 32'b0 : ($op[1] ? ($op[0] ? $quot[31:0] : $prod[31:0])
                                             : ($op[0] ? $diff[31:0] 
                                                        : $sum[31:0]));


```
The generated block diagram and waveforms are as shown
![Step 2](./Lab7/17.png)

## Validity
When generating a waveform, results are obtained for each clock cycle, and while there may be no compilation errors, logical errors can still slip through, making them difficult to detect by merely analyzing the waveforms. Additionally, some "don't care" conditions might be irrelevant to the design and should be ignored. The concept of validity is introduced to address these issues. The global clock continuously drives operations, even when they are unnecessary, leading to excessive power consumption. In physical circuits, clocks are powered by voltage or current sources, consuming energy with every cycle. In complex systems, failing to bypass unnecessary operations can lead to substantial power waste. To optimize power efficiency, the clock signal is disabled during unneeded cycles through a technique called clock gating. Validity is crucial for implementing clock gating, ensuring that only the necessary operations are executed.

### 1. Total Distance Calculator
Code is given below
```tl-verilog
|calc
  @1
    $reset = *reset;
    $clk_yog = *clk;
            
    ?$vaild      
      @1
        $aa_seq[31:0] = $aa[3:0] * $aa;
        $bb_seq[31:0] = $bb[3:0] * $bb;;
      
      @2
        $cc_seq[31:0] = $aa_seq + $bb_seq;;
      
      @3
        $cc[31:0] = sqrt($cc_seq);
            
      @4
         $total_distance[63:0] = 
            $reset ? '0 :
            $valid ? >>1$total_distance + $cc :
                     >>1$total_distance;


```


The generated block diagram and waveforms are as shown
![Step 2](./Lab7/18.png)

### 2. 2 Cycle Calulator with validity
![Step 2](./Lab7/20.png)
Code is given below
```tl-verilog
|calc
@0
   $reset = *reset;
    $clk_yog = *clk;
         
@1
    $val1 [31:0] = >>2$out [31:0];
    $val2 [31:0] = $rand2[3:0];
         
    $valid = $reset ? 1'b0 : >>1$valid + 1'b1 ;
    $valid_or_reset = $valid || $reset;
         
vaild_or_reset
   @1   
      $sum [31:0] = $val1 + $val2;
      $diff[31:0] = $val1 - $val2;
      $prod[31:0] = $val1 * $val2;
      $quot[31:0] = $val1 / $val2;
            
   @2   
      $out [31:0] = $reset ? 32'b0 :
                          ($op[1:0] == 2'b00) ? $sum :
                          ($op[1:0] == 2'b01) ? $diff :
                          ($op[1:0] == 2'b10) ? $prod :
                                                $quot ;
```


The generated block diagram and waveforms are as shown
![Step 2](./Lab7/19.png)

### 3. 2 Calculator with Single Value Memory
![Step 2](./Lab7/21.png)
Code is given below
```tl-verilog
|calc
  @0
    $reset = *reset;
    $clk_yog = *clk;
         
   @1
    $val1 [31:0] = >>2$out;
    $val2 [31:0] = $rand2[3:0];
         
    $valid = $reset ? 1'b0 : >>1$valid + 1'b1 ;
    $valid_or_reset = $valid || $reset;
         
  ?$vaild_or_reset
    @1   
      $sum [31:0] = $val1 + $val2;
      $diff[31:0] = $val1 - $val2;
      $prod[31:0] = $val1 * $val2;
      $quot[31:0] = $val1 / $val2;
            
     @2   
        $mem[31:0] = $reset ? 32'b0 :
                     ($op[2:0] == 3'b101) ? $val1 : >>2$mem ;
            
        $out [31:0] = $reset ? 32'b0 :
                       ($op[2:0] == 3'b000) ? $sum :
                      ($op[2:0] == 3'b001) ? $diff :
                      ($op[2:0] == 3'b010) ? $prod :
                      ($op[2:0] == 3'b011) ? $quot :
                      ($op[2:0] == 3'b100) ? >>2$mem : >>2$out ;
```


The generated block diagram and waveforms are as shown
![Step 2](./Lab7/22.png)

</details>

<details>
<summary><strong>Laboratory 8:</strong> Basic RISCV CPU Micro-architecture </summary>

# Implementation of the RISC-V CPU Core
This section will walk you through the different implementation steps followed to achieve the design of the complete RISC-V CPU core. You can find the codes [here](https://github.com/YogeshGoyyalA-1/Asic_Design/tree/main/Lab8/codes).


Given below is the riscv block diagram
![Step 2](./Lab8/1.jpg)

The design of a basic RISC-V CPU core involves several key logical blocks, which include the following components:

### 1:- Program Counter(PC) and next PC Logic

The Program Counter (PC) is a register that stores the address of the next instruction to be executed, functioning as a pointer into the instruction memory. Since the memory is byte-addressable and each instruction is 32 bits long, the PC increments by 4 bytes after each instruction to point to the next one. Upon the initial execution, a reset signal sets the PC to 0, ensuring that the first instruction is fetched from the correct starting point. For branch instructions, an immediate value is added to the current PC, resulting in a new address given by the formula: `NextPC = Incremented PC + Offset value`. Generally, the PC advances by 4 to fetch the next sequential instruction, but it resets to zero if a reset signal is triggered. The accompanying diagram illustrates how the PC functions, showing its progression through instructions and its behavior during resets and branch operations.

![Step 2](./Lab8/2.png)
Code is given below
```tl-verilog
$reset = *reset;
$clk_yog = *clk;
$reset = *reset;

|cpu
  @0
    $reset = *reset;
    $pc[31:0] = >>1$reset ? 32'b0 : >>1$pc + 32'd4;
```

Generated block diagram and waveform for the pc counter is shown below
![Step 2](./Lab8/19.png)
![Step 2](./Lab8/3.png)

### 2:- Instruction Fetch

The Instruction Fetch Unit (IFU) within a CPU is tasked with organizing program instructions to be fetched from memory and executed in the correct sequence, forming the core's control logic.The program counter identifies the address of the next instruction stored in the instruction memory. This instruction must be retrieved to proceed with processing and further calculations.In this context, the instruction memory is integrated into the program. Within the Instruction Fetch logic, instructions are retrieved from the instruction memory and then forwarded to the Decode logic for processing. The read address for the instruction memory is derived from the program counter, which outputs a 32-bit instruction (instr[31:0]).

![Step 2](./Lab8/4.png)

Code is given below
```tl-verilog
|cpu
  @0
    $reset = *reset;
    $clk_yog = *clk;
    $pc[31:0] = $reset ? '0 : >>1$pc + 32'd4;
         
    $imem_rd_en = !$reset ? 1 : 0;
    $imem_rd_addr[M4_IMEM_INDEX_CNT-1:0] = $pc[M4_IMEM_INDEX_CNT+1:2];

  @1
    $instr[31:0] = $imem_rd_data[31:0];
```

Generated block diagram and waveform for the instruction fetch cycle is shown below

![Step 2](./Lab8/5.png)


### 3:- Instruction Decode
In the decode stage, the goal is to extract detailed information from the instruction read during the fetch stage. This includes determining the instruction set, identifying any immediate values, and extracting register values.During Instruction Decode, every instruction is analyzed to identify its type, whether it includes immediate values, and the specific fields it contains. The opcode is mapped to the corresponding instruction, and the bit fields are interpreted according to the RISC-V ISA specifications.

![Step 2](./Lab8/6.png)

Code is given below

```tl-verilog
 //INSTRUCTION TYPES DECODE         
@1
  $is_u_instr = $instr[6:2] ==? 5'b0x101;
         
  $is_s_instr = $instr[6:2] ==? 5'b0100x;
         
  $is_r_instr = $instr[6:2] ==? 5'b01011 ||
                       $instr[6:2] ==? 5'b011x0 ||
                       $instr[6:2] ==? 5'b10100;
         
  $is_j_instr = $instr[6:2] ==? 5'b11011;
         
  $is_i_instr = $instr[6:2] ==? 5'b0000x ||
                       $instr[6:2] ==? 5'b001x0 ||
                       $instr[6:2] ==? 5'b11001;
         
  $is_b_instr = $instr[6:2] ==? 5'b11000;
         
  //INSTRUCTION IMMEDIATE DECODE
  $imm[31:0] = $is_i_instr ? {{21{$instr[31]}}, $instr[30:20]} :
                      $is_s_instr ? {{21{$instr[31]}}, $instr[30:25], $instr[11:7]} :
                      $is_b_instr ? {{20{$instr[31]}}, $instr[7], $instr[30:25], $instr[11:8], 1'b0} :
                      $is_u_instr ? {$instr[31:12], 12'b0} :
                      $is_j_instr ? {{12{$instr[31]}}, $instr[19:12], $instr[20], $instr[30:21], 1'b0} :
                                    32'b0;
         
         
         
         
         
  //INSTRUCTION FIELD DECODE
  $rs2_valid = $is_r_instr || $is_s_instr || $is_b_instr;
  ?$rs2_valid
    $rs2[4:0] = $instr[24:20];
            
  $rs1_valid = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
  ?$rs1_valid
    $rs1[4:0] = $instr[19:15];
         
  $funct3_valid = $is_r_instr || $is_i_instr || $is_s_instr || $is_b_instr;
  ?$funct3_valid
    $funct3[2:0] = $instr[14:12];
            
  $funct7_valid = $is_r_instr ;
  ?$funct7_valid
    $funct7[6:0] = $instr[31:25];
  $rd_valid = $is_r_instr || $is_i_instr || $is_u_instr || $is_j_instr;
  ?$rd_valid
    $rd[4:0] = $instr[11:7];
         
         
   //INSTRUCTION DECODE
  $opcode[6:0] = $instr[6:0];
         
  $dec_bits [10:0] = {$funct7[5], $funct3, $opcode};
  $is_beq = $dec_bits ==? 11'bx_000_1100011;
  $is_bne = $dec_bits ==? 11'bx_001_1100011;
  $is_blt = $dec_bits ==? 11'bx_100_1100011;
  $is_bge = $dec_bits ==? 11'bx_101_1100011;
  $is_bltu = $dec_bits ==? 11'bx_110_1100011;
  $is_bgeu = $dec_bits ==? 11'bx_111_1100011;
  $is_addi = $dec_bits ==? 11'bx_000_0010011;
  $is_add = $dec_bits ==? 11'b0_000_0110011;
         
  `BOGUS_USE ($is_beq $is_bne $is_blt $is_bge $is_bltu $is_bgeu $is_addi $is_add)
```
### Instructions to be Decoded are as follows:- 
![Step 2](./Lab8/7.png)
 
Instruction Decoding happens in various stages
- 1. INSTRUCTION TYPES DECODE :- In the Instruction Decode logic, each instruction is decoded to determine its type, any immediate values, and the specific field types. The opcode is converted into the corresponding instruction, with all bit values interpreted according to the RISC-V ISA. The decoding process begins by identifying the instruction type using 5 bits from `instr[6:2]`. The lower two bits (`instr[1:0]`) are always set to `11` for Base integer instructions. 

- 2. INSTRUCTION IMMEDIATE DECODE :- The instruction sets have an immediate field. In order to decoder this field we use the following code:-

- 3. INSTRUCTION FIELD DECODE AND INSTRUCTION DECODE :- Other instruction fields like funct7, rs2, rs1, funct3, rd and opcode are extracted from the 32-bit instruction based on the instruction type. We collect all the bit values of funct7, funct3, opcode, rs2, rs1 and rd into a single vector and then decode the type of instruction. At this point valid condtions need to be defined for fields like rs1, rs2, funct3 and funct7 because they are unique to only certain instruction types.

Generated block diagram and waveform for the instruction Instruction Decode is shown below
![Step 2](./Lab8/8.png)



### 4:- Register File Read

Most instructions, particularly arithmetic ones, operate on source registers, requiring a read from these registers. The CPU's register file supports two simultaneous reads for the source operands (rs1 and rs2) and one write per cycle to the destination register. Inputs `rs1` and `rs2` are fed into the register file, producing the corresponding register contents as outputs. Enable bits are set based on the validity of rs1 and rs2 conditions defined earlier. This setup, known as a 2-port register file, allows reading from two registers simultaneously. The read instructions are stored in registers and then sent to the ALU for processing.

Code is given below

```tl-verilog
//REGISTER FILE READ
$rf_wr_en = 1'b0;
$rf_wr_index[4:0] = 5'b0;
$rf_rd_en1 = $rs1_valid;
$rf_rd_index1[4:0] = $rs1;
$rf_rd_en2 = $rs2_valid;
$rf_rd_index2[4:0] = $rs2;
         
$src1_value[31:0] = $rf_rd_data1;
$src2_value[31:0] = $rf_rd_data2;
```
Generated block diagram and waveform for the instruction Instruction Decode is shown below
![Step 2](./Lab8/20.png)
![Step 2](./Lab8/9.png)

### 5:- Arithmetic and logic Unit(ALU)

The Arithmetic Logic Unit (ALU) is responsible for computing results based on the chosen operation. It processes the data from two registers provided by the register file, performs the corresponding arithmetic operation, and then writes the ALU's result back to memory via the register file's write port. Currently, the code supports only ADD and ADDI operations for executing the test code. All operations will be added at a later step.

Code is given below

```tl-verilog
//ARITHMETIC AND LOGIC UNIT (ALU)
$result[31:0] = $is_addi ? $src1_value + $imm :
              $is_add ? $src1_value + $src2_value :
                32'bx ;
```
Generated block diagram and waveform for the instruction Instruction Decode is shown below
![Step 2](./Lab8/21.png)
![Step 2](./Lab8/10.png)

### 6:- Register File Write

This step is crucial for handling instructions that require storing the output in a destination register (rd). The ALU's result is written back to memory through the register_file_write port, with the register_file_write_enable signal determined by the validity of the destination register (`rd`). The register_file_write_index then assigns the value from the destination register (rd) to the appropriate memory location. Since the RISC-V architecture has a hardwired x0 register, which is always zero, an additional condition is implemented to prevent any write operations to the x0 register. After the ALU completes its operations on the register values, these results may need to be written back into the registers. This process ensures that no write occurs to x0, maintaining its constant value of zero.

Block diagram of a 2-port Register File, with 2 Read and 1 Write per cycle:
![Step 2](./Lab8/11.png)

General Block Diagram of Register File and ALU:

![Step 2](./Lab8/12.png)

Code is given below

```tl-verilog
//REGISTER FILE WRITE
$rf_wr_en = $rd_valid && $rd != 5'b0;
$rf_wr_index[4:0] = $rd;
$rf_wr_data[31:0] = $result;
```
Generated block diagram and waveform for the instruction Instruction Decode is shown below
![Step 2](./Lab8/22.png)
![Step 2](./Lab8/13.png)

### 7:- Memory File
In addition to all of these, we also have a Memory file for which we have load and store instructions. The Store instruction is going to write a value fetched from the register file into the memory. The Load instruction is going to access the memory, take the value from it and them load it into the register file

### 8:- Branch Instruction

The final step involves adding support for branch instructions. In the RISC-V ISA, branches are conditional, meaning a specific branch is taken based on a certain condition. Additionally, the branch target PC must be calculated, and if the branch is taken, the PC will update to this new branch target when necessary.


Code is given below

```tl-verilog
//BRANCH INSTRUCTIONS 1
$taken_branch = $is_beq ? ($src1_value == $src2_value):
$is_bne ? ($src1_value != $src2_value):
$is_blt ? (($src1_value < $src2_value) ^ ($src1_value[31] != $src2_value[31])):
$is_bge ? (($src1_value >= $src2_value) ^ ($src1_value[31] != $src2_value[31])):
$is_bltu ? ($src1_value < $src2_value):
$is_bgeu ? ($src1_value >= $src2_value):
                                    1'b0;
`BOGUS_USE($taken_branch)
         
//BRANCH INSTRUCTIONS 2
 $br_target_pc[31:0] = $pc +$imm;
```
Generated block diagram and waveform for the instruction Instruction Decode is shown below
![Step 2](./Lab8/14.png)
</details>


<details>
<summary><strong>Laboratory 9:</strong> Complete pipelined RISCV CPU Micro Architecture </summary>

### Pipelining the RISC-V CPU Core
The RISC-V core designed is divided into 5 pipeline stages. Pipelining in Makerchip is extremely simple. To define a pipeline use the following syntax:

```tl-verilog
|<pipeline_name>
  @<pipeline_stage>
    instruction1 in the current stage
    instruction2 in the current stage
    .
    .
  @<pipeline_stage>
    instruction1 in the current stage
    instruction2 in the current stage
    .
    .

```
 Staging in a pipeline is a physical attribute with no impact to behaviour. At this point support for register file bypass is provided. 

 ### Load/Store Instructions
 Load/store and jump support is added along with the following two extra lines of code to test load and store.
 
```tl-verilog
m4_asm(SW, r0, r10, 10000)
m4_asm(LW, r17, r0, 10000)
```

![Step 2](./Lab9/1.png)

##  Testing the core with a Testbench
Now that the implementation is complete, a simple testbench statement can be added to ensure whether the core is working correctly or not. The "passed" and "failed" signals are used to communicate with the Makerchip platform to control the simulation. It tells the platform whther the simulation passed without any errors, failed with a list of errors that can be inferred from the log files, and hence to stop the simulation, if failed.

When the following line of code as mentioned below is added on Makerchip, the simulation will pass only if the value stored in r10 = sum of numbers from 1 to 9.
 
```tl-verilog
*passed = |cpu/xreg[17]>>5$value == (1+2+3+4+5+6+7+8+9);
```

![Step 2](./Lab9/7.png)
![Step 2](./Lab9/8.png)

Here, in the instruction memory, register r10 has been used to store the sum value. The simulation passed message can be seen under the "Log" tab. We have used ">>5" (ahead by 5) operator, because instead of stopping the simulator immediately, we wait for a couple of more cycles so as to see a little bit more on the waveform.
![Step 2](./Lab9/4.png)

### CLK Waveform
![Step 2](./Lab9/10.png)
### Reset Waveform
![Step 2](./Lab9/11.png)

![Step 2](./Lab9/9.png)
- We can observe that values are are being incremented and final value is `2d` which is 45 in hex

We can observe the simulation passed message
## The VIZ Graphic Visualizer
As we can see from the diagram, the final sum output of numbers from 1 to 9 , ie equal to 45 has been stored in the register r10, and simultaneously written into memory address 16 (4 because of byte addressing).
![Step 2](./Lab9/5.png)

# Final RISC-V CPU Core Implementation
- The snapshot of the final output can be seen below.
![Step 2](./Lab9/2.png)

**Final Block Diagarm is as shown**
![Step 2](./Lab9/3.png)



#### **Observation**:- A 5-stage pipeline design, using `clk_yog`, computes the sum of numbers from 1 to 9 across various stages. The stages include Instruction Fetch, Instruction Decode, Execute, Memory Access, and Write-back. The entire process takes 58 cycles to complete.
</details>
<details>
<summary><strong>Laboratory 10:</strong> Converting TL-Verilog to Verilog and Simulating with a Testbench</summary>

### Objective:
The RISC-V processor was initially designed using TL-Verilog in the Makerchip IDE. To deploy this design on an FPGA, it must first be converted to standard Verilog. This conversion was achieved using the Sandpiper-SaaS compiler. Following the conversion, pre-synthesis simulations will be conducted using the GTKWave simulator to verify the design.
### Step-by-Step Procedure:

1. **Install Required Packages:**
Begin by installing the necessary packages using pip:
```bash
pip3 install pyyaml click sandpiper-saas
```
2. **Clone the github repo:** 
clone this repo containing VSDBabySoC design files and testbench. Move into the VSDBabySoc directory
```bash
git clone https://github.com/manili/VSDBabySoC.git
cd VSDBabySoc
```
![Step 2](./Lab10/1.png)

3. **Replace the rvmyth.tlv file in the VSDBabySoC Directory:** 
replace in src/module with the rvmth.tlv given [here](https://github.com/YogeshGoyyalA-1/Asic_Design/tree/main/Lab10/codes). or replace the code with the code given below and also change the testbench according to our makerchip code.

4. **Convert .tlv to .v using converter:**
Now we have written the code in TL-Verilog .tlv which is a high level language and we want to convert into low level verilog that is to translate .tlv definition of rvmyth into .v definition. To do so Run the following command as follows

```bash
sandpiper-saas -i ./src/module/*.tlv -o rvmyth.v --bestsv --noline -p verilog --outdir ./src/module/
```
![Step 2](./Lab10/2.png)

4. **Make the pre_synth_sim.vcd:**
We will create the pre_synth_sim.vcd by running the following command
```bash
make pre_synth_sim
```
The result of the simulation i.e the pre_synth_sim.vcd will be stored in the output/pre_synth_sim directory
![Step 2](./Lab10/3.png)

5 .**Now to compile and simulate RISC-V design run the following code:**
To compile and simulate vsdbabysoc design.

```bash
iverilog -o output/pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module
cd output
./pre_synth_sim.out
```
To generate pre_synth_sim.vcd file,which is our simulation waveform file.
![Step 2](./Lab10/4.png)

6. **To open the Simulation file in gtkwave tool:**
To do so run the follwowing command 
```bash
gtkwave pre_synth_sim.vcd
```
![Step 2](./Lab10/5.png)
### Pre-synthesis Simulation results:
Signals to plot are the following:

- clk_yog: This is the clock input to the RISC-V core.
- reset: This is the input reset signal to the RISC-V core.
- OUT[9:0]: This is the 10-bit output [9:0] OUT port of the RISC-V core. This port comes from the RISC-V register #14, originally.

Our aim is to verify whether the waveform which we obtained by running the .tlv in makerchip and the waveforms obtained by converting .tlv to .v then simulating it on gtkwave are same or not. We will verify this with the help of below waveforms which includes the one obtained in the previous labs and the one which we obtained from gtkwave

### Waveforms from Makerchip platform IDE by running .tlv file for comparison
**Clk Waveform**
![Step 2](./Lab10/10.png)
**Reset Waveform**
![Step 2](./Lab10/11.png)
**Final Output**
![Step 2](./Lab10/9.png)

**Observation** :- We can see the gradual increment in sum from 0 to 9 in the end the sum of numbers from 0 to 9 is 45 which is `Ox2D` in hexadecimal which is stored in the register 14

### Waveforms from GTKwave platform by running .v file after conversion
**Clk Waveform**
![Step 2](./Lab10/6.png)
**Reset Waveform**
![Step 2](./Lab10/7.png)
**Final Output**
![Step 2](./Lab10/8.png)

**Observation** :- We can see the gradual increment in sum from 0 to 9 in out[9:0] in the end the sum of numbers from 0 to 9 is 45 which is `Ox2D` in hexadecimal

### Observation:- We have verified our code for the processor works in the intended way as the output waveforms that we obtained from .tlv file and after conversion to low level .v file using gtkwave gives the same waveforms in both the cases as intended. 
</details>

<details>
<summary><strong>Laboratory 11:</strong>To generate waveform for DAC and PLL peripheral for Risc-V processor.</summary>

### BabySoC Simulation

Developing and simulating the complete micro-architecture of a RISC-V CPU is a complex task. For this simulation, we'll focus on incorporating two key IP blocks: **PLL** and **DAC**.

---

#### **Phase-Locked Loop (PLL)**

A Phase-Locked Loop (PLL) is an electronic system that aligns the phase and frequency of an output signal with a reference signal. It generally consists of three primary components:

1. **Phase Detector:** Compares the phase of the reference signal with the output signal, generating an error signal based on their difference.
2. **Loop Filter:** Smooths the error signal, reducing noise and improving the system's stability.
3. **Voltage-Controlled Oscillator (VCO):** Adjusts its output frequency in response to the filtered error signal to minimize the phase difference.

PLLs are widely used in applications such as clock generation, frequency synthesis, and data recovery in communication systems.

#### **Digital-to-Analog Converter (DAC)**

A Digital-to-Analog Converter (DAC) converts digital signals (typically binary) into analog signals (such as voltage or current). This conversion is essential in systems where digital data needs to be interpreted by analog devices or for outputs that need to be perceived by humans, such as in audio and video devices.

DACs are commonly found in applications including audio playback, video display, and signal processing.

---

#### Files Required for BabySoC Simulation

Please click [here](https://github.com/Subhasis-Sahu/BabySoC_Simulation/tree/main) to clone the reposoitory which has the necessary files we need to for simulation

* **src/module:** Contains all RTL files and `testbench.v` needed to simulate the BabySoC design.
* **src/include:** Houses RTL files referenced in the main RTL files within `src/module` via `include` directives.

### To perform Funtional Simulation
- After cloning the repository replace the rvymth.v file with your required rvymth.v. Also modify the vsdbabysoc.v file to point to our core clock. 
- Follow the steps below to perform functional simulation
```bash
cd BabySoC_Simulation
```
```bash
iverilog -o ./pre_synth_sim.out -DPRE_SYNTH_SIM src/module/testbench.v -I src/include -I src/module/
```
```bash
./pre_synth_sim.out
```
```
gtkwave pre_synth_sim.vcd
```

![Step 2](./Lab11/4.png)

In the below screenshot, the output of the sum 1 to 9 can be observed after simulation that is the gradual increment from 0x00 to 0x2D in hexadecimal

![Step 2](./Lab11/5.png)

**VCO_IN** is the input clk reference signal to the PLL module.
**CLK** is the output clk signal from the PLL module.
**CLK_yog** is the clock used by the RISC-V CPU for the operations.
**RV_TO_DAC** is the output wire connected to the `Xreg[14]` register of the register file,
**OUT** is the analog signal coming out of the DAC unit.
**reset** is the reset signal for the RISC-V CPU.

### Observation:-