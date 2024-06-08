onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -divider XTEA_TOP
add wave -noupdate /tb/XTEA/clock
add wave -noupdate /tb/XTEA/reset
add wave -noupdate /tb/XTEA/start
add wave -noupdate /tb/XTEA/cfg
add wave -noupdate /tb/XTEA/busy
add wave -noupdate /tb/XTEA/ready
add wave -noupdate -radix hexadecimal /tb/XTEA/data_i
add wave -noupdate -radix hexadecimal /tb/XTEA/key
add wave -noupdate -radix hexadecimal /tb/XTEA/data_o
add wave -noupdate /tb/XTEA/EA
add wave -noupdate -divider ENC_DRIVER
add wave -noupdate /tb/XTEA/enc_r
add wave -noupdate /tb/XTEA/ENC_DRIVER/EA
add wave -noupdate -radix decimal /tb/XTEA/ENC_DRIVER/i
add wave -noupdate -radix hexadecimal /tb/XTEA/ENC_DRIVER/data_o
add wave -noupdate -divider DEC_DRIVER
add wave -noupdate /tb/XTEA/dec_r
add wave -noupdate /tb/XTEA/DEC_DRIVER/EA
add wave -noupdate -radix decimal /tb/XTEA/DEC_DRIVER/i
add wave -noupdate -radix hexadecimal /tb/XTEA/DEC_DRIVER/data_o
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {845 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 2
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ns} {15750 ns}
