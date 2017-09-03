"""generate tests case collection for choosing"""
import json
import Queue
import unittest
import argparse
from sys import stdout


def load_tests_from_dir(search_dir):
    assert search_dir

    test_suit = unittest.TestLoader().discover(search_dir)

    return test_suit


def parse_tests(tests_suit):
    tests_set = collect_tests(tests_suit)
    return convert_tests(tests_set)


def convert_tests(tests_set):
    tests_tree = init_tree_root()
    for test_case in tests_set:
        test_dirs, test_obj = parse_test_case(test_case)

        insert_test_case(tests_tree, test_dirs, test_obj)

    return tests_tree


def init_tree_root():
    tests_tree = dict(name='root',
                      desc='',
                      type='package',
                      note='',
                      data={},
                      label=[])

    return tests_tree


def insert_test_case(tests_tree, test_dirs, test_obj):
    current_node = tests_tree

    for test_dir in test_dirs:
        current_data = current_node['data']
        if test_dir not in current_data:
            temp_obj = dict(name=test_dir,
                            desc='',
                            type='package',  # todo verify every type
                            note='',
                            data={},
                            label=[])
            current_data[test_dir] = temp_obj

        current_node = current_data[test_dir]

    current_node['data'][test_obj['name']] = test_obj


def parse_test_case(test_case):
    assert test_case._testMethodName
    # assert test_case._testMethodDoc

    test_dirs = str.split(test_case.__class__.__module__, '.')
    test_dirs.append(test_case.__class__.__name__)

    test_name = test_case._testMethodName
    test_desc = test_case._testMethodDoc
    # test_path = test_case._testMethodName

    test_obj = dict(name=test_name,
                    desc=test_desc,
                    type='function',
                    note='',
                    label=[], )

    return test_dirs, test_obj


def collect_tests(tests_suit):
    # Breadth-First Search
    tests_queue = Queue.Queue()
    tests_queue.put(tests_suit)

    tests_set = list()
    while not tests_queue.empty():
        tests = tests_queue.get()
        if isinstance(tests, unittest.TestSuite):
            for test in tests:
                tests_queue.put(test)
        elif isinstance(tests, unittest.TestCase):
            tests_set.append(tests)
        else:
            raise ValueError

    return tests_set


def print_tests_tree(tests_tree, mode, option):
    if mode == 'file':
        print_tests_to_file(tests_tree, option)
    else:
        print_tests_to_stdout(tests_tree, option)


def get_print_option(args):
    option = {}

    if 'file' not in args or not args.file:
        mode = 'stdout'
    else:
        mode = 'file'
        option['path'] = args.file

    return mode, option


def print_tests_to_stdout(tests_tree, option):
    json.dump(tests_tree, stdout, indent=4)


def print_tests_to_file(tests_tree, option):
    assert option['path']

    fp = open(option['path'], 'w+')
    json.dump(tests_tree, fp, indent=4)
    fp.close()


def discover_tests(args):
    tests_suit = load_tests_from_dir(args.root)

    tests_tree = parse_tests(tests_suit)

    # get print mode and options
    mode, option = get_print_option(args)
    print_tests_tree(tests_tree, mode, option)


def main():
    """main to generate tests collection"""
    parser = argparse.ArgumentParser(description='Discover test cases for user to run')

    parser.add_argument('-d', type=str, dest='root',
                        default='./',
                        help='Specify the root directory to discover more test cases')
    parser.add_argument('-f', type=str, dest='file',
                        help='Specify the test cases out device, default to stdout')

    args = parser.parse_args()
    discover_tests(args)


if __name__ == '__main__':
    main()
