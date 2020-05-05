#!/usr/bin/env python3

from optparse import OptionParser
from re import search, sub
"""Command line arguments"""
usage = "usage: %prog [options] file..."
parser = OptionParser(usage=usage)
parser.add_option('-i', '--initial-html', dest='header',
                  help='File for initial template of compiled HTML',
                  default='initial.html')
parser.add_option('-o', '--output-type', dest='output_type',
                  help='Type of output (filename | date)',
                  default='filename')
(options, args) = parser.parse_args()


"""Valid argument testing
TODO: Add support for directories
"""
markdown_files = []
for file in args:
    if search(".md", file) is not None:
        # Is a markdown file
        markdown_files.append(file)
    else:
        print(file, "is not a markdown file, skipping")

