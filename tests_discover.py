import unittest
import argparse

def __load_tests_from_dir(search_dir):
    assert search_dir
    
    test_suit = unittest.TestLoader().discover(search_dir)
    
    return test_suit

def __parse_tests(tests_suit):
    pass
def __print_tests_tree(tests_tree, mode, option):
    pass

def __get_print_option(args):
    option = dict()
    if 'file' not in args:
        mode = 'stdout'
    else:
        mode = 'file'
        option['path'] = args['file']
        
    return (mode, option)

def __print_tests_to_stdout(tests_tree, option):
    pass

def __print_tests_to_file(tests_tree, option):
    pass

def __print_tests(fd, tests_tree, option):
    pass

def __discover_tests(args):
    tests_suit = __load_tests_from_dir(args['root'])
    
    tests_tree = __parse_tests(tests_suit)
    
    #get print mode and options
    mode, option = __get_print_option(args)
    __print_tests_tree(tests_tree, mode, option)
    pass

def main():
    parser = argparse.ArgumentParser(description='Discover test cases for user to run')
    
    parser.add_argument('-d', type=str, dest='root', default='./', help='Specify the root direcovery to discover more test cases')
    parser.add_argument('-f', type=str, dest='file', help='Specify the test cases out device, default to stdout')
    
    args = parser.parse_args()
    __discover_tests(args)
    
if __name__ == '__main__':
    main()
