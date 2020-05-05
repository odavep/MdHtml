#!/usr/bin/env python3

from optparse import OptionParser
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


