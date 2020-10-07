// ArrayVsList.cpp
// Created 10/1/2020 5:44:36 PM

#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <chrono>

using namespace std::chrono; //  For higher resolution timer

class UniformRandomGenerator {
	//  A uniform distribution object
	std::uniform_int_distribution<int> dist;
	//  A Mersenne Twister random number generator with a seed
	//  obtained from a random_device object
	std::mt19937 mt;
	UniformRandomGenerator& operator=(const UniformRandomGenerator& other);
public:
	//  The smallest pseudorandom number this generator can produce
	const int MIN;

	//  The largest pseudorandom number this generator can produce
	const int MAX;

	//  Create a pseudorandom number generator that produces values in
	//  the range low...high
	UniformRandomGenerator(int low, int high) : dist(low, high),
		mt(std::random_device()()),
		MIN(low), MAX(high) {}

	//  Return a pseudorandom number in the range MIN...MAX
	int operator()() {
		return dist(mt);
	}
};


class Stopwatch {
	//  The time when the stopwatch is started
	high_resolution_clock::time_point start_time;
	//  The time when the stopwatch is stopped
	high_resolution_clock::time_point stop_time;
	//  Records whether or not the stopwatch currently
	//  is running
	bool running;
public:

	//  A stopwatch begins its life in a non-running state
	Stopwatch() : running(false) {}

	//  Starts the stopwatch.  Puts the stopwatch in a 
	//  running state.
	//  Does nothing if the stopwatch currently is running.
	void start() {
		if (!running) {
			running = true;
			start_time = high_resolution_clock::now();
		}
	}

	//  Stops the stopwatch.  Puts the stopwatch in a 
	//  non-running state.
	//  Does nothing if the stopwatch currently is not 
	//  running.
	void stop() {
		if (running) {
			stop_time = high_resolution_clock::now();
			running = false;
		}
	}

	//  Returns the elapsed time in seconds since the stopwatch
	//  last was started.  Ordinarily the client will stop the
	//  stopwatch before calling this method.  If the client 
	//  calls this method while the stopwatch is running,
	//  the processing necessary to compute the elapsed time
	//  may unduly compromise the ongoing timing.
	double elapsed() const {
		if (!running) {  //  Stopwatch stopped
			auto diff = duration_cast<duration<double>>(stop_time - start_time);
			return diff.count();
		}
		else {  //  Stopwatch currently running
			auto now = high_resolution_clock::now();
			auto diff = duration_cast<duration<double>>(now - start_time);
			return diff.count();
		}
	}
};


//  Generates pseudorandom numbers in the range 
//  1, 2, 3, ..., 1,000,000
UniformRandomGenerator randgen(0, 1000000);


template <typename T>
void populate_sequence(T& seq, unsigned n) {
	for (unsigned i = 0; i < n; i++)
		seq.push_back(randgen());
}

template <typename T, typename V>
void copy_sequence(T& to, const V& from) {
	for (auto iter = from.begin(); iter != from.end(); iter++)
		to.push_back(*iter);
}



template <typename T>
bool remove(T& seq, int n) {
	auto begin = seq.begin(),
		end = seq.end();
	for (auto cursor = begin; cursor != end; cursor++)
		if (*cursor == n) {
			seq.erase(cursor);
			return true;  //  Removed an element
		}
	return false;  //  Element not present to remove
}

template <typename T>
int do_removes(T& seq, unsigned count) {
	int removed = 0;
	Stopwatch timer;
	timer.start();

	//  Try to remove values in the range 0...count - 1
	for (unsigned i = 0; i < count; i++) {
		if (remove(seq, i))
			removed++;
	}
	timer.stop();
	std::cout << "(" << timer.elapsed() << " sec) ";
	return removed;
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& seq) {
	os << '{';
	auto cursor = begin(seq);
	auto last = end(seq);
	if (cursor != last) {
		os << *cursor;
		cursor++;
		while (cursor != last)
			os << ',' << *cursor++;
	}
	os << '}';
	return os;
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& seq) {
	os << '{';
	auto cursor = seq.begin();
	auto last = seq.end();
	if (cursor != last) {
		os << *cursor;
		cursor++;
		while (cursor != last)
			os << ',' << *cursor++;
	}
	os << '}';
	return os;
}

int main() {
	const int SIZE = 100'000;  // 10'000;    // 1'000'000;
	std::vector<int> arr;
	std::list<int> lst;

	populate_sequence(arr, SIZE);
	copy_sequence(lst, arr);
	//cout << arr << endl;
	//cout << lst << endl;
	std::cout << "List results : " << do_removes(lst, SIZE/2) << '\n';
	std::cout << "Array results: " << do_removes(arr, SIZE/2) << '\n';

}

