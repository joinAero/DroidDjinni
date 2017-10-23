#!/bin/bash

base_dir="$(cd "$(dirname "$0")" && pwd)"

djinni_dir="$base_dir/../deps/djinni"
out_dir="$base_dir/output"

while getopts "d:o:" opt; do
  case $opt in
    d) djinni_dir=$OPTARG ;;
    o) out_dir=$OPTARG ;;
  esac
done

djinni_run() {
    local profile="$1"; shift
    local in_idl="$1"; shift
    "$base_dir/scripts/run_djinni.sh" \
        -p "$base_dir/idls/profile/$profile" \
        -d "$djinni_dir" \
        -i "$base_dir/idls/$in_idl" \
        -o "$out_dir"
}

info() {
    if [[ -z "$2" ]]; then
        echo -e "\033[32m$1\033[0m"
    else
        echo -e "\033[$2m$1\033[0m"
    fi
}

clean() {
    if [ -e "$out_dir" ]; then
        echo "Deleting \"$out_dir\"..."
        rm -r "$out_dir"
    fi
}

clean

info "Generate leveldb"
djinni_run "leveldb_profile.yaml" "leveldb.idl"

date > "$out_dir/gen.stamp"
info "Output: $out_dir"
