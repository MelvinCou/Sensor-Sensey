#pragma once

#include "data.pb.h"

void loRaBegin();

void sendMessage(const Data& message);
