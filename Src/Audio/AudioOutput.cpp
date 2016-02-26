#include "AudioOutput.h"

float AudioOutput::nextSampleImpl()
{
	Assert(mInputs.size() == 1);
	return mInputs[0]->nextSample();
}
