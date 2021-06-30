#!/bin/bash
#echo Converting mtl files

# converts all *.jpg and *.bmp files to *.png and patches model.mtl

dir="."
test $(find "$dir" -type d | head -n 1) || exit 1

# subdirectory (optional)
sub="$1"
if [ "$1" ]; then
  dir="$dir/$sub";
  test $(find "$dir" -type d | head -n 1) || exit 1
fi

while read x
do
  >&2 echo "patching $x" &&
#  >&2 echo "patching $(basename "$x")" &&
  sed -i.bak 's/.png/.jpg/' "$x" &&
  rm -f "$x.bak" &&
  sed -i.bak 's/.bmp/.jpg/' "$x" &&
  rm -f "$x.bak"
  if [ $? -ne 0 ]; then exit 1; fi
done < <(find "$dir" -name '*.mtl') &&

>&2 echo "done"
