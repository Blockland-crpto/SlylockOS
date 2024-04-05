mkdir lib

./build/libacpi_build.sh
./build/libata_build.sh
./build/libfs_build.sh
./build/libinitrd_build.sh
./build/libkeyboard_build.sh
./build/libmmio_build.sh
./build/libmouse_build.sh
./build/libpci_build.sh
./build/libports_build.sh
./build/librtc_build.sh
./build/libserial_build.sh
./build/libtimer_build.sh
./build/libvga_build.sh
./build/sosix_build.sh

csources=$(find ./kernel/modules/* -type f -name "*.c")
headers=$(find ./include/* -type f -name "*.h")

libaries=$(find ./lib/* -type f -name "*.a")

cobjects=$(echo ${csources//\.c/.o})

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
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-inline-functions -nostdinc -fno-builtin -I./include/kernel -I./include/sosix -I./include/libs -fstack-protector-strong -c -o $ta $tb
done
objb="${objb:1}"


gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include/kernel -I./include/sosix -I./include/libs -fno-stack-protector  -c -o ./bin/main.o ./kernel/main.c

export LD_LIBRARY_PATH=/home/runner/SlylockOS/
ld -T link.ld --verbose -m elf_i386 -o kernel.bin ./bin/main.o $objb  ./bin/boot.o $libaries

rm -r iso

mkdir env
mkdir sys
mkdir tmp
echo '' >> sys/membuf

mkdir iso
mkdir iso/boot
mkdir iso/boot/grub

mv kernel.bin iso/boot/kernel.bin
echo 'set timeout=0' >> iso/boot/grub/grub.cfg
echo 'set default="SlylockOS"' >> iso/boot/grub/grub.cfg
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

qemu-system-i386 \
	-cdrom SlylockOS.iso \
	-m 512M \
	-vga std \
	-serial file:serial.log \
	-hda floppy.img \
	-device virtio-mouse \
	-device sb16 