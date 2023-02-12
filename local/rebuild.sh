#!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail

if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi

if [[ "${1-}" =~ ^-*h(elp)?$ ]]; then
    echo 'Usage: ./rebuild.sh'
    exit
fi

cd "$(dirname "$0")"

main() {
    cd ..
    CC=clang LD=lld meson setup --wipe --debug -Dengine=jit -Dkernel=ish build
    ninja -C build
}

main "$@"
