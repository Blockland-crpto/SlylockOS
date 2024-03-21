mkdir lib
./build/libc_build.sh
./build/libcpp_build.sh
./build/libtui_build.sh
./build/libsdk_build.sh
./build/libgo_build.sh

csources=$(find ./kernel/* -type f -name "*.c")
cheaders=$(find ./include/* -type f -name "*.h")

gosources=$(find ./kernel/* -type f -name "*.go")

libaries=$(find ./lib/* -type f -name "*.a")

cobjects=$(echo ${csources//\.c/.o})
goobjects=$(echo ${gosources//\.go/.o})

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
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include/kernel -I./include/libc -I./include/libtui -I./include/libsdk -fno-stack-protector  -c -o $ta $tb
done
objb="${objb:1}"


objbg=''
charg=' '
endg=$(awk -F"${charg}" '{print NF-1}' <<< "${goobjects}")
endg=$((endg+1))
for i in $(seq 1 $endg); do 
tag=$(echo ./bin/$(basename $(echo $goobjects | cut -d" " -f$i )))
tbg=$(echo $gosources | cut -d" " -f$i)
objbg="${objbg} ${tag}"
gccgo -m32 -Wall -O -fno-stack-protector -static -Werror -nostdlib -nostartfiles -nodefaultlibs -c -o $tag $tbg -L/lib -lflibc
done
objbg="${objbg:1}"

export LD_LIBRARY_PATH=/home/runner/MiniOS/
ld -T link.ld --verbose -m elf_i386 -o kernel.bin $objb $objbg ./bin/boot.o $libaries

rm -r iso

mkdir sys
mkdir tmp
echo '' >> sys/membuf

mkdir iso
mkdir iso/boot
mkdir iso/boot/grub

mv kernel.bin iso/boot/kernel.bin
echo 'set timeout-0' >> iso/boot/grub/grub.cfg
echo 'set default-0' >> iso/boot/grub/grub.cfg
echo 'menuentry "MiniOS" {' >> iso/boot/grub/grub.cfg
echo '  multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
echo '  module  /boot/os.initrd' >> iso/boot/grub/grub.cfg
echo '  boot' >> iso/boot/grub/grub.cfg
echo '}' >> iso/boot/grub/grub.cfg
rm initrdgen
gcc initrdgen.c -o initrdgen
inp="readme ./lib/flibc.a ./lib/libtui.a ./lib/libsdk.a ./sys/membuf ./tmp"
res=''
for word in $inp; do
res="${res} ${word}"
res="${res} ${word}"
done
./initrdgen $res
mv ./initrd.img ./iso/boot/os.initrd
grub-mkrescue --output=minios.iso iso
rm -r bin
rm -r lib
rm -r iso
rm -r sys
rm -r tmp

qemu-system-i386 -cdrom minios.iso -m 512M -device pci-bridge,chassis_nr=1,id=bridge1

