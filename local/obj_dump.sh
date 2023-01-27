#!/usr/bin/env bash

if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi
START=''
STOP=''
while [ $# -gt 0 ]; do
  case "$1" in
    --start-address)
      START="$2"
      ;;
    --stop-address)
      STOP="$2"
      ;;
    *) ;;
  esac
  shift
done

if [[ $START == $STOP ]]; then
  $STOP = $START + 1
fi

llvm-objdump -d -l -C --start-address=$START --stop-address=$STOP /home/jasonconway/git/ish/build/ish
