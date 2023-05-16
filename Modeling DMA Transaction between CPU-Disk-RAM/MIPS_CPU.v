module MIPS_CPU
	(
		input  CLK , HRQ, EOP , update,
		output reg HLDA, IOR ,IOW ,
		output reg [9:0] DRAM_startingAddress,
		output reg [9:0] IO_startingAddress,
		output reg [9:0] addressCounter
	);
	
	 /* Code Variables */
	reg  [31:0] PC, RegisterFile[0:31],InsturctionMemory[0:1023],IR,ALUOut;
	wire [4:0] rs,rt,rd;
	wire [31:0] rsRegister , rtRegister , rdRegister;
	wire [5:0] opCode; 
	
	/* Temp Variables */
	reg [9:0] customDRAM_StartingAddress;
	reg [9:0] customIO_StartingAddress;	
	reg [9:0] customAddressCounter;
	reg customIOR , customIOW;
	
	
	/* Decoding The Instruction	*/
	assign rs = IR[25:21];
	assign rt = IR[20:16];
	assign rd = IR[15:11];
	assign opCode = IR[31:26];
	
	/* Register Values */
	assign rsRegister = RegisterFile[rs];
	assign rtRegister = RegisterFile[rt];
	assign rdRegister = RegisterFile[rd];
	
	/* Initializations */
	initial
    begin
		PC = 0;
		HLDA = 0; 
		IOR = 0;
		IOW = 0;
		
		/* Test values for Testings*/
		RegisterFile[1] = 20;
		RegisterFile[2] = 10;
		
		/* Instructions Binaries */
		
		/*	add  $r1 ,$r2 ,$r3 */
		InsturctionMemory[0] = 32'b 0000_0000_0010_0010_0001_1000_0010_0000;
		/*	sub  $r1 ,$r2 ,$r3 */	
		InsturctionMemory[1] = 32'b 0000_0000_0010_0010_0001_1000_0010_0010;    
		/*	and  $r1 ,$r2 ,$r3 */
		InsturctionMemory[2] = 32'b 0000_0000_0010_0010_0001_1000_0010_0100;    
		/*	or  $r1 ,$r2 ,$r3 */
		InsturctionMemory[3] = 32'b 0000_0000_0010_0010_0001_1000_0010_0101;  
		/* 5th location in memory is zeros */
		InsturctionMemory[4] = 32'b0;
		InsturctionMemory[5] = 32'b0;
		InsturctionMemory[6] = 32'b0; 
		
	end
	
 	/* Block for Instructions Executions  */
	always @(posedge CLK)
		begin

			/* Save instruction and increment PC */
			IR <= InsturctionMemory[PC>>2];
			PC <= PC+4;
			
			/* Do ALU operation */
			if(opCode == 6'b000000)
			begin
				case(IR[5:0])
					32: ALUOut <= rsRegister + rtRegister;
					34: ALUOut <= rsRegister - rtRegister;
					36: ALUOut <= rsRegister & rtRegister;
					37: ALUOut <= rsRegister | rtRegister;
				endcase
				/* Save value in rd in register file */
				RegisterFile[rd] <= ALUOut;	 
			end 			
		end
		
		 /* Block for DMA Handling  */
		always @(posedge CLK or HRQ)
		begin
			if( HRQ == 1)
			begin
				HLDA = 1 ;
			end		
		end
		
		always @(negedge EOP)
		begin
			HLDA = 0; 
		end	
		
		always@( negedge update)
		begin
			DRAM_startingAddress = customDRAM_StartingAddress ;
			IO_startingAddress   = customIO_StartingAddress;			
			addressCounter = customAddressCounter;
			IOR = customIOR;
			IOW = customIOW;			
		end
		
		
endmodule






