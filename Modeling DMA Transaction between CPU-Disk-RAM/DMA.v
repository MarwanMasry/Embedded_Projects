module DMA
	(
		input CLK , DREQ , HLDA, IOR ,IOW ,
		input [9:0] DRAM_startingAddress,
		input [9:0] IO_startingAddress,
		input [9:0] addressCounter,
		output reg  IOR_command , IOW_command ,MEMR , MEMW, DACK , HRQ , EOP,
		output reg  [9:0]  addressBus_IO,
		output reg  [9:0]  addressBus_DRAM,	
		inout  wire [31:0] dataBus		
	);
	
	
	/* Temp Variables */
	reg[9:0] i;
	reg[9:0] j;
	reg endOfProcess;
		
	/* Initial values */
	initial 
		begin
		IOR_command = 0;
		IOW_command = 0;
		MEMR = 0;
		MEMW = 0;
		DACK = 0;
		HRQ  = 0;
		i = 0;

	end
	
	/* Always Block	 */
	always@(posedge CLK)
	begin
		if( DREQ == 1)
		begin
			HRQ = 1 ;
		end
		
		if( HLDA == 1)
		begin
			DACK = 1 ;
			
			if(IOR == 1 && endOfProcess == 0)
			begin
				IOR_command = 1;
				MEMW = 1;

				addressBus_DRAM = DRAM_startingAddress + i ;
				addressBus_IO = IO_startingAddress + i ;
				i = i+1;
				j =j -1 ;
				
				if( j == 0)
				begin
					endOfProcess = 1;
					#2
					endOfProcess = 0;
					#2
					endOfProcess = 1;					
				end
				
			end
			
			if(IOW == 1 && endOfProcess == 0)
			begin
				IOW_command = 1;
				MEMR = 1;
				
				addressBus_DRAM = DRAM_startingAddress + i ;
				addressBus_IO = IO_startingAddress + i ;
				i = i+1;
				j =j -1 ;
				
				if( j == 0)
				begin
					endOfProcess = 1;
					#2
					endOfProcess = 0;
					#2
					endOfProcess = 1;					
				end
			end
		end
	end
	
	/* Reset Block */
	always @(endOfProcess)
	begin
		IOR_command = 0;
		IOW_command = 0;
		MEMR = 0;
		MEMW = 0;
		DACK = 0;
		HRQ  = 0;
		i = 0 ;

		EOP = 1 ;
		#15
		EOP = 0;
	end
	
	always@(IOR or IOW)
	begin
		#3
		j = addressCounter;
		endOfProcess = 0;
	end
	
endmodule 
