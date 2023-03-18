#!/bin/python

import random
import string
import sys
import os

def random_string(length):
    letters = string.ascii_lowercase
    return ''.join([random.choice(letters) for i in range(length)])


if (len(sys.argv) < 2):
    puts("python env.py <size>")
    sys.exit(1)

size = int(sys.argv[1])


out = open('enviroment.info', "w")
for i in range(size):
    var = random_string(5)
    out.write(f"export {var}={var}\n")
out.close()



