sources=$(find ./libs/sosix/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir sosixbin
for i in $(seq 1 $end); do 
ta=$(echo ./sosixbin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin  -fno-stack-protector -I./include/kernel -I./include/sosix -c -o $ta $tb
done

ar rcs lib/sosix.a sosixbin/*.o

rm -r sosixbin