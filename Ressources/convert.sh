#!/bin/bash

for f in *; do
  echo "File -> $f"
  convert $f -resize 200% $f
done
