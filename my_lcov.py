#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Purpose: Calculate UT coverage of git commits' new code
Usage: ./ut_incremental_check.py <since>..<until> <monitor_c_files> <lcov_dir> <threshold>
"""

from __future__ import print_function
import sys
import os
import re
import json
import subprocess
from html.parser import HTMLParser
from pprint import pprint

__version__ = 'V1.0'
__author__ = 'wahaha02'
__date__ = '2016-7-25'

DEBUG = False


class GcovHTMLParser(HTMLParser):

    def __init__(self):
        super().__init__()
        self.uncovers = []
        self.covers = []
        self.is_line_num = False
        self.line_num = 0

    def handle_starttag(self, tag, attrs):
        if tag == "span":
            for attr in attrs:
                if attr[0] == 'class' and attr[1] == 'lineNum':
                    self.is_line_num = True
                elif attr[0] == 'class' and attr[1] == 'lineNoCov':
                    self.uncovers.append(self.line_num)
                elif attr[0] == 'class' and attr[1] == 'lineCov':
                    self.covers.append(self.line_num)

    def handle_data(self, data):
        if self.is_line_num:
            try:
                self.line_num = int(data)
            except ValueError:
                self.line_num = -1

    def handle_endtag(self, tag):
        if tag == "span":
            self.is_line_num = False


class UTCover:

    def __init__(self, since_until, monitor, lcov_dir, thresh):
        self.since, self.until = since_until.split('..')
        self.monitor = json.loads(monitor)
        self.lcov_dir = lcov_dir
        self.thresh = float(thresh)
        print(self.since, self.until)
    def get_src(self):
        result = subprocess.run(["git", "diff", "--name-only", self.since, self.until],
                                stdout=subprocess.PIPE, text=True)
        src_files = [f for f in result.stdout.split('\n')
                     for m in self.monitor if m in f
                     if os.path.splitext(f)[1][1:] in ['c', 'cpp']]
        if DEBUG:
            print(src_files)
        return src_files

    def get_change(self, src_files):
        changes = {}
        for f in src_files:
            process = subprocess.Popen("git log --pretty=format:%h 9834e86 acb497f",
                                    shell=True, stdout=subprocess.PIPE, text=True)
            stdout, stderr = process.communicate()
            print(stdout)
            commits = stdout.split('\n')
            print(commits)

            # 修正错误:awk命令引号问题
            # cmd = f"git blame {f} | grep -E '({'|'.join(commits)})' | awk -F' *|)' '{{print $6}}'"

            cmd = "git blame %s | grep -E '(%s)' | awk  -F' *|)' '{print $6}'" %(f, '|'.join(commits))

            print("Command:", cmd)

            result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, text=True)
            lines = result.stdout.split('\n')

            # 修正错误:字典键写成了方括号
            changes[f] = [int(i) for i in lines if i.isdigit()]

        if DEBUG:
            pprint(changes)

        return changes

    def get_ghp(self, f):
        gcov_file = os.path.join(self.lcov_dir, f + '.gcov.html')
        if not os.path.exists(gcov_file):
            return None

        ghp = GcovHTMLParser()
        ghp.feed(open(gcov_file, 'r').read())

        return ghp

    def get_lcov_data(self, changes):
        uncovers = {}
        lcov_changes = {}

        for f, lines in changes.items():
            ghp = self.get_ghp(f)
            if not ghp:
                uncovers[f] = lines
                lcov_changes[f] = lines
                continue

            if DEBUG:
                print(f, ghp.uncovers, ghp.covers, lines)
            lcov_changes[f] = sorted(set(ghp.uncovers + ghp.covers) & set(lines))
            uncov_lines = set(ghp.uncovers) & set(lines)
            if uncov_lines:
                uncovers[f] = sorted(uncov_lines)
            ghp.close()

        return lcov_changes, uncovers

    def create_uncover_trs(self, uncovers):
        tr_format = '''
    <tr>
      <td class="coverFile"><a href="%(file)s.gcov.html">%(file)s</a></td>
      <td class="coverFile">%(uncov_lines)s </td>
    </tr>
'''
        trs = ''
        for f, v in uncovers.items():
            gcov_file = os.path.join(self.lcov_dir, f + '.gcov.html')
            if os.path.exists(gcov_file):
                s = ''
                p = re.compile(r'^<span class="lineNum">\s*(?P<num>\d+)\s*</span>')
                for line in open(gcov_file, 'r').readlines():
                    match = p.search(line)
                    if match:
                        num = match.group('num')
                        s += f'<a name="{num}">{line}</a>'
                    else:
                        s += line
                open(gcov_file, 'w').write(s)

            data = {'file': f, 'uncov_lines': ', '.join(
                [f'<a href="{f}.gcov.html#{i}">{i}</a>' for i in v])}
            trs += tr_format % data

        return trs

    def create_report(self, changes, uncovers):
        change_lines = 0
        uncov_lines = 0
        for v in changes.values():
            change_lines += len(v)
        for v in uncovers.values():
            uncov_lines += len(v)

        cov_lines = change_lines - uncov_lines
        coverage = round(cov_lines / change_lines, 4) if change_lines > 0 else 1

        with open('ut_incremental_coverage_report.template', 'r') as f:
            template = f.read()

        data = {'cov_lines': cov_lines,
                'change_lines': change_lines,
                'coverage': coverage * 100,
                'uncover_trs': self.create_uncover_trs(uncovers)}

        output_file = os.path.join(self.lcov_dir, 'ut_incremental_coverage_report.html')
        with open(output_file, 'w') as f:
            f.write(template % data)

        return coverage

    def check(self):
        src_files = self.get_src()
        changes = self.get_change(src_files)
        lcov_changes, uncovers = self.get_lcov_data(changes)
        coverage = self.create_report(lcov_changes, uncovers)
        return 0 if coverage > self.thresh else 1


if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.exit(0)

    ret = UTCover(*sys.argv[1:])
    result=ret.check()
    sys.exit(result)