gosources=$(find ./libs/libgo/* -type f -name "*.go")
goobjects=$(echo ${gosources//\.go/.o})
objbg=''
charg=' '
endg=$(awk -F"${charg}" '{print NF-1}' <<< "${goobjects}")
endg=$((endg+1))
mkdir libgobin
for i in $(seq 1 $endg); do 
tag=$(echo ./libgobin/$(basename $(echo $goobjects | cut -d" " -f$i )))
tbg=$(echo $gosources | cut -d" " -f$i)
objbg="${objbg} ${tag}"
gccgo -m32 -Wall -O -fno-stack-protector -static -Werror -nostdlib -nostartfiles -nodefaultlibs -c -o $tag $tbg -L/lib -lflibc
done
objbg="${objbg:1}"

ar rcs lib/libgo.a libgobin/*.o

rm -r libgobin