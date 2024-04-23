#
sources=$(find ./libs/librtc/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir librtcbin
for i in $(seq 1 $end); do 
ta=$(echo ./librtcbin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall $optimize -fstrength-reduce -fomit-frame-pointer -fno-inline-functions -nostdinc -fno-builtin  -fstack-protector-all $debug $headers -c -o $ta $tb
done

ar rcs lib/librtc.a librtcbin/*.o

rm -r librtcbin