#pragma once
#include "stockStream.h"

stockStream::stockStream(instrument* papr)
{
	date = papr -> getDate(0);
	open = papr -> getOpen(0);
	high = papr -> getHigh(0);
	low = papr -> getLow(0);
	close = papr -> getClose(0);
	volume = papr -> getVolume(0);
}
void stockStream::getNext()
{
	open = papr -> getOpen(index);
	high = papr -> getHigh(index);
}