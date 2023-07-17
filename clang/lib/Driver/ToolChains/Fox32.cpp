//===--- Fox32.cpp - Fox32 ToolChain Implementations ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Fox32.h"
#include "CommonArgs.h"
#include "clang/Driver/Compilation.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/Options.h"
#include "llvm/Option/ArgList.h"

using namespace clang::driver;
using namespace clang::driver::toolchains;
using namespace clang;
using namespace llvm::opt;

Fox32ToolChain::Fox32ToolChain(const Driver &D, const llvm::Triple &Triple,
                               const ArgList &Args)
    : ToolChain(D, Triple, Args) {
  // ProgramPaths are found via 'PATH' environment variable.
}

bool Fox32ToolChain::isPICDefault() const { return true; }

bool Fox32ToolChain::isPIEDefault(const llvm::opt::ArgList &Args) const { return false; }

bool Fox32ToolChain::isPICDefaultForced() const { return true; }

bool Fox32ToolChain::SupportsProfiling() const { return false; }

bool Fox32ToolChain::hasBlocksRuntime() const { return false; }
