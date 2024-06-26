mkdir lib
export headers=$(echo "-I./kernel/include
						-I./libs/libacpi/include
						-I./libs/libapic/include
						-I./libs/libata/include		
						-I./libs/libdebug/include
						-I./libs/libdelegate/include
						-I./libs/libdevmgr/include
						-I./libs/libdmgctrl/include
						-I./libs/libexe/include
						-I./libs/libfs/include
						-I./libs/libinitrd/include
						-I./libs/libkeyboard/include
						-I./libs/libmem/include
						-I./libs/libmmio/include
						-I./libs/libmodule/include
						-I./libs/libmouse/include
						-I./libs/libmultiboot/include
						-I./libs/libnmi/include
						-I./libs/libpci/include
						-I./libs/libpic/include
						-I./libs/libports/include
						-I./libs/libpower/include
						-I./libs/libproc/include
						-I./libs/libreg/include
						-I./libs/librtc/include
						-I./libs/libserial/include
						-I./libs/libsound/include
						-I./libs/libsse/include
						-I./libs/libssp/
						-I./libs/libtimer/include
						-I./libs/libvalidate/include
						-I./libs/libvga/include
						-I./libs/posix/include")
export debug=$(echo "-DDEBUG -Wextra -Wstack-protector -fanalyzer")
#-Wno-discarded-qualifiers
export security=$(echo "-fstack-protector-all -fstack-clash-protection")
export optimize=$(echo "-Og -g -Wstack-usage=1100")
./build/libacpi_build.sh
./build/libapic_build.sh
./build/libata_build.sh
./build/libdebug_build.sh
./build/libdelegate_build.sh
./build/libdevmgr_build.sh
./build/libdmgctrl_build.sh
./build/libexe_build.sh
./build/libfs_build.sh
./build/libinitrd_build.sh
./build/libkeyboard_build.sh
./build/libmem_build.sh
./build/libmmio_build.sh
./build/libmodule_build.sh
./build/libmouse_build.sh
./build/libmultiboot_build.sh
./build/libnmi_build.sh
./build/libpci_build.sh
./build/libpic_build.sh
./build/libports_build.sh
./build/libpower_build.sh
./build/libproc_build.sh
./build/libreg_build.sh
./build/librtc_build.sh
./build/libserial_build.sh
./build/libsound_build.sh
./build/libsse_build.sh
./build/libssp_build.sh
./build/libtimer_build.sh
./build/libvalidate_build.sh
./build/libvga_build.sh
./build/posix_build.sh

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

cppsources=$(find ./kernel/modules/* -type f -name "*.cpp")
cppobjects=$(echo ${cppsources//\.cpp/.o})

objbp=''
charp=' '
endp=$(awk -F"${charp}" '{print NF-1}' <<< "${cppobjects}")
endp=$((endp+1))

for i in $(seq 1 $endp); do 
tap=$(echo ./bin/$(basename $(echo $cppobjects | cut -d" " -f$i )))
tbp=$(echo $cppsources | cut -d" " -f$i)
objbp="${objbp} ${tap}"
g++ -m32 -elf_i386 $optimize $headers -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive -fstack-protector-all -c -o $tap $tbp

done
objbp="${objbp:1}"


gcc -m32 -elf_i386 -Wall $optimize -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin $debug $headers -fno-stack-protector  -c -o ./bin/main.o ./kernel/main.c

export LD_LIBRARY_PATH=/home/runner/SlylockOS/
ld -T link.ld --verbose -m elf_i386 -o kernel.bin ./bin/main.o $objb $objbp ./bin/boot.o $libaries


rm -r iso

mkdir env
mkdir sys
mkdir tmp
mkdir dev
echo '' >> sys/membuf
echo '' >> sys/pty
echo '' >> sys/tty

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
inp="./lib/posix.a ./sys/membuf ./sys/pty ./sys/tty ./tmp ./env ./dev"
res=''
for word in $inp; do
res="${res} ${word}"
res="${res} ${word}"
done
./initrdgen $res
mv ./initrd.img ./iso/boot/os.initrd
grub-mkrescue --output=SlylockOS.iso iso
rm -r bin
rm -r iso
rm -r sys
rm -r tmp
rm -r env
rm -r dev
objcopy --only-keep-debug kernel.bin kernel.sym

rm -f kernel.bin

qemu-system-i386 -cdrom SlylockOS.iso -m 256M -vga std -serial file:serial.log -drive file=floppy.img,format=raw,if=ide -device virtio-mouse -device sb16 -device pci-bridge,chassis_nr=1,id=pci.1,bus=pci.0,addr=5 -device nec-usb-xhci,id=usb,bus=pci.0,addr=6 -curses