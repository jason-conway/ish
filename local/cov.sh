#!/usr/bin/env bash

set -o errexit

cd "$(dirname "$0")" && cd ..

llvm-profdata merge -sparse default.profraw -o ish.profdata
llvm-profdata show --topn=50 default.profraw -o out.txt
llvm-cov show ./build/ish --instr-profile=ish.profdata -format=html --show-branches=percent --fs-profile-debug-prob-diff-threshold=90 >  prof.html
