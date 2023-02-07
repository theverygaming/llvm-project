//===--- fox32.cpp - fox32 ToolChain Implementations ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "fox32.h"
#include "CommonArgs.h"
#include "clang/Driver/Compilation.h"
#include "clang/Driver/InputInfo.h"
#include "clang/Driver/Options.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang::driver;
using namespace clang::driver::toolchains;
using namespace clang::driver::tools;
using namespace clang;
using namespace llvm::opt;

static void addMultilibsFilePaths(const Driver &D, const MultilibSet &Multilibs,
                                  const Multilib &Multilib,
                                  StringRef InstallPath,
                                  ToolChain::path_list &Paths) {
  if (const auto &PathsCallback = Multilibs.filePathsCallback())
    for (const auto &Path : PathsCallback(Multilib))
      addPathIfExists(D, InstallPath + Path, Paths);
}

bool fox32ToolChain::hasGCCToolchain(const Driver &D,
                                     const llvm::opt::ArgList &Args) {
  return false;
}

/// fox32 Toolchain
fox32ToolChain::fox32ToolChain(const Driver &D, const llvm::Triple &Triple,
                               const ArgList &Args)
    : Generic_ELF(D, Triple, Args) {
  getProgramPaths().push_back(D.Dir);
  getFilePaths().push_back(computeSysRoot() + "/lib");
}

ToolChain::RuntimeLibType fox32ToolChain::GetDefaultRuntimeLibType() const {
  return GCCInstallation.isValid() ? ToolChain::RLT_Libgcc
                                   : ToolChain::RLT_CompilerRT;
}

ToolChain::UnwindLibType
fox32ToolChain::GetUnwindLibType(const llvm::opt::ArgList &Args) const {
  return ToolChain::UNW_None;
}

void fox32ToolChain::addClangTargetOptions(const llvm::opt::ArgList &DriverArgs,
                                           llvm::opt::ArgStringList &CC1Args,
                                           Action::OffloadKind) const {
  CC1Args.push_back("-nostdsysteminc");
}

void fox32ToolChain::AddClangSystemIncludeArgs(const ArgList &DriverArgs,
                                               ArgStringList &CC1Args) const {
  if (DriverArgs.hasArg(options::OPT_nostdinc))
    return;
}

void fox32ToolChain::addLibStdCxxIncludePaths(
    const llvm::opt::ArgList &DriverArgs,
    llvm::opt::ArgStringList &CC1Args) const {}

void fox32::Linker::ConstructJob(Compilation &C, const JobAction &JA,
                                 const InputInfo &Output,
                                 const InputInfoList &Inputs,
                                 const ArgList &Args,
                                 const char *LinkingOutput) const {}
// fox32 tools end.
