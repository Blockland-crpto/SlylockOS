set -e
sources=$(find ./libs/libkeyboard/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir libkeyboardbin
for i in $(seq 1 $end); do 
ta=$(echo ./libkeyboardbin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-inline-functions -nostdinc -fno-builtin  -fstack-protector-all $headers -c -o $ta $tb
done

ar rcs lib/libkeyboard.a libkeyboardbin/*.o

rm -r libkeyboardbin