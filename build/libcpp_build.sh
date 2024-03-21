sources=$(find ./libs/libcpp/* -type f -name "*.cpp")
objects=$(echo ${sources//\.cpp/.o})
objb=''
char=' '
end=$(awk -F"${char}" '{print NF-1}' <<< "${objects}")
end=$((end+1))
mkdir libcppbin
for i in $(seq 1 $end); do 
ta=$(echo ./libcppbin/$(basename $(echo $objects | cut -d" " -f$i )))
tb=$(echo $sources | cut -d" " -f$i)
objb="${objb} ${ta}"
g++ -m32 -elf_i386 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fstrength-reduce -fomit-frame-pointer -finline-functions -fno-stack-protector -fpermissive -I./include/kernel -I./include/libc -I./include/libcpp -c -o $ta $tb
done

ar rcs lib/libcpp.a libcppbin/*.o

rm -r libcppbin