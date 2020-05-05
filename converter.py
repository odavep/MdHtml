#!/usr/bin/env python3

from optparse import OptionParser
from os.path import getctime
from time import ctime
from datetime import datetime
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


"""Read header"""
header = []
with open(options.header, 'r') as file:
    header = file.readlines()

"""Read and compile markdown to HTML"""
markdown_compiled = []
for filename in markdown_files:
    file_lines = []
    with open(filename, 'r') as file:
        file_lines = file.readlines()
    content_parsed = []
    for line in file_lines:
        # NOTE: When parsing regexes, use \g<number> for the object capture
        # Sub rules
        line = sub(r"#(.*)", r"<h1>\g<1></h1>", line)
        line = sub(r"\*\*(.*)\*\*", r"<strong>\g<1></strong>", line)
        line = sub(r"\*(.*)\*", r"<i>\g<1></i>", line)
        content_parsed.append(line)
    markdown_compiled.append({'name': filename, 'content': content_parsed})

"""Template time"""
for md in markdown_compiled:
    header_copy = ''.join(header).replace("%title%", md['name'])\
                                 .replace("%body%", ''.join(md['content']))
    file_name = ""
    if options.output_type.startswith("f"):
        file_name = md['name'].replace('.md', '.html')
    else:
        time = datetime.strptime(
            ctime(getctime(md['name'])), "%a %b %d %H:%M:%S %Y")
        file_name = str(time).replace(" ", "@") + ".html"
    with open(file_name, 'w') as file:
        file.write(header_copy)
