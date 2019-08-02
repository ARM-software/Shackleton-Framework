This folder contains support files that are included in many files across the Shackleton project, including utilities from basic math to json parsing to testing.

All testing material can be found in this directory. Testing can be enabled when running the Shackleton tool by providing the -test flag on startup. Adding the test flag will enable a single line in the main code that calls a master test method (can be found in test.c) that calls all other tests. Some tests are commented out by default, but they are clearly labeled and can be uncommented at any time.