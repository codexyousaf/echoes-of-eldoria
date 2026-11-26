# Contributing

Full rules are in the Echoes of Eldoria Complete Project Guide.

- Only the owner of a file edits it. Need a change in someone else's file? Open a GitHub Issue.
- A slice includes only shared/*.h and files from its own folder.
- Logic and structure headers never include raylib.h or raygui.h.
- Work on a branch feature/<slice>-<task> created from dev, then open a Pull Request into dev.
- Before a PR: compiles with -Wall -Wextra without warnings, your test or demo runs,
  every data structure operation has a complexity comment.
- Never commit build/, *.exe, *.o, *.d. Do commit .vscode/ and libs/.