mkdir lib
./build/sosix_build.sh

csources=$(find ./kernel/modules/* -type f -name "*.c")
cppsources=$(find ./kernel/modules/* -type f -name "*.cpp")
headers=$(find ./include/* -type f -name "*.h")

libaries=$(find ./lib/* -type f -name "*.a")

cobjects=$(echo ${csources//\.c/.o})
cppobjects=$(echo ${cppsources//\.cpp/.o})

objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${cobjects}")
end=$((end+1))

mkdir bin
nasm -f elf ./kernel/arch/i386/boot.asm -o ./bin/boot.o
for i in $(seq 1 $end); do 
ta=$(echo ./bin/$(basename $(echo $cobjects | cut -d" " -f$i )))
tb=$(echo $csources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-inline-functions -nostdinc -fno-builtin -I./include/kernel -I./include/sosix -fstack-protector-strong -c -o $ta $tb
done
objb="${objb:1}"


objbcpp=''
charcpp=' '
endcpp=$(awk -F"${charcpp}" '{print NF-1}' <<< "${cppobjects}")
endcpp=$((endcpp+1))

for i in $(seq 1 $endcpp); do 
tacpp=$(echo ./bin/$(basename $(echo $cppobjects | cut -d" " -f$i )))
tbcpp=$(echo $cppsources | cut -d" " -f$i)
objbcpp="${objbcpp} ${tacpp}"
g++ -m32 -elf_i386 -Wall -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive -nostdlib -I./include/kernel -I./include/sosix -c -o $tacpp $tbcpp
done
objbcpp="${objbcpp:1}"


gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include/kernel -I./include/sosix -fno-stack-protector  -c -o ./bin/main.o ./kernel/main.c

export LD_LIBRARY_PATH=/home/runner/SlylockOS/
ld -T link.ld --verbose -m elf_i386 -o kernel.bin ./bin/main.o $objb $objbcpp ./bin/boot.o $libaries

rm -r iso

mkdir env
mkdir sys
mkdir tmp
echo '' >> sys/membuf

mkdir iso
mkdir iso/boot
mkdir iso/boot/grub

mv kernel.bin iso/boot/kernel.bin
echo 'set timeout-0' >> iso/boot/grub/grub.cfg
echo 'set default-0' >> iso/boot/grub/grub.cfg
echo 'menuentry "SlylockOS" {' >> iso/boot/grub/grub.cfg
echo '  multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
echo '  module  /boot/os.initrd' >> iso/boot/grub/grub.cfg
echo '  boot' >> iso/boot/grub/grub.cfg
echo '}' >> iso/boot/grub/grub.cfg
rm initrdgen
gcc initrdgen.c -o initrdgen
inp="readme ./lib/sosix.a ./sys/membuf ./tmp ./env"
res=''
for word in $inp; do
res="${res} ${word}"
res="${res} ${word}"
done
./initrdgen $res
mv ./initrd.img ./iso/boot/os.initrd
grub-mkrescue --output=SlylockOS.iso iso
rm -r bin
rm -r lib
rm -r iso
rm -r sys
rm -r tmp
rm -r env

qemu-system-i386 -cdrom SlylockOS.iso -m 512M -device pci-bridge,chassis_nr=1,id=bridge1 -hda floppy.img

