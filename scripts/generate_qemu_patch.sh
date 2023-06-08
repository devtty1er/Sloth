#!/bin/bash -eu

WD_ERR_MSG="cd Sloth/ before running..."
git_root=$(git rev-parse --show-toplevel 2>/dev/null) || { echo "$WD_ERR_MSG" >&2; exit 1; }
if [[ "$PWD" != "$git_root" ]] || [[ "$(basename "$git_root")" != "Sloth" ]]; then
  echo "$WD_ERR_MSG" >&2
  exit 1
fi

GIT_REPO=./resources/qemu/
(
  cd $GIT_REPO || { printf "Error: Failed to cd into $GIT_REPO\n" >&2; exit 1; }
  git status --porcelain | grep '.' && { printf 'Error: Untracked or modified files found, please commit or stash them.\n' >&2; exit 1; }
  git diff v5.1.0 || { printf "Error: Failed to execute git diff v5.1.0\n" >&2; exit 1; }
)