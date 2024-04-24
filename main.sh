mkdir lib
export headers=$(echo "-I./kernel/include
						-I./libs/libacpi/include
						-I./libs/libapic/include
						-I./libs/libata/include		
						-I./libs/libdebug/include
						-I./libs/libexe/include
						-I./libs/libfs/include
						-I./libs/libinitrd/include
						-I./libs/libkeyboard/include
						-I./libs/libmem/include
						-I./libs/libmmio/include
						-I./libs/libmodule/include
						-I./libs/libmouse/include
						-I./libs/libmultiboot/include
						-I./libs/libpci/include
						-I./libs/libports/include
						-I./libs/libproc/include
						-I./libs/librtc/include
						-I./libs/libserial/include
						-I./libs/libsound/include
						-I./libs/libsse/include
						-I./libs/libssp/include
						-I./libs/libtimer/include
						-I./libs/libvga/include
						-I./libs/sosix/include")
export debug=$(echo "-DDEBUG")
export optimize=$(echo "-Og -g")
./build/libacpi_build.sh
./build/libapic_build.sh
./build/libata_build.sh
./build/libdebug_build.sh
./build/libexe_build.sh
./build/libfs_build.sh
./build/libinitrd_build.sh
./build/libkeyboard_build.sh
./build/libmem_build.sh
./build/libmmio_build.sh
./build/libmodule_build.sh
./build/libmouse_build.sh
./build/libmultiboot_build.sh
./build/libpci_build.sh
./build/libports_build.sh
./build/libproc_build.sh
./build/librtc_build.sh
./build/libserial_build.sh
./build/libsound_build.sh
./build/libsse_build.sh
./build/libssp_build.sh
./build/libtimer_build.sh
./build/libvga_build.sh
./build/sosix_build.sh

csources=$(find ./kernel/modules/* -type f -name "*.c")

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
gcc -m32 -elf_i386 -Wall $optimize -fstrength-reduce -fomit-frame-pointer -fno-inline-functions -nostdinc -fno-builtin $debug $headers -fstack-protector-all -c -o $ta $tb
done
objb="${objb:1}"


gcc -m32 -elf_i386 -Wall $optimize -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin $debug $headers -fno-stack-protector  -c -o ./bin/main.o ./kernel/main.c

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

cp kernel.bin iso/boot/kernel.bin
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

objcopy --only-keep-debug kernel.bin kernel.sym

rm -f kernel.bin

qemu-system-i386 -cdrom SlylockOS.iso -m 512M -vga std -serial file:serial.log -drive file=floppy.img,format=raw,if=ide -device virtio-mouse -device sb16 -device pci-bridge,chassis_nr=1,id=pci.1,bus=pci.0,addr=5 -device nec-usb-xhci,id=usb,bus=pci.0,addr=6