	component unsaved is
		port (
			clk_50_in_clk           : in std_logic := 'X'; -- clk
			clk_50_2_in_clk         : in std_logic := 'X'; -- clk
			clk_50_3_in_clk         : in std_logic := 'X'; -- clk
			reset_bridge_in_reset_n : in std_logic := 'X'  -- reset_n
		);
	end component unsaved;

	u0 : component unsaved
		port map (
			clk_50_in_clk           => CONNECTED_TO_clk_50_in_clk,           --       clk_50_in.clk
			clk_50_2_in_clk         => CONNECTED_TO_clk_50_2_in_clk,         --     clk_50_2_in.clk
			clk_50_3_in_clk         => CONNECTED_TO_clk_50_3_in_clk,         --     clk_50_3_in.clk
			reset_bridge_in_reset_n => CONNECTED_TO_reset_bridge_in_reset_n  -- reset_bridge_in.reset_n
		);

