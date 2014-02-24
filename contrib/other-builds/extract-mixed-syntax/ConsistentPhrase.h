/*
 * ConsistentPhrase.h
 *
 *  Created on: 20 Feb 2014
 *      Author: hieu
 */

#pragma once

#include <cassert>
#include <vector>
#include <iostream>
#include "moses/TypeDef.h"
#include "NonTerm.h"

class ConsistentPhrase
{
public:
	typedef std::vector<NonTerm> NonTerms;

	std::vector<int> corners;

	ConsistentPhrase(const ConsistentPhrase &copy);
	ConsistentPhrase(int sourceStart, int sourceEnd,
			int targetStart, int targetEnd);

	virtual ~ConsistentPhrase();

	int GetWidth(Moses::FactorDirection direction) const
	{ return (direction == Moses::Input) ? corners[1] - corners[0] + 1 : corners[3] - corners[2] + 1; }


	void AddNonTerms(const std::string &source,
						const std::string &target);
	const NonTerm &GetNonTerm() const
	{
		assert(m_nonTerms.size() == 1);
		return m_nonTerms[0];
	}
	const NonTerms &GetNonTerms() const
	{ return m_nonTerms;}

  bool operator<(const ConsistentPhrase &other) const;

  std::string Debug() const;
  void Output(std::ostream &out) const;
  void Output(std::ostream &out, Moses::FactorDirection direction) const;

protected:
  NonTerms m_nonTerms;
};

