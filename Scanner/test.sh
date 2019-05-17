#!bin/bash
name=print
in=$name.c
out=$name.out
./myscanner input/$in > $out
diff output/$out $out