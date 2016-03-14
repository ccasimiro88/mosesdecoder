/*
 * InputPaths.cpp
 *
 *  Created on: 23 Oct 2015
 *      Author: hieu
 */
#include <iostream>
#include "InputPaths.h"
#include "../Sentence.h"
#include "../System.h"
#include "../legacy/Range.h"
#include "Manager.h"
#include "InputPath.h"

using namespace std;

namespace Moses2
{
namespace SCFG
{
void InputPaths::Init(const Sentence &input, const ManagerBase &mgr)
{
  MemPool &pool = mgr.GetPool();
  size_t numPt = mgr.system.mappings.size();
  size_t size = input.GetSize();
  size_t maxLength = min(size, mgr.system.maxPhraseLength);

  m_matrix = new (pool.Allocate< Matrix<InputPath*> >()) Matrix<InputPath*>(pool, size, maxLength);
  m_matrix->Init(NULL);

  // create normal paths of subphrases through the sentence
  for (size_t startPos = 0; startPos < size; ++startPos) {
	const InputPath *prefixPath = NULL;

	for (size_t phaseSize = 1; phaseSize <= maxLength; ++phaseSize) {
	  size_t endPos = startPos + phaseSize - 1;

	  if (endPos >= size) {
		  break;
	  }

	  SubPhrase subPhrase = input.GetSubPhrase(startPos, phaseSize);
	  Range range(startPos, endPos);

	  InputPath *path = new (pool.Allocate<InputPath>()) InputPath(pool, subPhrase, range, numPt, prefixPath);
	  m_inputPaths.push_back(path);

	  prefixPath = path;

	  m_matrix->SetValue(startPos, phaseSize - 1, path);
	}
  }

}


}
}
