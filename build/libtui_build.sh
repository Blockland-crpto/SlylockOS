sources=$(find ./libs/libtui/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir libtuibin
for i in $(seq 1 $end); do 
ta=$(echo ./libtuibin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include/kernel -I./include/libc -I./include/libtui -I./include/libsdk -fno-stack-protector -c -o $ta $tb
done

ar rcs lib/libtui.a libtuibin/*.o

rm -r libtuibin