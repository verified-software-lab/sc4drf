export POLYFLAG="micro-benchmarks/utilities/polybench.c -Imicro-benchmarks -Imicro-benchmarks/utilities -DPOLYBENCH_NO_FLUSH_CACHE -DPOLYBENCH_TIME -D_POSIX_C_SOURCE=200112L"
export LLOV_DIR=$HOME/LLOV-v0.3
export LLVM_DIR=/usr/lib/llvm-10/lib/clang/10.0.0

for i in `grep no.c civl-list.txt`; do echo $i; $LLOV_DIR/bin/clang $POLYFLAG -I$LLOV_DIR/include -I$LLVM_DIR/include/ -L$LLOV_DIR/lib -Xclang -disable-O0-optnone -Xclang -load -Xclang $LLOV_DIR/lib/OpenMPVerify.so -fopenmp -g $LLOV_DIR/micro-benchmarks/$i |& egrep -c 'detected.'; done
