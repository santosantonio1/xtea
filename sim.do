if {[file isdirectory work]} { vdel -all -lib work }
vlib work
vmap work work

vlog -work work ./hdl/tb.v
vlog -work work ./hdl/xtea_top.v
vlog -work work ./hdl/xtea_enc.v
vlog -work work ./hdl/xtea_dec.v

vsim -voptargs=+acc=lprn -t ns work.tb

set StdArithNoWarnings 1
set StdVitalGlitchNoWarnings 1

do wave.do 

run 15 us