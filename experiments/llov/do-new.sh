export LLOV_DIR=$HOME/LLOV-v0.3
export LLVM_DIR=/usr/lib/llvm-10/lib/clang/10.0.0

for i in `grep .c civl-new.txt`; do echo $i; $LLOV_DIR/bin/clang -I$LLOV_DIR/include -I$LLVM_DIR/include/ -L$LLOV_DIR/lib -Xclang -disable-O0-optnone -Xclang -load -Xclang $LLOV_DIR/lib/OpenMPVerify.so -fopenmp -g ./new_examples/$i |& egrep -c 'detected.'; done
