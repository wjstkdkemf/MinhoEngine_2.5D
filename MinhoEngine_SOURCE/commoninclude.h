#pragma once
#include <Windows.h>
#include <assert.h>
#include <iostream>
#include <memory>

#include<vector>
#include<algorithm>
#include<iostream>
#include<map>
#include<bitset>
#include<functional>
#include<filesystem>
#include<stack>
#include<queue>
#include<mutex>
#include<thread>

#include <mmsystem.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <functional>
#include <ostream>
#include <sstream>

#include "MinMath.h"
#include "MinEnums.h"

#define BIT(x) (1 << x)
#define CAST_UINT(value) static_cast<UINT>(value)
#define CAST_FLOAT(value) static_cast<float>(value)

#define MIN_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }