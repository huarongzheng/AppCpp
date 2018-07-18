#!/usr/bin/python
# below prints "hello" on screen what if due to project requirements we need to print "debug: hello"
# how many ways to do that
# what if greet() cannot be changed
def greet():
    print "hello"

def debug(func):
    def wrapper():
        print "[DEBUG]: enter {}()".format(func.__name__)
        return func()
    return wrapper
greet = debug(greet)

if __name__ == '__main__':
    greet()


