project('task1', 'cpp', default_options: ['cpp_std=c++23', 'warning_level=3'])
gtest = dependency('gtest_main')
executable('task1', 'main.cpp')

test = executable('tests', 'tests/tester.cpp', dependencies: [gtest])

test('test', test)
