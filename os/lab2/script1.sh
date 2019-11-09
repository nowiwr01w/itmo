#!/bin/bash

# -E use regular
# -o names only (without date)
# -r do recursive
# -s don't show error text 
# -h don't print name of files in result search

grep -E -r -o -s -h "ACPI.*" "/var/log/" > error.log
grep -E -r -h [[:alnum:]]  error.log
cat error.log