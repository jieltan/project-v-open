############################################
# This simple script should fix the missing 
# links to the RISCV gnu toolchain
# Jielun Tan
# 07/21/2018
############################################

#!/usr/bin/bash
path=$(pwd)
for exe in riscv64-unknown-elf/bin/*; do
	ln -s $path/$exe bin/riscv64-unknown-elf-$(echo $exe | cut -d'/' -f3)
done

