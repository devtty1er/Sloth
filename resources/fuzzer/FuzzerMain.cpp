//===- FuzzerMain.cpp - main() function and flags -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// main() and flags.
//===----------------------------------------------------------------------===//

#include "FuzzerDefs.h"
#include "FuzzerPlatform.h"

typedef int (*UserCallback)(const uint8_t *Data, size_t Size);
extern "C" int libFuzzerStart(int argc, char **argv, UserCallback LLVMFuzzerTestOneInput) {
  return fuzzer::FuzzerDriver(&argc, &argv, LLVMFuzzerTestOneInput);
}
