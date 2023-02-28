#!/bin/bash

# Find all .c files in the src directory and its subdirectories
find src -name "*.c" -type f | while read file; do
  # Execute c_format_42 on each file
  c_formatter_42 "$file"
done

find include -name "*.h" -type f | while read file; do
  # Execute c_format_42 on each file
  c_formatter_42 "$file"
done
