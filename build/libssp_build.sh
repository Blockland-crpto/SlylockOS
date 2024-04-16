set -e
sources=$(find ./libs/libssp/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir libsspbin
for i in $(seq 1 $end); do 
ta=$(echo ./libsspbin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-inline-functions -nostdinc -fno-builtin  -fstack-protector-all $headers -c -o $ta $tb
done

ar rcs lib/libssp.a libsspbin/*.o

rm -r libsspbin