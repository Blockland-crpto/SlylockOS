sources=$(find ./libs/libhab/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir libhabbin
for i in $(seq 1 $end); do 
ta=$(echo ./libhabbin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include/kernel -I./include/libc -I./include/libtui -I./include/libsdk -fno-stack-protector -c -o $ta $tb
done

ar rcs lib/libhab.a libhabbin/*.o

rm -r libhabbin