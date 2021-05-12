#!/bin/sh

CC_BLUE="\e[0;94m"
CC_GREEN="\e[0;92m"
CC_RED="\e[0;91m"
CC_WHITE="\e[0;97m"
CC_BLUE_BG="\e[0;104m${expand_bg}"
CC_EXPAND_BG="\e[K"
CC_GREEN_BG="\e[0;102m${expand_bg}"
CC_RED_BG="\e[0;101m${expand_bg}"
CC_BOLD="\e[1m"
CC_RESET="\e[0m"
CC_ULINE="\e[4m"

VALGRIND=1

die () {
    printf "$CC_RED%s$CC_RESET\n" "$1" > /dev/stderr
    exit 1
}

check_dependencies () {
    for dep in "$@"; do
        command -v "$dep" > /dev/null \
            || die "Dependency $1 not installed"
    done
}

check_optional_dependency () {
    if ! command -v "$1" > /dev/null; then
        printf "$CC_RED%s not found.$CC_RESET\n" "$1" > /dev/stderr
        [ -n "$2" ] \
            && printf "$CC_RED%s is required for: %s$CC_RESET\n" "$1" "$2" > /dev/stderr
        return 1
    fi
    return 0
}

check_optional_dependencies_quiet () {
    for dep in "$@"; do
        command -v "$dep" > /dev/null \
            || return 1
    done
}

print_header () {
    printf "\n$CC_BLUE=== %s ===$CC_RESET\n" "$1"
}

test_file () {
    base="$(basename "$1")"
    print_header "Testing $base"
    if [ "$VALGRIND" = 1 ]; then
        printf "My wsort:\n"
        time valgrind --leak-check=full --show-leak-kinds=all \
            ./wsort < "$1" > "./out/my$base"
        printf "\nReference wsort:\n"
        time valgrind --leak-check=full --show-leak-kinds=all \
            ./wsort-ref < "$1" > "./out/their$base"
    else
        printf "My wsort:"
        time ./wsort < "$1" > "./out/my$base"
        printf "\nReference wsort:"
        time ./wsort-ref < "$1" > "./out/their$base"
    fi
    echo
    diff "./out/my$base" "./out/their$base" \
        && echo "=> No difference"
}

{ [ -d "./raw" ] && [ "$#" -gt 0 ]; } || die "no input files"
[ -e "./wsort" ] || die "no wsort"
[ -e "./wsort-ref" ] || die "no wsort-ref"

[ "$VALGRIND" = 1 ] \
    && check_dependencies valgrind

mkdir ./out 2> /dev/null
if [ "$#" -gt 0 ]; then
    for file in "$@"; do
        test_file "$file"
    done
else
    for file in $(find ./raw -type f); do
        test_file "$file"
    done
fi
