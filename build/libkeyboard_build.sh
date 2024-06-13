#
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
gcc -m32 -elf_i386 -Wall $optimize -fstrength-reduce -fomit-frame-pointer -fno-inline-functions -nostdinc -fno-builtin $security $debug $headers -c -o $ta $tb
done

cppsources=$(find ./libs/libkeyboard/* -type f -name "*.cpp")
cppobjects=$(echo ${cppsources//\.cpp/.o})

objbp=''
charp=' '
endp=$(awk -F"${charp}" '{print NF-1}' <<< "${cppobjects}")
endp=$((endp+1))

for i in $(seq 1 $endp); do 
tap=$(echo ./libkeyboardbin/$(basename $(echo $cppobjects | cut -d" " -f$i )))
tbp=$(echo $cppsources | cut -d" " -f$i)
objbp="${objbp} ${tap}"
g++ -m32 -elf_i386 $optimize $headers  $debug $security -ffreestanding  -fno-exceptions -fno-rtti -fpermissive -c -o $tap $tbp

done
objbp="${objbp:1}"

ar rcs lib/libkeyboard.a libkeyboardbin/*.o

rm -r libkeyboardbin