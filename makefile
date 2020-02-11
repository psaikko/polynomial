demo: demo.cpp polynomial.h
	$(CXX) --std=c++14 -pedantic -Wall -Wextra $< -o $@

tests: test_polynomial.cpp polynomial.h
	$(CXX) --std=c++14 -pedantic -Wall -Wextra $< -o $@
