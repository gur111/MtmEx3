#!/bin/bash
set -e -o pipefail

function cleanup {
    EXIT_CODE=$?
    set +e # disable termination on error
    if ls -a1 | grep $TMP_DIR ; then
        rm -Rf $TMP_DIR
        echo "deleted dir $TMP_DIR"
    fi
    cd $orig_dir
    exit $EXIT_CODE
}

trap cleanup EXIT

orig_dir=$(pwd)
TMP_DIR=.tmp_sub
mkdir -p $TMP_DIR

# Replace include from parent to local
for folder in $(ls -1 | grep "^part.$") ; do
    echo dir is $TMP_DIR/$folder
    mkdir -p $TMP_DIR/$folder
    for file in $(ls -1 $folder | grep "\.h\|\.cpp") ; do 
        sed 's/\.\.\/part.\///g' $folder/$file > $TMP_DIR/$folder/$file
    done

    # Add dependencies
    for dep in $(grep -roh $folder/ -e ".*\.\./part./\w*\.h" | grep -v "//" | grep -oh -e "part./\w*\.") ; do
        echo "Copying dep $dep*"
        cp $dep* $TMP_DIR/$folder
    done
done

cd $TMP_DIR
t=$(date "+%H:%M:%S")
zip ../sub_$t.zip ./*
cd -

