demo: demo.cpp polynomial.h
	$(CXX) --std=c++14 $< -o $@

tests: test_polynomial.cpp polynomial.h
	$(CXX) --std=c++14 $< -o $@
