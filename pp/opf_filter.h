#ifndef OPF_FILTER_H
#define OPF_FILTER_H

#include <stddef.h>
#include <iostream>
#include <string>

#include "oprofpp.h"

// Add run-time checking if true.
static const bool sanity_check = true;

//---------------------------------------------------------------------------
// A simple container for a fileno:linr location
struct file_location {
	// This rely on a ref counted string implementation for efficiency.
	string filename;	// string() if not valid.
	int linenr;             // 0 means internally generated by the compiler
};

//---------------------------------------------------------------------------
// associate vma address with (filename linenr counter[])
struct sample_entry {
	file_location file_loc;
	unsigned long vma;        // would be bfd_vma but avoid depend on bfd.h
	counter_array_t counter;

	void debug_dump(ostream & out) const;
};

//---------------------------------------------------------------------------
// stored as a vector<symbol_entry> sorted by increased vma.
struct symbol_entry {
	sample_entry sample;
	string name;
	// [first, last[ gives the range of symbol_entry.
	size_t first;
	size_t last;

	void debug_dump(ostream & out) const;
};

//---------------------------------------------------------------------------

class symbol_container_impl;

class symbol_container_t {
public:
	 symbol_container_t();
	~symbol_container_t();

	void push_back(const symbol_entry &);

	size_t size() const;
	const symbol_entry & operator[](size_t index) const;
	const symbol_entry * find(string filename, size_t linenr) const;
	const symbol_entry * find_by_vma(unsigned long vma) const;

	/// get a vector of symbol_entry sorted by increased count.
	void get_symbols_by_count(size_t counter, 
				  vector<const symbol_entry*>& v) const;

private:
	symbol_container_impl * impl;
};

//---------------------------------------------------------------------------

class sample_container_impl;

class sample_container_t {
public:
	sample_container_t();
	~sample_container_t();

	void push_back(const sample_entry &);

	size_t size() const;
	const sample_entry & operator[](size_t index) const;
	bool accumulate_samples_for_file(counter_array_t & counter, 
					 const string & filename) const;
	bool accumulate_samples(counter_array_t &, const string & filename, 
				size_t linenr) const;
	const sample_entry * find_by_vma(unsigned long vma) const;

private:
	sample_container_impl * impl;
};

#endif /* !OPF_FILTER_H */
