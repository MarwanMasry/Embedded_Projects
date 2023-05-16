module IO_device
	(
		inout wire [31:0] dataBus,
		input wire [9:0]  addressBus_IO,
		input wire IOR_command , IOW_command , DACK , CLK,
		output reg DREQ
	);  
	
	/* Module Memory */
	reg [31:0] IO_device_memory[0:1023];
	
	/* Temp Variables */
	integer i;
	reg Start_Requisting_DMA;
	
	
	/* Initial value */
	initial 
	begin
		DREQ = 0;
	end
	
	 /* IO Device is in output mode we put data in data lines*/ 
	assign dataBus = (IOR_command)? IO_device_memory[addressBus_IO] : 32'bzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz; 
	
	
	/* Initializations */
	initial
	begin
		for(i = 0; i<1024 ; i = i+1)
		begin
			IO_device_memory[i] = i;
		end		
	end


	/* Always Block	 */
	always@(posedge CLK or addressBus_IO or dataBus)
	begin
		
		if( Start_Requisting_DMA == 1)
			DREQ = 1;	
		
		if( Start_Requisting_DMA == 0)
			DREQ = 0;	

		
		if(DACK == 1)
		begin			
			if( IOW_command == 1)
			begin
				IO_device_memory[addressBus_IO] = dataBus;
			end
			
		end		
	end
		
endmodule

