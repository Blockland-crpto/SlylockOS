sources=$(find ./libs/libapic/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir libapicbin
for i in $(seq 1 $end); do 
ta=$(echo ./libapicbin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-inline-functions -nostdinc -fno-builtin  -fstack-protector-all -I./include/kernel -I./include/sosix -I./include/libs -c -o $ta $tb
done

ar rcs lib/libapic.a libapicbin/*.o

rm -r libapicbin