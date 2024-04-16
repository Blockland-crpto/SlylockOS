set -e
sources=$(find ./libs/libsound/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir libsoundbin
for i in $(seq 1 $end); do 
ta=$(echo ./libsoundbin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall -O -fstrength-reduce -fomit-frame-pointer -fno-inline-functions -nostdinc -fno-builtin  -fstack-protector-all $headers -c -o $ta $tb
done

ar rcs lib/libsound.a libsoundbin/*.o

rm -r libsoundbin