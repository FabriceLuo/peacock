import unittest
import argparse

def __load_tests_from_dir(search_dir):
    assert search_dir
    
    test_suit = unittest.TestLoader().discover(search_dir)
    
    return test_suit

def __parse_tests(test_suit):
    pass

def __discover_tests():
    pass

def main():
    parser = argparse.ArgumentParser(description='Discover test cases for user to run')
    
    parser.add_argument('-d', type=str, dest='root', default='./', help='Specify the root direcovery to discover more test cases')
    parser.add_argument('-f', type=str, dest='file', help='Specify the test cases out device, default to stdout')
    
    args = parser.parse_args()
    __discover_tests(args)
    
if __name__ == '__main__':
    main()