#
sources=$(find ./libs/libgcc/* -type f -name "*.c")
objects=$(echo ${sources//\.c/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir libgccbin
for i in $(seq 1 $end); do 
ta=$(echo ./libgccbin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
gcc -m32 -elf_i386 -Wall $optimize -fstrength-reduce -fomit-frame-pointer -fno-inline-functions -nostdinc -fno-builtin  -fstack-protector-all $debug $headers -c -o $ta $tb
done

cppsources=$(find ./libs/libgcc/* -type f -name "*.cpp")
cppobjects=$(echo ${cppsources//\.cpp/.o})

objbp=''
charp=' '
endp=$(awk -F"${charp}" '{print NF-1}' <<< "${cppobjects}")
endp=$((endp+1))

for i in $(seq 1 $endp); do 
tap=$(echo ./libgccbin/$(basename $(echo $cppobjects | cut -d" " -f$i )))
tbp=$(echo $cppsources | cut -d" " -f$i)
objbp="${objbp} ${tap}"
g++ -m32 -elf_i386 $optimize $headers -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fpermissive -fstack-protector-all -c -o $tap $tbp

done
objbp="${objbp:1}"

ar rcs lib/libgcc.a libgccbin/*.o

rm -r libgccbin