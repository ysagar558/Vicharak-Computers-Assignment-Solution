# Vicharak-Computers-Assignment-Solution

Step 1: Setup the 8-bit CPU Simulator
Clone the repository.
git clone https://github.com/lightcode/8bit-computer.git

Step 2: Understand the 8-bit CPU Architecture
Review the Verilog code in the rtl/ directory.
Focus on machine.v to understand the CPU’s instruction set.
Identify the instruction set including data transfer, arithmetic, logical, branching, machine control, I/O, and stack operations.

Step 3: Design SimpleLang
Define the syntax and semantics for variable declarations, assignments, arithmetic operations, and conditionals.
Document the language constructs with examples (as provided in your description).

Step 4: Create a Lexer
A lexer converts the input SimpleLang code into tokens. 

Step 5: Develop a Parser
The parser will convert tokens into an Abstract Syntax Tree (AST).

Step 6: Generate Assembly Code
Traverse the AST to generate assembly code for the 8-bit CPU. This involves mapping high-level constructs to the CPU's instruction set.

Step 7: Integrate and Test
Integrate the lexer, parser, and code generator into a single compiler program.
Test the compiler with SimpleLang programs and verify the generated assembly code by running it on the 8-bit CPU simulator.


