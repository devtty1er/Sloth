#!/bin/bash -eu

WD_ERR_MSG="cd Sloth/ before running..."
git_root=$(git rev-parse --show-toplevel 2>/dev/null) || { echo "$WD_ERR_MSG" >&2; exit 1; }
if [[ "$PWD" != "$git_root" ]] || [[ "$(basename "$git_root")" != "Sloth" ]]; then
  echo "$WD_ERR_MSG" >&2
  exit 1
fi

GIT_REPO=./resources/qemu/
PATCH=$(realpath ./resources/patches/qemu.patch)
# subshell to guarantee return to working directory
(
  cd $GIT_REPO || { printf "Error: Failed to cd into $GIT_REPO\n" >&2; exit 1; }
  git status --porcelain | grep '.' && { printf 'Error: Untracked or modified files found, please commit or stash them.\n' >&2; exit 1; }
  git describe --tags --exact-match | grep -q "v5.1.0" || { printf "Error: Not on tag v5.1.0\n" >&2; exit 1; }
  git apply --stat $PATCH || { printf "Error: Failed to stat patch $PATCH\n" >&2; exit 1; }
  git apply --check $PATCH || { printf "Error: Patch $PATCH does not apply cleanly\n" >&2; exit 1; }
  git apply $PATCH || { printf "Error: Failed to apply patch $PATCH\n" >&2; exit 1; }
)
