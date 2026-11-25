#!/bin/bash
set -e

cd "$(dirname "$0")"

glslc ./utilities.comp -o bin/utilities.spv
glslc ./complex.comp -o bin/complex.spv
