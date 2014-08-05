import sys
import difflib
import subprocess
import os
import re

test_parse = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                        '../../build/test_parse')

test_typecheck = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                        '../../build/test_typecheck')

PARSE_PASS_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                        'parse-pass/')

PARSE_FAIL_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                               'parse-fail/')

TYPECHECK_FAIL_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                   'typecheck-fail/')

FAILURE_TEMPLATE = ("{}\n"
                     "failed test {}\n"
                     "output: {}\n"
                     "{}\n"
)

STATUS_OK = 1
STATUS_FAIL = 2
STATUS_IGNORED = 3

HR_LEN = 65
HR = '-' * 65

def is_ignored(filename):
    with open(filename) as f:
        if f.read().startswith("// IGNORE"):
            return True
        else:
            return False

def test_parse_pass(filename):
    p1 = subprocess.Popen([test_parse, filename], stderr=subprocess.PIPE)
    err = p1.communicate()[1]

    short_filename = filename.replace(PARSE_PASS_PATH, '')
    if p1.returncode == 0:
        print('\t[parse-pass] '+short_filename+' ... ok')
        return (STATUS_OK, '')
    else:
        print('\t[parse-pass] '+short_filename+' ... fail')
        return (STATUS_FAIL, FAILURE_TEMPLATE.format(HR,
            filename,
            err.decode(encoding='UTF-8'),
            HR))



def test_parse_fail(filename):
    return test_fail(test_parse, 'parse-fail', PARSE_FAIL_PATH, filename)

def test_typecheck_fail(filename):
    return test_fail(test_typecheck, 'typecheck-fail', TYPECHECK_FAIL_PATH, filename)

def test_fail(test_exe, name, path_prefix, filename):
    short_filename = filename.replace(path_prefix, '')
    sys.stdout.write('\t['+name+'] '+short_filename )
    sys.stdout.flush()

    if is_ignored(filename):
        sys.stdout.write('... fail\n')
        return (STATUS_IGNORED, 'test case ignored')

    expected_errors = {}

    with open(filename, "rt") as f:
        line_number = 1
        for l in f.readlines():
            parts = l.split("//~")
            if len(parts) == 2:
                line_offset = 0
                for i in range(0, len(parts[1])):
                    if parts[1][i] != '^':
                        break
                    line_offset += 1
                errors =  expected_errors.get(line_number-line_offset, [])
                errors.append(parts[1][line_offset:].strip())
                expected_errors[line_number-line_offset] = errors
            line_number += 1

    p1 = subprocess.Popen([test_exe, filename], stderr=subprocess.PIPE)
    err = p1.communicate()[1]
    err = err.decode(encoding='UTF-8')

    if p1.returncode == 0:
        sys.stdout.write('... fail\n')
        return (STATUS_FAIL, FAILURE_TEMPLATE.format(HR,
                                                    filename,
                                                    'Test did run, but should fail',
                                                    HR
            ))
    elif p1.returncode == 1:
        error_re = re.compile(filename+":(?P<line>\d+)\..+error: \\x1b\[0m\\x1b\[1m(?P<msg>.+)\\x1b\[0m$")
        for l in err.split("\n"):
            if "error: " in l:
                m = re.search(error_re, l)
                if int(m.groupdict()['line']) not in expected_errors:
                    sys.stdout.write('... fail\n')
                    return (STATUS_FAIL, FAILURE_TEMPLATE.format(HR,
                                    filename,
                                    'unexpected error message: '+l,
                                    HR))
                found = False
                for expected_error in expected_errors[int(m.groupdict()['line'])]:
                    if m.groupdict()['msg'].find(expected_error) != -1:
                        found = True

                if not found:
                    sys.stdout.write('... fail\n')
                    return (STATUS_FAIL, FAILURE_TEMPLATE.format(HR,
                                                filename,
                                                ('expected error message not thrown; expected: '+expected_error,
                                                '\ngot error messages: '+m.groupdict()['msg']),
                                                HR))

        sys.stdout.write('... ok\n')
        return (STATUS_OK, '')
    else:
        sys.stdout.write('... fail\n')
        return (STATUS_FAIL, FAILURE_TEMPLATE.format(HR,
                                               filename,
                                               'Test did fail with error code != 1',
                                                 HR
            ))

def run_tests(directory, test_fn, verbose=False):
    results = []
    for dirname, dirnames, filenames in os.walk(directory):
        results += [test_fn(os.path.join(dirname, test_file)) for test_file in filenames if test_file.endswith(".casm")]

    ok_results = [True for (status,_) in results if status == STATUS_OK]
    fail_results = [msg for (status, msg) in results if status == STATUS_FAIL]
    ignored_results = [msg for (status, msg) in results if status == STATUS_IGNORED]

    print('run {} tests, ok: {}\tfailed: {}\tignored: {}'.format(
        len(ok_results)+len(fail_results)+len(ignored_results),
        len(ok_results),
        len(fail_results),
        len(ignored_results)
    ))

    if verbose:
        print('\n'.join(fail_results))

    return (len(ok_results), len(fail_results), len(ignored_results))


if __name__ == '__main__':
    ok_count_sum = 0
    fail_count_sum = 0
    ignored_count_sum = 0

    ok, fail, ignored = run_tests(PARSE_PASS_PATH, test_parse_pass)
    ok_count_sum += ok
    fail_count_sum += fail
    ignored_count_sum += ignored

    ok, fail, ignored = run_tests(PARSE_FAIL_PATH, test_parse_fail)
    ok_count_sum += ok
    fail_count_sum += fail
    ignored_count_sum += ignored

    ok, fail, ignored = run_tests(TYPECHECK_FAIL_PATH, test_typecheck_fail)
    ok_count_sum += ok
    fail_count_sum += fail
    ignored_count_sum += ignored

    print('')
    print(HR)
    if fail_count_sum == 0:
        print('\n\nTest summary (OK):')
    else:
        print('\nTest summary (FAIL):')
    print('  run {} tests, ok: {}\tfailed: {}\tignored: {}\n'.format(
        ok_count_sum+fail_count_sum+ignored_count_sum,
        ok_count_sum,
        fail_count_sum,
        ignored_count_sum
    ))
    print(HR)

    if fail_count_sum == 0:
        sys.exit(0)
    else:
        sys.exit(1)
