/* -*- Mode: C++; -*- */
// $Id$
// copyright (c) 2004 by Christos Dimitrakakis <dimitrak@idiap.ch>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/** SMART_ASSERT - A simple method for better assertions.
 *
 * - AUTHOR:
 *
 *  Christos Dimitrakakis, 2003.
 * 
 * - ACKNOWLEDGEMENTS:
 *
 * The Assert class is due to John Torjo. The macro trick is due to
 * Paul Mensonides. This implementation is based on an article by
 * Andrei Alexandrescu and John Torjo in C/C++ Users Journal.
 *
 * - USAGE:
 *
 * SMART_ASSERT (test_expression)(obj)..(obj)
 *
 * - EXAMPLE:
 * 
 * If you wish to assert that x>y, you can do:
 * SMART_ASSERT (x>y)
 *
 * To print out the actual values of x and y:
 * SMART_ASSERT (x>y)(x)(y)
 *
 * This also works for more complex expressions:
 *
 * SMART_ASSERT (min(a,b) < min (b,c))(min(a,b))(min(b,c));
 *
 * - CAVEATS:
 *
 * It might not work for unprotected comma operators.
 *
 */

#ifndef SMART_ASSERT_H
#define SMART_ASSERT_H

#include <iostream>
#include <string>
#include <cassert>

/// Asert class
class Assert {
protected:
	bool holds_; ///< does the assertion hold?
public:
	/// If assertion holds.
	Assert(bool holds) : holds_(holds), SMART_ASSERT_A (*this),
						 SMART_ASSERT_B (*this) {}
	Assert& SMART_ASSERT_A; ///< clever macro A
	Assert& SMART_ASSERT_B; ///< clever macro B
	/// Print out result
	template <typename T>
	Assert& print_current_val(T f, const char* c) {	 
		std::cout << "Assertion failed: " << c << ":" << f << std::endl;
		return *this;
	}
	/// For printing out line number, function, etc
	Assert& print_context(const char* c, const int i)
	{
		std::cout << c << ":" << i << std::endl;
		return *this;
	}
	/// Generate error
	void error (const char* c) {
		std::cout << "Error: " << c << std::endl;
		abort();
	}
	/// Generate warning
	void warning (const char* c) {
		std::cout << "Warning: " << c << std::endl;
	}
};

/// Make an assertion
static Assert make_assert (bool flag) {
	return Assert(flag);
}


// Must define the macros afterwards
/// Clever macro A
#define SMART_ASSERT_A(x) SMART_ASSERT_OP(x, B)
/// Clever macro B
#define SMART_ASSERT_B(x) SMART_ASSERT_OP(x, A)
/// Clever macro recursion
#define SMART_ASSERT_OP(x, next) \
    SMART_ASSERT_A.print_current_val((x), #x).SMART_ASSERT_ ## next
/// High-level macro
#define SMART_ASSERT( expr) \
if ( (expr) ) ; \
else make_assert( #expr).print_context( __FILE__, __LINE__).SMART_ASSERT_A


#endif
