	component nios_system is
		port (
			audio_clk_out_clk                                     : out   std_logic;                                        -- clk
			audio_config_external_interface_SDAT                  : inout std_logic                     := 'X';             -- SDAT
			audio_config_external_interface_SCLK                  : out   std_logic;                                        -- SCLK
			audio_external_interface_ADCDAT                       : in    std_logic                     := 'X';             -- ADCDAT
			audio_external_interface_ADCLRCK                      : in    std_logic                     := 'X';             -- ADCLRCK
			audio_external_interface_BCLK                         : in    std_logic                     := 'X';             -- BCLK
			audio_external_interface_DACDAT                       : out   std_logic;                                        -- DACDAT
			audio_external_interface_DACLRCK                      : in    std_logic                     := 'X';             -- DACLRCK
			camera_video_decoder_external_interface_TD_CLK27      : in    std_logic                     := 'X';             -- TD_CLK27
			camera_video_decoder_external_interface_TD_DATA       : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- TD_DATA
			camera_video_decoder_external_interface_TD_HS         : in    std_logic                     := 'X';             -- TD_HS
			camera_video_decoder_external_interface_TD_VS         : in    std_logic                     := 'X';             -- TD_VS
			camera_video_decoder_external_interface_clk27_reset   : in    std_logic                     := 'X';             -- clk27_reset
			camera_video_decoder_external_interface_TD_RESET      : out   std_logic;                                        -- TD_RESET
			camera_video_decoder_external_interface_overflow_flag : out   std_logic;                                        -- overflow_flag
			char_lcd_external_interface_DATA                      : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- DATA
			char_lcd_external_interface_ON                        : out   std_logic;                                        -- ON
			char_lcd_external_interface_BLON                      : out   std_logic;                                        -- BLON
			char_lcd_external_interface_EN                        : out   std_logic;                                        -- EN
			char_lcd_external_interface_RS                        : out   std_logic;                                        -- RS
			char_lcd_external_interface_RW                        : out   std_logic;                                        -- RW
			clk_50_2_in_clk                                       : in    std_logic                     := 'X';             -- clk
			clk_50_3_in_clk                                       : in    std_logic                     := 'X';             -- clk
			clk_50_in_clk                                         : in    std_logic                     := 'X';             -- clk
			flash_bridge_out_tcm_address_out                      : out   std_logic_vector(22 downto 0);                    -- tcm_address_out
			flash_bridge_out_tcm_read_n_out                       : out   std_logic_vector(0 downto 0);                     -- tcm_read_n_out
			flash_bridge_out_tcm_write_n_out                      : out   std_logic_vector(0 downto 0);                     -- tcm_write_n_out
			flash_bridge_out_tcm_data_out                         : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- tcm_data_out
			flash_bridge_out_tcm_chipselect_n_out                 : out   std_logic_vector(0 downto 0);                     -- tcm_chipselect_n_out
			green_leds_external_interface_export                  : out   std_logic_vector(8 downto 0);                     -- export
			hex3_hex0_external_interface_HEX0                     : out   std_logic_vector(6 downto 0);                     -- HEX0
			hex3_hex0_external_interface_HEX1                     : out   std_logic_vector(6 downto 0);                     -- HEX1
			hex3_hex0_external_interface_HEX2                     : out   std_logic_vector(6 downto 0);                     -- HEX2
			hex3_hex0_external_interface_HEX3                     : out   std_logic_vector(6 downto 0);                     -- HEX3
			hex7_hex4_external_interface_HEX4                     : out   std_logic_vector(6 downto 0);                     -- HEX4
			hex7_hex4_external_interface_HEX5                     : out   std_logic_vector(6 downto 0);                     -- HEX5
			hex7_hex4_external_interface_HEX6                     : out   std_logic_vector(6 downto 0);                     -- HEX6
			hex7_hex4_external_interface_HEX7                     : out   std_logic_vector(6 downto 0);                     -- HEX7
			mtl_clk_out_clk                                       : out   std_logic;                                        -- clk
			mtl_controller_external_interface_CLK                 : out   std_logic;                                        -- CLK
			mtl_controller_external_interface_HS                  : out   std_logic;                                        -- HS
			mtl_controller_external_interface_VS                  : out   std_logic;                                        -- VS
			mtl_controller_external_interface_DATA_EN             : out   std_logic;                                        -- DATA_EN
			mtl_controller_external_interface_R                   : out   std_logic_vector(7 downto 0);                     -- R
			mtl_controller_external_interface_G                   : out   std_logic_vector(7 downto 0);                     -- G
			mtl_controller_external_interface_B                   : out   std_logic_vector(7 downto 0);                     -- B
			ps2_key_external_interface_CLK                        : inout std_logic                     := 'X';             -- CLK
			ps2_key_external_interface_DAT                        : inout std_logic                     := 'X';             -- DAT
			ps2_mouse_external_interface_CLK                      : inout std_logic                     := 'X';             -- CLK
			ps2_mouse_external_interface_DAT                      : inout std_logic                     := 'X';             -- DAT
			pushbuttons_external_interface_export                 : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			red_leds_external_interface_export                    : out   std_logic_vector(17 downto 0);                    -- export
			reset_bridge_in_reset_n                               : in    std_logic                     := 'X';             -- reset_n
			sd_card_conduit_end_b_SD_cmd                          : inout std_logic                     := 'X';             -- b_SD_cmd
			sd_card_conduit_end_b_SD_dat                          : inout std_logic                     := 'X';             -- b_SD_dat
			sd_card_conduit_end_b_SD_dat3                         : inout std_logic                     := 'X';             -- b_SD_dat3
			sd_card_conduit_end_o_SD_clock                        : out   std_logic;                                        -- o_SD_clock
			sdram_clk_out_clk                                     : out   std_logic;                                        -- clk
			sdram_wire_addr                                       : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba                                         : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n                                      : out   std_logic;                                        -- cas_n
			sdram_wire_cke                                        : out   std_logic;                                        -- cke
			sdram_wire_cs_n                                       : out   std_logic;                                        -- cs_n
			sdram_wire_dq                                         : inout std_logic_vector(31 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm                                        : out   std_logic_vector(3 downto 0);                     -- dqm
			sdram_wire_ras_n                                      : out   std_logic;                                        -- ras_n
			sdram_wire_we_n                                       : out   std_logic;                                        -- we_n
			serial_port_external_interface_RXD                    : in    std_logic                     := 'X';             -- RXD
			serial_port_external_interface_TXD                    : out   std_logic;                                        -- TXD
			sram_external_interface_DQ                            : inout std_logic_vector(15 downto 0) := (others => 'X'); -- DQ
			sram_external_interface_ADDR                          : out   std_logic_vector(19 downto 0);                    -- ADDR
			sram_external_interface_LB_N                          : out   std_logic;                                        -- LB_N
			sram_external_interface_UB_N                          : out   std_logic;                                        -- UB_N
			sram_external_interface_CE_N                          : out   std_logic;                                        -- CE_N
			sram_external_interface_OE_N                          : out   std_logic;                                        -- OE_N
			sram_external_interface_WE_N                          : out   std_logic;                                        -- WE_N
			switches_external_interface_export                    : in    std_logic_vector(17 downto 0) := (others => 'X'); -- export
			sys_clk_out_clk                                       : out   std_logic;                                        -- clk
			vga_clk_out_clk                                       : out   std_logic                                         -- clk
		);
	end component nios_system;

	u0 : component nios_system
		port map (
			audio_clk_out_clk                                     => CONNECTED_TO_audio_clk_out_clk,                                     --                           audio_clk_out.clk
			audio_config_external_interface_SDAT                  => CONNECTED_TO_audio_config_external_interface_SDAT,                  --         audio_config_external_interface.SDAT
			audio_config_external_interface_SCLK                  => CONNECTED_TO_audio_config_external_interface_SCLK,                  --                                        .SCLK
			audio_external_interface_ADCDAT                       => CONNECTED_TO_audio_external_interface_ADCDAT,                       --                audio_external_interface.ADCDAT
			audio_external_interface_ADCLRCK                      => CONNECTED_TO_audio_external_interface_ADCLRCK,                      --                                        .ADCLRCK
			audio_external_interface_BCLK                         => CONNECTED_TO_audio_external_interface_BCLK,                         --                                        .BCLK
			audio_external_interface_DACDAT                       => CONNECTED_TO_audio_external_interface_DACDAT,                       --                                        .DACDAT
			audio_external_interface_DACLRCK                      => CONNECTED_TO_audio_external_interface_DACLRCK,                      --                                        .DACLRCK
			camera_video_decoder_external_interface_TD_CLK27      => CONNECTED_TO_camera_video_decoder_external_interface_TD_CLK27,      -- camera_video_decoder_external_interface.TD_CLK27
			camera_video_decoder_external_interface_TD_DATA       => CONNECTED_TO_camera_video_decoder_external_interface_TD_DATA,       --                                        .TD_DATA
			camera_video_decoder_external_interface_TD_HS         => CONNECTED_TO_camera_video_decoder_external_interface_TD_HS,         --                                        .TD_HS
			camera_video_decoder_external_interface_TD_VS         => CONNECTED_TO_camera_video_decoder_external_interface_TD_VS,         --                                        .TD_VS
			camera_video_decoder_external_interface_clk27_reset   => CONNECTED_TO_camera_video_decoder_external_interface_clk27_reset,   --                                        .clk27_reset
			camera_video_decoder_external_interface_TD_RESET      => CONNECTED_TO_camera_video_decoder_external_interface_TD_RESET,      --                                        .TD_RESET
			camera_video_decoder_external_interface_overflow_flag => CONNECTED_TO_camera_video_decoder_external_interface_overflow_flag, --                                        .overflow_flag
			char_lcd_external_interface_DATA                      => CONNECTED_TO_char_lcd_external_interface_DATA,                      --             char_lcd_external_interface.DATA
			char_lcd_external_interface_ON                        => CONNECTED_TO_char_lcd_external_interface_ON,                        --                                        .ON
			char_lcd_external_interface_BLON                      => CONNECTED_TO_char_lcd_external_interface_BLON,                      --                                        .BLON
			char_lcd_external_interface_EN                        => CONNECTED_TO_char_lcd_external_interface_EN,                        --                                        .EN
			char_lcd_external_interface_RS                        => CONNECTED_TO_char_lcd_external_interface_RS,                        --                                        .RS
			char_lcd_external_interface_RW                        => CONNECTED_TO_char_lcd_external_interface_RW,                        --                                        .RW
			clk_50_2_in_clk                                       => CONNECTED_TO_clk_50_2_in_clk,                                       --                             clk_50_2_in.clk
			clk_50_3_in_clk                                       => CONNECTED_TO_clk_50_3_in_clk,                                       --                             clk_50_3_in.clk
			clk_50_in_clk                                         => CONNECTED_TO_clk_50_in_clk,                                         --                               clk_50_in.clk
			flash_bridge_out_tcm_address_out                      => CONNECTED_TO_flash_bridge_out_tcm_address_out,                      --                        flash_bridge_out.tcm_address_out
			flash_bridge_out_tcm_read_n_out                       => CONNECTED_TO_flash_bridge_out_tcm_read_n_out,                       --                                        .tcm_read_n_out
			flash_bridge_out_tcm_write_n_out                      => CONNECTED_TO_flash_bridge_out_tcm_write_n_out,                      --                                        .tcm_write_n_out
			flash_bridge_out_tcm_data_out                         => CONNECTED_TO_flash_bridge_out_tcm_data_out,                         --                                        .tcm_data_out
			flash_bridge_out_tcm_chipselect_n_out                 => CONNECTED_TO_flash_bridge_out_tcm_chipselect_n_out,                 --                                        .tcm_chipselect_n_out
			green_leds_external_interface_export                  => CONNECTED_TO_green_leds_external_interface_export,                  --           green_leds_external_interface.export
			hex3_hex0_external_interface_HEX0                     => CONNECTED_TO_hex3_hex0_external_interface_HEX0,                     --            hex3_hex0_external_interface.HEX0
			hex3_hex0_external_interface_HEX1                     => CONNECTED_TO_hex3_hex0_external_interface_HEX1,                     --                                        .HEX1
			hex3_hex0_external_interface_HEX2                     => CONNECTED_TO_hex3_hex0_external_interface_HEX2,                     --                                        .HEX2
			hex3_hex0_external_interface_HEX3                     => CONNECTED_TO_hex3_hex0_external_interface_HEX3,                     --                                        .HEX3
			hex7_hex4_external_interface_HEX4                     => CONNECTED_TO_hex7_hex4_external_interface_HEX4,                     --            hex7_hex4_external_interface.HEX4
			hex7_hex4_external_interface_HEX5                     => CONNECTED_TO_hex7_hex4_external_interface_HEX5,                     --                                        .HEX5
			hex7_hex4_external_interface_HEX6                     => CONNECTED_TO_hex7_hex4_external_interface_HEX6,                     --                                        .HEX6
			hex7_hex4_external_interface_HEX7                     => CONNECTED_TO_hex7_hex4_external_interface_HEX7,                     --                                        .HEX7
			mtl_clk_out_clk                                       => CONNECTED_TO_mtl_clk_out_clk,                                       --                             mtl_clk_out.clk
			mtl_controller_external_interface_CLK                 => CONNECTED_TO_mtl_controller_external_interface_CLK,                 --       mtl_controller_external_interface.CLK
			mtl_controller_external_interface_HS                  => CONNECTED_TO_mtl_controller_external_interface_HS,                  --                                        .HS
			mtl_controller_external_interface_VS                  => CONNECTED_TO_mtl_controller_external_interface_VS,                  --                                        .VS
			mtl_controller_external_interface_DATA_EN             => CONNECTED_TO_mtl_controller_external_interface_DATA_EN,             --                                        .DATA_EN
			mtl_controller_external_interface_R                   => CONNECTED_TO_mtl_controller_external_interface_R,                   --                                        .R
			mtl_controller_external_interface_G                   => CONNECTED_TO_mtl_controller_external_interface_G,                   --                                        .G
			mtl_controller_external_interface_B                   => CONNECTED_TO_mtl_controller_external_interface_B,                   --                                        .B
			ps2_key_external_interface_CLK                        => CONNECTED_TO_ps2_key_external_interface_CLK,                        --              ps2_key_external_interface.CLK
			ps2_key_external_interface_DAT                        => CONNECTED_TO_ps2_key_external_interface_DAT,                        --                                        .DAT
			ps2_mouse_external_interface_CLK                      => CONNECTED_TO_ps2_mouse_external_interface_CLK,                      --            ps2_mouse_external_interface.CLK
			ps2_mouse_external_interface_DAT                      => CONNECTED_TO_ps2_mouse_external_interface_DAT,                      --                                        .DAT
			pushbuttons_external_interface_export                 => CONNECTED_TO_pushbuttons_external_interface_export,                 --          pushbuttons_external_interface.export
			red_leds_external_interface_export                    => CONNECTED_TO_red_leds_external_interface_export,                    --             red_leds_external_interface.export
			reset_bridge_in_reset_n                               => CONNECTED_TO_reset_bridge_in_reset_n,                               --                         reset_bridge_in.reset_n
			sd_card_conduit_end_b_SD_cmd                          => CONNECTED_TO_sd_card_conduit_end_b_SD_cmd,                          --                     sd_card_conduit_end.b_SD_cmd
			sd_card_conduit_end_b_SD_dat                          => CONNECTED_TO_sd_card_conduit_end_b_SD_dat,                          --                                        .b_SD_dat
			sd_card_conduit_end_b_SD_dat3                         => CONNECTED_TO_sd_card_conduit_end_b_SD_dat3,                         --                                        .b_SD_dat3
			sd_card_conduit_end_o_SD_clock                        => CONNECTED_TO_sd_card_conduit_end_o_SD_clock,                        --                                        .o_SD_clock
			sdram_clk_out_clk                                     => CONNECTED_TO_sdram_clk_out_clk,                                     --                           sdram_clk_out.clk
			sdram_wire_addr                                       => CONNECTED_TO_sdram_wire_addr,                                       --                              sdram_wire.addr
			sdram_wire_ba                                         => CONNECTED_TO_sdram_wire_ba,                                         --                                        .ba
			sdram_wire_cas_n                                      => CONNECTED_TO_sdram_wire_cas_n,                                      --                                        .cas_n
			sdram_wire_cke                                        => CONNECTED_TO_sdram_wire_cke,                                        --                                        .cke
			sdram_wire_cs_n                                       => CONNECTED_TO_sdram_wire_cs_n,                                       --                                        .cs_n
			sdram_wire_dq                                         => CONNECTED_TO_sdram_wire_dq,                                         --                                        .dq
			sdram_wire_dqm                                        => CONNECTED_TO_sdram_wire_dqm,                                        --                                        .dqm
			sdram_wire_ras_n                                      => CONNECTED_TO_sdram_wire_ras_n,                                      --                                        .ras_n
			sdram_wire_we_n                                       => CONNECTED_TO_sdram_wire_we_n,                                       --                                        .we_n
			serial_port_external_interface_RXD                    => CONNECTED_TO_serial_port_external_interface_RXD,                    --          serial_port_external_interface.RXD
			serial_port_external_interface_TXD                    => CONNECTED_TO_serial_port_external_interface_TXD,                    --                                        .TXD
			sram_external_interface_DQ                            => CONNECTED_TO_sram_external_interface_DQ,                            --                 sram_external_interface.DQ
			sram_external_interface_ADDR                          => CONNECTED_TO_sram_external_interface_ADDR,                          --                                        .ADDR
			sram_external_interface_LB_N                          => CONNECTED_TO_sram_external_interface_LB_N,                          --                                        .LB_N
			sram_external_interface_UB_N                          => CONNECTED_TO_sram_external_interface_UB_N,                          --                                        .UB_N
			sram_external_interface_CE_N                          => CONNECTED_TO_sram_external_interface_CE_N,                          --                                        .CE_N
			sram_external_interface_OE_N                          => CONNECTED_TO_sram_external_interface_OE_N,                          --                                        .OE_N
			sram_external_interface_WE_N                          => CONNECTED_TO_sram_external_interface_WE_N,                          --                                        .WE_N
			switches_external_interface_export                    => CONNECTED_TO_switches_external_interface_export,                    --             switches_external_interface.export
			sys_clk_out_clk                                       => CONNECTED_TO_sys_clk_out_clk,                                       --                             sys_clk_out.clk
			vga_clk_out_clk                                       => CONNECTED_TO_vga_clk_out_clk                                        --                             vga_clk_out.clk
		);

