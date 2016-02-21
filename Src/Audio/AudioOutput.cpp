#include "AudioOutput.h"

float AudioOutput::nextSample()
{
	Assert(mInputs.size() == 1);
	return mInputs[0]->nextSample();
}
