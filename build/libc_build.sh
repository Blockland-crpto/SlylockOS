sources=$(find ./libs/flibc/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir libcbin
for i in $(seq 1 $end); do 
ta=$(echo ./libcbin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin  -fno-stack-protector -I./include/kernel -I./include/libc -c -o $ta $tb
done

ar rcs lib/flibc.a libcbin/*.o

rm -r libcbin