<!-- This part is copied from Angular project -->

# Contributing to client-cpp

## Submission Guidelines

### Submitting a Pull Request (PR)

Before you submit your Pull Request (PR) consider the following guidelines:

1. Search GitHub for an open or closed PR that relates to your submission. You don't
want to duplicate existing efforts.
2. Be sure that an issue describes the problem you're fixing, or documents the design
for the feature you'd like to add. Discussing the design upfront helps to ensure that
we're ready to accept your work.
3. Fork the repository.
4. In your forked repository, make your changes in a new git branch:

   ```sh
   git checkout -b my-fix-branch master
   ```

5. Create your patch, **including appropriate test cases**.
6. Run the full test suite and ensure that all tests pass.

   ```sh
   mkdir build && cd build && cmake .. && cmake --build . && ctest
   ```

7. Commit your changes using a descriptive commit message that follows our commit
message conventions.
8. Push your branch to GitHub:

   ```sh
   git push origin my-fix-branch
   ```

9. In GitHub, send a pull request to `client-cpp:master`.

### Reviewing a Pull Request

#### Addressing review feedback

1. Make the required updates to the code.
2. Re-run the test suites to ensure tests are still passing.
3. Create a fixup commit and push to your GitHub repository (this will update your
Pull Request):

  ```sh
  git commit --all --fixup HEAD
  git push
  ```

That's it! Thank you for your contribution!

#### Updating the commit message

A reviewer might often suggest changes to a commit message. In order to update the
commit message of the last commit on your branch:

1. Check out your branch:

   ```sh
   git checkout my-fix-branch
   ```

2. Amend the last commit and modify the commit message:

   ```sh
   git commit --amend
   ```

3. Push to your GitHub repository:

   ```sh
   git push --force-with-lease
   ```

#### After your pull request is merged

After your pull request is merged, you can safely delete your branch and pull the
changes from the master (upstream) repository:

+ Delete the remote branch on GitHub either through the GitHub web UI or your local
shell as follows:

  ```sh
  git push origin --delete my-fix-branch
  ```

+ Check out the master branch:

  ```sh
  git checkout master -f
  ```

+ Delete the local branch:

  ```sh
  git branch -D my-fix-branch
  ```

+ Update your local `master` with the latest upstream version:

  ```sh
  git pull --ff upstream main
  ```

## Commit Message Format

We have very precise rules over how our Git commit messages must be formatted. This
format leads to easier to read commit history.

Each commit message consists of a *header*, a *body*, and a *footer*.

```
<header>
<BLANK LINE>
<body>
<BLANK LINE>
<footer>
```

The header is mandatory and must conform to the Commit Message Header format.

The body is mandatory for all commits. When the body is present it must be at least
20 characters long and must conform to the Commit Message Body format.

The footer is optional. The Commit Message Footer format describes what the footer is used for and the structure it must have.

### Commit Message Header

```
<type>(<scope>): <short summary>
  │       │             │
  │       │             └─⫸ Summary in present tense. Not capitalized. No period at the end.
  │       │
  │       └─⫸ Commit Scope: util (and some other scopes)
  │
  └─⫸ Commit Type: build|ci|docs|feature|fix|refactor|test|perf|
```

The `<type>` and `<summary>` fields are mandatory, the `(<scope>)` field is optional.

#### Type

Must be one of the following:

+ build: Changes that affect the build system or external dependencies
+ ci: Changes to our CI configuration files and scripts
+ docs: Documentation only changes
+ feature: A new feature
+ fix: A bug fix
+ perf: A code change that improves performance
+ refactor: A code change that neither fixes a bug nor adds a feature
+ test: Adding missing tests or correcting existing tests

#### Summary

Use the summary field to provide a succinct description of the change:

+ use the imperative, present tense: "change" not "changed" nor "changes"
+ don't capitalize the first letter
+ no dot (.) at the end

### Commit Message Body

Just as in the summary, use the imperative, present tense: "fix" not "fixed" nor "fixes".

Explain the motivation for the change in the commit message body. This commit message should explain
why you are making the change. You can include a comparison of the previous behavior with the new
behavior in order to illustrate the impact of the change.

### Commit Message Footer

The footer can contain information about breaking changes and deprecations and is also the place to
reference GitHub issues, Jira tickets, and other PRs that this commit closes or is related to. For
example:

```
BREAKING CHANGE: <breaking change summary>
<BLANK LINE>
<breaking change description + migration instructions>
<BLANK LINE>
<BLANK LINE>
Fixes #<issue number>
```

or

```
DEPRECATED: <what is deprecated>
<BLANK LINE>
<deprecation description + recommended update path>
<BLANK LINE>
<BLANK LINE>
Closes #<pr number>
```

Breaking Change section should start with the phrase "BREAKING CHANGE: " followed by a summary of the
breaking change, a blank line, and a detailed description of the breaking change that also includes
migration instructions.

Similarly, a Deprecation section should start with "DEPRECATED: " followed by a short description of
what is deprecated, a blank line, and a detailed description of the deprecation that also mentions the
recommended update path.

### Revert commits

If the commit reverts a previous commit, it should begin with `revert:` , followed by the header of the reverted commit.

The content of the commit message body should contain:

1. information about the SHA of the commit being reverted in the following format: This reverts commit `<SHA>`,
2. a clear description of the reason for reverting the commit message.
