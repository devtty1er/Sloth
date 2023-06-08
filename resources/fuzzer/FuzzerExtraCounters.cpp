//===- FuzzerExtraCounters.cpp - Extra coverage counters ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// Extra coverage counters defined by user code.
//===----------------------------------------------------------------------===//

#include "FuzzerPlatform.h"
#include <cstdint>
#include <cstring>

#if LIBFUZZER_LINUX || LIBFUZZER_NETBSD || LIBFUZZER_FREEBSD ||                \
    LIBFUZZER_FUCHSIA || LIBFUZZER_EMSCRIPTEN
#define MAP_SIZE (1 << 16)

extern unsigned char* afl_area_ptr;

namespace fuzzer {
uint8_t *ExtraCountersBegin() {
		return afl_area_ptr;
}
uint8_t *ExtraCountersEnd() {
	return afl_area_ptr+MAP_SIZE;
}
ATTRIBUTE_NO_SANITIZE_ALL
void ClearExtraCounters() {  // hand-written memset, don't asan-ify.
	memset(afl_area_ptr, 0, MAP_SIZE);
}

}  // namespace fuzzer

#else
// TODO: implement for other platforms.
namespace fuzzer {
uint8_t *ExtraCountersBegin() { return nullptr; }
uint8_t *ExtraCountersEnd() { return nullptr; }
void ClearExtraCounters() {}
}  // namespace fuzzer

#endif
