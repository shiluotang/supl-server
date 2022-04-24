#!/usr/bin/env bash

function mksdir() {
    for d in "${@}"
    do
        if [[ ! -d ${d} ]]; then
            mkdir -p "${d}"
        fi
    done
}

function main() {
mksdir build-aux m4 bin
if [[ ! -f ./configure ]]; then
    if ! autoreconf -vi; then
        rm -f ./configure
    fi
fi
if [[ ! -f build-aux/depcomp ]]; then
    automake --add-missing
fi
if [[ ! -f build-aux/test-driver ]]; then
    automake --add-missing
fi
if [[ ! -f bin/Makefile ]]; then
    if pushd bin >& /dev/null; then
        if !  ../configure; then
            rm -f Makefile
        fi
        popd >& /dev/null
    fi
fi
make -C bin all check
}
